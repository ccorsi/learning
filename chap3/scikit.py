"""

This file will contain all of the scikit examples that are
part of the Chapter 3 of the Python Machine Learning book.

This also includes extensions to the examples that I would
implement to better understand what was being taught in
the book.

"""

import numpy as np

# Internal datasets class used to download data
from sklearn import datasets, tree
from sklearn.ensemble import RandomForestClassifier
from sklearn.linear_model import Perceptron, LogisticRegression
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier

import matplotlib.pyplot as plt

from chap3.utils import sigmoid, get_iris_data, standardize_data

from utils.menu import create_menu, add_menu_item, add_menu_item_with_action
from utils.utils import plot_decision_regions

"""
NOTE: The Perceptron implementation has the disadvantage in 
which it is only useful when the data is perfectly separable.  
If the data is not then the Perceptron implementation will 
never stabily when it is being trained.  No matter how many 
epochs are being used.
"""
def run_sklearn_perceptron_test():
  # Download the iris dataset that was used within the chapter 
  # 2 examples.
  iris = datasets.load_iris()
  # Seperate the data between training/test input data and
  # training/test output data
  X = iris.data[:, [2,3]]
  y = iris.target
  # Print how many unique classifications is represented within 
  # the downloaded iris data.
  print('Class labels: {}'.format(np.unique(y)))
  # print('X:',X)

  # This section will show how we can split the data into
  # training and test data

  # We are spiling the data set into training and testing 
  # input and output data.  The test_size signifies that
  # we want to use 30% of the data as test data.  While 
  # the random_state is used to randomize the data into
  # the training and test set.  While the stratify set as
  # y means that we want to have the same distribution of
  # the data within the training and test sets as compared
  # to the original data.
  X_train, X_test, y_train, y_test = train_test_split(X, y, 
                test_size=0.3, random_state=1, stratify=y)
  #print('len(X_train):',len(X_train))
  #print('len(X_test):',len(X_test))
  #print('0.3*len(X):',0.3*len(X))

  # The following shows that the training and testing data
  # was generated within the same distribution of data as
  # the original data.
  print('Labels count in y:', np.bincount(y))
  print('Lables count in y_train', np.bincount(y_train))
  print('Lables count in y_test', np.bincount(y_test))

  # We are going to feature scale the data in this section of 
  # the code.
  sc = StandardScaler()
  # Calling the fit method will allow the StandardScalar
  # instance to be able to estimate the parameters sample means
  # and standard deviation.
  sc.fit(X_train)
  # It uses the estimated mean and standard deviation to 
  # transform the data into a standardized form.  This is 
  # also being applied to the test data.
  X_train_std = sc.transform(X_train)
  print('X_train','X_train_std')
  for train,train_std in zip(X_train,X_train_std):
    print(train,'==>',train_std)
  X_test_std = sc.transform(X_test)
  print('X_test', 'X_test_std')
  for train,train_std in zip(X_test,X_test_std):
    print(train,'==>',train_std)

  # We are going to use the scikit learning package 
  # Perceptron implementation to perform the same actions
  # that have been shown with the Chapter 2 implementation.

  # NOTE: The Perceptron also has the n_iter which is the
  #   parameter that is also called the epochs.  This means
  #   the number of passes that the Perceptron goes through
  #   the training data.
  ppn = Perceptron(eta0=0.1, random_state=1)
  ppn.fit(X_train_std, y_train)

  # Now that we've trained the Perceptron let us now make
  # predictions using the test data.  We are going to use
  # the standardized testing data.
  y_pred = ppn.predict(X_test_std)
  missed_predictions = (y_test != y_pred).sum()
  print('Misclassified examples: {}'.format(missed_predictions))
  print('Classification accuracy: {:.2f}'.format((1-missed_predictions/y_test.sum())*100))

  # The above can also be done using one of the metrics classes.
  print('Accuracy: {:.3f}'.format(accuracy_score(y_test, y_pred)))

  # scikit learn provides a score method for each classifier 
  # that provides the same functionality as is been shown above
  print('Accuracy: {:.3f}'.format(ppn.score(X_test_std, y_test)))

  # clear all prior graphs before continuing
  plt.clf()

  X_combined_std = np.vstack((X_train_std, X_test_std))
  y_combined = np.hstack((y_train, y_test))
  plot_decision_regions(X=X_combined_std,
    y=y_combined, classifier=ppn, test_idx=range(105, 150))
  plt.xlabel('petal length [standardized]')
  plt.ylabel('petal width [standardized]')
  plt.legend(loc='upper left')
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Press enter to continue:')
  plt.clf()
  plt.close()

