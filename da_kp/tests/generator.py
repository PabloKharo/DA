import sys
import random
import string
    
def main():
    len = 100000

    with open('gen', 'w') as ftest:
        random_list = [ random.choice("ab") for _ in range(len) ]
        ftest.write("compress\n")
        ftest.write("".join(random_list))
    
    

main()