-- For Session №1
BEGIN;
-- For Session №2
BEGIN;
-- For Session №1
SHOW TRANSACTION ISOLATION LEVEL;
-- For Session №2
SHOW TRANSACTION ISOLATION LEVEL;
-- For Session №1
UPDATE pizzeria SET rating = 2 WHERE id = 1;
-- For Session №2
UPDATE pizzeria SET rating = 3 WHERE id = 2;
-- For Session №1
UPDATE pizzeria SET rating = 1 WHERE id = 2;
-- For Session №2
UPDATE pizzeria SET rating = 5 WHERE id = 1;
-- For Session №1
COMMIT;
-- For Session №2
COMMIT;
-- For Session №1
SELECT * FROM pizzeria;
-- For Session №2
SELECT * FROM pizzeria;

/*Рассмотрим так называемый “Christ-Lock'*/
/* В чем же он заключается?
 * После последовательных изменений одного кортежей в каждой
 * сессии (разных по отношению друг другу), мы пытаемся
 * следующим изменением в первой сессии изменить кортеж, который
 * изменила вторая сессия. Вспоминаем задание 01, где в таком
 * случае мы застывали в ожидании окончания транзакции второй
 * сессии, здесь происходит тоже самое. Теперь возвращаясь во
 * вторую сессию и производя те же манипуляции но отношению к
 * первой сессии в теории мы должны получить то же ожидание. Но
 * это по сути замкнутый круг, ни один не закончит транзакцию пока
 * не дождется друг друга. Поэтому во второй сессии нас
 * заблокируют. В итоге данные будут актуальны только состоящие
 * из изменений первой сессии. */