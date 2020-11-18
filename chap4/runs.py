"""
This file will contain the required code that will be used
to update the current menu selection for Chapter 4 of the
book Python Machine Learning.
"""

from io import StringIO

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.compose import ColumnTransformer
from sklearn.ensemble import RandomForestClassifier
from sklearn.feature_selection import SelectFromModel
from sklearn.impute import SimpleImputer
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import LabelEncoder, OneHotEncoder, FunctionTransformer, StandardScaler, RobustScaler, MinMaxScaler

from utils.menu import create_menu, add_menu_item, add_menu_item_with_action
from utils.utils import get_data

from chap4.sbs import SBS

"""
This method shows how we can use pandas DataFrame 
instance to load and determine which row/column 
contains null values.

It also shows the different options that can be 
used to remove rows and/or columns that contain
missing data from the instansiated DataFrame 
instance.

The option of removing samples that have missing 
data can be useful but it is not always a good idea.
Too much data that is removed can leave you with not
enough data to create a meaningful model.  This can 
be affected by the removal of samples and/or features.
Removal of rows are explained above but removal of 
features can cause the model to be lacking in data 
that can have a large effect on the ability for the
model to correctly classify new samples.

The DataFrame class is very useful to help determine
how the loaded data is organized.  It provides many 
more methods than what is shown in this method.
"""
def run_missing_data_example():
  csv_data = \
  '''A,B,C,D
  1.0,2.0,3.0,4.0
  5.0,6.0,,8.0
  10.0,11.0,12.0,
  '''
  df = pd.read_csv(StringIO(csv_data))
  print('Loaded csv data into pandas DataFrame object')
  print(df)
  input('Press enter to continue:')

  print('Display the number of entries that are null')
  print(df.isnull().sum())
  input('Press enter to continue:')

  print('Underlining numpy array values')
  print(df.values)
  input('Press entry to continue:')

  print('Dropping rows with missing data')
  print(df.dropna(axis=0))
  input('Press Enter to continue:')

  print('Dropping columns with missing data')
  print(df.dropna(axis=1))
  input('Press enter to continue:')

  print('Dropping rows where all columns have missing data')
  print(df.dropna(how='all'))
  input('Press enter to continue:')

  print('Dropping rows that have less than 4 real values')
  print(df.dropna(thresh=4))
  input('Press enter to continue:')

  print('Only drop rows that contain missing data for a specifc column')
  print(df.dropna(subset=['C']))
  input('Press enter to continue:')

"""
This method shows how we can impute missing data using 
the columns mean values as replacements.   We also shows
what happens if we use the median and most frequent 
strategies.

This set of actions using the SimpleImputer class belong
to the classes of "transformers" within the scikit library.
This mainly uses the "fit" and "transform" methods.  Where
the "fit" method is used to "train" the imputer and the
"transform" method is used to impute the passed data. 
Note this requires that the transforming data set is
consistent with the trained data set.

This is different than classifiers, "estimators" that contain 
the "fit" and "predict" methods to initially generate the 
model given a training set using the "fit" method.  We
then use the "predict" method to predict the expected
values using a training set. Note that "estimators" can 
also have a "tranformer" method and this will be shown 
how it is used in another example.

If we are then going to impute the training data set 
then we should also perform the same task on the test
data sets to be able to provide consistency.

"""
def run_impute_real_data_example():
  csv_data = \
  '''A,B,C,D
  1.0,2.0,3.0,4.0
  5.0,6.0,,8.0
  10.0,11.0,12.0,
  '''
  df = pd.read_csv(StringIO(csv_data))
  print('Originally loaded data')
  print(df)
  input('Press enter to continue:')

  imr = SimpleImputer(missing_values=np.nan, strategy='mean')
  imr = imr.fit(df.values)
  imputed_data = imr.transform(df.values)
  print('Loaded data after it has been imputed using the mean')
  print(imputed_data)  
  input('Press enter to continue:')

  print('Imputing the loaded data using DataFrame fillna feature using the mean')
  print(df.fillna(df.mean()))
  input('Press enter to continue:')

  imr = SimpleImputer(missing_values=np.nan, strategy='median')
  imr = imr.fit(df.values)
  imputed_data = imr.transform(df.values)
  print('Loaded data after is has been imputed using the median')
  print(imputed_data)  
  input('Press enter to continue:')

  imr = SimpleImputer(missing_values=np.nan, strategy='most_frequent')
  imr = imr.fit(df.values)
  imputed_data = imr.transform(df.values)
  print('Loaded data after is has been imputed using the most frequent')
  print(imputed_data)  
  input('Press enter to continue:')

