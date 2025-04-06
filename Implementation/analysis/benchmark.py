import sys
import os

# Add the build directory to Python path
build_dir = os.path.abspath('../')
sys.path.insert(0, build_dir)

import pandas as pd
import numpy as np

import sorters
from data import list_generators

sorts = []
for name, obj in sorters.__dict__.items():
    if callable(obj):
        sorts.append(name)

print(sorts)