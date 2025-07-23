/* В принципе суть ”phantom reads” та же, что и у
 * “Non-RepeatabIe Reads” поскольку базируются
 * они на одном и том же недостатке уровня
 * изоляции READ СОММТТ */

-- For Session №1
BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED;
-- For Session №2
BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED;
-- For Session №1
SHOW TRANSACTION ISOLATION LEVEL;
-- For Session №2
SHOW TRANSACTION ISOLATION LEVEL;


-- For Session №1
SELECT SUM(rating) FROM pizzeria;


-- For Session №2
INSERT INTO pizzeria VALUES (10, 'Kazan Pizza', 5.0);
-- For Session №2
COMMIT;


-- For Session №1
SELECT SUM(rating) FROM pizzeria;
-- For Session №1
COMMIT;


-- For Session №1
SELECT SUM(rating) FROM pizzeria;
-- For Session №2
SELECT SUM(rating) FROM pizzeria;


/* В итоге в рамках одной транзакции в первой сессии можно
 * увидеть, что набор выдаваемых строк до завершения
 * транзакции второй сессии и после различаются */