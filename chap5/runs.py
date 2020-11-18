"""
This module will contain the different implementations that 
are related to chapter 5 of the Python Machine Learning. It
will also contain other implementations that are not part of 
the book but that is something that I decided to include for 
myself.

Chapter 5 discusses the topic of "Compressing Data via 
Dimensionality Reduction".  While chapter 4 was all about 
feature selection.  This chapter talks about "feature 
extraction".  The chapter will discuss three types of feature
extraction techniques:

  1 - "Principal component analysis" (PCA) for unsupervised     
      data compression

  2 - "Linear discriminant analysis" (LDA) as a supervised 
      dimensionality reduction technique for maximizing class 
      separability

  3 - Nonlinear dimensionality reduction via "kernel principal 
      component analysis" (KPCA)

The use feature extraction is to tranform or project the data 
onto a new feature space.  This is different than feature 
selection which keeps all of the features around.  Feature 
extraction is useful for reducing the size of the data set by
completely removing features from the data space.  This can 
then make the data more manageable.

Note that the use of feature selection and feature extraction 
is used against the issue of the curse of dimensionality that 
can plage a model that includes a large amount of features that
produce sparse data.

"""
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt 

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.decomposition import PCA

from utils.menu import create_menu, add_menu_item, add_menu_item_with_action
from utils.utils import get_data, plot_decision_regions

