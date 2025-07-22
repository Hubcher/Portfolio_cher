SELECT person.name, count_of_visits
FROM (SELECT person_id, COUNT(person_visits.person_id) AS count_of_visits
      FROM person_visits
      GROUP BY person_id
      HAVING COUNT(person_visits.person_id) > 3) AS person_visits_count
LEFT JOIN person ON person.id = person_visits_count.person_id;
