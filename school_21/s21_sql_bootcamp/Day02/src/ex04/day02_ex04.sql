SELECT pizza_name, pizzeria.name AS pizzeria_name, price
FROM menu
LEFT JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
WHERE
  menu.pizza_name='mushroom pizza' OR menu.pizza_name='pepperoni pizza'
ORDER BY menu.pizza_name, pizzeria_name;
