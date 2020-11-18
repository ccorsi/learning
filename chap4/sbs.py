"""
This file contains the implementation of the "Squential backward selection" algorithm.  The algorithim aims to 
return the number of initial features of a model such that
is does not affect the classifier performance while improving 
the performance of the model.

The model uses a "criterian function" that is uses to determine
which feature can be removed from the set of current features. 
This process is done iteratively and with the use of the 
greedy algorithm concept.  At each step to removes the feature 
that has the least performance loss.  This process is continued
until it has reduced the number of features the requested 
amount.

Here is the algorithm using a criterian function J:

  1 - Initialize the algorithm with current feature dimension 
      k=d, where d is the initial number of features for the 
      sample space X_d.

  2 - Determine the feature x_, that maximizes the criterian, 
      x_ = argmax J(X_k - x), where x element of X_k

  3 - Remove feature x_ from the current feature set such that 
      X_k becomes X_k-1.

  4 - While k is not the desired number of features then goto 
      step 2.

Note that this class is used to purge one or more features from
the feature set to generate as good or better model than using
the full feature set.  The reduction in features will provide 
a performance boost that can be beneficial in the case that 
we are dealing with a lot of different features associalted 
with our model.

NOTE that this is only one example of a feature selection 
algorithm.  There are others that can be implemented/used.
The scikit library has more information pertaining to the  
ones that they implement at:

  https://scikit-learn.org/stable/modules/feature_selection.html

There are also several implementations of these type of 
algorithims at the following:

  http://rasbt.github.io/mlxtend/user_guide/feature_selection/SequentialFeatureSelector/

"""

import numpy as np

from itertools import combinations
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split

class SBS(object):
  """
  This class implements the Sequential Backward Selection 
  algorithm.
  """
  def __init__(self, estimator, k_features,          
               scoring=accuracy_score, test_size=0.25,
               random_state=1, debug=False):
    self.scoring = scoring
    self.estimator = estimator
    self.k_features = k_features
    self.test_size = test_size
    self.random_state = random_state
    self.debug_ = debug

  def fit(self, X, y):
    # We are separating our dataset into training and testing
    # datasets to help determine the best number of features 
    # that should be keep for the desired number of features.
    # The passed dataset is also called the
    # "validation dataset".  Since we want to avoid using its
    # associated test dataset.  That will be used to determine
    # how good our remaining set of features will fair with
    # the test dataset that was not passed to this method.
    X_train, X_test, y_train, y_test =  \
      train_test_split(X, y, test_size=self.test_size,
                      random_state=self.random_state)
    
    # gather the current sample space feature size
    dim = X_train.shape[1]
    self.indices_ = tuple(range(dim))
    self.subsets_ = [self.indices_]
    # Calculate the criterian on the using the full set of 
    # features of the sample space
    score = self._calc_score(X_train, X_test, y_train, y_test, 
                             self.indices_)
    if self.debug_ == True:
      print('dim',dim,'score',score,'indices',self.indices_)
    # store its score
    self.scores_ = [score]

    while dim > self.k_features:
      scores = []
      subsets = []

      for p in combinations(self.indices_, r=dim - 1):
        score = self._calc_score(X_train, X_test, y_train, 
                                 y_test, p)
        scores.append(score)
        subsets.append(p)

      best = np.argmax(scores)
      self.indices_ = subsets[best]
      self.subsets_.append(self.indices_)
      dim -= 1
      if self.debug_ == True:
        print('dim',dim,'best',best,'scores[best]',scores[best],'indices',self.indices_)

      self.scores_.append(scores[best])

    self.k_score_ = self.scores_[-1]

    return self

  def transform(self, X):
    return X[:, self.indices_]

  def _calc_score(self, X_train, X_test, y_train, y_test, 
                  indices):
    self.estimator.fit(X_train[:, indices], y_train)
    y_pred = self.estimator.predict(X_test[:, indices])
    score = self.scoring(y_test, y_pred)
    return score