"""
The following method will show how someone can use the Logistic
regression technique to help make predictions about data for
classifications.  This method is defined as a probalistic model
for binary classification.

Let us introduce the concept of "odds" which is the represented 
as the odds of a particular event being true.  In our binary 
classification problem then this is defined as:

           p / (1 - p)

Where p is defined as the probability of the positive event.

Using the prior information we can then define the logit 
function as follows:

  logit(p) = ln(p/(1-p))

were ln is the natural logarithm of base e.  Note that the 
logit method takes values between 0 and 1 and produces values
on the entire real number range.

Thus the linear relationshio between feature values and the
log-odds is:

  logit(p(y == 1|x)) = w_0*x_0 + w_1*x_1 + ... + w_m*x_m
                     = sum (w_i*x_i), where i = 0,1,..,m

where p(y == 1|x) is the conditional probability that a 
particular example belongs to class y == 1 given its feature x. 

Let us now look at the opposite of above.  Let us then 
predict the probability that a certain example belongs 
to a particular class y.

This is called the "logistic sigmoid function" which is
abbreviated as "sigmod function" and is defined as:

  q(z) = 1 / (1 + e^-z)

where z is the combination of inputs and weights:

  z = w_0*x_0 + w_1*x_1 + ... + w_m*_x_m

recalling that the w_0 is the bias and x_0 is always 1.

The above explains how to use the logistic sigmoid function 
to be able to determine if a given input is part of a given
class.  This can be extended to classifications that require
the possibility of it belongs one of more than two classes of
outputs.  The sidmoid function can then be used to calculate
each class given a set of input and weights.  The weights in
this case is a matric instead of a vector.  The resulting 
output, y, is an array of size d where d is the number of 
different classifications.
"""
def run_logistic_regression():
  # We are going to create a simple sigmoid graph for
  # illustrative purposes only.
  z = np.arange(-7, 7, 0.1)
  # print(z)
  phi_z = sigmoid(z)

  import matplotlib.pyplot as plt

  plt.plot(z, phi_z)
  plt.axvline(0.0, color='k')
  plt.ylim(-0.1, 1.1)
  plt.xlabel('z')
  plt.ylabel('$\phi (z)$')
  # y axis ticks and gridline
  plt.yticks([0.0, 0.5, 1.0])
  ax = plt.gca()
  ax.yaxis.grid(True)
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Hit enter when done.')
  plt.clf()
  plt.close()

