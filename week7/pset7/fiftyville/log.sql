--This query selects all the information about the crime that matches the given data.
--SELECT * FROM crime_scene_reports WHERE street = "Chamberlin Street" AND day = 28 AND month = 7 AND year = 2020;

--From the description of the crime, there is three interviews that were conducted on the same date where each of them mentions the courthouse.
--SELECT name, transcript FROM interviews WHERE day = 28 AND month = 7 AND year = 2020 AND transcript LIKE "%courthouse%";

--License plates of the cars that left the courthouse parking lot in the time frame from Ruth intervie transcript.
--SELECT license_plate FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute >= 15 AND minute <= 25;

--People's id of all withdraw transactions done on Fifer Street ATM on same date
--SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2020 AND atm_location = "Fifer Street" AND transaction_type = "withdraw");

--Numbers of callers and reveivers that match Raymond's transcript.
--SELECT caller, receiver FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2020 AND duration <= 60;

--Fiftyville's airport id.
--SELECT id FROM airports WHERE city = "Fiftyville";

--This query finds the city of destination from matching flights.
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville") AND day = 29 AND month = 7 AND year = 2020 ORDER BY hour LIMIT 1);

-- FLight id
--SELECT id FROM flights WHERE origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville") AND day = 29 AND month = 7 AND year = 2020 ORDER BY hour LIMIT 1);

--Passengers's passport numbers of flight
--SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville") AND day = 29 AND month = 7 AND year = 2020 ORDER BY hour LIMIT 1); 

-- This query finds the matching names considering all the information.
SELECT
    name
    FROM
    people
    WHERE
    id
    IN (
        SELECT
            person_id
            FROM
            bank_accounts
            WHERE
            account_number
            IN (
                SELECT
                    account_number
                    FROM
                    atm_transactions
                    WHERE
                    day = 28 AND month = 7 AND year = 2020 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"
               )
       )
    AND
    phone_number
    IN (
        SELECT
            caller -- or receiver
            FROM
            phone_calls
            WHERE day = 28 AND month = 7 AND year = 2020 AND duration <= 60
       )
    AND
    passport_number
    IN (
        SELECT
            passport_number
            FROM
            passengers
            WHERE
            flight_id = (
                         SELECT
                             id
                             FROM
                             flights
                             WHERE
                             origin_airport_id
                             IN (
                                 SELECT
                                     id
                                     FROM
                                     airports
                                     WHERE
                                     city = "Fiftyville"
                                )
                             AND day = 29 AND month = 7 AND year = 2020
                             ORDER BY
                             hour
                             LIMIT 1
                        ))
    AND
    license_plate 
    IN (
        SELECT
            license_plate
            FROM
            courthouse_security_logs
            WHERE
            day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute >= 15 AND minute <= 25
       );
