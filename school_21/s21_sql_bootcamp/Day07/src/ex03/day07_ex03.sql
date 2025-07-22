SELECT COALESCE(orderd.name, visit.name) AS name, (COALESCE(visit.count, 0) + COALESCE(orderd.count, 0)) AS total_count
FROM (SELECT pizzeria.name, pizzeria_visits_count.count, 'visit' AS action_type
      FROM (SELECT pizzeria_id, COUNT(pizzeria_id) AS count
            FROM person_visits
            GROUP BY pizzeria_id) AS pizzeria_visits_count
      LEFT JOIN pizzeria ON pizzeria.id = pizzeria_visits_count.pizzeria_id) as visit
FULL JOIN
    (SELECT pizzeria.name, pizzeria_order_count.count, 'order' AS action_type
    FROM(SELECT pizzeria_id, COUNT(pizzeria_id) AS count
         FROM person_order LEFT JOIN menu ON menu.id = person_order.menu_id
         GROUP BY pizzeria_id) AS pizzeria_order_count
    LEFT JOIN pizzeria ON pizzeria.id = pizzeria_order_count.pizzeria_id) as orderd
ON orderd.name = visit.name
ORDER BY total_count DESC, name;