"""
The following example shows how we can use the 
Principal Component Analysis (PCA) selection extraction 
technique. Specifically, this is an unsupervised linear 
transformation technique.

PCA takes a d-feature input dataset and transforms it into a 
k-feature input dataset.  It does this by ordering each feature
by the variance of each feature.  It will then transform the
d-dimensional input dataset into a k-dimensional input dataset.
Note that k < d and that we are only looking at the 
unsupervised dataset.  This technique does not require the 
labels to be able to perform the feature extraction of the 
dataset.

Assuming that:

  - W is an d x k-dimensional matrix
  - x is an d-dimensional vector, [x_1,x_2,...,x_d]
  - z is an k-dimensional vector, [z_1,z_2,...,z_k]

where W is the transformation matrix that produces the 
feature extraction from d features to k features of the
input dataset where k < d.  The z vector is ordered 
such that the first entry contains more variance than the
subsequent feature.  Where  z = xW, W transforms x into z
where z contains the k largest covariance for the d feature 
set.

Before we can perform PCA we need to standardize the 
dataset since this process is sensitive to data scaling. 
Standardizing the dataset will allow PCA to properly 
determine the variance of each feature in the feature set.

Here are the steps required to properly implement PCA:

  1 - Standardize the d-dimensional dataset
  2 - Construct the covariance matrix
  3 - Decompose the covariance matrix into its eigenvectors
      and eigenvalues
  4 - Sort the eigenvalues by descending order to rank the
      corresponding eigenvectors
  5 - Select k eigenvectors, which correspond to the k 
      largest eigenvalues, where k is the dimensionality of
      the new feature supspace (k <= d)
  6 - Construct a projection matrix, W, from the top "k"
      eigenvectors
  7 - Transform the d-dimensional input dataset, X, using 
      the projection matrix, W, to optain the new k-dimensional
      feature subspace

1 - Standardize the d-dimensional dataset.

  - This is done to be able to remove any data scaling issues
    that can be caused by varying dataset values for different
    features.  This is avoiding having feature i which contains
    large dataset values to override feature j which contains 
    small dataset values.  

2 - Construct the covariance matrix

  - This matrix will be used to determine which features have 
    the greatest variance of the given d feature sets.  It does 
    this by creating a square matrix of dimension d x d.  Each 
    entry is determing the covariance between feature i and j.
    The formula is:

      SIGMA(j,k) 
        = (1/(n - 1)) * SUM[i]((x_j_i - u_j) * (x_k_i - u_k))

    where n is the size of the dataset.  j and k are the jth 
    and kth feature of the dataset.  While i is the ith entry 
    in the dataset.

3 - Decompose the covariance matrix into its eigenvectors
    and eigenvalues

  - Using the generated covariance matrix we use the  
    eigendecomposition technique to generate the eigenvalues 
    and eigenvectors associated with the covariance matrix

4 - Sort the eigenvalues by descending order to rank the
    corresponding eigenvectors

  - We then sort the eigenvalues into a descending order to 
    determine the ranking of their associated eigenvectors

5 - Select k eigenvectors, which correspond to the k 
    largest eigenvalues, where k is the dimensionality of
    the new feature supspace (k <= d)

  - we select the first k eigenvectors from the sorted 
    eigenvalues.  In the following example we only use 
    the top two features from the generated eigenpair which
    accounts for around 60% of the total variance.
    In practice, this is something that needs to be decided
    on the computational efficiency and the performance of
    the classifier that is being used.

6 - Construct a projection matrix, W, from the top "k"
    eigenvectors

  - taking the k top eigenvectors, we then create a projection
    matrix.  As mentioned above the determination of the k top 
    features depend on different requirements that one needs to
    determine given the current environment requirements.

7 - Transform the d-dimensional input dataset, X, using 
    the projection matrix, W, to optain the new k-dimensional
    feature subspace

  - Taking the projection matrix, we multiple the dataset 
    entries with them to extract the k top features of the 
    dataset.  The resulting subspace dataset can then be 
    used to create the subsequent model for a given classifier.

"""
def run_principal_component_analysis_example():
  url = 'https://archive.ics.uci.edu/ml/machine-learning-databases/wine/wine.data'
  fname = 'data/wine/wine.data'
  data = get_data(url,fname)
  df = pd.read_csv(data,header=None)
  df.columns = ['Class label',
    'Alcohol', 'Malic Acid', 'Ash', 'Alcalinity of ash', 
    'Magnesium', 'Total phenols', 'Flavanoids',
    'Nonflavanoid phenols', 'Proanthocyanins',
    'Color intensity', 'Hue', 'OD280/OD315 of diluted wines',
    'Proline'
  ]
  print('Describe:')
  print(df.describe())
  print('Info:')
  print(df.info())
  print('Head:')
  print(df.head())
  input('Press enter to continue:')

  # We are going to split the loaded data into input and 
  # output data.  
  X, y = df.iloc[:, 1:].values, df.iloc[:, 0].values
  # Note that setting the stratify to 'y' means that 
  # we want to insure that the training and test sets 
  # have the same proportions of data to allow for
  # more coverage.  This just means that we want to
  # insure that we have a evenly distributed data of
  # similar data.  This will allow our model to better
  # predict the resulting values using the test data.
  # Which in turn should allow us to better predict 
  # new data.
  X_train, X_test, y_train, y_test = \
    train_test_split(X, y, test_size=0.3, random_state=0,
    stratify=y)

  # We need to standardize the dataset to remove the 
  # issue with data sensitivity
  sc = StandardScaler()
  X_train_std = sc.fit_transform(X_train)
  # X_test_std = sc.transform(X_test)

  print('X_train_std shape:', X_train_std.shape)
  print('X_train_std.T shape:', X_train_std.T.shape)
  input('Press enter to continue:')

  # We now need to create the covariance matrix to 
  # determine which of the features have the greatest
  # variance impact of the dataset.
  cov_mat = np.cov(X_train_std.T) # T is the transpose?
  print('Covariance matrix:')
  print(cov_mat)
  print('covariance matrix shape:', cov_mat.shape)
  input('Press enter to continue:')
  # We create the eigenvalues and eigenvectors from 
  # the covariance matrix. 
  eigen_vals, eigen_vecs = np.linalg.eig(cov_mat)
  # Note that the eig method works with symmetric and 
  # non-symmetric square matrices.  This can produce 
  # a matrix that can contain complex values.  Using 
  # the np.linalg.eigh method will insure that the 
  # resulting set of eigenvalues and eigenvectors 
  # will only contain real eigenvalues.

  # Recall that the above is called the process of 
  # eigendecomposition.
  print('')
  print('Eigenvalues:')
  print('%s' % eigen_vals)
  input('Press enter to continue:')

  # Sum the totals of the eigenvalues vector
  tot = sum(eigen_vals)
  # Create an of the percentage of the eigenvalues 
  # compared to each other in decending order
  var_exp = [(i / tot) for i in sorted(eigen_vals,
                                       reverse=True)]
  # Create a vector that produces the accumulation 
  # of the prior n entries of the passed vector
  cum_var_exp = np.cumsum(var_exp)
  plt.title('Variance Explained Ratios')
  plt.bar(range(1, 14), var_exp, alpha=0.5, align='center',
          label='Individual explained variance')
  plt.step(range(1, 14), cum_var_exp, where='mid',
           label='Cumulative explained variance')
  plt.xlabel('Principal component index')
  plt.ylabel('Explained variance ratio')
  plt.legend(loc='best')
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Press enter to continue:')
  plt.close()
  
  # Note that the above graph shows that the top feature 
  # accounts for around 40% of the total variance.  
  # While adding the second feature will then account for
  # around 60% of the total variance.

  # We are creating a eigen pair tuple of 
  # (eigen value, eigen vector) entries
  eigen_pairs = [(np.abs(eigen_vals[i]), eigen_vecs[:, i])
                  for i in range(len(eigen_vals))]
  # Sort the (eigenvalue, eigenvector) tuple in descending 
  # order
  eigen_pairs.sort(key=lambda k: k[0], reverse=True)

  # Create the projection matrix using the top 2 features 
  # from the sorted eigenpairs.  
  w = np.hstack((eigen_pairs[0][1][:, np.newaxis], 
                 # extract eigenvalue 
                 eigen_pairs[1][1][:, np.newaxis])) 
                 # extract eigenvector
  
  # We've produced a 13x2 matrix from the top 2 features
  # that will be applied to the dataset
  print('Projection Matrix:')
  print(w)
  input('Press enter to continue:')

  x_pca = X_train_std[0].dot(w)
  print('Result of applying the projection matrix to x[0]')
  print(x_pca)
  input('Press enter to continue:')

  # Apply the projection matrix to the training dataset
  X_train_pca = X_train_std.dot(w)

  print('Produced a matrix of shape:', X_train_pca.shape,
  'from a training set of shape:', X_train_std.shape)
  # plot the generated projected dataset
  colors = ['r', 'b', 'g']
  markers = ['s', 'x', 'o']
  for l, c, m in zip(np.unique(y_train), colors, markers):
    plt.scatter(X_train_pca[y_train==l, 0],
                X_train_pca[y_train==l, 1],
                c=c, label=l, marker=m)
  plt.xlabel('Principal Component 1')
  plt.ylabel('Principal Component 2')
  plt.title('Graph of Top 2 Principal Components for the Wine DataSet')
  plt.legend(loc='lower left')
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Press enter to continue:')
  plt.close()
  # The generated graph plot shows that the x-axis will 
  # have data that is more spread out compared to the 
  # data for the y-axis.

