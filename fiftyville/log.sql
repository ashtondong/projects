-- Keep a log of any SQL queries you execute as you solve the mystery.

-- query for the description of the crime scene on 7/28 on Humphrey Street
SELECT description FROM crime_scene_reports
    WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';
    -- result: Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
    -- | Littering took place at 16:36. No known witnesses.

-- look at the bakery_security_logs around the time the robbery took place
SELECT hour, minute, activity, license_plate FROM bakery_security_logs
    WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute <= 25;
    -- result:

/*| hour | minute | activity | license_plate |
+------+--------+----------+---------------+
| 10   | 16     | exit     | 5P2BI95       |
| 10   | 18     | exit     | 94KL13X       |
| 10   | 18     | exit     | 6P58WS2       |
| 10   | 19     | exit     | 4328GD8       |
| 10   | 20     | exit     | G412CB7       |
| 10   | 21     | exit     | L93JTIZ       |
| 10   | 23     | exit     | 322W7JE       |
| 10   | 23     | exit     | 0NTHK55       |
+------+--------+----------+---------------+
 */

-- look at the people with license plates around the time of theft. Suspects
SELECT * FROM people
    WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute <= 25);

/*  id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
| 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X      */

-- look at everyone whose had interviews on that day
SELECT name, transcript FROM interviews
   WHERE month = 7 AND day = 28;
   -- | Ruth| Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
   -- | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
   -- | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- look at people who were at the ATM on 7/28 and if it falls in the suspect list.
SELECT account_number, amount FROM atm_transactions
    WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

/*  account_number | amount | transaction_type |
+----------------+--------+------------------+
| 28500762       | 48     | withdraw         |
| 28296815       | 20     | withdraw         |
| 76054385       | 60     | withdraw         |
| 49610011       | 50     | withdraw         |
| 16153065       | 80     | withdraw         |      |
| 25506511       | 20     | withdraw         |
| 81061156       | 30     | withdraw         |
| 26013199       | 35     | withdraw */

-- join people and their bank accounts

SELECT name FROM people
    JOIN bank_accounts ON person_id = people.id
    WHERE account_number IN(
        SELECT account_number FROM atm_transactions
        WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')
    AND name IN (
        SELECT name FROM people
        WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute <= 25));

    -- narrowed down suspect list. containing people that withdrew money on 7/28 and was seen on security footage within the crime period
   /*  | name  |
    +-------+
    | Bruce |
    | Diana |
    | Iman  |
    | Luca  |
    +-------+ */

-- look at phone calls and see who they called for less than a minute. Get the caller and receiver info on 7/28
SELECT name FROM people
    WHERE phone_number IN (
        SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60) AND name IN (
            SELECT name FROM people
            JOIN bank_accounts ON person_id = people.id
            WHERE account_number IN(
            SELECT account_number FROM atm_transactions
            WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')
        AND name IN (
            SELECT name FROM people
            WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute <= 25)));

/*     | name  |
    +-------+
    | Diana |
    | Bruce |
    +-------+ */

-- look at who received their calls
-- bruce and diana's receivers: (375) 555-8161, (725) 555-3243 respectively
SELECT name FROM people
    WHERE phone_number = '(375) 555-8161' OR phone_number = '(725) 555-3243';

/*     +--------+
    |  name  |
    +--------+
    | Philip |
    | Robin  |
    +--------+ */

-- look for the earliest flight on 7/29
SELECT city FROM airports
    WHERE id = (SELECT destination_airport_id FROM flights WHERE month = 7 AND day = 29 AND hour < 9);

    -- New York City
    -- be careful of using too many joins, it will produce multiple outputs of the same answer because you're creating multiple columns of the same data in the joined table.

-- we need the name of the person that flew to NYC that morning

SELECT passport_number FROM passengers
    WHERE flight_id = (SELECT id FROM flights WHERE month = 7 AND day = 29 AND hour < 9);
 /*    +-----------------+
    | passport_number |
    +-----------------+
    | 7214083635      |
    | 1695452385      |
    | 5773159633      |
    | 1540955065      |
    | 8294398571      |
    | 1988161715      |
    | 9878712108      |
    | 8496433585      |
    +-----------------+ */

-- look at who's passport numbers these are

SELECT name FROM people
    WHERE passport_number IN (
        SELECT passport_number FROM passengers
        WHERE flight_id = (SELECT id FROM flights WHERE month = 7 AND day = 29 AND hour < 9)
    );