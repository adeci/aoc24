# Advent of Code Day 4 - part1

def main():
    print('Advent of Code Day 4 - part1')

    grid = []

    with open('../input.txt', 'r') as file:
        for line in file:
            grid.append(line.strip())

    total = 0

    for row in grid:
        total += ''.join(row).count('XMAS')
        total += ''.join(row)[::-1].count('XMAS')

    for col in zip(*grid):
        total += ''.join(col).count('XMAS')
        total += ''.join(col)[::-1].count('XMAS')

    diags = []
    # tl->br diagonal
    for i in range(len(grid[0]) + len(grid) - 1):
        diag = []
        for j in range(len(grid)):
            if 0 <= i - j < len(grid[0]):
                diag.append(grid[j][i - j])
        diags.append(diag)
    # tr->bl
    for i in range(len(grid[0]) + len(grid) - 1):
        diag = []
        for j in range(len(grid)):
            if 0 <= i - j < len(grid[0]):
                diag.append(grid[j][-(i - j + 1)])
        diags.append(diag)

    for diag in diags:
        total += ''.join(diag).count('XMAS')
        total += ''.join(diag)[::-1].count('XMAS')

    print(total)


if __name__ == '__main__':
    main()
