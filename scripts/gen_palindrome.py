#!/bin/env python3

import random
import sys


def random_character():
    return chr(random.randint(97, 122))


def gen_palindrome(length: int) -> str:
    s = ''
    for _ in range(length):
        c = random_character()
        s += c
    return s


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <length>')
        sys.exit(1)

    length = int(sys.argv[1])
    print(gen_palindrome(length))
