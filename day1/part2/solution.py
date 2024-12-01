# Advent of Code Day 1 - part2

def main():
    print('Advent of Code Day 1 - part2')

    simScore = 0
    leftList = []
    rightList = []

    with open('../input.txt', 'r') as file:
        for line in file:
            line = line.strip()
            splitter = line.split('   ', 1)
            left, right = splitter
            leftList.append(int(left))
            rightList.append(int(right))

    for i in range(0, len(leftList)):
        score = rightList.count(leftList[i])
        simScore += leftList[i] * score

    print(simScore)


if __name__ == '__main__':
    main()
