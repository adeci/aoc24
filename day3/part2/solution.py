# Advent of Code Day 3 - part2

import re


def main():
    print('Advent of Code Day 3 - part2')

    with open('../input.txt', 'r') as file:
        data = file.read()

    regex = r'mul\((\d+),(\d+)\)|do\(\)|don\'t\(\)'
    # group 0 is any match, group 1 AND group 2 garuntee mul is found
    total = 0
    do_flag = True
    for rgxmatch in re.finditer(regex, data):
        if (rgxmatch.group(1) and rgxmatch.group(2)) and do_flag:
            total += int(rgxmatch.group(1)) * int(rgxmatch.group(2))
        elif rgxmatch.group(0) == 'do()':
            do_flag = True
        elif rgxmatch.group(0) == 'don\'t()':
            do_flag = False
    print(total)


if __name__ == '__main__':
    main()