def run_scikit_logistic_regression_example():
  X_train, X_test, y_train, y_test = get_iris_data()

  X_train_std, X_test_std = standardize_data(X_train, X_test)
  
  # We are going to use the LogisticRegression class from the
  # scikit but use the One-vs.-rest multi-class setting.
  lr = LogisticRegression(C=100.0, random_state=1, 
    solver='lbfgs', multi_class='ovr')
  lr.fit(X_train_std, y_train)

  # we are going to combine the training and test data to be
  # able to plot it visually.
  X_combined_std = np.vstack((X_train_std, X_test_std))
  y_combined = np.hstack((y_train, y_test))

  plot_decision_regions(X_combined_std, y_combined,
    classifier=lr, test_idx=range(105, 150)) 

  # we are going to display the predicted values for the
  # first three test entries.
  preds = lr.predict_proba(X_test_std[:3, :])
  print('preds - predict_proba')
  print(preds)
  print('preds.sum(axis=1)')
  print(preds.sum(axis=1))
  print('preds.argmax(axis=1)')
  print(preds.argmax(axis=1))
  preds = lr.predict(X_test_std[:3, :])
  print('preds - predict')
  print(preds)
  preds = lr.predict(X_test_std[0, :].reshape(1,-1))
  print('preds - predict with reshape(1,-1)')
  print(preds)
  """
  THIS DOES NOT WORK BUT I STILL DON'T UNDERSTAND WHY!!!!
  IT TALKS ABOUT USING THE RESHAPE METHOD BUT IT IS NOT CLEAR
  HOW THIS SHOULD BE DONE.  I'VE TRIED SEVERAL COMBINATIONS 
  WITHOUT ANY SUCCESS.
  preds = lr.predict(X_test_std[:].argmax(axis=1))
  print('preds - predict with argmax(1) for all test data')
  print(preds)
  """
  input('Press Enter to continue:')

  plt.title('Logistic Regression Using One-vs.-rest (OvR) method')
  plt.xlabel('petal length [standardized]')
  plt.ylabel('petal width [standardized]')
  plt.legend(loc='upper left')
  plt.tight_layout()
  plt.ion()
  plt.show()

  input('Press Enter to continue:')
  plt.clf()
  plt.close()

  # We are now going to use the more recommended multinomial 
  # multi-class parameter.  This is what is recommended in 
  # practice over the Over-vs.-rest setting.
  lr = LogisticRegression(C=100.0, random_state=1, 
    solver='lbfgs', multi_class='multinomial')
  lr.fit(X_train_std, y_train)

  plot_decision_regions(X_combined_std, y_combined,
    classifier=lr, test_idx=range(105, 150)) 

  plt.title('Logistic Regression Using The Multinomial method')
  plt.xlabel('petal length [standardized]')
  plt.ylabel('petal width [standardized]')
  plt.legend(loc='upper left')
  plt.tight_layout()
  plt.ion()
  plt.show()

  input('Press Enter to continue:')
  plt.clf()
  plt.close()

def run_scikit_logistic_regression__vary_regularization_example():
  X_train, X_test, y_train, y_test = get_iris_data()

  X_train_std, X_test_std = standardize_data(X_train, X_test)
  
  weights, params = [], []

  # We are going to produce different models using the
  # same set of training data but will only change the
  # value of the regularization, C.
  # Note that decreasing the value of C increases the bias
  #   and lowers the variance of the model
  for c in np.arange(-5,5):
    print('Training model using c={}'.format(c))
    lr = LogisticRegression(C=10.**c, random_state=1, 
          solver='lbfgs', multi_class='ovr')
    lr.fit(X_train_std, y_train)
    weights.append(lr.coef_[1])
    params.append(10.**c)
    print('Completed training model using c={}'.format(c))

  weights = np.array(weights)

  plt.plot(params, weights[:, 0], label='petal length')
  plt.plot(params, weights[:, 1], linestyle='--', 
          label='petal width')
  plt.ylabel('weigth coefficient')
  plt.xlabel('C')
  plt.legend(loc='upper left')
  plt.xscale('log')
  plt.ion()
  plt.show()

  input('Press Enter to continue:')
  plt.clf()
  plt.close()

