WITH
    cte_p_pizza AS (
        SELECT person.name AS person_name
        FROM person_order
        JOIN person ON person_order.person_id = person.id
        JOIN menu ON menu.id = person_order.menu_id
        WHERE person.gender = 'female' AND pizza_name = 'pepperoni pizza'
    ),
    cte_ch_pizza AS (
        SELECT person.name AS person_name
        FROM person_order
        JOIN person ON person_order.person_id = person.id
        JOIN menu ON menu.id = person_order.menu_id
        WHERE person.gender = 'female' AND pizza_name = 'cheese pizza'
    )
SELECT person.name
FROM person
JOIN cte_p_pizza ON cte_p_pizza.person_name = person.name
JOIN cte_ch_pizza ON cte_ch_pizza.person_name = person.name;
