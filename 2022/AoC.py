import os
from pathlib import Path


def load_input(base_name: str = __file__):
    input_path = Path(os.path.abspath(os.path.dirname(base_name)))
    input_name = os.path.basename(base_name)
    input_file = (input_path / input_name).with_suffix('.input')
    with open(input_file, "r") as f:
        res = f.readlines()
    return res


def chunk(string: str, length: int = 4):
    return [string[0+i:length+i] for i in range(0, len(string), length)]


def divide_chunks(l, n):
    for i in range(0, len(l), n):
        yield l[i:i + n]
