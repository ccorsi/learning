"""

This file will contain all of the general examples that are
part of the Chapter 3 of the Python Machine Learning book.

These general examples are mainly added to include those
examples from the book but this will also contain examples
that extend what is in the book.  This is more for me to be
able understand what was being shown as well as providing a
means to solidify my understanding of the sections read.

"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import SGDClassifier
from sklearn.svm import SVC

from chap3.logisticregression import LogisticRegressionGD
from chap3.utils import sigmoid, get_iris_data, standardize_data
from utils.menu import create_menu, add_menu_item, add_menu_item_with_action
from utils.utils import plot_decision_regions

"""
The following method will provide an example of the cost
of a single training example using the sigmoid function using
a range of input values. 
"""
def run_cost_of_a_single_training():

  def cost_1(z):
    return - np.log(sigmoid(z))
  def cost_0(z):
    return - np.log(1 - sigmoid(z))

  z = np.arange(-10, 10, 0.1)
  phi_z = sigmoid(z)
  c1 = [cost_1(x) for x in z]
  plt.plot(phi_z, c1, label='J(w) if y=1')
  c0 = [cost_0(x) for x in z]
  plt.plot(phi_z, c0, linestyle='--', label='J(w) if y=0')
  plt.ylim(0.0, 5.1)
  plt.xlim([0, 1])
  plt.xlabel('$\phi$(z)')
  plt.ylabel('J(w)')
  plt.legend(loc='best')
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Hit Enter When Done:')
  plt.clf()
  plt.close()

def run_logistic_regression_example():
  X_train, X_test, y_train, y_test = get_iris_data()

  """
  import os
  import pandas as pd
  from utils.utils import get_data

  s = os.path.join('https://archive.ics.uci.edu','ml','machine-learning-databases','iris','iris.data')
  fname = os.path.join('data','iris','iris.data')
  df = pd.read_csv(get_data(s,fname),header=None,encoding='utf-8')

  print('Tailed data:')
  print(df.tail())
  print('Described data:')
  print(df.describe())

  # Extract all non-virginica iris flowers from the data
  data = df.loc[lambda s : s[4] != 'Iris-virginica']

  data.describe()

  # Extract the input data of petal length and petal width
  X = data.loc[:, [2, 3]].values

  print(X_data)

  X_data = np.copy(X)

  # standardize the data
  X_data[:,0] = (X[:,0] - X[:,0].mean()) / X[:,0].std()
  X_data[:,1] = (X[:,1] - X[:,1].mean()) / X[:,1].std()

  # Extract the ouput data and convert the names into integers
  y_data = np.where(data.loc[:, [4]].values == 'Iris-setosa', 0, 1)

  NOTE: The use of the X_data and y_data was causing an 
    exception when being called by the fit method.

  """

  X_train_01_subset = X_train[(y_train == 0) | (y_train == 1)]
  y_train_01_subset = y_train[(y_train == 0) | (y_train == 1)]

  lrgd = LogisticRegressionGD(eta=0.05, n_iter=1000, 
    random_state=1)

  lrgd.fit(X_train_01_subset, y_train_01_subset)

  plot_decision_regions(X=X_train_01_subset, 
    y=y_train_01_subset, classifier=lrgd)

  plt.xlabel('petal length [standardized]')
  plt.ylabel('petal width [standardized]')
  plt.legend(loc='upper left')
  plt.tight_layout()
  plt.ion()
  plt.show()

  input('Press Enter to continue:')
  plt.clf()
  plt.close()

def run_create_different_instances_of_sgdclassifier():
  ppn = SGDClassifier(loss='perceptron')
  print('ppn',ppn)
  lr = SGDClassifier(loss='log')
  print('lr',lr)
  svm = SGDClassifier(loss='hinge')
  print('svm',svm)
  input('Press Entry to continue:')

"""
The following example will generate data that can not be
linearly separable and requires a non-linear representation
instead.  This type of data can not be separated using the
linear logistic regression or the linear SVM model.  

The solution that this can be divided is the use of the 
"kernel methods".  This is done by adding another dimension
to the set of parameters that will allow for the data to be
separated.  For example, we might have training data of 2
features, x_1 and x_2.  We can then add the feature x_3 that
is related using a combination of x_1 and x_2. For instance,
we can related them as follows, <x_1, x_2, x_1^2 + x_2^2>.
The data can then be divided using a hyperplane using a 
linear model such that when it is projected back to the 
original features it becomes a non-linear decision model.

