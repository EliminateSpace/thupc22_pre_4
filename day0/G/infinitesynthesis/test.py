import random
n = 100000
print(n)
for i in range(n):
	print(random.choice([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 33, 100, 333]), end = " ")
	# print(random.randint(1, 10), end = " ")
	# print(random.choice([1, 1, 2, 2, 3, 3, 30, 32, 33]), end = " ")
print()

for i in range(n):
	print(random.randint(300, 333), end = " ")
print()