"""

Some notes on the difference between Logistic Regression and
Support Vector Machine.

In practice, Linear Logistic Regression, (LR), and Linear 
Support Vector Machine, (SVM), produce similar results.

LR tries to maximize the conditional likelihood of the training
data, which makes it more prone to outlines compared to SVMs,
which mostly concern itselfs with points closet to the descision
boundary.

While LR is a simplier model to implement and has the ability
to easily be updated which makes the appealing to streaming 
data.

"""
def run_scikit_support_vector_machine_example():
  # Get the iris data
  X_train, X_test, y_train, y_test = get_iris_data()
  # Standardize the iris data
  X_train_std, X_test_std = standardize_data(X_train, X_test)
  
  # create an instance of a Support Vector Machine classifier.
  # TODO: read about the kernel options and what does it mean
  #  using linear as a kernel.
  svm = SVC(kernel='linear', C=1.0, random_state=1)

  svm.fit(X_train_std, y_train)

  X_combined_std = np.vstack((X_train_std, X_test_std))
  y_combined = np.hstack((y_train, y_test))

  plot_decision_regions(X_combined_std, y_combined, 
    classifier=svm, test_idx=range(105, 150))
  
  plt.title('Support Vector Machine')
  plt.xlabel('petal length [standardized]')
  plt.ylabel('petal width [standardized]')
  plt.legend(loc='upper left')
  plt.tight_layout()
  plt.ion()
  plt.show()

  input('Press Enter to continue:')
  plt.clf()
  plt.close()

"""
The following method provides an exanmple of how a Descision
Tree is implemented.  A descision tree takes data and splits
data into paths that will then lead to an action that should
be followed.  The tree is generated given classification or
value type comparisions.   This can end up generating a fairly
deep tree.  The descision used to determine how to separate the
tree is called "information gain(IG)".  The process can produce
a fairly deep tree which usually lead to overfitting.  This 
is minimized by limiting the depth of the generated descision
tree.  Note that the descision tree can use two or more child
nodes but in practice this is kept to only two child nodes
because of performance considerations.  

The first example will show how the different options used
to generate the descision tree can produce different splits
in the descision tree.

The separation criterian can be determined using different
criterians that will determine the affinity of data with
the left compared to the right node.  Its objective is to
minimize the possibility of misclassification of new data.

There are several types of criterians that can be used. 
There is the Gini, Entropy and the Classification Error.  
Note that the Gini and Entropy criterian produce similar
results and it is not of any benefit using both of them.
The above criterian provide the ability to grow a descision
tree but it does not necessarily provide a stopping point.
It is possible for the descision tree to become so big that
it is overfitting.  This is then managed using the 
Classification Error criterian.

The Classification Error criterian is useful for
pruning the descision tree and it is not recommend for 
growing the descision tree.  

Thus the combination of the Gini or Entropy criterian with
the Classification Error would provide the ability to 
grow a descision tree while keeping the tree from 
overfitting the training data.

The above is used to determine maximize the split of the
descision tree at each node.  The calculation that is being
performed is called the "Information Gain (IG)".  The 
formula used is the following:

  IG(D_p,f) = I(D_p) - SUM((N_j/N_p) * I(D_j))

Where

  f is the feature to perform the split
  D_p & D_j are the dataset of the parent and jth child node
  I is the "impurity" measure
  N_p is the total number of training examples at the parent node
  N_j is the total number of training examples in the jth child node

We are then trying to maximize the above formula at each node.
This does not imply that a particular order at node p will then
produce a similar order at a child j of node p.  This 
information is only relavent to the current node.

The three criterians mentioned above have the following
formulas:

Entropy:

  I_H(t) = - SUM(p(i|t) * log_2(p(i|t))), for i = 1..c

  where p(i|t) is the proportion of the examples that belong
  to class i for a particular node t.  Note that c is the 
  number of splits that the node t can be divided into.  As
  mentioned above, in practice this is set to 2.

Gini:

  I_G(t) = 1 - SUM(p(i|t)^2), for i = 1..c

Classification Error:

  I_E(t) = 1 - MAX{p(i|t)}, for i = 1..c

"""
def gini(p):
  """
  This method implements the "Gini impurity" which uses
  probability measures to figure minimize the classification
  error.  The gini value is maximium whenever the data is
  uniformaly distributed.

  The Gini criterian is to minimize the probability of 
  misclassification.
  """
  return (p)*(1 - p) + (1 - p) * (1 - (1 - p))

