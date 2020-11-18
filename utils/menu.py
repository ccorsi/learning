"""

This simple implementation will allow us to create a text based
menu feature that can be used to display and act on a given
menu item.  It will include the name of the menu item and its
associated action.

Design:
-------

As was stated above this implementation is fairly simple and
is only used within a console based application.  It is intended
to be a fairly easy to use implementation that minimizes the
effort required to generate a console menu and allow a developer
to focus on what they are trying to develop.

There are four methods that are required to create a menu.
They are:

  - create_menu
  - add_menu_item
  - add_menu_item_with_action
  - add_sub_menu

The add_sub_menu is really a helper method that combines
calls to the create_menu and add_menu_item methods.

The create_menu method is used to create a menu instance.
Menu instances can contain zero or more menu items.  Menu
items can be associated with another menu or with an action.
An action is basically a call to a non-argument method or
to a class instance that has a non-argument method implemented.

The add_menu_item is called menu to a parent menu.  This is
basically creating a child menu using the passed name.  A
top level menu create be created by only passing the name.

The add_menu_item_with_action method is used to create a
menu item that will perform an action/command.  The method
takes for arguments.  The first one is the menu that will
be associated this particular action/command.  The second
is the title/name of the menu item. Followed by a method 
or class instance that is callable.  Lastly, the final 
argument is that top level menu instance.  This tells the 
created menu item that after executing the action, it 
should then call the passed menu instance.

The add_sub_menu method is a helper class that uses the 
combination of the create_menu and add_menu_item methods.

def create_menu(name, parentMenu):

def add_menu_item_with_action(menu, title, action, mainMenu):

def add_menu_item(name, menu, parentMenu):

def add_sub_menu(name, menu, parentMenu):

TODO: The current implementation can end up generating a 
stack overflow error since after each menu call it does 
not start from the first menu call.  This needs to be 
resolved if this menu package can then be used extensively.

"""

class NotAMenu(object):
  """
  This is just a definition of a no action type menu reference.
  """
  def __init__(self,title):
    self._title = title

  def title(self):
    return self._title

  def __call__(self):
    pass

class Menu(object):
  """
  This is the top level class that is used to run the menu
  for the given application.  This is only required as a 
  starting point.  Every other menu items will use the 
  subsequently defined class.
  """
  def __init__(self,title,parent=NotAMenu('Exit'),items=None):
    """
    This constructor expects a tuple, preferably a list, 
    that contains the menu items associated with this menu.
    The menu can also be created using the add_menu_item method.

    While the title is used to display the current menu that
    is being processed.
    """
    self._items = items if items != None else []
    self._title = title
    self._parent = parent

  def title(self):
    return self._title

  def add_menu_item(self,item):
    """
    This method will expect a passed item of type menu item
    that will be used to generate the menu with.
    """
    self._items.append(item)

  def __call__(self):
    """
    This call will display this Menu title and the list of
    Menu Items that are associated with this particular Menu.
    """
    while (True):
      print()
      print('Menu:', self._title)
      print()
      for i,item in enumerate(self._items,1):
        print('\t{} - {}'.format(i,item.title()))
      print('\t{} - {}'.format(len(self._items) + 1, self._parent.title()))
      print()
      try:
        option = int(input('Select one of the above option: '))
        if (option > 0 and option <= len(self._items) + 1):
          break
        print('Option: {} is out of range'.format(option))
      except Exception as exc:
        print('Invalid option: {}'.format(exc))
    if (option <= len(self._items)):
      self._items[option-1]()
    elif (self._parent != None):
      self._parent()

  def __str__(self):
    return 'Menu(items={})'.format(self._items)

class MenuItem(object):
  """
   This class will associate a particular Menu Item
  with a given Menu.  It will use the calling mechanism
  to process the current Menu action and upon completion
  it will call the passed prior menu.
  """
  def __init__(self,title,action):
    self._action = action
    self._title = title
  
  def __call__(self):
    self._action()

  def title(self):
    return self._title
    
  def __str__(self):
    return 'MenuItem(title="{}",action={})'.format(self._title,self._action)

