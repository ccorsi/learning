"""
This file will contain the methods that can be called to 
run the different tests for using environments within Replit.
"""

from utils.menu import Menu, MenuItem, add_menu_item, add_menu_item_with_action
from importlib import import_module
from unittest import TestCase, TestSuite, main

class CheckLibrariesTestCase(TestCase):

  def green(self,m):
    return '\033[1;32m{:s}\033[m'.format(m)

  def yellow(self,m):
    return '\033[1;33m{:s}\033[m'.format(m)

  def red(self,m):
    return '\033[1;31m{:s}\033[m'.format(m)

  def load_import(self,libname):
    import_module(libname)

  def test_load_numpy(self):
    self.load_import('numpy')

  def test_load_scipy(self):
    self.load_import('scipy')

  def test_load_matplotlib(self):
    self.load_import('matplotlib')

  def test_load_torch(self):
    self.load_import('torch')

  def test_load_tqdm(self):
    self.load_import('tqdm')

class NumpyArraysTestCase(TestCase):
  def test_array(self):
    import numpy as np
    print('Example using rand')
    print([ np.random.rand() for _ in range(10) ])
    print('Example using random')
    print(np.random.random([10]))

test_classes = [CheckLibrariesTestCase, NumpyArraysTestCase]

def load_tests(loader, tests, pattern):
  """
  The unittest module looks for this method within a module
  and provides it the necessary instances to add tests too.
  We just need to insure that we set the module name to this
  file module name.
  """
  global test_classes

  suite = TestSuite()
  for test_class in test_classes:
    suite.addTests(loader.loadTestsFromTestCase(test_class))
  return suite

def test_numpy_arrays():
  global test_classes
  test_classes = [NumpyArraysTestCase]
  # execute tests within this module only and don't exit when done
  main(module=__name__, exit=False)

def check_imports():
  print('Called check_numpy')
  global test_classes
  test_classes = [CheckLibrariesTestCase]
  # execute tests within this module only and don't exit when done
  main(module=__name__, exit=False)

def add_others_menu_items(parentMenu,mainMenu):
  # Create the new Menu that will be added to the parentMenu
  others = Menu('Others Examples:', parent=parentMenu)
  # Create MenuItems to be added to the newly created menu
  add_menu_item_with_action(others, 'Check Imports', check_imports, mainMenu)
  add_menu_item_with_action(others, 'Test Numpy Arrays', test_numpy_arrays, mainMenu)
  # Add menu to the parent menu
  add_menu_item('Others Examples', others, parentMenu)
