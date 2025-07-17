SELECT DAYS.date as missing_date
FROM GENERATE_SERIES('2022-01-01', '2022-01-10', interval '1 day') as DAYS
LEFT JOIN
  (SELECT DISTINCT visit_date FROM person_visits
  WHERE person_id = 1 OR person_id = 2) as visit_of_1_or_2
ON DAYS.date=visit_of_1_or_2.visit_date
WHERE visit_of_1_or_2.visit_date is NULL
ORDER BY missing_date;
