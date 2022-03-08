-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Query to know info about the crime scene report
SELECT *
    FROM crime_scene_reports
    WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";
-- ID : 295
-- Description : Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time –
-- each of their interview transcripts mentions the bakery.

-- Query for transcript of the interviews of the witnesses
SELECT *
    FROM interviews
    WHERE year = 2021 AND month = 7 AND day = 28;


-- Query to get info about withdraw at the atm near the bakery
SELECT *
    FROM atm_transactions
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND atm_location LIKE "Leggett Street%"
    AND transaction_type = "withdraw";

-- Query for people related to account number who withdrawed the day of the thief
SELECT name
    FROM people
    WHERE id IN
        (SELECT person_id
        FROM bank_accounts
        WHERE account_number IN
            (SELECT account_number
            FROM atm_transactions
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND atm_location LIKE "Leggett Street%"
            AND transaction_type = "withdraw"));


-- Query for footage of the bakery parking lot
SELECT *
    FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25;

-- Query for name of people who left the parking lot
SELECT name
    FROM people
    WHERE license_plate IN
        (SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute >= 15
        AND minute <= 25);

-- Query to get name of people who called less than a minute
SELECT name
    FROM people
    WHERE phone_number IN
        (SELECT caller
        FROM phone_calls
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration < 60);

-- Receiver
SELECT name
    FROM people
    WHERE phone_number IN
        (SELECT receiver
        FROM phone_calls
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration < 60);


-- Receiver of 1min call from Diana and Bruce= Philip & Robin
SELECT name, id
    FROM people
    WHERE phone_number IN
        (SELECT receiver
            FROM people
            JOIN phone_calls
            ON caller = phone_number
            WHERE (name = "Bruce" OR name = "Diana")
            AND year = 2021 AND month = 7 AND day = 28 AND duration < 60);


-- Query for caller of 30min
SELECT *
        FROM phone_calls
        WHERE year = 2021 AND month = 7 AND day = 28 AND duration > 1500 and duration < 2100;
        -- Nothing

-- Flights
SELECT *
    FROM flights
    WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1;


-- Destination
SELECT full_name, city
    FROM airports
    WHERE id =
        (SELECT destination_airport_id
        FROM flights
        WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1);

-- Thief
SELECT name
    FROM people
    WHERE passport_number IN
        (SELECT passport_number
        FROM passengers
        WHERE flight_id =
            (SELECT id
            FROM flights
            WHERE year = 2021
            AND month = 7
            AND day = 29
            ORDER BY hour
            LIMIT 1))
    AND (name = "Bruce" OR name = "Diana");

-- Accomplice
SELECT name, id
    FROM people
    WHERE phone_number IN
        (SELECT receiver
        FROM people
        JOIN phone_calls
        ON caller = phone_number
        WHERE (name = "Bruce")
        AND year = 2021 AND month = 7 AND day = 28 AND duration < 60);


