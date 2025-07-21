CREATE SEQUENCE seq_person_discount START WITH 1;
SELECT SETVAL('seq_person_discount', (SELECT MAX(id) FROM person_discounts));

ALTER TABLE person_discounts
    ALTER COLUMN id SET DEFAULT (NEXTVAL('seq_person_discount'));
