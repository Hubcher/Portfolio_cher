SELECT
  COALESCE(PERSON.name,'-') as person_name,
  VISIT.visit_date as visit_date,
  COALESCE(PIZZERIA.name,'-') as pizzeria_name
FROM
  (SELECT * from person_visits WHERE visit_date BETWEEN '2022-01-01' AND '2022-01-03') as VISIT
FULL JOIN person PERSON ON VISIT.person_id = PERSON.id
FULL JOIN pizzeria PIZZERIA ON VISIT.pizzeria_id = PIZZERIA.id
ORDER BY person_name, visit_date, pizzeria_name;
