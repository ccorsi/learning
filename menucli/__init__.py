
import os
import sys

"""
MIT License

Copyright (c) 2020 Claudio Corsi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

"""

__all__ = ["create_menu", "create_submenu", "add_menu_item_action"]
__version__ = '2020.11.14'
__author__ = 'Claudio Corsi'

"""

This simple implementation will allow you to create a text based
menu that can be used to display and act on a given menu item.
It will include the name of the menu item and its associated
action.

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
  - create_submenu
  - add_menu_item_with_action

The create_menu method is used to create a top level menu item
instance.  Menu instances can contain zero or more menu items.
Menu items can be associated with another menu or with an action.
An action is basically a call to a no-argument method or
to a class instance that has a no-argument callable method
implementation.

The add_menu_item_with_action method is used to create a
menu item that will perform an action/command.  The method
takes four arguments.  The first one is the menu item that
will be associated with this particular action/command.
The second parameter is the title/name of the menu item. 
Followed by a no-argument method or a callable class instance.
Lastly, the final argument is the top level menu instance.  
This tells the created menu item that after executing the action,
it should then return the passed menu item instance.

def create_menu(title, exit_title):

def create_submenu(title, exit_title, parent_menu_item=None):

def add_menu_item_action(menu_item, title, action, next_menu_item):

"""


value = os.getenv("MEMUCLI_TEST")

if value is not None:
    end_line = '\n'
else:
    end_line = ''


def _select_menu_item(title, items):
    global end_line

    while True:
        print()
        print('Menu:', title)
        print()
        for i, item in enumerate(items, 1):
            # print('type:', type(item))
            print('\t{} - {}'.format(i, item.title()))
        print()
        try:
            print('Select one of the above option: ', end=end_line)
            option = int(input(''))
            if option > 0 and (option <= len(items)):
                return items[option - 1]
            print('Option: {} is out of range'.format(option))
        except Exception as exception:
            print('Invalid option: {}'.format(exception), file=sys.stderr)


class _Menu(object):
    """
    This is the top level menu class that is used to execute
    the menu commands.  This is only required as a starting
    point.  This class will contain the different menu items
    that a user can select.  These are added using the
    add_menu_item method.  The menu is executed as a regular
    method call since it implements the callable protocol.
    """

    def __init__(self, title, exitTitle='Exit', items=None):
        """
        This constructor expects a tuple, preferably a list,
        that contains the menu items associated with this menu.
        The menu can also be created using the add_menu_item method.

        Args:
            title:      The title of this menu
            exitTitle:  The title of the exit menu item
            items:      A tuple containing one or more menu items
                        associated with this menu

        Note that the an exit menu item will be added to this menu
        as soon as it is called.  The user does not required explicitly
        add an Exit menu item.

        """
        self._items = items if items is not None else []
        self._title = title
        self._exit_title = exitTitle
        self._add_exit_menu_item = False

    def title(self):
        return self._title

    def add_menu_item(self, item):
        """
        This method will expect a passed item of type menu item
        that will be used to generate the menu with.
        """
        self._items.append(item)

    def items(self):
        return self._items

    def __call__(self):
        # print('Calling _Menu')
        """
        This call will display this Menu title and the list of
        Menu Items that are associated with this particular Menu.

        It will then execute each selected menu item until the
        Exit menu item was called.  At that time, the menu call
        will return to the user.

        """

        if self._add_exit_menu_item is False:
            self._add_exit_menu_item = True
            if self._exit_title is not None:
                self._items.append(_ExitMenuItem(self._exit_title))

        item = _TopMenuItem(self)

        while item is not None:
            # Call the selected item
            item = item()

    def __str__(self):
        return 'Menu(items={})'.format(self._items)


class _TopMenuItem(object):
    """
    This class is used to enable the addition of the Menu instance to be
    included as part of the menu items that can be called by the Menu instance
    callable method.
    """

    def __init__(self, menu):
        """
        The Menu instance is passed to the constructor and will be used
        to process that calls associated with it.
        """
        self._menu = menu

    def __call__(self, *args, **kwargs):
        # print('Calling _TopMenuItem')
        return _select_menu_item(self._menu.title(), self._menu.items())

    def title(self):
        return self._menu.title()

    def items(self):
        return self._menu.items()

    def add_menu_item(self, item):
        """
        This method will expect a menu item to be passed
        that will be used to generate the menu with.
        """
        self._menu.add_menu_item(item)

    def show(self):
        self._menu()


class _ExitMenuItem(object):
    """
    This class is used to exit from the menu calls.  It is just a convenient
    way of adding an exit menu item option to the menu
    """

    def __init__(self, title):
        self._title = title
        self._items = []

    def title(self):
        return self._title

    def items(self):
        return self._items

    def __call__(self, *args, **kwargs):
        # print('Calling _ExitMenuItem')
        return None