def run_scikit_principal_component_analysis_example():
  # The following will now perform the same task using the
  # scikit library as has been generated by using the numpy 
  # library.
  url = 'https://archive.ics.uci.edu/ml/machine-learning-databases/wine/wine.data'
  fname = 'data/wine/wine.data'
  data = get_data(url,fname)
  df = pd.read_csv(data,header=None)
  df.columns = ['Class label',
    'Alcohol', 'Malic Acid', 'Ash', 'Alcalinity of ash', 
    'Magnesium', 'Total phenols', 'Flavanoids',
    'Nonflavanoid phenols', 'Proanthocyanins',
    'Color intensity', 'Hue', 'OD280/OD315 of diluted wines',
    'Proline'
  ]
  # print('Describe:')
  # print(df.describe())
  # print('Info:')
  # print(df.info())
  # print('Head:')
  # print(df.head())
  # input('Press enter to continue:')

  # We are going to split the loaded data into input and 
  # output data.  
  X, y = df.iloc[:, 1:].values, df.iloc[:, 0].values
  # Note that setting the stratify to 'y' means that 
  # we want to insure that the training and test sets 
  # have the same proportions of data to allow for
  # more coverage.  This just means that we want to
  # insure that we have a evenly distributed data of
  # similar data.  This will allow our model to better
  # predict the resulting values using the test data.
  # Which in turn should allow us to better predict 
  # new data.
  X_train, X_test, y_train, y_test = \
    train_test_split(X, y, test_size=0.3, random_state=0,
    stratify=y)

  # We need to standardize the dataset to remove the 
  # issue with data sensitivity
  sc = StandardScaler()
  X_train_std = sc.fit_transform(X_train)
  X_test_std = sc.transform(X_test)

  print('X_train_std shape:', X_train_std.shape)
  print('X_train_std.T shape:', X_train_std.T.shape)
  
  # Initialize the PCA and LogisticRegression estimator
  pca = PCA(n_components=2)
  lr = LogisticRegression(multi_class='ovr',
                          random_state=1,
                          solver='lbfgs')
  
  # perform dimensionality reduction (selection extraction)
  X_train_pca = pca.fit_transform(X_train_std)
  # We only transform the test dataset and not fit it since
  # we don't want to effect the test results by also fitting
  # the test dataset
  X_test_pca = pca.transform(X_test_std)

  # we now fit the reduced dataset with the logistic
  # regression classifier
  lr.fit(X_train_pca, y_train)
  plot_decision_regions(X_train_pca, y_train, classifier=lr)
  plt.title('Training - Principal Component Analysis for top 2 features')
  plt.xlabel('Principal Component 1')
  plt.ylabel('Principal Component 2')
  plt.legend(loc='lower left')
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Press enter to continue:')
  plt.close()

  # plot the resulting outcome of using the reduced feature
  # selection on the test dataset
  plot_decision_regions(X_test_pca, y_test, classifier=lr)
  plt.title('Test - Principal Component Analysis for top 2 features')
  plt.xlabel('Principal Component 1')
  plt.ylabel('Principal Component 2')
  plt.legend(loc='lower left')
  plt.tight_layout()
  plt.ion()
  plt.show()
  print('Explained variance ratio for the top 2 components')
  print(pca.explained_variance_ratio_)
  print('sum(explained_variance_ratio_):',
        sum(pca.explained_variance_ratio_))
  print('Accumulated pre-entries:',
        np.cumsum(pca.explained_variance_ratio_))
  input('Press enter to continue:')
  plt.close()

  # The following is an example of how to get the different 
  # distribution of the features principal components for a 
  # given training data set that has also been standardized.
  # This is done by setting the n_components parameter to 
  # None.  This will make the PCA instance use all of the 
  # features of the dataset.
  pca = PCA(n_components=None)
  X_train_pca = pca.fit_transform(X_train_std)
  print('Explained variance ratio for all components')
  print(pca.explained_variance_ratio_)
  print('sum(explained_variance_ratio_):',
        sum(pca.explained_variance_ratio_))
  print('Accumulated pre-entries:',
        np.cumsum(pca.explained_variance_ratio_))
  input('Press enter to continue:')


def add_chapter_five_menu_items(menu,mainMenu):
  chap5 = create_menu('Chapter 5 Examples', mainMenu)
  add_menu_item('Chapter 5 Examples', chap5, menu)
  add_menu_item_with_action(chap5,
    'Principal Component Analysis Example',
    run_principal_component_analysis_example, menu)
  add_menu_item_with_action(chap5,
    'Scikit Principal Component Analysis Example',
    run_scikit_principal_component_analysis_example, menu)