class Action(object):
  def __init__(self,action,mainMenu):
    self._action = action
    self._mainMenu = mainMenu

  def __call__(self):
    self._action()
    self._mainMenu()

def create_menu(name, ancestorMenu=NotAMenu('Exit')):
  """
  This method is used to create a menu and associate it
  with an ancestor menu, i.e., parent menu.  By default,
  it uses a ancestor menu that will just exit from the
  menu and return to the console prompt.  This is
  useful when creating the top-level menu.

  Args:
    name -  The name of the menu to be created
    ancestorMenu - The menu that this menu will be associated 
                   with

  Examples:
    top-level menu can be created as follows:
      menu = create_menu('Menu')
    create menu with ancestor menu:
      fileMenu = create_menu('File', menu)
  """
  menu =  Menu(name, parent=ancestorMenu)
  return menu

def add_menu_item_with_action(menu, title, action, mainMenu):
  """
  This will create a menu item that contains an action 
  that is defined by the user as a non-argument method
  call or a instance class with a non-argument callable
  method.

  Args:
    menu - menu that this menu item is associated to
    title - title of the menu item being created
    action - non-arg method or non-arg callable class instance
    mainMenu - top level menu
  
  Examples:
    Add an 'Open' menu item that will call the open_file
    method.

      add_menu_item_with_action(file, 'Open', open_file, main)
    
    where open_file is defined as:

      def open_file():
        ...

    Add an 'Save' menu item that will use an instance of the
      Save class.

      add_menu_item_with_action(file, 'Save', Save(), main)

    where Save is defined as:

      class Save(object):
        ....
        def __call__(self):
          ...
    
  """
  menuItem = MenuItem(title, Action(action, mainMenu))
  menu.add_menu_item(menuItem)
  return menuItem

def add_menu_item(name, menu, parentMenu):
  """
  This method will create a menu item associated with the
  passed menu and will then add the menu item to the passed
  parent menu. 

  The created menu item will execute the passed action/command
  that was passed.

  Args:
    name - name/title of the menu item
    menu - menu that the menu item will call when selected
    parentMenu - menu that the menu item is added to
  """
  menuItem = MenuItem(name, menu)
  parentMenu.add_menu_item(menuItem)
  return menuItem

def add_sub_menu(name, menu, parentMenu):
  """
  This method will will a sub-menu associated with 
  the parent menu.  The passed menu will be called 
  whenever the sub menu is selected.

  Args:
    name - name/title of the sub-menu
    menu - menu that the sub-menu will call when selected
    parentMenu - menu that the sub-menu will be added too.
  """
  submenu = create_menu('Sub-Menu', parentMenu)
  add_menu_item('Sub-Menu', submenu, menu )
  return submenu

def original_test_menu():
  main = Menu('Main')
  fileMenu = Menu('File',parent=main)
  def called():
    print('Called Open')
  openMenuItem = MenuItem('Open', Action(called, main))
  fileMenu.add_menu_item(openMenuItem)
  menuItem = MenuItem('File', fileMenu)
  main.add_menu_item(menuItem)
  main()

def test_menu():
  main = create_menu('Main')
  fileMenu = create_menu('File',main)
  add_menu_item_with_action(fileMenu,'Open',
    lambda:print('Called Open'), main)
  add_menu_item('File', fileMenu, main)
  main()

def test_sub_menus():
  main = create_menu('Menu')
  menu = create_menu('Top', main)
  add_menu_item_with_action(menu, 'Top Call',
    lambda:print('Called Top Call Menu Item'), main)
  add_menu_item('Top', menu, main)
  submenu = add_sub_menu('Sub-Menu', menu, main )
  add_menu_item_with_action(submenu, 'SubMenu Call',
    lambda:print('Called SubMenu Call Menu Item'), main)
  main()

if (__name__ == "__main__"):
  try:
    test_menu()
  except Exception as exc:
    print('An exception was raised while testing Menu feature',exc)