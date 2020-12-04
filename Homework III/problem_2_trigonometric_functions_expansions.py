from sympy import *
import numpy as np

x = symbols('x')
init_printing(use_unicode = True)

functions = [sin(x), cos(x), tan(x), sec(x), csc(x)]
names_of_functions = ['sin(x)', 'cos(x)', 'tan(x)', 'sec(x)', 'csc(x)']

for i in range(len(functions)):
    print(names_of_functions[i], '=' , functions[i].series(x, 0, 4)) 
