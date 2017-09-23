#!/usr/bin/env python
import random

def gen(n=10, scale=10, idx='0'):
    res = [random.randint(0, scale) for i in range(n)]
    with open('%s.in' % idx, "w") as f:
        f.write('%d\n' % n)
        f.write(' '.join([str(i) for i in res]) + '\n')
    res.sort()
    with open('%s.out' % idx, "w") as f:
        f.write(' '.join([str(i) for i in res]) + '\n')

def main():
    gen(5, 5, 'case0')
    gen(10, 10, 'case1')
    gen(100, 100, 'case2')
    gen(100000, 100000, 'case3')
    gen(1000, 1000000, 'case4')

main()
