"""
This code comes from the book 

  Python Machine Learning, 3rd edition 
  by Sebastian Raschka  

All of the following code is copyright w.r.t. the above author.
While the copy has not been copied directly from its github source.
It is being copied manually to provide a better understanding of
what is being implemented.  While it also offered me the chance to
enhance the code with my own idiosyncrasy.

"""

import numpy as np

from utils.checks import checks, checktype, closed, gteq

"""

This class implements the Logistic Regression classifier 
using the logistic sigmoid function.

"""
class LogisticRegressionGD(object):
  """
    Logistic Regression classifier using Gradient Descent.

    Parameters:
    -----------
    eta : float
      - learning rate [0.0,1.0]
    n_iter : int
      - passes over the training set (epochs)
    random_state : int
      - random number seed used to initialize the weight

    Attributes:
    -----------

    w_ : ld-array
      - Weights after fitting
    cost_ : list
      - Logistoc cost function value in each epoch
"""

  @checks({
    'eta': [checktype(float), closed(0.0, 1.0)],
    'n_iter': [checktype(int), gteq(1)],
    'random_state': [checktype(int), gteq(1)]
  })
  def __init__(self, eta=0.01, n_iter=100, random_state=1):
    self.eta = eta
    self.n_iter = n_iter
    self.random_state = random_state

  def fit(self, X, y):
    """
Fit the training data

Parameters:
-----------
X : {array-like}, shape = [n_examples, n_features]
  Training vectors, where n_examples is the number of 
  examples and n_features is the number of features.
y : array-like, shape = [n_examples] 
"""
    rgen = np.random.RandomState(self.random_state)
    self.w_ = rgen.normal(loc=0.0, scale=0.01, size=1 + X.shape[1])
    self.cost_ = []

    for _ in range(self.n_iter):
        net_input = self.net_input(X)
        output = self.activation(net_input)
        errors = (y - output)
        self.w_[1:] += self.eta * X.T.dot(errors)
        self.w_[0] += self.eta * errors.sum()
        # note that we are computing the 'cost' instead
        # of the sum of squared errors cost.
        cost = (-y.dot(np.log(output)) - ((1 - y).dot(np.log(1-output))))
        self.cost_.append(cost)
    
    return self

  def net_input(self, X):
    """Calculate the net input"""
    return np.dot(X, self.w_[1:]) + self.w_[0]

  def activation(self, z):
    """Compute logistic sigmoid actication"""
    return (1.0 / (1.0 + np.exp(-np.clip(z, -250, 250))))

  def predict(self, X):
    """Return class label after unit step"""
    return np.where(self.net_input(X) >= 0.0, 1, -1)
    # this is equivalent to:
    # return np.where(self.activation(self.net_input(X)) >= 0.0, 1, -1)

  def __str__(self):
    return "LogisticRegressionGD(eta={},n_iter={},random_state={})".format(self.eta, self.n_iter, self.random_state)
