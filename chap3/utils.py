"""
This contains general methods that are used by the different
examples that are part of or inspired by Chapter 3 of the 
Python Machine Learning book that help with those examples.
"""

import numpy as np

# Internal datasets class used to download data
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

def get_iris_data():
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

  return X_train, X_test, y_train, y_test

def standardize_data(X_train, X_test):
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
  X_test_std = sc.transform(X_test)

  return X_train_std, X_test_std

def sigmoid(z):
  """
  This method implements the sigmoid function using Numpy.

    z - a vector of real values passed to the exponetial 
        function.

  Note that the sigmoid function will take values within the
  real number range and return a value between 0 and 1. 
  As z moves towards infinity then the method will return a
  value closer to 1.  While z moves to negative infinity the
  method will return a value closer to 0.  The method has a
  0.5 has its intercept.

  This method is used as an activation function for a 
  given model to determine of a given input is part of a given
  class.
  """

  return 1.0 / (1.0 + np.exp(-z))

def get_random_number(slow,shigh,dlow,dhigh):
  return dlow + 1.0 * ( (np.random.randint(slow,shigh) - slow) / (shigh - slow) ) * (dhigh - dlow)

def in_circle(x, y, r=1, t=1, f=-1):
  return t if ((x**2 + y**2) <= r**2) else f 