def entropy(p):
  """
  This method implements the entropy used to calculate 
  which class a given feature belongs to.  Note that 
  a uniformed distribution would result in a maximal
  entropy.

  The Entropy criterian attempts to maximize the mutual
  information in the tree.
  """
  return - p * np.log2(p) - (1 - p) * np.log2((1 - p))

def error(p):
  """
  This method implements the Classification error. This
  is used to prune the descision tree and not to grow the
  tree.  It should be used in conjunction with either the
  Gini or Entropy criterian.
  """
  return 1 - np.max([p, 1 -p])

def run_decision_tree_example():
  iris = datasets.load_iris()

  X = iris.data[:, [2,3]]
  y = iris.target

  X_train, X_test, y_train, y_test = train_test_split(X, y, 
                test_size=0.3, random_state=1, stratify=y)

  tree_model = DecisionTreeClassifier(criterion='gini',
      max_depth=4, random_state=1)
  tree_model.fit(X_train, y_train)

  X_combined = np.vstack((X_train, X_test))
  y_combined = np.hstack((y_train, y_test))

  plot_decision_regions(X_combined, y_combined,
    classifier=tree_model, test_idx=range(105, 150))

  plt.xlabel('petal length [cm]')
  plt.ylabel('petal width [cm]')
  plt.legend(loc='upper left')
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Press Enter to continue:')
  plt.close()

  tree.plot_tree(tree_model)
  plt.title('Decision Tree with Max Depth 4')
  plt.ion()
  plt.show()
  input('Press Enter to continue:')
  plt.close()

  tree_model = DecisionTreeClassifier(criterion='gini',
      max_depth=3, random_state=1)
  tree_model.fit(X_train, y_train)

  tree.plot_tree(tree_model)
  plt.title('Decision Tree with Max Depth 3')
  plt.ion()
  plt.show()
  input('Press Enter to continue:')
  plt.close()

  """
  NOTE: The following code does not work within Replit
  because it needs a third party native library that
  needs to be installed.

  from sklearn.tree import export_graphviz

  from pydotplus import graph_from_dot_data
  
  dot_data = export_graphviz(tree_model, filled=True,
    rounded=True,
    class_names=['Setosa', 'Versicolor', 'Virginica'],
    feature_names=['petal length', 'petal width'],
    out_file=None)
  graph = graph_from_dot_data(dot_data)
  graph.write_png('tree.png')
  plt.ion()
  plt.show()
  input('Press Enter to continue:')
  plt.close()
  """

def run_compare_impurity_criterians():
  x = np.arange(0.0, 1.0, 0.01)
  ent = [entropy(p) if p != 0 else None for p in x]
  sc_ent = [e*0.5 if e else None for e in ent]
  err =  [error(i) for i in x]
  # This was included in the code but it is not being used!
  # fig = plt.figure()
  ax = plt.subplot(111)
  
  for i, lab, ls, c in zip([ent, sc_ent, gini(x), err],
                        ['Entropy', 'Entropy (scaled)',
                         'Gini impurity',
                         'Misclassification error'],
                         ['-', '-', '--', '-.'],
                         ['black', 'lightgrey',
                         'red', 'green','cyan']):
    ax.plot(x, i, label=lab, linestyle=ls, lw=2,color=c)
  
  ax.legend(loc='upper center', bbox_to_anchor=(0.5, 1.15),
      ncol=5, fancybox=True, shadow=False)
  ax.axhline(y=0.5, linewidth=1, color='k', linestyle='--')
  ax.axhline(y=1.0, linewidth=1, color='k', linestyle='--')
  plt.ylim([0, 1.1])
  plt.xlabel('p(i=1)')
  plt.ylabel('impurity index')
  plt.ion()
  plt.show()
  input('Press Enter to continue:')
  plt.close()

