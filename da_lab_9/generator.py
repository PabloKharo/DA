# -*- coding: utf-8 -*-

import sys
import random
import string

if __name__ == "__main__":
    n = 10
    m = 100
    start = 1
    finish = n

    test_file_name = "tests/01"
    with open( "{0}.t".format( test_file_name ), 'w' ) as output_file:
        output_file.write("{0} {1} {2} {3}\n".format(n, m, start, finish))
        for i in range(m):
            fromP = random.randint(1, n - 1)
            toP = random.randint(1, n - 1)
            while(toP == fromP):
                toP = random.randint(1, n - 1)

            value = random.randint(1, 50)
            output_file.write("{0} {1} {2}".format(fromP, toP, value))
            output_file.write("\n")
            