#!/bin/env python3

from os import mkdir
import random
from shutil import rmtree
import sys

from gen_multiply import gen_multiply
from gen_palindrome import gen_palindrome

MULTIPLY_COUNT = 1000000
PALINDROME_LENGTH = 3000


def gen_task_set(multiply_count: int, palindrome_count: int, task_count: int):
    multiplies = [gen_multiply(MULTIPLY_COUNT) for _ in range(multiply_count)]
    palindromes = [gen_palindrome(PALINDROME_LENGTH)
                   for _ in range(palindrome_count)]

    rmtree('resources', ignore_errors=True)
    mkdir('resources')
    for i, multiply in enumerate(multiplies):
        with open(f'resources/multiply_{i}.txt', 'w') as f:
            f.write(multiply)

    for i, palindrome in enumerate(palindromes):
        with open(f'resources/palindrome_{i}.txt', 'w') as f:
            f.write(palindrome)

    print(
        f'Generated {multiply_count} multiplies and {palindrome_count} palindromes')

    with open('resources/task_set.txt', 'w') as f:
        for i in range(task_count):
            if random.randint(0, 1) == 0:
                f.write(
                    f'multiply resources/multiply_{random.randint(0, multiply_count - 1)}.txt\n')
            else:
                f.write(
                    f'palindrome resources/palindrome_{random.randint(0, palindrome_count - 1)}.txt\n')

    print(f'Generated {task_count} tasks')


if __name__ == '__main__':
    if len(sys.argv) < 4:
        print(
            f'Usage: {sys.argv[0]} <multiply_count> <palindrome_count> <task_count>')
        sys.exit(1)

    multiply_count = int(sys.argv[1])
    palindrome_count = int(sys.argv[2])
    task_count = int(sys.argv[3])

    gen_task_set(multiply_count, palindrome_count, task_count)
