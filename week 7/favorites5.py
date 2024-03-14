import csv

from collections import Counter

with open("favorite.csv", "r") as file:
		reader = csv.DictReader(file)
		counts = Counter()

		for row in reader:
			favorite = row["problem"]  # Changing 'problem' you'll get other ones
			counts[favorite] += 1


favorite = input("Favorite: ")
print(f"{favorite}: {counts[favorite]}")
