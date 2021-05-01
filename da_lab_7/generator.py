# -*- coding: utf-8 -*-

import sys
import random
import string

if __name__ == "__main__":
    n = 10000
    m = 10000

    test_file_name = "tests/01"
    with open( "{0}.t".format( test_file_name ), 'w' ) as output_file:
        output_file.write("{0} {1}\n".format(n, m))
        for i in range(n):
            for j in range(m):
                value = random.randint(1, 100)
                output_file.write("{0} ".format(value))
            output_file.write("\n")
            