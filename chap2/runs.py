"""
This file contains the different methods that can be called that
will display the different features that can be executed with
the simple implementation of the Perceptron, Adaline Gradient Descent and Adaline Stochastic Gradient Descent.
"""

import os
import time

# specific machine learning type imports
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

from utils.utils import get_data, plot_decision_regions
from utils.menu import MenuItem, Menu, Action, add_menu_item_with_action

# Python Machine Learning Examples imports
from chap2.perceptron import Perceptron

def add_chapter_two_menu_items(parentMenu, mainMenu):
  chap2 = Menu('Chapter 2 Examples:', parent = parentMenu)
  chap2.add_menu_item(MenuItem('Perceptron Example', Action(run_perceptron_test, mainMenu)))
  chap2.add_menu_item(MenuItem('Adaline Example', Action(run_adaline_test, mainMenu)))
  parentMenu.add_menu_item(MenuItem('Chapter 2 Examples',chap2))
  add_menu_item_with_action(chap2, 'Adaline Gradient Descent Example', run_adaline_gradient_descent, mainMenu)
  add_menu_item_with_action(chap2, 'Adaline Gradient Descent With Feature Scaling Example', run_adaline_gradient_descent_with_feature_scaling, mainMenu)
  add_menu_item_with_action(chap2, 'Adaline Stochastic Gradient Descent Example', run_adaline_stochastic_gradient_descent, mainMenu)

def run_perceptron_test():
  s = os.path.join('https://archive.ics.uci.edu','ml','machine-learning-databases','iris','iris.data')
  fname = os.path.join('data','iris','iris.data')
  df = pd.read_csv(get_data(s,fname),header=None,encoding='utf-8')
  print('Tailed data:')
  print(df.tail())
  print('Described data:')
  print(df.describe())

  # select setosa and versicolor flower names
  # specifically we are extracting the first 100 rows but
  # only the flower name column.
  y = df.iloc[0:100, 4].values

  # update them so that they are using -1 and 1 instead
  # of a string name, easier to use within calculations
  y = np.where(y == 'Iris-setosa', -1, 1)

  # extract the sepal length and petal length,
  # columns 0 and 2
  X = df.iloc[0:100, [0, 2]].values

  # plot the data for a visual representation
  plt.scatter(X[:50, 0], X[:50, 1], color='red', marker='o', label='setosa')
  plt.scatter(X[50:100, 0], X[50:100, 1], color='blue', marker='x', label='versicolor')
  plt.xlabel('sepal length [cm]')
  plt.ylabel('petal length [cm]')
  plt.legend(loc='upper left')
  # This will allow the show method to return instead of waiting
  plt.ion()
  # hmm, this first graph is not being displayed at all.
  plt.show()

  # sleep for 10 seconds to allow you to see the generated
  # graph before moving on to  display another graph
  print('Showing a scattered graph of the sepal and petal lengths.')
  # time.sleep(10)

  ppn = Perceptron(eta=0.1,n_iter=10)
  ppn.fit(X, y)
  plt.plot(range(1, len(ppn.errors_) + 1), ppn.errors_, marker='o')
  plt.xlabel('Epochs')
  plt.ylabel('Number of updates')
  plt.show()
  print('Showing misclassification erros from the fit call.')

  # let us wait 10 seconds before exiting program
  # time.sleep(10)

  plot_decision_regions(X, y, classifier=ppn)
  plt.xlabel('sepal length [cm]')
  plt.ylabel('petal length [cm]')
  plt.legend(loc='upper left')
  plt.ion()
  plt.show()

  time.sleep(10)

def run_adaline_gradient_descent():
  from chap2.adaline import AdalineGD

  s = os.path.join('https://archive.ics.uci.edu','ml','machine-learning-databases','iris','iris.data')
  fname = os.path.join('data','iris','iris.data')
  df = pd.read_csv(get_data(s,fname),header=None,encoding='utf-8')
  print('Tailed data:')
  print(df.tail())
  print('Described data:')
  print(df.describe())

  # select setosa and versicolor flower names
  # specifically we are extracting the first 100 rows but
  # only the flower name column.
  y = df.iloc[0:100, 4].values

  # update them so that they are using -1 and 1 instead
  # of a string name, easier to use within calculations
  y = np.where(y == 'Iris-setosa', -1, 1)

  # extract the sepal length and petal length,
  # columns 0 and 2
  X = df.iloc[0:100, [0, 2]].values

  fig, ax = plt.subplots(nrows=2, ncols=1, figsize=(6,5))
  # insure that there is some space between the two sub plots
  fig.subplots_adjust(hspace=0.75)
  adal1 = AdalineGD(n_iter=10, eta=0.01).fit(X, y)
  print(adal1)
  ax[0].plot(range(1, len(adal1.cost_) + 1),
    np.log10(adal1.cost_), marker='o')
  ax[0].set_xlabel('Epochs')
  ax[0].set_ylabel('log(Sum-squared-error)')
  ax[0].set_title('Adaline - Learning Rate 0.01')
  adal2 = AdalineGD(n_iter=10, eta=0.0001).fit(X, y)
  print(adal2)
  ax[1].plot(range(1, len(adal2.cost_) + 1), 
    adal2.cost_, marker='o')
  ax[1].set_xlabel('Epochs')
  ax[1].set_ylabel('log(Sum-squared-error)')
  ax[1].set_title('Adaline - Learning Rate 0.0001')
  plt.ion()
  plt.show()

