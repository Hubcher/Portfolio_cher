-- For Session №1
SHOW TRANSACTION ISOLATION LEVEL;

-- For Session №2
SHOW TRANSACTION ISOLATION LEVEL;

-- For Session №1
BEGIN;

-- For Session №2
BEGIN;

-- For Session №1
/* Вывод текущего кортежа */
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';

-- For Session №2
/* Вывод текущего кортежа */
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';

-- For Session №1
/* Обновление данных */
UPDATE pizzeria SET rating = 4 WHERE name = 'Pizza Hut';

-- For Session №2
/* Обновление данных второй  сессии сопровождается 
 * ожиданием окончания транзакции первой сессии */
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';

-- For Session №1
COMMIT;
-- For Session №2
COMMIT;
-- For Session №1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- For Session №2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';


/* Вывод: при последовательной фиксации двух транзакций, 
 * изменения первой транзакции будут утеряны из-за 
 * перезаписи их второй транзакцией */