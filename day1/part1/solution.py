# Advent of Code Day 1 - part1

def main():
    print('Advent of Code Day 1 - part1')

    totalDiff = 0
    leftList = []
    rightList = []

    with open('../input.txt', 'r') as file:
        for line in file:
            line = line.strip()
            splitter = line.split('   ', 1)
            left, right = splitter
            leftList.append(int(left))
            rightList.append(int(right))

    leftList.sort()
    rightList.sort()
    for i in range(0, len(leftList)):
        diff = abs(leftList[i] - rightList[i])
        totalDiff += diff

    print(totalDiff)


if __name__ == '__main__':
    main()
