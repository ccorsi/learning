"""
This contains general tools methods and classes that will be
used throughout the different code examples of this repository.
"""

import requests
# Used to read text data
from io import StringIO
# Used to read binary data
# from io import BytesIO
from pathlib import Path

# specific machine learning type imports
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

def get_data(url,fname):
  """
  This method will be used to determine if the
  file exists locally.  If it does, it will 
  return an IOBase type instance of that file
  or it will download the file using the url
  and store it to the file location.
  """
  p = Path(fname)
  if (p.exists()):
    print('File:',fname,'already exists.')
    return p.open()
  else:
    print('File:',fname,'does not exist, downloading file from ',url)
    # Get the required data
    r = requests.get(url)
    if (r.status_code == 200):
      # create subdirectory if none exist.
      Path(p.parent).mkdir(parents=True)
      print('File was successfully downloaded.')
      p.write_bytes(r.content)
      return p.open()
    else:
      print('File was not successfully downloaded status:',r.status_code,'with status',r.status)
      return StringIO('')

"""

This method will expect metric input data, X, and expected output
value, y.  It will use the passed classifier and resolution to 
generate the decision regions for the passed data.

"""
def plot_decision_regions(X, y, classifier, test_idx=None, resolution=0.02):
  # setup marker generator and color map
  markers = ( 's', 'x', 'o', '^', 'v' )
  colors = ('red', 'blue', 'lightgreen', 'gray', 'cyan')
  # This does not work with the case that there are more
  # unique y elements than colors.
  cmap = ListedColormap(colors[:len(np.unique(y))])

  # plot the decision surface 
  x1_min, x1_max = X[:, 0].min() - 1, X[:, 0].max() + 1
  x2_min, x2_max = X[:, 1].min() - 1, X[:, 1].max() + 1

  xx1, xx2 = np.meshgrid(np.arange(x1_min,x1_max,resolution),np.arange(x2_min,x2_max,resolution))

  Z = classifier.predict(np.array([xx1.ravel(), xx2.ravel()]).T)
  Z = Z.reshape(xx1.shape)
  
  plt.contourf(xx1, xx2, Z, alpha=0.3, cmap=cmap)
  plt.xlim(xx1.min(), xx1.max())
  plt.ylim(xx2.min(), xx2.max())

  # plot class examples
  for idx, cl in enumerate(np.unique(y)):
    plt.scatter(x=X[y == cl, 0],
                y=X[y == cl, 1],
                alpha=0.1,
                c=colors[idx],
                marker=markers[idx],
                label=cl,
                edgecolor='black')

  # Highlight the test examples
  if (test_idx != None):
    # plot all examples
    # X_test, y_test = X[test_idx, :], y[test_idx]
    X_test, _ = X[test_idx, :], y[test_idx]

    plt.scatter(X_test[:, 0], X_test[:, 1], c=[],
    edgecolor='black', alpha=1.0, linewidth=1, marker='o',
    s=100, label='test set')