"""
def run_create_simple_dataset_using_np_logical_xor():
  np.random.seed(1)
  X_xor = np.random.randn(200, 2)
  # print('X_xor',X_xor)
  y_xor = np.logical_xor(X_xor[:, 0] > 0,
                         X_xor[:, 1] > 0)
  # print('y_xor',y_xor)
  y_xor = np.where(y_xor, 1, -1)
  # print('y_xor',y_xor)
  blue = [X_xor[y_xor == 1, 0], X_xor[y_xor == 1, 1]]
  squared = []
  for x_1, x_2 in zip(blue[0],blue[1]):
    squared.append((x_1**2 + x_2**2))
  blue.append(squared)
  red = [X_xor[y_xor == -1, 0], X_xor[y_xor == -1, 1]]
  squared = []
  for x_1, x_2 in zip(red[0],red[1]):
    squared.append((x_1**2 + x_2**2))
  red.append(squared)
  plt.scatter(X_xor[y_xor == 1, 0],
              X_xor[y_xor == 1, 1],
              c='b', marker='x',
              label='1')
  plt.scatter(X_xor[y_xor == -1, 0],
              X_xor[y_xor == -1, 1],
              c='r', marker='s',
              label='-1')
  plt.xlim([-3, 3])
  plt.ylim([-3, 3])
  plt.legend(loc='best')
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Press Entry to continue:')
  plt.clf()
  plt.close()

  """
  The following code will take the different x values and
  generate a 3rd dimension by sqauring them to provide an
  example how we can use the concept of "kernel methods".
  The prior data does not provide a clean delineation of
  the above data but it shows a simple example.

  The idea of kernel methods is to take data that requires
  a nonlinear representation and transform it into one that
  can use a linear representation.  This is done by extending
  the data by adding an extra dimension that uses a combination
  of the other dimension to produce values that provide the
  ability to create a linear model.  This is usually done by
  using a nonlinear function like a polynomial function. 
  For instance, we have features (x_1, x_2) that requires a
  nonlinear model and add a feature x_3 = x_1^2 + x_2^2 that
  produces data that can be modeled using a linear model.
  """
  fig = plt.figure()
  ax = fig.add_subplot(111, projection='3d')
  ax.scatter(blue[0], blue[1], blue[2], c='b', marker='x')
  ax.scatter(red[0], red[1], red[2], c='r', marker='s')
  ax.set_xlabel('X')
  ax.set_ylabel('Y')
  ax.set_zlabel('Z')
  ax.set_title('Squaring the x and y values')
  ax.view_init(10)
  plt.ion()
  plt.show()
  input('Press Entry to continue:')
  plt.clf()
  plt.close()

def get_random_number(slow,shigh,dlow,dhigh):
  return dlow + 1.0 * ( (np.random.randint(slow,shigh) - slow) / (shigh - slow) ) * (dhigh - dlow)

def in_circle(x, y, r=1, t=1, f=-1):
  return t if ((x**2 + y**2) <= r**2) else f 

"""
I am trying to reproduce what is on page 149 of the 
Python Machine Learning book.
"""
def create_a_scattered_nonlinear_data():
  x_1 = np.random.normal(0,1,200)
  x_2 = np.random.normal(0,1,200)
  y = np.array([in_circle(x,y) for x,y in zip(x_1,x_2)])

  # Gather all of the blue points
  blue = [
    x_1[y == 1],
    x_2[y == 1],
    x_1[y == 1]**2 + x_2[y == 1]**2
  ]
  # Gather all of the red points
  red = [
    x_1[y == -1],
    x_2[y == -1],
    x_1[y == -1]**2 + x_2[y == -1]**2
  ]

  plt.scatter(blue[0],
              blue[1],
              c='b', marker='x',
              label='1')
  plt.scatter(red[0],
              red[1],
              c='r', marker='s',
              label='-1')
  plt.xlim([np.min(x_1) - 1, np.max(x_1) + 1])
  plt.ylim([np.min(x_2) - 1, np.max(x_2) + 1])
  plt.legend(loc='best')
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Press Entry to continue:')
  plt.clf()
  plt.close()

  fig = plt.figure()
  ax = fig.add_subplot(111, projection='3d')
  ax.scatter(blue[0], blue[1], blue[2], c='b', marker='x')
  ax.scatter(red[0], red[1], red[2], c='r', marker='s')
  ax.set_xlabel('X')
  ax.set_ylabel('Y')
  ax.set_zlabel('Z')
  ax.set_title('Squaring the x and y values')
  ax.view_init(1)
  plt.ion()
  plt.show()
  input('Press Entry to continue:')
  plt.clf()
  plt.close()

"""
This method will show how we can use a kernel trick to be able
to convert nonlinearly separated data into linearly separable
data using the kernel trick that is based on the "radial
basis function", this is also known as the "Gaussian kernel".

