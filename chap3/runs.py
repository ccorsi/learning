"""
This file will contain the methods that can be called to 
run the different examples from Chapter 3 of the book 
Python Machine Learning by Sebastian Raschka.
"""

from utils.menu import create_menu, add_menu_item
from chap3.general import add_chapter_three_general_example_menu_items
from chap3.scikit import add_chapter_three_scikit_example_menu_items

def add_chapter_three_menu_items(menu,mainMenu):
  chap3 = create_menu('Chapter 3 Examples:', mainMenu)
  add_menu_item('Chapter 3 Examples', chap3, menu) 
  # Add Chapter 3 General Examples menu items
  add_chapter_three_general_example_menu_items(chap3,menu,mainMenu)
  # Add Chapter 3 Scikit Examples menu items
  add_chapter_three_scikit_example_menu_items(chap3, menu, mainMenu)
