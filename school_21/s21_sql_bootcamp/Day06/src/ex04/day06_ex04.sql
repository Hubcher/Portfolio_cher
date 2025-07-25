ALTER TABLE person_discounts
    ADD CONSTRAINT ch_nn_person_id CHECK(person_id is NOT NULL),
    ADD CONSTRAINT ch_nn_pizzeria_id CHECK(pizzeria_id is NOT NULL),
    ADD CONSTRAINT ch_nn_discount CHECK(discount is NOT NULL),
    ADD CONSTRAINT ch_range_discount CHECK(discount >= 0 AND discount < 100),
    ALTER COLUMN discount SET DEFAULT 0;

-- ALTER TABLE person_discounts
--     DROP CONSTRAINT IF EXISTS ch_nn_person_id,
--     DROP CONSTRAINT IF EXISTS ch_nn_pizzeria_id,
--     DROP CONSTRAINT IF EXISTS ch_nn_discount,
--     DROP CONSTRAINT IF EXISTS ch_range_discount;
