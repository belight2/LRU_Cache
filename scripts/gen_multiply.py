#!/bin/env python3

import random
import sys

DELTA = 0.05


def random_number():
    return 1 + (random.random() - 0.5) * DELTA


def gen_multiply(count: int) -> str:
    s = ''
    for _ in range(count):
        n = random_number()
        s += f'{str(n)} '
    return s


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <count>')
        sys.exit(1)

    count = int(sys.argv[1])
    print(gen_multiply(count))
