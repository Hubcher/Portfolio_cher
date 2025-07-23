/* В этом задании описывается тот же порядок действий, 
 * что и в прошлом, но с уровнем изоляции SERIALIZABLE */
-- For Session №1
BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;
-- For Session №2
BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;

-- For Session №1
SHOW TRANSACTION ISOLATION LEVEL;
-- For Session №2
SHOW TRANSACTION ISOLATION LEVEL;

-- For Session №1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';


-- For Session №2
UPDATE pizzeria SET rating = 3.0 WHERE name = 'Pizza Hut';
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


/* По сравнению с выводом при REPEATABLE READ -
 * здесь ”Non-Repeatable Reads” не прослеживается.
 * Поскольку SERIALIZABLE максимально изолирует
 * транзакции друг от друга, пока транзакция сессии 1 не
 * завершится, результат транзакции сессии 2 он не увидит */