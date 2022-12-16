import os
import sys
import inspect
from pathlib import Path


def scriptinfo():
    """
    Returns a dictionary with information about the running top level Python
    script:
    ---------------------------------------------------------------------------
    dir:    directory containing script or compiled executable
    name:   name of script or executable
    source: name of source code file
    ---------------------------------------------------------------------------
    "name" and "source" are identical if and only if running interpreted code.
    When running code compiled by py2exe or cx_freeze, "source" contains
    the name of the originating Python script.
    If compiled by PyInstaller, "source" contains no meaningful information.
    """

    # ---------------------------------------------------------------------------
    # scan through call stack for caller information
    # ---------------------------------------------------------------------------
    for teil in inspect.stack():
        # skip system calls
        if teil[1].startswith("<"):
            continue
        if teil[1].upper().startswith(sys.exec_prefix.upper()):
            continue
        trc = teil[1]

    # trc contains highest level calling script name
    # check if we have been compiled
    if getattr(sys, "frozen", False):
        scriptdir, scriptname = os.path.split(sys.executable)
        return {"dir": scriptdir, "name": scriptname, "source": trc}

    # from here on, we are in the interpreted case
    scriptdir, trc = os.path.split(trc)
    # if trc did not contain directory information,
    # the current working directory is what we need
    if not scriptdir:
        scriptdir = os.getcwd()

    scr_dict = {"name": trc, "source": trc, "dir": scriptdir}
    print(scr_dict)
    return scr_dict


def load_input(base_name: str = ""):
    suffix = sys.argv[1] if len(sys.argv) > 1 else "in"
    input_path = Path(os.path.abspath(os.path.dirname(base_name)))
    input_name = os.path.basename(base_name)
    input_file = (input_path / input_name).with_suffix(f".{suffix}")
    # input_file = Path(os.path.basename(scriptinfo()['source'])).with_suffix(f".{suffix}")
    with open(input_file, "r") as f:
        res = f.readlines()
    return res


def chunk(string: str, length: int = 4):
    return [string[0 + i : length + i] for i in range(0, len(string), length)]


def divide_chunks(l, n):
    for i in range(0, len(l), n):
        yield l[i : i + n]
