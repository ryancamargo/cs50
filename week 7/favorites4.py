import csv

from collections import Counter

with open("favorite.csv", "r") as file:
		reader = csv.DictReader(file)
		counts = Counter()

		for row in reader:
			favorite = row["language"]  # Changing 'language' you'll get other ones
			counts[favorite] += 1


for favorite, count in counts.most_common():
		print(f"{favorite}:{counts[favorite]}")
