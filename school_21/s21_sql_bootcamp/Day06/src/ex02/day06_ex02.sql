SELECT person.name AS name, menu.pizza_name, menu.price,
       (menu.price * (1 - person_discounts.discount/100)) AS discount_price, pizzeria.name AS pizzeria_name
FROM person_order
LEFT JOIN person ON person_order.person_id = person.id
LEFT JOIN menu ON menu.id = person_order.menu_id
LEFT JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
LEFT JOIN person_discounts ON person_discounts.person_id = person_order.person_id AND
                              person_discounts.pizzeria_id = menu.pizzeria_id
ORDER BY name, pizza_name;
