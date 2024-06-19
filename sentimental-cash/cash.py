from cs50 import get_float


def main():
    # ask how many dollars the customer is owed.
    dollars = get_dollars()

    # calculate number of quarters
    quarters = calculate_quarters(dollars)
    dollars = dollars - quarters * 0.25

    # calculate number of dimes
    dimes = calculate_dimes(dollars)
    dollars = round(dollars - dimes * 0.10, 2)

    # calculate number of nickles
    nickels = calculate_nickels(dollars)
    dollars = round(dollars - nickels * 0.05, 2)

    # calculate number of pennies
    pennies = calculate_pennies(dollars)
    dollars = round(dollars - pennies * 0.01, 2)

    # sum coins
    coins = quarters + dimes + nickels + pennies

    # print total number of coins
    print(coins)


def get_dollars():
    while True:
        change = get_float("Change owed:\n")
        if change > 0:
            return change


def calculate_quarters(dollars):
    q = 0
    d = dollars
    value = float(0.25)

    while d >= value:
        d = d - value
        q += 1

    return q


def calculate_dimes(dollars):
    di = 0
    d = dollars
    value = float(0.10)

    while d >= value:
        d = d - value
        di += 1

    return di


def calculate_nickels(dollars):
    n = 0
    d = dollars
    value = float(0.05)

    while d >= value:
        d = round(d - value, 2)
        n += 1

    return n


def calculate_pennies(dollars):
    p = 0
    d = dollars
    value = float(0.01)

    while d >= value:
        d = d - value
        p += 1

    return p


main()

