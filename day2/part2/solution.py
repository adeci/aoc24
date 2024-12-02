# Advent of Code Day 2 - part2

def checkValidity(array):
    return all((i < j and 1 <= j - i <= 3) for i, j in zip(array, array[1:])) or \
        all((i > j and 1 <= i - j <= 3) for i, j in zip(array, array[1:]))


def main():
    print('Advent of Code Day 2 - part2')

    total = 0
    with open('../input.txt', 'r') as file:
        for line in file:
            line = line.strip()
            strList = line.split(' ')
            array = [int(i) for i in strList]
            if checkValidity(array):
                total += 1
                continue
            for i in range(len(array)):
                testArray = array[:i] + array[i+1:]
                if checkValidity(testArray):
                    total += 1
                    break
    print(total)


if __name__ == '__main__':
    main()
