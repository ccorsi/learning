"""
Part of this code also comes from the book 

  Python Machine Learning, 3rd edition 
  by Sebastian Raschka  

All of the reentered/copied code from the above author book
is copyright w.r.t. the author.  All other code that does
not come from the book is copyright with respect to Claudio
Corsi.  A License will become associated with that code in
the near future.
"""
# general module imports
import sys
import traceback

if (__name__ == "__main__"):
  from utils.menu import create_menu
  from utils.runs import add_utils_menu_items
  from chap2.runs import add_chapter_two_menu_items
  from chap3.runs import add_chapter_three_menu_items
  from others.runs import add_others_menu_items
  from chap4.runs import add_chapter_four_menu_items
  from chap5.runs import add_chapter_five_menu_items
  
  menu = create_menu('Main')
  add_chapter_two_menu_items(menu, menu)
  add_chapter_three_menu_items(menu, menu)
  add_chapter_four_menu_items(menu, menu)
  add_chapter_five_menu_items(menu, menu)
  add_utils_menu_items(menu, menu)
  add_others_menu_items(menu, menu)

  try:
    menu()
  except Exception as ex:
    print('An exception was raised {}'.format(ex))
    traceback.print_exc(file=sys.stdout)
