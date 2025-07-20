SET enable_seqscan = off;
EXPLAIN ANALYZE
    SELECT
        menu.pizza_name,
        pizzeria.name AS pizzeria_name
FROM menu
JOIN pizzeria on menu.pizzeria_id = pizzeria.id;