"""
This method will show how we can impute classified 
training data set to prepare for processing by some
classifier.

There are two types of categories of classification
type data.  They are "ordinal" and "nominal" features. 
Types of "ordinal" features are classification data that 
can be order.  While "nominal" cannot be ordered.  
For example, shirts sizes can be ordered by shirt colors 
cannot be ordered.

The method is going to show how we can quantify these
different categorical features using pandas DataFrame
class.

"""
def run_impute_categorical_data_example():
  df =  pd.DataFrame([
    ['green', 'M', 10.1, 'class2'],
    ['red', 'L', 13.5, 'class1'],
    ['blue', 'XL', 15.3, 'class2'],
  ])
  df.columns = ['color', 'size', 'price', 'classlabel']
  print('Training set containing ordinal and nominal data')
  print(df)
  input('Press enter to continue:')

  # The following shows how to replace categorical data 
  # with numeric data
  size_mapping = { 'XL' : 3, 'L' : 2, 'M' : 1}
  df['size'] = df['size'].map(size_mapping)

  print('Result of converting to size into values')
  print(df)

  # The following shows how we can revert the size 
  # column into its original categorical data.
  inv_size_mapping = {v:k for k,v in size_mapping.items()}
  print('Example of reverting size categorical data')
  print(df['size'].map(inv_size_mapping))
  input('Press enter to continue:')

  class_mapping = {label: idx for idx, label in enumerate(np.unique(df['classlabel']))}
  print('Conversion of classlabel to numerial values')
  print(class_mapping)
  df['classlabel'] = df['classlabel'].map(class_mapping)
  print(df)
  input('Press enter to continue:')

  inv_class_mapping = {v:k for k,v in class_mapping.items()}
  print('Reverting classlabel to original nominal values')
  print(df['classlabel'].map(inv_class_mapping))
  input('Press enter to continue:')

  class_le = LabelEncoder()
  # NOTE that you are passing the equivalent numpy array to the
  #      fit_transform method
  y = class_le.fit_transform(df['classlabel'].values)
  print('Using the LabelEncoder class to convert the classlabel to numerical and label values')
  print('Converted to numerical values using the fit_transform method')
  print(y)
  print('Converted to label values using the inverse_transform method')
  print(class_le.inverse_transform(y))
  input('Press enter to continue:')

