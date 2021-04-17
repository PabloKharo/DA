import sys
import random
import string

TestCount = 500000

def get_random_md5():
    random_list = [ random.choice('0123456789abcdef') for _ in range(32) ]
    return "".join(random_list)

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <test directory>")
        sys.exit(1)
    
    test_dir = sys.argv[1]

    test = []
    for _ in range(TestCount):
        key = get_random_md5()
        value = random.randint(1, 2**64 - 1)
        test.append((key, value))
    
    test_name = "{}/{:02d}".format(test_dir, TestCount)
    with open(f'{test_name}.t', 'w') as ftest:
        for key, value in test:
            ftest.write(f'{key}\t{value}\n')

    answer = sorted(test, key=lambda x: x[0])
    with open(f'{test_name}.a', 'w') as ftest:
        for key, value in answer:
            ftest.write(f'{key}\t{value}\n')



main()