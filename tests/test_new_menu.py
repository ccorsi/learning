#!/bin/env python

from menucli import create_menu, create_submenu, add_menu_item_action
from tests.utils import extract_option_number
from utils import start_process


def test_new_menu():
    menu = create_menu('Top Menu', 'Exit')


def test_create_submenu():
    menu = create_menu('Top Menu', 'Exit')
    submenu = create_submenu('Sub Menu', 'Exit', menu)


class Called(object):
    def __init__(self, message):
        self._message = message

    def __call__(self, *args, **kwargs):
        print(self._message)
        # import traceback
        # traceback.print_stack()


def create_test_menu():
    topmenuitem = create_menu('Top Menu', 'Exit')
    submenuitem = create_submenu('Level One Menu', 'Exit', topmenuitem)
    subsubmenuitem = create_submenu('Level Two Menu', 'Exit', submenuitem)
    add_menu_item_action(topmenuitem, 'TopLevelMenuItemOne', Called('Called action'), topmenuitem)
    add_menu_item_action(submenuitem, 'LevelTwoMenuItemOne', Called('Called submenu action'), topmenuitem)
    add_menu_item_action(subsubmenuitem, 'LevelThreeMenuItemOne', Called('Called subsubmenu action'), topmenuitem)
    add_menu_item_action(topmenuitem, 'TopLevelMenuItemTwo', Called('Called2 action'), topmenuitem)
    topmenuitem.show()


class SendOptions(object):

    def __init__(self, options=None, keep=False):
        self._options = [] if options is None else options
        self._count = 0
        self._option = ''
        self._lines = []
        self._keep = keep

    def __call__(self, process, line):
        print("out: {}".format(line))
        if len(line) > 0 and self._keep is True:
            self._lines.append(line)
        if line.find('Select one of the above option') != -1:
            print('Sending menu option: {}'.format(self._option))
            process.stdin.write('{}\n'.format(self._option))
            process.stdin.flush()
            self._count += 1
            self._option = ''
        elif self._count < len(self._options):
            if line.find(self._options[self._count]) != -1:
                self._option = extract_option_number(line)

    def __contains__(self, value):
        for line in self._lines:
            if line.find(value) != -1:
                return True

        print('Did not find the string [{}] within the output: {}'.format(value, self._lines))
        return False

class SendExit(object):

    def __call__(self, process, line):
        print('out: {}'.format(line))
        if line.find('Select one of the above option') != -1:
            print('Sending menu option: {}'.format(self._option))
            process.stdin.write('{}\n'.format(self._option))
            process.stdin.flush()
        elif line.find('Exit') != -1:
            self._option = extract_option_number(line)


class ProcessErrors(object):
    def __init__(self):
        self._hasError = False

    def __call__(self, process, line):
        print('err: {}'.format(line))
        self._hasError = True
        self._errors = [line] if self._errors is None else self._errors.append(line)

    @property
    def hasError(self):
        return self._hasError

    @property
    def error(self):
        return self._errors


def test_new_menu_method():
    errors = ProcessErrors()
    output = SendOptions(['Exit'])

    start_process(__name__, 'create_test_menu', output, errors)

    assert errors.hasError is False, 'Errors were raised when running test'


def test_sub_menus():
    errors = ProcessErrors()
    output = SendOptions(['Level One Menu', 'Exit'])

    start_process(__name__, 'create_test_menu', output, errors)

    assert errors.hasError is False, 'Errors were raised when running test with error: {}'.format(errors.error)


def test_level_two_menu_item():
    errors = ProcessErrors()
    output = SendOptions(['Level One Menu', 'Level Two Menu', 'LevelThreeMenuItemOne', 'Exit'], True)

    start_process(__name__, 'create_test_menu', output, errors)

    assert errors.hasError is False, 'Errors were raised when running test with error: {}'.format(errors.error)

    assert 'Called subsubmenu action' in output, 'Expected Menu Item was not called for menu item LevelThreeMenuItemOne'


def test_regular_expression_with_number():
    v = extract_option_number('\t4 - Exit')
    assert v == '4', 'Did not find option 4'


def test_regular_expression_without_number():
    v = extract_option_number('\tNo number value')
    assert v is None, 'Was not supposed to a number value'


if __name__ == "__main__":
    print('Calling the test script')
    try:
        # menucli.test_new_menu()
        test_new_menu_method()
    except Exception:
        import traceback

        traceback.print_exc()
