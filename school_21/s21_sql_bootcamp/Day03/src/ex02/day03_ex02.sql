WITH buff_of_id AS (
    SELECT menu.id AS menu_id FROM menu
    EXCEPT ALL
    SELECT person_order.menu_id FROM person_order
    ORDER BY menu_id
)
SELECT menu.pizza_name, menu.price, pizzeria.name AS pizzeria_name
FROM buff_of_id
LEFT JOIN menu ON buff_of_id.menu_id = menu.id
LEFT JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
ORDER BY pizza_name, price;
