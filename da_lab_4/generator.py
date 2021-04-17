# -*- coding: utf-8 -*-

import sys
import random
import string

import re

def count_substring(string, substring):
    res = 0
    left = 0
    while 1:
        left = string.find(substring, left)
        if left == -1:
            break
        left += 1
        res += 1
    return res

# def get_random_key():
#     return random.choice( string.ascii_letters ).lower()


def get_random_key():
    key = ""
    length = random.randint(1, 2)
    while length > 0:
        key += random.choice( ['a', 'b', 'c', 'd', 'e'] )
        length -= 1
    return key

if __name__ == "__main__":
    # Проверяем, что передали 1 аргумент.
    if len(sys.argv) != 2:
        print( "Usage: {0} <count of tests>".format( sys.argv[0] ) )
        sys.exit(1)

    count_of_tests = int( sys.argv[1] )

    pattern = 10**2
    texts = 10**4


    for enum in range( count_of_tests ):
        test_file_name = "tests/{:02d}".format( enum + 1 )
        with open( "{0}.t".format( test_file_name ), 'w' ) as output_file, \
             open( "{0}.a".format( test_file_name ), "w" ) as answer_file:

            # Для каждого файла генерируем от 1 до 100 тестов.
            words = list()
            for i in range(pattern):
                strlen = random.randint(1, 10)
                words.append("")
                while strlen > 0:
                    words[i] += get_random_key() + ' '
                    strlen -= 1
                words[i] += get_random_key()
                output_file.write("{0}\n".format(words[i]))

            output_file.write("\n")
            counter = 0
            text = " "
            for i in range(texts):
                text += get_random_key() + ' '

            output_file.write("{0}\n".format(text))
            for word in words:
                counter += count_substring(text, " " + word + " ")
            
            answer_file.write("{0}".format(counter))

                     