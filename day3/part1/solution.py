# Advent of Code Day 3 - part1

import re


def main():
    print('Advent of Code Day 3 - part1')

    with open('../input.txt', 'r') as file:
        data = file.read()

    regex = r'mul\((\d+),(\d+)\)'
    datamatch = re.findall(regex, data)
    total = 0
    extract = [(int(num1), int(num2)) for num1, num2 in datamatch]
    for i in range(len(extract)):
        total += extract[i][0] * extract[i][1]
    print(total)


if __name__ == '__main__':
    main()