class _MenuItem(object):
    """
    This class will control which item that the Menu class should
    execute.  It will call the passed item to determine which
    actions the Menu class is supposed to call.

    Args:
        item - Callable class that will return which action the
                menu instance is supposed to call.  This will
                return None if there is no action to be called.
    """

    def __init__(self, item):
        # This is callable class
        self._item = item

    def __call__(self, *args, **kwargs):
        # print('Calling _MenuItem')
        return self._item()

    def add_menu_item(self, item):
        self._item.add_menu_item(item)

    def title(self):
        return self._item.title()

    def items(self):
        return self._item.items()


class _Action(object):
    """
    This class is used to actually execute the command for one of
    the child menu items.  It will call the passed action and then
    return the passed menu item.
    """

    def __init__(self, action, item):
        """
        This constructor will execute the passed callable action
        and return the passed menu item.

        Args:
            action: A parameterless callable class or method that
                    will be called when this action callable method
                    is called.
            item:   The menu item that will be return when the action
                    was called by this class callable method.
        """
        self._action = action
        self._item = item

    def __call__(self, *args, **kwargs):
        # print('Calling _Action')
        # Call the associated action call
        self._action()
        return self._item


class _MenuAction(object):
    """
    This class will actually call the particular action that
    is associated with a child of the Menu.  It will then
    return the associated item that will be called after
    this call is performed.  That item will probably be
    the top menu item.
    """

    def __init__(self, title, action, item):
        """
        This constructor will execute the passed callable action
        and return the passed menu item.

        Args:
            title:  The name of this menu item to be displayed when
                    the menu list is created.
            action: A parameterless callable class or method that
                    will be called when this action callable method
                    is called.
            item:   The menu item that will be return when the action
                    was called by this class callable method.
        """
        self._title = title
        self._action = action
        self._item = item

    def title(self):
        return self._title

    def items(self):
        # TODO: do I need this call???
        return [self._item]

    def __call__(self, *args, **kwargs):
        # print('Calling _MenuAction')
        self._action()
        return self._item


class _SubMenu(object):
    def __init__(self, title, exit_title='Exit', parentMenu=None, items=None):
        """
        This constructor expects a tuple, preferably a list,
        that contains the menu items associated with this menu.
        The menu can also be created using the add_menu_item method.

        While the title is used to display the current menu that
        is being processed.
        """
        self._items = items if items is not None else []
        self._title = title
        self._parentMenu = parentMenu
        self._exit_title = exit_title
        self._appended = False

    def __call__(self, *args, **kwargs):
        """
        This call will display this Menu title and the list of
        Menu Items that are associated with this particular Menu.
        """
        # print('Calling _SubMenu')
        if self._appended is False:
            self._appended = True
            if self._parentMenu is not None:
                self._items.append(self._parentMenu)
            if self._exit_title is not None:
                self._items.append(_ExitMenuItem(self._exit_title))

        return _select_menu_item(self._title, self._items)

    def add_menu_item(self, item):
        self._items.append(item)

    def title(self):
        return self._title

    def items(self):
        return self._items


def create_menu(title, exit_title):
    """
    This method is used to create the Menu instance that will be used
    to execute the command line menu.

    Args:
        title:      This Menu Title will be displayed when the menu
                    is being executed
        exit_title: The Exit title that will be displayed when the
                    menu is being displayed.  This string will be
                    associated with the menu item that will exit
                    from the menu call.
    """
    menu = _Menu(title, exit_title)
    return _TopMenuItem(menu)


def create_submenu(title, exit_title, parent_menu_item=None):
    """
    This method is used to create a sub-menu that is associated
    with a given menu item.

    Args:
        title:              The title that will be displayed for
                            this sub-menu
        exit_title:         The title that will be displayed for
                            this sub-menu exit call
        parent_menu_item:   This menu item parent menu item, this
                            is usually the top level menu item
    """
    submenu = _SubMenu(title, exit_title, parent_menu_item)
    submenu_item = _MenuItem(submenu)
    parent_menu_item.add_menu_item(submenu_item)
    return submenu_item


def add_menu_item_action(menu_item, title, action, next_menu_item):
    """
    This method will add an menu action item to the passed menu item.

    Args:
        menu_item:      The menu item that the action is associated too
        title:          The title that this menu item will display
        action:         A callable action class or method that will be
                        called when this menu item is selected
        next_menu_item: The subsequent menu item that will be returned
                        upon calling the passed action
    """
    menu_item.add_menu_item(_MenuAction(title, action, next_menu_item))
