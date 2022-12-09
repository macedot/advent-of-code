import os
from pathlib import Path
from string import ascii_lowercase, ascii_uppercase

def load_input(base_name: str = __file__):
    input_path = Path(os.path.abspath(os.path.dirname(base_name)))
    input_name = os.path.basename(base_name)
    input_file = (input_path / input_name).with_suffix('.input')
    with open(input_file, "r") as f:
        res = f.readlines()
    return res