"""
The following method will show how we can use one-hot
encoding to deal with one of the most common mistakes 
in dealing with categorial data, specifically nominal 
data.  The main issue is that converting categorical
input data into numerical values can cause the model
to produce nonoptimal results.  The use of one-hot 
encoding is going to be shown that is part of the 
scikit package.  As part of that, it will show different
ways of performing one-hot encoding of the data.
"""
def run_one_hot_encoding_on_nominal_data_example():
  df =  pd.DataFrame([
    ['green', 'M', 10.1, 'class2'],
    ['red', 'L', 13.5, 'class1'],
    ['blue', 'XL', 15.3, 'class2'],
  ])
  df.columns = ['color', 'size', 'price', 'classlabel']

  print('Training set containing ordinal and nominal data')
  print(df)
  input('Press enter to continue:')
  
  X = df[['color','size','price']].values
  color_le = LabelEncoder()
  # We are only going to label encode the color column
  X[:, 0] = color_le.fit_transform(X[:, 0])
  print('Transformed color column')
  print(X)
  input('Press enter to continue:')

  X = df[['color','size','price']].values
  color_one = OneHotEncoder()
  # We are only applying the one-hot encoding to the 
  # size column only.
  r = color_one.fit_transform(X[:, 0].reshape(-1,1)).toarray()
  print('Applied one-hot encoding to the size column')
  print(r)
  input('Press enter to continue:')

  # We are explicitly converting the size into a range
  # df['size'] = df['size'].map({'M':1,'L':2,'XL':3}) 
  def csize(s,**fromTo):
    for i in range(len(s)):
      # This will only work if the inner array is size 1.
      # I personally do not like this technique and 
      # prefer the DataFrame map method above.  I wonder
      # if there is a map method that can be used instead.
      s[i] = fromTo[s[i][0]]
    return s

  # The following transformation method is a general 
  # implementation  that can be used with any dictionary.
  def general_replace(s,**mapping):
    mappings = mapping['mapping']
    etype = mapping['type']
    if hasattr(s,'__iter__') and not isinstance(s,etype):
      for i in range(len(s)):
        # print('Processing array:',s[i])
        s[i] = general_replace(s[i],**mapping)
      # print('Returning s',s)
      return s
    else:
      # print('Converting value:', s)
      return mappings[s]
  
  # we are now going to apply the one-hot encoding to one or
  # more columns using the ColumnTransformer class
  X = df[['color','size','price']].values
  c_transf = ColumnTransformer([
    ('onehot', OneHotEncoder(), [0]),
    ('sizetransformer', FunctionTransformer(general_replace, kw_args= {'mapping':{'M':1,'L':2,'XL':3}, 'type':str}), [1]),
    ('nothing', 'passthrough', [2])
  ],verbose=False)

  print('One-hot and Function transformations of training data')
  print(X)
  input('Press enter to continue:')

  r = c_transf.fit_transform(X).astype(float)
  print('After using ColumnTransformer to one-hot size column')
  print(r)
  input('Press enter to continue:')

  print('The following will show how to use the get_dummies DataFrame method')
  X = pd.get_dummies(df[['color','size','price']])
  print('X',X)
  input('Press enter to continue:')

  print('The following will show how to use the get_dummies DataFrame method and drop one of the generated columns')
  X = pd.get_dummies(df[['color','size','price']],drop_first=True)
  print('X',X)
  input('Press enter to continue:')

  X = df[['color','size','price']].values
  color_ohe = OneHotEncoder(categories='auto',drop='first')
  func_tranf = FunctionTransformer(general_replace, kw_args= {'mapping':{'M':1,'L':2,'XL':3}, 'type':str})
  c_transf = ColumnTransformer([
    ('onehot', color_ohe, [0]),
    ('sizetransformer', func_tranf, [1]),
    ('nothing', 'passthrough', [2])
  ],verbose=False)
  r = c_transf.fit_transform(X).astype(float)
  print('Transformation of data using drop feature of the one-hot feature')
  print(r)
  input('Press enter to continue:')
  
def run_ordinal_encoding_of_data_example():
  df =  pd.DataFrame([
    ['green', 'M', 10.1, 'class2'],
    ['red', 'L', 13.5, 'class1'],
    ['blue', 'XL', 15.3, 'class2'],
  ])
  df.columns = ['color', 'size', 'price', 'classlabel']

  print('Training set containing ordinal and nominal data')
  print(df)
  input('Press enter to continue:')

  df['x > M'] = df['size'].apply(lambda x : 1 if x in { 'L', 'XL'} else 0)
  df['x > L'] = df['size'].apply(lambda x : 1 if x == 'XL' else 0)
  del df['size']
  print(df)
  input('Press enter to continue:')

def run_split_dataset_into_training_and_test_datasets():
  """
  This method shows how we can split the dataset into 
  training and test datasets.  It uses the uci wine 
  dataset as an example.
  """
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
  # print(df)
  print('Describe:')
  print(df.describe())
  print('Info:')
  df.info()
  print('Class labels', np.unique(df['Class label']))
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

  """
  
  The above split is one of the recommended way of taking
  a datasets and distributing it between training and test
  datasets.  There is also the split of 60/40, 80/20 and 90/10
  as well as the above 70/30.  The decision of how to split
  the data depends on the size of the dataset itself.  We 
  would want to use more training data but we also want to
  leave enough test data to provide for a better test. 

  More information can be found in the following paper:

    https://arxiv.org/pdf/1811.12808.pdf

  This paper talks about the different strategies of 
  dividing the dataset.

  """

  print('X_train', X_train)
  input('Press enter to continue:')
  
