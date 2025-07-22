SELECT person.name, person_visits_count.count_of_visits
FROM (SELECT person_id, COUNT(person_id) AS count_of_visits
      FROM person_visits
      GROUP BY person_id) AS person_visits_count
LEFT JOIN person ON person.id = person_visits_count.person_id
ORDER BY count_of_visits DESC, name
LIMIT 4;