def run_adaline_gradient_descent_with_feature_scaling():
  from chap2.adaline import AdalineGD

  s = os.path.join('https://archive.ics.uci.edu','ml','machine-learning-databases','iris','iris.data')
  fname = os.path.join('data','iris','iris.data')
  df = pd.read_csv(get_data(s,fname),header=None,encoding='utf-8')
  print('Tailed data:')
  print(df.tail())
  print('Described data:')
  print(df.describe())


  # select setosa and versicolor flower names
  # specifically we are extracting the first 100 rows but
  # only the flower name column.
  y = df.iloc[0:100, 4].values

  # update them so that they are using -1 and 1 instead
  # of a string name, easier to use within calculations
  y = np.where(y == 'Iris-setosa', -1, 1)

  # extract the sepal length and petal length,
  # columns 0 and 2
  X = df.iloc[0:100, [0, 2]].values

  """
  The next section of code will take advantage of the "feature scaling"
  "standardization".  This concept just converts the current data 
  properties into a normal distribution of mean 0 and variance of 1.

  This technique allows the gradient descent learing technique to 
  converge more quickly but it does not make the original dataset
  normally distributed.   It just centers the data and each feature
  will have a standard deviation of 1.
  """

  plt.clf()
  print('X[:,0]')
  print(X[:,0])
  print('X[:,1]')
  print(X[:,1])
  X_std = np.copy(X)
  X_std[:,0] = (X[:,0] - X[:,0].mean()) / X[:,0].std()
  X_std[:,1] = (X[:,1] - X[:,1].mean()) / X[:,1].std()
  print('X_std[:,0]')
  print(X_std[:,0])
  print('X_std[:,1]')
  print(X_std[:,1])

  ada_gd = AdalineGD(n_iter=15, eta=0.01)
  print(ada_gd)
  ada_gd.fit(X_std, y)
  plot_decision_regions(X_std, y, classifier=ada_gd)
  plt.title('Adaline - Gradient Descent')
  plt.xlabel('sepal length [standardized]')
  plt.ylabel('pedal length [standardized]')
  plt.legend(loc='upper left')
  plt.tight_layout()
  plt.ion()
  plt.show()
  input('Hit Enter to see next graph')
  plt.clf()
  plt.plot(range(1, len(ada_gd.cost_) + 1),
  ada_gd.cost_, marker='o')
  plt.xlabel('Epochs')
  plt.ylabel('Sum-squared-error')
  plt.tight_layout()
  plt.ion()
  plt.show()
  # plt.clf()

def run_adaline_stochastic_gradient_descent():
  s = os.path.join('https://archive.ics.uci.edu','ml','machine-learning-databases','iris','iris.data')
  fname = os.path.join('data','iris','iris.data')
  df = pd.read_csv(get_data(s,fname),header=None,encoding='utf-8')
  print('Tailed data:')
  print(df.tail())
  print('Described data:')
  print(df.describe())


  # select setosa and versicolor flower names
  # specifically we are extracting the first 100 rows but
  # only the flower name column.
  y = df.iloc[0:100, 4].values

  # update them so that they are using -1 and 1 instead
  # of a string name, easier to use within calculations
  y = np.where(y == 'Iris-setosa', -1, 1)

  # extract the sepal length and petal length,
  # columns 0 and 2
  X = df.iloc[0:100, [0, 2]].values

  # applying "feature scaling"/"standardization" to the data
  X_std = np.copy(X)
  X_std[:,0] = (X[:,0] - X[:,0].mean()) / X[:,0].std()
  X_std[:,1] = (X[:,1] - X[:,1].mean()) / X[:,1].std()

  from chap2.adaline import AdalineSGD

  # The following code uses the Stochastic Gradient Descent
  # with the Adaline implementation
  ada_sgd = AdalineSGD(n_iter=15, eta=0.01, random_state=1)
  print(ada_sgd)
  ada_sgd.fit(X_std, y)
  plot_decision_regions(X_std, y, ada_sgd)
  plt.title('Adaline - Stochastic Gradient Descent')
  plt.xlabel('sepal length [standardized]')
  plt.ylabel('pedal length [standardized]')
  plt.tight_layout()
  plt.ion()
  # plt.ioff()
  plt.show()
  input('Hit enter to see the next graph')
  plt.clf()
  plt.plot(range(1, len(ada_sgd.cost_) + 1), ada_sgd.cost_, 
  marker='o')
  plt.xlabel('Epochs')
  plt.ylabel('Average Cost')
  plt.tight_layout()
  plt.show()


