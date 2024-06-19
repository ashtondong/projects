import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")  # error

    # TODO: Read database file into a variable
    dataFile = sys.argv[1]
    dataList = []
    with open(dataFile) as dFile:
        if dataFile == "databases/small.csv":
            DictReader = csv.DictReader(dFile)
            for data in DictReader:  # this is iterating through each DICTIONARY in the LIST dataList
                data["AGATC"] = int(data["AGATC"])
                data["AATG"] = int(data["AATG"])
                data["TATC"] = int(data["TATC"])
                dataList.append(data)
        if dataFile == "databases/large.csv":
            DictReader = csv.DictReader(dFile)
            for data in DictReader:  # this is iterating through each DICTIONARY in the LIST dataList
                data["AGATC"] = int(data["AGATC"])
                data["TTTTTTCT"] = int(data["TTTTTTCT"])
                data["AATG"] = int(data["AATG"])
                data["TCTAG"] = int(data["TCTAG"])
                data["GATA"] = int(data["GATA"])
                data["TATC"] = int(data["TATC"])
                data["GAAA"] = int(data["GAAA"])
                data["TCTG"] = int(data["TCTG"])
                dataList.append(data)

        # print(dataList)
        # produces a list of dictionaries holding the data.csv file

    # TODO: Read DNA sequence file into a variable
    seqFile = sys.argv[2]
    with open(seqFile) as sFile:
        sequence = sFile.read()  # reads the txt file
        # produces a string. We don't need to use .csv reader because it's not a csv file and we don't need it as a list of string.
        # print(sequence) # prints the string

    # TODO: Find longest match of each STR in DNA sequence
    tmplist = []
    subsequence = []
    longest_run = 0
    strSize = 0
    counts = {}

    for data in dataList:  # go into the data list and take all keys
        tmplist = list(data.keys())

    # print(tmplist)

    subsequence = tmplist[1:]
    # print(subsequence)

    for i in subsequence:
        strSize += 1  # iterate through the subsequence list and count the number of STRs

    # checking for the longest match for each subsequence and storing in dictionary
    for STR in subsequence:
        longest_run = longest_match(sequence, STR)
        counts[STR] = longest_run

    # print(counts)

    # TODO: Check database for matching profiles
    i = 0
    name = None
    checkSTR = 0  # checking to see if all STRs match for a person

    # print(list(counts.items()))
    # print(list(dataList[10].items())[1:])

    while i < len(dataList):
        for j in range(len(counts)):
            countsList = list(counts.items())[j]  # make the dictionary "count" into a list of tuples and index into it
            if countsList in list(dataList[i].items())[1:]:  # if that tuple is in the "dataList" of tuples
                checkSTR += 1
        if checkSTR == strSize:  # the amount of STR pairs we're checking
            name = dataList[i]["name"]

        i += 1
        checkSTR = 0  # reset checkSTR for next person

    if name != None:
        print(name)
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
