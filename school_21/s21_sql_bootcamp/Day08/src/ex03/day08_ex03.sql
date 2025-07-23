/* Зная из прошлых заданий с уровнем изоляции
 * READ COMMITED о принципе его работы, данный
 * пример является простым примером определенного
 * частного случая выходящего из логики работы
 * данного уровня изоляции*/

-- For Session №1
BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED;

-- For Session №2
BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED;

-- For Session №1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';

-- For Session №2
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';
-- For Session №2
COMMIT;

-- For Session №1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- For Session №1
COMMIT;

-- For Session №1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- For Session №2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';

/* Аномалия “Non-Repeatable Reads“ показывает, что в
 первой сессии в рамках одной транзакции мы можем
 на выводе кортежа наблюдать различные выводы,
 поскольку между ними на стороне может завершиться
 транзакция второй сессии */