"""
def run_kernel_trick_using_radial_basis_function():
  np.random.seed(1)
  X_xor = np.random.randn(200, 2)
  # print('X_xor',X_xor)
  y_xor = np.logical_xor(X_xor[:, 0] > 0,
                         X_xor[:, 1] > 0)
  # print('y_xor',y_xor)
  y_xor = np.where(y_xor, 1, -1)

  """
  The following will use the radial basis function feature
  to convert nonlinearly separated training data into a 
  linearly separated training data using the radial basis
  function.  It takes that training data X and applies a
  function call to that data to produce another dimension
  that can make the training data linearly separable. 
  This function is called a "kernel function".

  We will also should how increasing the gamma value will
  cause overfitting of the training data.  This will use
  the iris data as an example.
  """
  svm = SVC(kernel='rbf', random_state=1, gamma=0.1, C=10.0)
  svm.fit(X_xor, y_xor)
  plot_decision_regions(X_xor, y_xor, classifier=svm)
  plt.title('Kernel Trick RBF - Using Logical XOR Generated Data')
  plt.legend(loc='upper left')
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Press Entry to continue:')
  plt.clf()
  plt.close()

  X_train, X_test, y_train, y_test = get_iris_data()

  X_train_std, X_test_std = standardize_data(X_train, X_test)

  # we are going to combine the training and test data to be
  # able to plot it visually.
  X_combined_std = np.vstack((X_train_std, X_test_std))
  y_combined = np.hstack((y_train, y_test))

  svm = SVC(kernel='rbf', random_state=1, gamma=0.2, C=1.0)
  svm.fit(X_train_std, y_train)
  plot_decision_regions(X_combined_std, y_combined,
                        classifier=svm, test_idx=range(105,150))
  plt.title('Iris RBF Kernel Trick with 0.2 Gamma')
  plt.xlabel('petal length [standardized]')
  plt.ylabel('petal width [standardized]')
  plt.ion()
  plt.show()
  input('Press Enter to continue:')
  plt.clf()
  plt.close()

  svm = SVC(kernel='rbf', random_state=1, gamma=100.0, C=1.0)
  svm.fit(X_train_std, y_train)
  plot_decision_regions(X_combined_std, y_combined,
                        classifier=svm, test_idx=range(105,150))
  plt.title('Iris RBF Kernel Trick with 100.0 Gamma')
  plt.xlabel('petal length [standardized]')
  plt.ylabel('petal width [standardized]')
  plt.ion()
  plt.show()
  input('Press Enter to continue:')
  plt.clf()
  plt.close()

def add_chapter_three_general_example_menu_items(chap3, menu,mainMenu):
  general = create_menu('Chapter 3 General Examples:', mainMenu)
  add_menu_item('Chapter 3 General Examples:', general, chap3)
  add_menu_item_with_action(general,
    'Cost of Classifying a Single Training Example',
    run_cost_of_a_single_training, menu)
  add_menu_item_with_action(general,
    'Logistic Regression using Gradient Descent Example',
    run_logistic_regression_example, menu)
  add_menu_item_with_action(general,
    'Examples of different instances of the SGDClassifier',
    run_create_different_instances_of_sgdclassifier, menu)
  add_menu_item_with_action(general,
    'Simple dataset using Numpy logical_xor feature',
    run_create_simple_dataset_using_np_logical_xor, menu)
  add_menu_item_with_action(general,
    'Sampled Data Useful for Kernel Methods',
    create_a_scattered_nonlinear_data, menu)
  add_menu_item_with_action(general,
    'Example of Kernel Trick using Radial Basis Function',
    run_kernel_trick_using_radial_basis_function, menu)