"""
This method will show how to create and use an instance of
a Random Forest using scikit RandomForestClassifier class.
A Random Forest is consider an ensemble because it is an
ensemble of Decision Trees.

A Random Forest is basically k Decision Trees.  The idea is
to average multiple (deep) decision trees that individually
suffer from high variance to build a more robust model that
has a better performance and is less suseptible to overfitting.
This just means that it is creating different Decision Tree 
using a subset of the training data such that each tree is 
somewhat different such that it reduces the level of variance
compared to a single Decision Tree.  This type of classifier 
show be considered whenever the data has a high degree of 
variance.

The algorithm for a Randome Forest is the following:

  1 - Draw a "bootstrap" random sample of size "n" from the 
      sample training set, with replacement

  2 - Grow a decision tree using the bootstrap sample.
      At each node:

        1 - Randomly select "d" features without replacement

        2 - Split the node using the feature that provides the
            best split according to the objective function,
            for instance, maximizing the information gain. 

  3 - Repeat step 1-2 "k" times. Producing "k" decision trees.

  4 - Aggregate the prediction by each tree to assign the class
      label by "majority vote".  A good old fashion democracy 
      type selection mechanism.

Note that it is important that we use replacement when selecting
the "n" random sample from the training data.  This will allow 
us to have the same probability of choosing each sample.

Note that we only choose a subset "d" features of the total 
number of features "m". 

The implementation provides the following advantages over the
decision tree implementation:

  - no need to worry about choosing good hyperparameters
  - no need to prune each decision tree because random forest 
    is robust against noise from each decision tree

While the above advantage removes the need for us to think about
those requirements.  It still does not remove all thought from
the process.  We still need to think about what we should set 
"k" too.  While a larger value of "k" will provide better
performance but at the expense of computational cost.

We still could manipulate the hyperparameters of a Random 
Forest implementation.  These are the "bootstrap" sample size
and the "d" features selection.  These can be fiddle with 
produce a better model.  The sample size "n" can be manipulated
to control the bias-variance of the data.  Decreasing the size
may increase the "randomness" which in turn can conteract the
possibility of overfitting.  While increase the sample size "n"
will increase the diversity of the sample at the cost of the
greater possibility of overfitting.

In practice how do we decide what value of "d" should be chosen?
This is usually set to sqrt(m) where m is the total features for
the data set.
"""
def run_scikit_random_forest_example():
  iris = datasets.load_iris()

  X = iris.data[:, [2,3]]
  y = iris.target

  X_train, X_test, y_train, y_test = train_test_split(X, y, 
                test_size=0.3, random_state=1, stratify=y)

  """
  The n_estimators is how many decision trees we want to 
  create for this random forest model.  While n_jobs is 
  used to set the number of cpu that should be used to 
  produce the model.
  """
  forest = RandomForestClassifier(criterion='gini',
    n_estimators=25, random_state=1, n_jobs=2)
  forest.fit(X_train, y_train)

  X_combined = np.vstack((X_train, X_test))
  y_combined = np.hstack((y_train, y_test))

  plot_decision_regions(X_combined, y_combined, 
    classifier=forest, test_idx=range(105, 150))

  plt.xlabel('petal length [cm]')
  plt.ylabel('petal width [cm]')
  plt.legend(loc='upper left')
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Press Enter to continue:')
  plt.close()