def run_adaline_test():
  from chap2.adaline import AdalineGD

  s = os.path.join('https://archive.ics.uci.edu','ml','machine-learning-databases','iris','iris.data')
  fname = os.path.join('data','iris','iris.data')
  df = pd.read_csv(get_data(s,fname),header=None,encoding='utf-8')
  print('Tailed data:')
  print(df.tail())
  print('Described data:')
  print(df.describe())

  # select setosa and versicolor flower names
  # specifically we are extracting the first 100 rows but
  # only the flower name column.
  y = df.iloc[0:100, 4].values

  # update them so that they are using -1 and 1 instead
  # of a string name, easier to use within calculations
  y = np.where(y == 'Iris-setosa', -1, 1)

  # extract the sepal length and petal length,
  # columns 0 and 2
  X = df.iloc[0:100, [0, 2]].values

  fig, ax = plt.subplots(nrows=2, ncols=1, figsize=(6,5))
  # insure that there is some space between the two sub plots
  fig.subplots_adjust(hspace=0.75)
  adal1 = AdalineGD(n_iter=10, eta=0.01).fit(X, y)
  print(adal1)
  ax[0].plot(range(1, len(adal1.cost_) + 1),
    np.log10(adal1.cost_), marker='o')
  ax[0].set_xlabel('Epochs')
  ax[0].set_ylabel('log(Sum-squared-error)')
  ax[0].set_title('Adaline - Learning Rate 0.01')
  adal2 = AdalineGD(n_iter=10, eta=0.0001).fit(X, y)
  print(adal2)
  ax[1].plot(range(1, len(adal2.cost_) + 1), 
    adal2.cost_, marker='o')
  ax[1].set_xlabel('Epochs')
  ax[1].set_ylabel('log(Sum-squared-error)')
  ax[1].set_title('Adaline - Learning Rate 0.0001')
  plt.ion()
  plt.show()

  """
  The next section of code will take advantage of the "feature scaling"
  "standardization".  This concept just converts the current data 
  properties into a normal distribution of mean 0 and variance of 1.

  This technique allows the gradient descent learing technique to 
  converge more quickly but it does not make the original dataset
  normally distributed.   It just centers the data and each feature
  will have a standard deviation of 1.
  """

  plt.clf()
  print('X[:,0]')
  print(X[:,0])
  print('X[:,1]')
  print(X[:,1])
  X_std = np.copy(X)
  X_std[:,0] = (X[:,0] - X[:,0].mean()) / X[:,0].std()
  X_std[:,1] = (X[:,1] - X[:,1].mean()) / X[:,1].std()
  print('X_std[:,0]')
  print(X_std[:,0])
  print('X_std[:,1]')
  print(X_std[:,1])

  ada_gd = AdalineGD(n_iter=15, eta=0.01)
  print(ada_gd)
  ada_gd.fit(X_std, y)
  plot_decision_regions(X_std, y, classifier=ada_gd)
  plt.title('Adaline - Gradient Descent')
  plt.xlabel('sepal length [standardized]')
  plt.ylabel('pedal length [standardized]')
  plt.legend(loc='upper left')
  plt.tight_layout()
  plt.ion()
  plt.show()
  plt.clf()
  plt.plot(range(1, len(ada_gd.cost_) + 1),
  ada_gd.cost_, marker='o')
  plt.xlabel('Epochs')
  plt.ylabel('Sum-squared-error')
  plt.tight_layout()
  plt.ion()
  plt.show()
  plt.clf()

  from chap2.adaline import AdalineSGD

  # The following code uses the Stochastic Gradient Descent
  # with the Adaline implementation
  ada_sgd = AdalineSGD(n_iter=15, eta=0.01, random_state=1)
  print(ada_sgd)
  ada_sgd.fit(X_std, y)
  plot_decision_regions(X_std, y, ada_sgd)
  plt.title('Adaline - Stochastic Gradient Descent')
  plt.xlabel('sepal length [standardized]')
  plt.ylabel('pedal length [standardized]')
  plt.tight_layout()
  plt.ion()
  # plt.ioff()
  plt.show()
  plt.plot(range(1, len(ada_sgd.cost_) + 1), ada_sgd.cost_, 
  marker='o')
  plt.xlabel('Epochs')
  plt.ylabel('Average Cost')
  plt.tight_layout()
  plt.show()
  # For some reason I cannot display the graphs so I am going to
  # just display the information on the console.
  print('ada_sgd.cost_')
  for ci, cost in enumerate(ada_sgd.cost_):
    print('{} - {}'.format(ci+1, cost))
