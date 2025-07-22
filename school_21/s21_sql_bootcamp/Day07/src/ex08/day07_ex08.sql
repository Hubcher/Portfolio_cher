SELECT person.address, pizzeria.name, COUNT(menu.pizzeria_id) AS count_of_orders
FROM person_order
JOIN menu ON menu.id = person_order.menu_id
JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
JOIN person ON person.id = person_order.person_id
GROUP BY person.address, pizzeria.name
ORDER BY person.address, pizzeria.name;
