# Introduction

This is a simple command line menu module that can be used to with
command line applications that would like to include a text based
menu.

## Objective

The goal of this command line menu module is to provide a simple
texted based menu.  The menu includes menu items that can be an
action/command or a sub menu.  The module was designed to make
the addition of menu items to a menu be a simple process.  There
are only tree methods that can needed to create a menu.  They are:

* create_menu
* create_submenu
* add_menu_item_action

These methods will be explained in detail in the following sections.

### Create a Menu

The __create_menu__ method is used to create the menu that will be used
by the application.  The only requirement to create a menu is to 
pass the string that defines the menu being created.  You will also 
be required to pass the string that will be used by the menu exit method.
This will be displayed as part of the list of menu items that can be
selected.  The selection of this menu item will cause the menu to exit.

When the menu is created and all of the required menu items have been
added then the returned menu can be executed using the show command.

Here is an example of how this method can be used.

```python

from menucli import create_menu

menu = create_menu('Top Level Menu', 'Exit')
...

menu.show()

```

### Create a Sub-Menu

The __create_submenu__ method is used to create a sub-menu associated
with a given menu item.  The method expects three parameters.  The 
name/title of the sub menu, the exit string and the menu that this
sub-menu will be associated with.

The name/title will be used by the passed menu to display this menu
item when the menu selection list is generated.

The name/title will be displayed when the sub-menu is called by the
passed menu.

The exit string will be included as part of this sub-menu menu list
and when selected.  The menu will exit.

The menu passed is which menu the creating sub-menu will be associated
with.
 
Here is an example of how this method can be used.

```python

from menucli import create_menu, create_submenu

menu = create_menu('Top Level Menu', 'Exit')

submenu = create_submenu('Sub Menu', 'Exit', menu)
 ...
menu.show()

```

### Add a Menu Action

The __add_menu_item_action__ method will add a menu item that will
have a user specific action/command that will be executed when this
menu item is selected.

The method expects four parameters.  They are the menu that this 
menu item will be associated with.  This menu item title that will
be displayed as part of a menu menu list.  The action/command that
will be called.  This is either a class that implements a callable
method or a no-argument method.  Lastly, the top level menu is 
passed.  This is what is returned when the action/command has been
called by the created menu item.

Here is an example of how this method can be used.

```python
from menucli import create_menu, create_submenu

menu = create_menu('Top Level Menu', 'Exit')

def action_call():
    # Execute the user defined commands
    ...

add_menu_item_action(menu, 'Top Level Menu Action', action_call, menu)

submenu = create_submenu('Sub Menu', 'Exit', menu)

class CallableAction(object):
    def __call__(self):
        # Execute user defined commands
        ...

add_menu_item_action(submenu, 'Top Level Menu Action', CallableAction(), menu)

menu.show()

```