"""
This method provides an example of a k-nearest neighbor (KNN)
classifier.  This type of classifier is called a "lazy learner"
because it does not learn a discriminative function for the 
training set but is just memories the training data set.  

The KNN algorithm uses the following steps:

  1 - Choose the number "k" and the distance metric

  2 - Find the k-nearest neighbors of the data record that we
      want to classify

  3 - Assign the class label by majority vote

The model will pick the "k" closest neighbors for a given 
sample and then determine which one is the closest (similar)
to the one that we are trying to classify.  This is done using
the distance metric.  The incoming data is also used to update
the model by providing more data to help determine how to 
classify incoming samples.  While this is a positive aspect of
the algorithm, it does cause computational complexity even
though the data grows linearly. 

The implementation also suffers from the "curse of dimensionality" as the number feature grow the data will become
more sparse since you are required a greater number of training
data to be able to provide a better prediction model.  The 
reason is that incoming data will be harder to classify because
of the distance of the incoming sample data compared to the 
current set of data.  We can find ourselves trying to classify
something that isn't close to any of the current set of data. 
This makes the process of classifying more challenging.

This leads to the issue of what type of distance function should
be used to determine the distance of the k-nearest data points.
Usually, we use a simple Euclidean distance for real-value 
examples.  Using an Euclidean distance requires that we 
standardize the data to provide equal value between features. 
There are other distance measures that can be used.  The
"minkowski" distance is a generalization of the Euclidean 
metric.  This also includes other metrics like the "Manhattan"
distance.  The formula is the following:

    d(x_i, x_j) = P-ROOT(K-SUM(P-NORM(x_i_k x_j_k)))

where p=2 reverts to the Euclidean distance and p=1 reverts to
the Manhattan distance. There are other distance implementations
that are part of the scikit.  These are described as part of
the DistanceMetric class.  One of these can be used with the
k-nearest neighbor implementation.

"""
def run_scikit_k_nearest_neighbot_example():
  iris = datasets.load_iris()

  X = iris.data[:, [2,3]]
  y = iris.target

  X_train, X_test, y_train, y_test = train_test_split(X, y, 
                test_size=0.3, random_state=1, stratify=y)

  knn = KNeighborsClassifier(n_neighbors=5, p=2, 
          metric='minkowski')

  knn.fit(X_train, y_train)

  X_combined = np.vstack((X_train, X_test))
  y_combined = np.hstack((y_train, y_test))

  sc = StandardScaler()

  sc.fit(X_combined)

  X_combined_std = sc.transform(X_combined)

  plot_decision_regions(X_combined_std, y_combined, 
    classifier=knn, test_idx=range(105, 150))

  plt.xlabel('petal length [standardized]')
  plt.ylabel('petal width [standardized]')
  plt.legend(loc='upper left')
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Press Enter to continue:')
  plt.close()

def add_chapter_three_scikit_example_menu_items(chap3,menu, mainMenu):
  scikit = create_menu('Chapter 3 Scikit Examples:', mainMenu)
  add_menu_item('Chapter 3 Scikit Examples:', scikit, chap3)
  add_menu_item_with_action(scikit, 
    'Learning Scikit with Perceptron',
    run_sklearn_perceptron_test, menu)
  add_menu_item_with_action(scikit,
    'Learning Scikit with Logistic Regression',
    run_logistic_regression, menu)
  add_menu_item_with_action(scikit,
    'Scikit Logistic Regression using Gradient Descent Example',
    run_scikit_logistic_regression_example, menu)
  add_menu_item_with_action(scikit,
    'Scikit Logistic Regression with varying Regularization Example',
    run_scikit_logistic_regression__vary_regularization_example, menu)
  add_menu_item_with_action(scikit,
    'Scikit Support Vector Machine Example',
    run_scikit_support_vector_machine_example, menu)
  add_menu_item_with_action(scikit,
    'Scikit Support of Decision Tree Example',
    run_decision_tree_example, menu)
  add_menu_item_with_action(scikit,
    'Show Comparision of Impurity Criterians for Descision Tree',
    run_compare_impurity_criterians, menu)
  add_menu_item_with_action(scikit,
    'Scikit Support of Random Forest Example',
    run_scikit_random_forest_example, menu)
  add_menu_item_with_action(scikit,
    'Scikit Support of K-nearest neighbor (KNN) Example',
    run_scikit_k_nearest_neighbot_example, menu)