
import re

# Load the content of the new file
file_path = "inputFile"

with open(file_path, "r") as file:
    file_content = file.read()

# Find all occurrences of the pattern 'mul(x,y)' using regex
pattern = r"mul\(\s*(-?\d+)\s*,\s*(-?\d+)\s*\)"
matches = re.findall(pattern, file_content)

# Compute the sum of the products of the numbers found
total_sum = sum(int(x) * int(y) for x, y in matches)
print(total_sum)
