#!/bin/bash

# Prompt the user for input
read -p "Create which day: " day

# Validate input is a number
if [[ ! $day =~ ^[0-9]+$ ]]; then
    echo "Must be a valid day number."
    exit 1
fi

# Define the day directory
day_dir="day${day}"

# Check if the directory already exists
if [[ -d $day_dir ]]; then
    echo "$day_dir already created."
    exit 1
fi

# Create the day directory
mkdir -p "$day_dir"

# Create parts directories and files
for part in part1 part2; do
    part_dir="${day_dir}/${part}"
    mkdir -p "$part_dir"

    # Create solution.c file
    cat <<EOF > "${part_dir}/solution.c"
/* Advent of Code Day ${day} - ${part} */
#include <stdio.h>
#include "../../utils/utils.h"

int main() {
    printf("Advent of Code Day ${day} - ${part}\\n");
    return 0;
}
EOF

    # Create solution.py file
    cat <<EOF > "${part_dir}/solution.py"""
# Advent of Code Day ${day} - ${part}

def main():
    print('Advent of Code Day ${day} - ${part}')


if __name__ == '__main__':
    main()
EOF

    # Create compile.sh file
    cat <<EOF > "${part_dir}/compile.sh"
#!/bin/bash

clang -I../../utils -o solution solution.c ../../utils/utils.c
if [[ \$? -eq 0 ]]; then
    echo "Compilation success."
    ./solution
else
    echo "Compilation fail."
fi
EOF

    chmod +x "${part_dir}/compile.sh"
done

echo "Day ${day} ready!"