"""
The following method will show how we can feature scale 
the dataset such that one feature will not have as much
impact on the loss function compared to another feature
for a given model.

There are two types of "feature scaling" techniques, 
"normalization" and "standardization".  These two 
techniques provide us with a mechanism to reduce the 
impact of one feature as compared to another on the 
loss function.  

The "normalization" technique will map the current set of data 
to values within [0,1] using the following formula:

  x_i_norm = (x_i - x_i_min) / (x_i_max - x_i_min)

where:
  - x_i is the value for a specific feature 
  - x_i_min is the minimum sample value of that feature
  - x_i_max is the maximum sample value of that feature

Note that the "normalization" technique is a special case
of the "min-max scaling" technique.

The "standardization" technique uses the sample mean and 
standard deviation to standardize the sample as a normal 
distribution of mean 0 and standard deviation of 1, N(0,1),
using the following formula:

  x_i_std = (x_i - mu_x) / sigma_x

where:

  - x_i is the value for a specific feature
  - mu_x is the sample mean for the given feature
  - sigma_x is the sample standard deviation for the given feature

While the "normalization" technique is commonly used in the
case of bounded interval values, "standardization" can be 
more practical in machine learning algorithms especially 
optimization algorithms such as the gradient descent.  The
reason is that most learning algorithms initially set the 
wieghts to 0 and since standardizations sets the mean to 
0 then this makes it easier to calculate the weighted values.
The other advantage is that it keeps information about the
outliners and is less sensitive to them compared to the 
normalization technique.breakpoint

The above techniques are not necessary for all types 
of machine learning algorithms.  For instance the 
Decision Tree and Forest Tree implementations don't 
require any feature scaling sine these are 
"scalar invariant".

The scikit package contains classes that can be used to
perform the above techniques on a given dataset.  They 
are the MinMaxScaler, StandardScaler and the RobustScaler 
classes.  The StandardScalar performs the "standardization"
technique. While the MinMaxScaler class can be used to 
perform the "normalization" technique.  The RobustScaler
class can also be used and it is recommended in cases that
the dataset is very small that contain many outliners and in 
the case of a model is overfitting.

"""
def run_bridge_features_onto_same_scale_example():
  data = np.array([0, 1, 2, 3, 4, 5])
  print('standardization:', (data - data.mean()) / (data.std()))
  print('normalization:', (data - data.min()) / (data.max() - data.min()))
  input('Press enter to continue:')

  norm = MinMaxScaler()
  data_norm = norm.fit_transform(data.reshape(-1,1))
  print('data_norm',data_norm)
  stdsc = StandardScaler()
  data_stdsc = stdsc.fit_transform(data.reshape(-1,1))
  print('data_stdsc',data_stdsc)
  robustsc = RobustScaler()
  data_robust = robustsc.fit_transform(data.reshape(-1,1))
  print('data_robust',data_robust)
  input('Press enter to continue:')

"""
The next set of examples will show how we should consider
looking for when we come upon the case that our model 
fits really well with the training data but is not as good
when we are using the testing data.  This is a sympton of
overfitting.  This type of condition means that the model
has a "high variance".  There are different types of cases
that can be causing this issue.  There are some common 
solutions that can help with this issue like:

  - Collect more training data
  - Introduce a penalty for complexity via regularization
  - Choose a simplier model with fewer parameters
  - Reduce the dimensionality of the data

These solutions will be shown with how they can alleviate
overfitting of an initial model.

Introducing a penalty for complexity via regularization.
This is the process of using L1 and L2 regularization 
approaches.

The use of the L2 regularization was used to reduce the
complexity of a model by penalizing the large weight 
values.  This was calculated using the following formula:

  L2: NORM(w:2,2) = SUM(SQUARE(w_j))

for m features.  The application of the L2 regularization 
adds a penalty to the loss function compared to not using
regularization which results in less extreme weight values.

The other procedure to reduce model complexity is the use 
of the L1 regularization technique.  This is useful in the 
case of sparsity.  Where there are a lot of features that 
have zero weights associated with them.  This is the case
when we are looking at training data that is associated
with a large number of feaures where the data is sparsed 
throughout the domain.  This feature provide us with the
ability to reduce the number of features that should be 
considered by our model.  This will leads to simiplier 
models that can then perform better.  The formule for the
L1 regularization is the following:

  L1: NORM(w:1) = SUM(ABS(w_j))

for m features.

The addition of the L2 regularization that penalizes the 
cost to the loss function.  We are effectively minimizing the 
unpenalized cost plus the penalized cost such that the
variance has been reduced compared to a model that does not 
include this regularization. This in turn basically means that 
we are including a bias to a simpler model to provide a 
reduction in variance as compared to not using a bias for the 
simple model. 

This concept is similar for the L1 regularization feature.  The
main use of the L1 regularization technique is when we are 
presented with training data that contains a large number of 
features that generates sparse data.  

"""

