-- Keep a log of any SQL queries you execute as you solve the mystery.

-- See all the tables in the database
.tables

-- Checking this table
.schema crime_scene_reports

-- Checking what crime scene reports occurred on July 28
SELECT * FROM crime_scene_reports WHERE day = 28 AND month = 7;

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. three witnesses. each of their interview transcripts mentions the bakery.

-- Checking for other 'bakery' reports that occurred
SELECT * FROM crime_scene_reports WHERE description LIKE '%bakery%';

-- Search for any 'CS50' occurrance
SELECT * FROM crime_scene_reports WHERE description LIKE '%CS50%';

-- Counting the number of reports (e.g., rows in the table)
SELECT COUNT(*) FROM crime_scene_reports;

-- Viewing the reports on Humphrey Street on July
SELECT * FROM crime_scene_reports WHERE month = 7 AND street = 'Humphrey Street';

-- Check bakery security logs schema
.schema bakery_security_logs;

-- Searching for activities on July 28 in the bakery security logs
SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28;

-- Plate number 5P2BI95, 13FNH73, R3G7486, G412CB7, 6P58WS2, 5P2BI95, 94KL13X, 4328GD8, L93JTIZ, 322W7JE,| 0NTHK55, 1106N58, NRYN856, WD5M8I6, V47T75I
-- Checking how many repetitions for each suspected plate (which at first are those registered at 10am)
SELECT COUNT(*) FROM bakery_security_logs WHERE month = 7 AND day = 28 AND license_plate = 'V47T75I';

-- Each one of them only entered and exit once

-- Check interviews table schema
.schema interviews

-- Check interviews table for transcripts in July 28
SELECT * FROM interviews WHERE year = 2023 AND month = 7 AND day = 28;

-- Ruth said sometime within 10 min the thief got into a car in the bakery partking lot and drove away
-- Eugene said earlier that morning July 28 (before he arrived at Emma's bakery) he was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- Raymond heard the thief say on a phone call that they were planning to take the earliest flight out of Fiftyville tomorrow.

-- Cheking Ruth info we have the following suspect license plates: 0NTHK55, 1106N58, NRYN856, WD5M8I6, V47T75I
-- Let's see if any of them went to the airport the day after the theft

-- Discovering the time Eugene arrived at Emma's bakery on July 28
.schema people

-- Getting Eugene license plate -------> 47592FJ
SELECT * FROM people WHERE name = 'Eugene';

-- Checking the time Eugene arrived at Emma's bakery
SELECT * FROM bakery_security_logs WHERE license_plate = '47592FJ';

-- Eugene did not arrive at Emma's bakery on July 28 .... at least not using his car ..
-- So he went there on July 26 on the afternoon, two days before the theft ... He gave the interview on July 28 stating he was there on that very morning .... but after July 26, he only went to Emma's bakery on July 30 .... that's suspect huh
-- Checking Eugene information ... what transactions were made on July 28 on Leggett Street? --> only one deposit --> let's see
SELECT * FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street';

-- Checking if those nine transaction were all from different account numbers
SELECT DISTINCT COUNT(account_number) FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street';

-- Cheking Raymond info --> earliest flight to Fiftyville July 29
-- Verifying fiftyville id
SELECT * FROM airports WHERE city = 'Fiftyville';

-- Getting the flights to fiftyville on july 29 2023
SELECT * FROM flights WHERE origin_airport_id = 8 AND year = 2023 AND month = 7 AND day = 29 ORDER BY hour ASC;

-- There was 5 flights out of fiftyville on July 29 2023 .... according to Raymonds interview, the thief is going to take the earliest one
-- Which is the 8:20am flight on July 29 ----> flight id is 36 and the destination id is 4
-- Lets see which city is the destination
SELECT * FROM airports WHERE id = 4;

-- The destination airport is LaGuardia Airport in the New York City

-- Lets check the owners of the plates that Ruth interview lead us to
SELECT * FROM people WHERE license_plate = '0NTHK55'; -- Kelsey
SELECT * FROM people WHERE license_plate = '1106N58'; -- Taylor
SELECT * FROM people WHERE license_plate = 'NRYN856'; -- Denise
SELECT * FROM people WHERE license_plate = 'WD5M8I6'; -- Thomas
SELECT * FROM people WHERE license_plate = 'V47T75I'; -- Jeremy

-- What info do we actually have?
-- Ruth interview > 5 potential suspects that fit in her description
-- Eugene interview > he was lying bc he didn't go to Emma's bakery on July 28 as he stated he did ... he was there on July 26 and July 30
-- Raymond interview > the thief got a flight out of Fiftyville to NYC on July 29 at 8:20am

-- Checking phone calls table and search for info on the Raymond's clue about the phone call around 10:15am on July 28 2023
-- Eugene phone number (666) 555-5774 ..... 666 is the sign of the beast isn't it ? huh
SELECT * FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND caller = '(666) 555-5774';

-- Eugene did a call on that day .... id 228 .... receiver (125) 555-8030 .... duration 326
-- Eugene called Raymond !!!!
-- Raymond doesn't have a passport number ...
-- Ruth did not go to Emma's bakery (using her car) on July 28, the same as Eugene ....

-- Checking bank accounts that matching atm transactions on July 28
28500762 ---> 467400 --> 2014 ---> Luca
28296815 --> 395717 --> 2014 ---> Kenny
76054385 --> 449774 --> 2015 ---> Taylor   ---------> TAYLOR is the thief acccording to Ruth statement AND according to Eugene
49610011 -- > 686048 --> 2010 ---> Bruce
16153065 ---> 458378 --> 2012 ---> Brooke
86363979 ---> 948985 --> 2010 ---> Kaelyn
25506511 ---> 396669 --> 2014 ---> Iman
81061156 ---> 438727 --> 2018 ---> Benista
26013199 ---> person id 514354 ---> year creation 2012

SELECT * FROM people WHERE id = 686048;


