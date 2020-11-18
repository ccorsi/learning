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
Note that the Perceptron class implements a single-layer neural network. 
This is based on Rosenblatt's perceptron rule.

The perceptron compares the true class labels to the predicted class labels to update the weights for the next training session, (epoch).

The Perceptron class will update the weights using a unit step function
that includes the learning rate which is defined as the eta field on the
class to update the weights.

Specifically for each feature weight, w, it uses the actual, a, and predicted, p, values and uses the learning rate, eta, such that:

    w = eta * (a - p)

where w is associated to the W weight that is applied to each feature. 
"""


class Perceptron(object):
    """
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
    errors_ : list
      - Number of misclassifications (updates) in each epoch
"""

    @checks({
        'eta': [checktype(float), closed(0.0, 1.0)],
        'n_iter': [checktype(int), gteq(1)],
        'random_state': [checktype(int), gteq(1)]
    })
    def __init__(self, eta=0.01, n_iter=50, random_state=1):
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
        self.errors_ = []

        for _ in range(self.n_iter):
            errors = 0
            for xi, target in zip(X, y):
                update = self.eta * (target - self.predict(xi))
                self.w_[1:] += update * xi
                self.w_[0] += update
                errors += int(update != 0.0)
            self.errors_.append(errors)

        return self

    def net_input(self, X):
        """Calculate the net input"""
        return np.dot(X, self.w_[1:]) + self.w_[0]

    def predict(self, X):
        """Return class label after unit step"""
        return np.where(self.net_input(X) >= 0.0, 1, -1)

    def __str__(self):
        return "Perceptron(eta={},n_iter={},random_state={})".format(self.eta, self.n_iter, self.random_state)