def run_l1_regularization_example():
  """
  This method will show how an L1 regularization impacts a
  LogisticRegression classifier using the wine dataset.
  """
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

  # We are going to split the loaded data into input and 
  # output data.  
  X, y = df.iloc[:, 1:].values, df.iloc[:, 0].values

  X_train, X_test, y_train, y_test = \
    train_test_split(X, y, test_size=0.3, random_state=0,
    stratify=y)

  sc = StandardScaler()
  # We need to reshape the training and test dataset such
  # that it contains 13 features per row.  This is why we
  # are reshaping this as -1, 13.
  X_train_std = sc.fit_transform(X_train.reshape(-1,13))
  X_test_std = sc.transform(X_test.reshape(-1,13))
  print('len(X_train): {}, len(X_train_std: {}, len(y_train): {}'.format(len(X_train),len(X_train_std),len(y_train)))
  input('Press enter to continue:')

  """
  Note that the using the penalty parameter set to l1 
  will enalbe to use of the L1 regularization technique.
  Since, the 'lbfgs' solver doesn't implement the L1
  regularization then we have to use the liblinear solver
  that implements the L1 regularization.

  Note that the lambda, C, value is set to the default value 
  of 1.0.  This value can be increased or descreased to 
  create a stronger or weaker impact of the regularization 
  effect on the model.
  """
  lr = LogisticRegression(penalty='l1',
            C=1.0,
            solver='liblinear',
            multi_class='ovr')

  lr.fit(X_train_std, y_train)
  # The following produces values of 1 for both our training 
  # and testing data set are being predicted with a 100% 
  # accuracy. 
  print('Training accuracy:', lr.score(X_train_std, y_train))
  print('Test accuracy:', lr.score(X_test_std, y_test))
  # The following values are related to the w_0, weight 
  # associated with the bias...
  print('Intercepts:',lr.intercept_)
  # The above intercepts are related to in the following 
  # matter:
  #  - how class 1 fits with class 2 and 3
  #  - how class 2 fits with class 1 and 3
  #  - how class 3 fits with class 1 and 2
  # This is the case since this model is using the 
  # one-vs.-rest (OvR) approach.  
  # This information is really the bias of the model.
  input('Press enter to continue:')
  # ...while the coef_ values are related to the remaining 
  # weight.
  print('coefficients:',lr.coef_)
  # while the above coefficients display three rows containing
  # the weight coefficients for each of the different classes.
  # In the wine dataset there are 3 unique classes of wines 
  # that is being predicted.
  input('Press enter to continue:')

