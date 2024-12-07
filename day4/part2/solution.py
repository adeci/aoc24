# Advent of Code Day 4 - part2

def main():
    print('Advent of Code Day 4 - part2')

    grid = []

    with open('../input.txt', 'r') as file:
        for line in file:
            grid.append(line.strip())

    diags = []
    # tl->br diagonal
    for i in range(len(grid[0]) + len(grid) - 1):
        diag = []
        for j in range(len(grid)):
            if 0 <= i - j < len(grid[0]):
                diag.append((grid[j][i - j], (j, i - j)))

        diags.append(diag)
    # tr->bl
    for i in range(len(grid[0]) + len(grid) - 1):
        diag = []
        for j in range(len(grid)):
            if 0 <= len(grid[0]) - (i - j + 1) - 1 < len(grid[0]):
                diag.append(
                    (grid[j][len(grid[0]) - (i - j + 1) - 1], (j, len(grid[0]) - (i - j + 1) - 1)))
        diags.append(diag)

    coordmap = {}
    for diag in diags:
        index = 0
        diag_string = ''.join(char for char, _ in diag)
        while index != -1:
            index = diag_string.find('MAS', index)
            if index == -1:
                break
            coord = diag[index + 1][1]
            if coord in coordmap:
                coordmap[coord] += 1
            else:
                coordmap[coord] = 1
            index += 1
            if index >= len(diag_string):
                break

        index = 0
        while index != -1:
            index = diag_string.find('SAM', index)
            if index == -1:
                break
            coord = diag[index + 1][1]
            if coord in coordmap:
                coordmap[coord] += 1
            else:
                coordmap[coord] = 1
            index += 1
            if index >= len(diag_string):
                break

    total = 0
    for i in coordmap:
        if coordmap[i] == 2:
            total += 1
    print(total)


if __name__ == '__main__':
    main()
