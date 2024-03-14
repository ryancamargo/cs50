import csv

with open("favorite.csv", "r") as file:
		reader = csv.DictReader(file)
		counts = {}

		for row in reader:
				favorite = row["language"]
				if favorite in counts:
						counts[favorite] += 1
				else:
						coounts[favorite] = 1

for favorite in sorted(counts, key=counts.get, reverse=True):
		print(f"{favorite}:{counts[favorite]}")
