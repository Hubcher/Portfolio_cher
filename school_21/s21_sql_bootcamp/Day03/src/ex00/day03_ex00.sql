SELECT menu.pizza_name, menu.price, pizzeria.name AS pizzeria_name, person_visits.visit_date FROM menu
LEFT JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
LEFT JOIN person_visits ON pizzeria.id = person_visits.pizzeria_id
LEFT JOIN person ON person_visits.person_id = person.id
WHERE person.name LIKE 'Kate' AND (menu.price BETWEEN 800 AND 1000)
ORDER BY menu.pizza_name, menu.price, pizzeria_name;
