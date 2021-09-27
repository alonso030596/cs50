import sys
import csv

def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python3 dna.py FILENAME.csv FILENAME.txt")

    with open(sys.argv[1]) as csvfile:
        csvreader = csv.DictReader(csvfile) 
        
        individuals = []

        # Read individuals into memory from csv file
        for row in csvreader:
            individuals.append(row)

    # Read DNA sequence into memory from text file
    with open(sys.argv[2], 'r') as txtfile:
        sequence = txtfile.read()
    
    STRs = list(individuals[0].keys())
    STRs.pop(0)
   
    counts = find_longest_STR(STRs, sequence)

    # Check for match
    for p in individuals:
        aux = {x:p[x] for x in STRs}
        if aux == counts:
            print(p["name"])
            break
        if p == individuals[len(individuals) - 1] and aux != counts:
            print("No match")


def find_longest_STR(STRs, sequence):
    counts = {}
    sequence_length = len(sequence)
    for STR in STRs:
        i = 0
        longest = 0
        while i != sequence_length:
            if (STR == sequence[i: i + len(STR)]):
                count = 1
                while STR == sequence[i + count * len(STR):i + (count + 1) * len(STR)]:
                    count += 1
                if count > longest:
                    longest = count
                i = i + (count) * len(STR) - 1 
            i += 1
        counts[STR] = str(longest)

    return counts


if __name__ == "__main__":
    main()
