"""
This file will contain all of the different menu driven
actions that can be called.  This also includes the 
methods that can be called.
"""

from utils.checks import checks, gt
from utils.menu import Menu, MenuItem, Action

class Simple(object):
  @checks({})
  def __init__(self):
    pass

  @classmethod
  @checks({})
  def cm(cls,a,b):
    pass

  @staticmethod
  @checks({})
  def sm(a,b):
    pass
  
  @checks({})
  def m(self,a,b):
    pass

  @checks({})
  def t(this,a,b):
    pass
  
@checks({'a':[gt(0)]})
def m(a,b):
  pass

from unittest import TestCase, TestSuite, main

class ChecksTestCase(TestCase):

  def test_method_check(self):
    m(7,8)

  def test_method_exception_check(self):
    with self.assertRaises(AssertionError):
      m(-7,8)

  def test_class_constructor(self):
    Simple()

  def test_class_instance_method(self):
    s = Simple()
    s.m(5,6)

  def test_class_static_method(self):  
    s = Simple()
    s.sm(3,4)

  def test_class_class_method(self):  
    s = Simple()
    s.cm(1,2)

  def test_class_instance_method_with_this_self(self):  
    s = Simple()
    s.t(9,10)

test_classes = []

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

def checks_tests():
  global test_classes
  test_classes = [ChecksTestCase]
  # execute tests within this module only and don't exit when done
  main(module=__name__, exit=False)

def menu_tests():
  global test_classes
  test_classes = []
  # execute tests within this module only and don't exit when done
  main(module=__name__, exit=False)

  from utils.menu import test_menu, test_sub_menus
  test_menu()
  test_sub_menus()

def all_tests():
  global test_classes
  test_classes = [ChecksTestCase]
  # execute tests within this module only and don't exit when done
  main(module=__name__, exit=False)

def add_utils_menu_items(parentMenu, mainMenu):
  utils = Menu('Utilities Tests', parent=parentMenu)
  utils.add_menu_item(MenuItem('Menu Tests', Action(menu_tests, mainMenu)))
  utils.add_menu_item(MenuItem('Checks Tests', Action(checks_tests, mainMenu)))
  utils.add_menu_item(MenuItem('All Utilities Tests', Action(all_tests, mainMenu)))
  parentMenu.add_menu_item(MenuItem('Utilities Tests:',utils))
