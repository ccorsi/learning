
from menucli import create_menu, create_submenu, add_menu_item_action

def test_new_menu():
    print('Called test new menu function')




class Called(object):
    def __init__(self, message):
        self._message = message

    def __call__(self, *args, **kwargs):
        print(self._message)
        import traceback
        traceback.print_stack()


def test_new_menu_method():
    topmenuitem = create_menu('Top Menu', 'Exit')
    submenuitem = create_submenu('SubMenu', 'Exit', topmenuitem)
    subsubmenuitem = create_submenu('SubSubMenu', 'Exit', submenuitem)
    add_menu_item_action(topmenuitem, 'CallMe', Called('Called action'), topmenuitem)
    add_menu_item_action(submenuitem, 'CallMeSubMenu', Called('Called submenu action'), topmenuitem)
    add_menu_item_action(subsubmenuitem, 'CallMeSubSubMenu', Called('Called subsubmenu action'), topmenuitem)
    add_menu_item_action(topmenuitem, 'CallMe2', Called('Called2 action'), topmenuitem)
    topmenuitem.show()


def test_new_menu():
    menu = _Menu('Top Menu', 'Exit')
    topmenu = _TopMenuItem(menu)
    submenu = _SubMenu('SubMenu', 'Exit')
    item = _MenuItem(submenu)
    menu.add_menu_item(item)
    menu.add_menu_item(_MenuAction('Call Me', lambda: print('Called action'), topmenu))
    menu()



def test_menu():
    main = create_menu('Main')
    fileMenu = create_menu('File', main)
    add_menu_item_with_action(fileMenu, 'Open',
                              lambda: print('Called Open'), main)
    add_menu_item('File', fileMenu, main)
    main()


def test_sub_menus():
    main = create_menu('Menu')
    menu = create_menu('Top', main)
    add_menu_item_with_action(menu, 'Top Call',
                              lambda: print('Called Top Call Menu Item'), main)
    add_menu_item('Top', menu, main)
    submenu = add_sub_menu('Sub-Menu', menu, main)
    add_menu_item_with_action(submenu, 'SubMenu Call',
                              lambda: print('Called SubMenu Call Menu Item'), main)
    main()


# if __name__ == "__main__":
#     try:
#         print('Calling test_new_menu_method')
#         test_new_menu_method()
#         # test_new_menu()
#     except Exception as exception:
#         print('An exception was raised when executing new menu module', exception)


if __name__ == "__main__":
    print('Calling the test script')
    try:
        # menucli.test_new_menu()
        test_new_menu_method()
    except Exception:
        import traceback
        traceback.print_exc()
