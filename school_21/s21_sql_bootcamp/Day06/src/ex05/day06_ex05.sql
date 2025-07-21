COMMENT ON TABLE person_discounts IS 'Скидки на пиццу для каждого человека по отпределенным пиццериям';
COMMENT ON COLUMN person_discounts.id IS 'Уникальный индекс каждой записи таблицы person_discounts';
COMMENT ON COLUMN person_discounts.person_id IS 'Внешний ключ person';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Внешний ключ pizzeria_id';
COMMENT ON COLUMN person_discounts.discount IS 'Скидка на пиццу в процентах';
