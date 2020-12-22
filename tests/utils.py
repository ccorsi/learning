import os
import re
import sys
from subprocess import Popen, PIPE;
from threading import Thread;
from contract import contract


def callme(m):
    print('Inside the method callme')
    print('With message {}'.format(m))
    print('Enter something')
    value = input('')
    print('1 - The returned input is [{}]'.format(value))
    print('Enter something')
    value = input('')
    print('2 - The returned input is [{}]'.format(value))


def load_and_execute():
    if len(sys.argv) < 3:
        print('Invalid number of command line parameters', sys.argv, file=sys.stderr)
        return

    # We ask the user to enter the name of the module to be loaded
    module_name, method_name = sys.argv[1], sys.argv[2]

    try:
        import importlib
        lib = importlib.import_module(module_name)
    except Exception as err:
        print("An exception was raised when loading module {} - {}".format(module_name, err), file=sys.stderr)
        return

    from inspect import getmembers
    functions = getmembers(lib)
    if hasattr(lib, method_name):
        attr = getattr(lib, method_name)
        parameters = dict()
        for parameter in sys.argv[3:]:
            name_value = parameter.split('=')
            parameters[name_value[0]] = name_value[1]
        try:
            attr(**parameters)
        except Exception as err:
            print("An exception was raised in module {} when calling method {} - {}".format(module_name, method_name,
                                                                                            err), file=sys.stderr)
    else:
        print("The module {} does not contain method {}".format(module_name, method_name), file=sys.stderr)


class checkList(object):
    def __init__(self, parameter_name):
        self._parameter_name = parameter_name

    def __call__(self, v):
        assert isinstance(v, list), 'Parameter {} has to be a list type'.format(self._parameter_name)


class checkNone(object):
    def __init__(self, parameter_name):
        self._parameter_name = parameter_name

    def __call__(self, v):
        assert v != None, 'Parameter {} cannot be set to None'.format(self._parameter_name)


@contract({
    'module': [checkNone('module')],
    'method': [checkNone('method')],
    'parameters': [checkNone, checkList('parameters')]
})
def execute(module, method, parameters=[]):
    """
    This method will generate a command line that will call this module main method.  The main
    method will then load the passed module and call the passed method.  It will also pass
    the values of the parameters.  The parameters need to be define as <name>=<value> and be
    stored within a list.  These parameters will be added to the command line.  Which will
    then be passed to the method within the sub-process.

    :param module:  The module to load within the sub-process
    :param method:  The name of the method being called within the passed module
    :param parameters:  Parameters to be passed to the calling method
    :return: The Process object
    """
    os.putenv('MEMUCLI_TEST','TRUE')

    command = [sys.executable, os.path.abspath(__file__), module, method] + parameters
    print('Executing command line: {}'.format(command))
    proc = Popen(command, universal_newlines=True, stdout=PIPE, stderr=PIPE, stdin=PIPE)
    return proc


class ProcessStreamThread(Thread):
    """
    This thread class is used to read input from the passed process
    for the given stream. It will then forward the input to the passed
    callable.
    """

    @contract({'process': [checkNone], 'stream': [checkNone], 'callback': [checkNone]})
    def __init__(self, process, stream, callback):
        """
        :param process:
        :param stream:
        :param callback:
        """
        Thread.__init__(self)
        self._process = process
        self._stream = stream
        self._callback = callback

    def run(self):
        while True:
            line = self._stream.readline()
            if line == '':
                # reached the EOF file thus we are done
                return
            # Pass the read line to the callback method
            self._callback(self._process, line.rstrip('\n'))


def start_process(module_name, method_name, callback_stdout, callback_stderr):
    """
    This method will create a sub process that will call the utils module.  It
    will pass the following parameters.  The module name, the method name in the
    pass module and parameters to be passed to the method.

    :param module_name:  The name of the module to load
    :param method_name:  The name of the method to be called
    :param callback_stdout:  The standard output callback
    :param callback_stderr:  The standard error callback
    :return:  The standard output and standard error thread instances
    """
    process = execute(module_name, method_name)
    stdout_thread = ProcessStreamThread(process, process.stdout, callback_stdout)
    stderr_thread = ProcessStreamThread(process, process.stderr, callback_stderr)
    stdout_thread.start()
    stderr_thread.start()
    stdout_thread.join()
    stderr_thread.join()

    return stdout_thread, stderr_thread


if __name__ == "__main__":
    print('We are going to test the multi processing package')

    if len(sys.argv) == 1:
        print('Inside parent process with args', sys.argv)
        proc = execute('utils', 'callme', ['m=Hello, it is a cruel world'])


        class Output(object):
            def __call__(self, process, line):
                print('out: {}'.format(line))
                if line.find('Enter something') != -1:
                    print('Sending some input')
                    process.stdin.write('Here is something\n')
                    process.stdin.flush()


        class Error(object):
            def __call__(self, process, line):
                print('err: {}'.format(line))


        o = ProcessStreamThread(proc, proc.stdout, Output())
        e = ProcessStreamThread(proc, proc.stderr, Error())
        o.start()
        e.start()
        o.join()
        e.join()

        execute('module_name', 'method_name', list(['arg1', 'arg2', 'arg3']))
    else:
        load_and_execute()


number_regex = re.compile('[0-9]+')


def extract_option_number(line):
    global number_regex

    m = number_regex.search(line)
    # assert m is not None, 'Did not find any integers in line: {}'.format(line)

    if m is None:
        return None
    else:
        return m.group(0)
