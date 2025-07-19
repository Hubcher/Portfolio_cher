INSERT INTO person_visits
VALUES (
    (SELECT MAX(id)+1 FROM person_visits),
    (SELECT id FROM person WHERE name = 'Dmitriy'),
    (SELECT id FROM pizzeria WHERE name = 'DoDo Pizza'),
    '2022-01-08'
);

INSERT INTO menu
VALUES
(19, (SELECT id FROM pizzeria WHERE name = 'Dominos'), 'greek pizza', 800);
VALUES (
    (SELECT MAX(id)+1 FROM person_order),
    (SELECT id FROM person WHERE name = 'Dmitriy'),
    (SELECT id FROM menu WHERE pizzeria_id = (SELECT id FROM pizzeria WHERE name = 'DoDo Pizza') AND
    pizza_name = 'cheese pizza'),
    '2022-01-08'
);

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;
SELECT * FROM mv_dmitriy_visits_and_eats;