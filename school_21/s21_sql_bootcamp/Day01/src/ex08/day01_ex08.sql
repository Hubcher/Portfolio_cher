SELECT order_date,
	CONCAT(name,' (age:', age,')') AS person_information
FROM person_order
    NATURAL JOIN (SELECT id AS person_id, name, age FROM person) AS person_info
ORDER BY order_date, name;
