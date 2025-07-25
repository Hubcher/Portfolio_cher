/* Продолжаем работу с аномалией ”phantom reads",
 * но уже на уровне изоляции REPEATABLE READ */
-- For Session №1
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- For Session №2
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- For Session №1
SELECT SUM(rating) FROM pizzeria;

-- For Session №2
INSERT INTO pizzeria VALUES (11, 'Kazan Pizza 2', 4.0);
COMMIT;

-- For Session №1
SELECT SUM(rating) FROM pizzeria;

COMMIT;
-- For Session №1

SELECT SUM(rating) FROM pizzeria;

-- For Session №2

SELECT SUM(rating) FROM pizzeria;

/* Как и в 4 задании, когда мы сравнивали REPEATABLE READ и
 * SERIALIZABLE на примере “Non-Repeatable Reads“, здесь
 * происходит тоже самое. SERIALIZABLE защищает транзакцию
 * первой сессии от изменений во второй имитируя работу их так,
 * будто они выполнялись последовательно (но только в случае,
 * если они не конфликтуют между собой) */