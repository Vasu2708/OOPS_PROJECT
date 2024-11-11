import sys
from collections import defaultdict
import random

def slovemy(a, mp, size, mx, visited, count):
    # Increment the count for the current size
    count[size] += 1
    print(f"Visiting size: {size}, count: {count[size]}")

    if size in visited:
        return

    visited.add(size)
    mx[0] = max(mx[0], size)

    if size + 1 in mp:
        for k in mp[size + 1]:
            slovemy(a, mp, size + k, mx, visited, count)

    visited.remove(size)

def slove():
    n = int(sys.stdin.readline())
    a = list(map(int, sys.stdin.readline().split()))
    mp = defaultdict(list)

    for i in range(n):
        mp[a[i] + i + 1].append(i)

    mx = [0]  # Using a list to allow mutation
    visited = set()
    count = defaultdict(int)  # Map to count occurrences of each size
    slovemy(a, mp, len(a), mx, visited, count)

    print(f"Maximum size: {mx[0]}")

    # Print the count of each size
    print("Size counts:")
    for size, cnt in count.items():
        print(f"Size = {size}, Count = {cnt}")

def generate_test_cases(t, max_n, max_value):
    print(t)  # Print the number of test cases
    for _ in range(t):
        # Random length of the array n
        n = random.randint(1, max_n)
        print(n)  # Print the length of the array
        # Generate n random integers within the specified range
        array = [random.randint(1, max_value) for _ in range(n)]
        print(" ".join(map(str, array)))  # Print the array elements

# Main execution
if __name__ == "__main__":
    # Generate random test cases
    t = 10  # Number of test cases
    max_n = 300000  # Maximum length of the array
    max_value = 10**12  # Maximum value for elements in the array

    generate_test_cases(t, max_n, max_value)

    # Uncomment below to run the main logic after generating test cases
    # t = int(sys.stdin.readline())
    # while t > 0:
    #     slove()
    #     t -= 1