"""
The following example will show how the varying of the 
penalty value can affect the weights of the generated 
model.
"""
def run_vary_l1_regularization_example():
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

  # We are going to split the loaded data into input and 
  # output data.  
  X, y = df.iloc[:, 1:].values, df.iloc[:, 0].values

  X_train, X_test, y_train, y_test = \
    train_test_split(X, y, test_size=0.3, random_state=0,
    stratify=y)

  sc = StandardScaler()
  # We need to reshape the training and test dataset such
  # that it contains 13 features per row.  This is why we
  # are reshaping this as -1, 13.
  X_train_std = sc.fit_transform(X_train.reshape(-1,13))
  # X_test_std = sc.transform(X_test.reshape(-1,13))

   # why do we need to do this when we don't use fig!!!!
  fig = plt.figure()
  ax = plt.subplot(111)
  colors = [
    'blue', 'green', 'red', 'cyan', 'magenta',
   'yellow', 'black', 'pink', 'lightgreen', 'lightblue',
   'gray', 'indigo', 'orange'
  ]

  weights, params = [], []
  w = {}
  
  for c in np.arange(-4.0, 6.0):
    lr = LogisticRegression(penalty='l1', C=10.**c,
      solver='liblinear', multi_class='ovr', random_state=0)
    lr.fit(X_train_std, y_train)
    # Note we are storing only class 1 coefficients and will
    # not include class 2 and class 3 to our plot.
    weights.append(lr.coef_[1])
    params.append(10.**c)
    key = 10.**c
    w[key] = lr.coef_
  
  weights = np.array(weights)

  print('w',w)
  input('Press enter to continue:')
  print('weights',weights)
  input('Press enter to continue:')
  for column, color in zip(range(weights.shape[1]), colors):
    plt.plot(params, weights[:, column],
      label=df.columns[column + 1], color=color)

  plt.title('Different values of L1 regularization for class 1')
  plt.axhline(0, color='black', linestyle='--', linewidth=3)
  plt.xlim([10**-5, 10**5])
  plt.ylabel('weight coefficient')
  plt.xlabel('C')
  plt.xscale('log')
  plt.legend(loc='upper left')
  ax.legend(loc='upper center', bbox_to_anchor=(1.38, 1.03),
    ncol=1, fancybox=True)
  plt.ion()
  plt.show()
  input('Press enter to continue:')
  plt.close()

"""
The following set of examples will describe the concept of 
"sequential feature selection algorithms".  Specifically,
we use the concept of feature selection, which is part of
the concept of "dimensionality reduction", to reduce a 
model complexity and avoid overfitting.  There are two 
techniques that will be discussed, "feature selection"
and "feature extraction".  These are implemented using 
"greedy search algorithms".  Even though this technique 
doesn't result in the optimal solution compared to an 
exhaustive search.  It does provide a suboptimal solution 
which are computationally more efficient than an exhaustive 
search.  It also allows us to find a solution within a
reasonable time compared to using an exhaustive search 
that will not complete within a reasonable time.  

The algorithims start with an initial d-dimensional feature
space and then reduce this feature space to a k-dimensional 
feature space where k<d. 

One such feature algorithm is the "sequential backward 
selection", (SBS), which tries to reduce the dimensionality 
of the model with minimal performance impact on the classifier 
while improving the computational efficient of the model.


There is more on this subject at the following link:

 https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.24.4369&rep=rep1&type=pdf

This is the paper, "Comparative Study of Techniques for 
Large-Scale Feature Selection".

"""

def run_sequential_backward_selection_example():
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

  # We are going to split the loaded data into input and 
  # output data.  
  X, y = df.iloc[:, 1:].values, df.iloc[:, 0].values

  X_train, X_test, y_train, y_test = \
    train_test_split(X, y, test_size=0.3, random_state=0,
    stratify=y)

  sc = StandardScaler()
  # We need to reshape the training and test dataset such
  # that it contains 13 features per row.  This is why we
  # are reshaping this as -1, 13.
  X_train_std = sc.fit_transform(X_train.reshape(-1,13))
  X_test_std = sc.fit_transform(X_test.reshape(-1,13))

  knn = KNeighborsClassifier(n_neighbors=5)
  # Find the 1 feature in the sample that best model the 
  # data using the KNN classifier
  sbs = SBS(knn, k_features=1)
  sbs.fit(X_train_std, y_train)

  # The following plot will show that the KNN classifier 
  # was able to perform 100% accuracy for k=[3,7,8,9,10,11,12]
  k_feat = [len(k) for k in sbs.subsets_]
  plt.plot(k_feat, sbs.scores_, marker='o')
  plt.ylim([0.7, 1.02])
  plt.ylabel('Accuracy')
  plt.xlabel('Number of features')
  plt.grid()
  plt.tight_layout()
  plt.title('Classification Accuracy of the KNN Classifier')
  plt.ion()
  plt.show()
  input('Press enter to continue:')
  plt.close()

  # The following will list the features that are used at k=3 
  k3 = list(sbs.subsets_[10])
  print('k3',k3)
  print(df.columns[1:][k3])

  knn.fit(X_train_std, y_train)
  print('Resulting accuracy using all features')
  print('Training accuracy:', knn.score(X_train_std, y_train))
  print('Testing accuracy:', knn.score(X_test_std, y_test))

  knn.fit(X_train_std[:, k3], y_train)
  print('Resulting accuracy using features:', k3)
  print('Training accuracy:', knn.score(X_train_std[:, k3], 
        y_train))
  print('Testing accuracy:', knn.score(X_test_std[:, k3], 
        y_test))

  # Note that the above run shows that the reduced number of
  # features produced a less accurate model than using all of
  # the features.  
  input('Press enter to continue:')

