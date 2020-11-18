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
Note that the AdalineGD class implements a single-layer neural network. 
This is based on Adaline rule (or Widrow-Hoff rule).

The AdalineGD compares the true class labels with the linear activation
function's continuous valued output to compute the model error and update
the weights, for the next training session, (epoch).

The AdalineGD class will update the weights using a linear activation 
function to update the weights.

The objective function is used to optimize the weights after each training
session.  This is often called the cost function that we want to minimize.
The cost function, J, is defined to learn the weights as the "sum of squared errors", (SSE), between the calculated and expected class values as:

  J(w) = 1/2 * sum((y-q(z))^2)

where y is the expected value and q is the cost function using input z.
To minimize this function, we need to use the "gradient descent" which
is the derivative of J. 

The weights will be updated using the following:

  w = w + dw

where dw is defined as the following:

  dw = -n * J'(w)

where J'(w) is defined as the following:

  J'(w) = - sum((a-q(z))) * xj

where the sum is over all of the values of y and xj is the specific value 
of the j-th x feature.  This is because this is the derivative of the
J(w) function with respect to the j-th feature.  We are taking the partial
derivative of the weights vector.

Note that the weight update is calculated based on all examples in the training set dataset, this is also know as "batch gradient descent".

It is important to realize that the setting on the eta parameter has a 
direct impact on how quickly we can find the best fitting model.  An eta
value that is too small will require many more iterations (epochs) to 
find the best model.  While an eta that is too large will overfit our 
model by swinging back and forth between the optimal model.  These two
concepts can be defined as underfitting and overfitting.  The particular
values of eta can produce one of these two extremes. It is then 
necessary to correclty choose the value of eta.  This class 
implementation currently does not provide a means to figure out the 
optimal value for eta.  Subsequent implements will show how this can be
done using the concept of "feature scaling".  Note that an example of 
performing "feature scaling" can be done using the AdalineGD class as is.
An example is shown in the run_adaline_test method call that is used.

"""
class AdalineGD(object):
    """
    ADAptive LInear NEuron classifier.

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
        self.cost_ = []

        for _ in range(self.n_iter):
            net_input = self.net_input(X)
            output = self.activation(net_input)
            errors = (y - output)
            self.w_[1:] += self.eta * X.T.dot(errors)
            self.w_[0] += self.eta * errors.sum()
            cost = (errors**2).sum() / 2.0
            self.cost_.append(cost)
        
        return self

    def net_input(self, X):
        """Calculate the net input"""
        return np.dot(X, self.w_[1:]) + self.w_[0]

    def activation(self, X):
        """Compute linear activation"""
        return X

    def predict(self, X):
        """Return class label after unit step"""
        return np.where(self.activation(self.net_input(X)) >= 0.0, 1, -1)

    def __str__(self):
        return "AdalineGD(eta={},n_iter={},random_state={})".format(self.eta, self.n_iter, self.random_state)

"""

The AdalineSGD implementation implements the concept of the "Stochastic 
Gradient Descent".

"""
class AdalineSGD(object):
  """
    ADAptive LInear NEuron classifier.

    Parameters:
    -----------
    eta : float
      - learning rate [0.0,1.0]
    n_iter : int
      - passes over the training set (epochs)
    shuffle : bool (default: True)
      - Shuffles training data every epoch if True to prevent cycles.
    random_state : int
      - random number seed used to initialize the weight

    Attributes:
    -----------

    w_ : ld-array
      - Weights after fitting
    cost_ : list
      - Sum-of-squares cost function value average over all training 
        examples in each epoch.
  """

  @checks({
      'eta': [checktype(float), closed(0.0, 1.0)],
      'n_iter': [checktype(int), gteq(1)],
      'random_state': [checktype(int), gteq(1)],
      'shuffle': [checktype(bool)]
  })
  def __init__(self, eta=0.01, n_iter=10, shuffle=True, random_state=None):
    self.eta = eta
    self.n_iter = n_iter
    self.shuffle = shuffle
    self.random_state = random_state
    self.w_initialized = False

  def fit(self, X, y):
    self._initialize_weights(X.shape[1])
    self.cost_ = []
    for _ in range(self.n_iter):
      if (self.shuffle):
        X, y = self._shuffle(X, y)
      cost = []
      for xi, target in zip(X, y):
        cost.append(self._update_weights(xi, target))
        avg_cost = sum(cost) / len(y)
        self.cost_.append(avg_cost)
    return self

  def partial_fit(self, X, y):
    """This method provides you the ability to learn in 
    real-time as well as being able to train the initial 
    model.  This is a good for the case that we don't have
    data about a particular case like a users likes and 
    dislike.  These cases require the model to be updated
    in real-time.
    For instance you can use this as follows:
    
      ada_sgd.partial_fit(X_std[0, :], y[0])
      
    """
    if (not self.w_initialized):
      self._initialize_weights(X.shape[1])
    if (y.ravel().shape[0] > 1):
      for xi, target in zip(X, y):
        self._update_weights(xi, target)
    else:
      self._update_weights(X, y)

    return self

  def _shuffle(self, X, y):
    r = self.rgen.permutation(len(y))
    return X[r], y[r]

  def _initialize_weights(self, m):
    """Initialize weights to small random numbers"""
    self.rgen = np.random.RandomState(self.random_state)
    self.w_ = self.rgen.normal(loc=0.0, scale=0.01, size=1 + m)
    self.w_initialized = True

  def _update_weights(self, xi, target):
    output = self.activation(self.net_input(xi))
    error = (target - output)
    self.w_[1:] += self.eta * xi.dot(error)
    self.w_[0] += self.eta * error
    cost = 0.5 * error**2
    return cost

  def net_input(self, X):
    return np.dot(X, self.w_[1:]) + self.w_[0]

  def activation(self, X):
    return X

  def predict(self, X):
    return np.where(self.activation(self.net_input(X)) >= 0, 1, -1)

  def __str__(self):
    return 'AdalineSGD(eta={},n_iter={},shuffle={},w_initialized={},random_state={})'.format(self.eta, self.n_iter, self.shuffle, self.w_initialized,self.random_state)
