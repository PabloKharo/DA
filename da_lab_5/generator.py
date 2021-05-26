import sys
import random
import string
    
def main():
    len = 200000

    with open(f'tests/01.t', 'w') as ftest:
        random_list = [ random.choice(string.ascii_letters) for _ in range(len) ]
        ftest.write("".join(random_list))

main()