"""
This example shows how we can use the Random Forest algorithm 
to determine the importance of each feature within the 
dataset. 

We can measure the feature importance as the average impurity 
decrease computed from all descision trees in the forest, 
without making any assumptions about whether our data is 
linearly separable or not.

"""
def run_assessing_feature_importance_using_random_forest():
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

  # We are going to split the loaded data into input and 
  # output data.  
  X, y = df.iloc[:, 1:].values, df.iloc[:, 0].values

  X_train, X_test, y_train, y_test = \
    train_test_split(X, y, test_size=0.3, random_state=0,
    stratify=y)

  feature_labels = df.columns[1:]
  forest = RandomForestClassifier(n_estimators=500,
                                  random_state=1)
  forest.fit(X_train, y_train)
  importances = forest.feature_importances_
  indices = np.argsort(importances)[::-1]

  for f in range(X_train.shape[1]):
    print('%2d) %-*s %f' % (f + 1, 30,
                            feature_labels[indices[f]],
                            importances[indices[f]]))

  plt.title('Feature Importance')
  plt.bar(range(X_train.shape[1]), importances[indices], 
          align='center')
  plt.xticks(range(X_train.shape[1]),
             feature_labels[indices],
             rotation=90)
  plt.xlim([-1, X_train.shape[1]])
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Press enter to continue:')
  plt.close()

  print('Example of Feature Selection using Select From Model')
  sfm = SelectFromModel(forest, threshold=0.1, prefit=True)
  X_selected = sfm.transform(X_train)
  print('Number of features that meet this threshold',
        'criterian',X_selected.shape[1])
  for f in range(X_selected.shape[1]):
    print('%2d) %-*s %f' % (f + 1, 30, 
                            feature_labels[indices[f]],
                            importances[indices[f]]))

  input('Press enter to continue:')

def add_chapter_four_menu_items(menu,mainMenu):
  chap4 = create_menu('Chapter 4 Examples', mainMenu)
  add_menu_item('Chapter 4 Examples', chap4, menu)
  add_menu_item_with_action(chap4,
    'Example of missing data using Pandas DataFormat',
    run_missing_data_example, menu)
  add_menu_item_with_action(chap4,
    'Example of imputing missing data for real value data',
    run_impute_real_data_example, menu)
  add_menu_item_with_action(chap4,
    'Example of imputing missing data for categorical data',
    run_impute_categorical_data_example, menu)
  add_menu_item_with_action(chap4,
    'Example of one-hot encoding on nominal data',
    run_one_hot_encoding_on_nominal_data_example, menu)
  add_menu_item_with_action(chap4,
    'Example of ordinal encoding of data',
    run_ordinal_encoding_of_data_example, menu)
  add_menu_item_with_action(chap4,
    'Example of splitting a dataset in training and test datasets',
    run_split_dataset_into_training_and_test_datasets, menu)
  add_menu_item_with_action(chap4,
    'Example of Bridging Features onto the same scale',
    run_bridge_features_onto_same_scale_example, menu)
  add_menu_item_with_action(chap4,
    'Example of the effect of using L1 Regularization',
    run_l1_regularization_example, menu)
  add_menu_item_with_action(chap4,
    'Example of the effect of varying L1 regularization',
    run_vary_l1_regularization_example, menu)
  add_menu_item_with_action(chap4,
    'Example of a Sequential Backward Selection using KNN',
    run_sequential_backward_selection_example, menu)
  add_menu_item_with_action(chap4,
    'Example of Assessing Feature Importance using Random Forest',
    run_assessing_feature_importance_using_random_forest, menu)
  