WITH visit_dates AS (
    SELECT DISTINCT visit_date
    FROM person_visits
    WHERE person_id = 1 OR person_id = 2
)
SELECT DAYS.date AS missing_date
FROM GENERATE_SERIES('2022-01-01', '2022-01-10', interval '1 day') AS DAYS
LEFT JOIN visit_dates
ON DAYS.date = visit_dates.visit_date
WHERE visit_dates.visit_date IS NULL
ORDER BY missing_date;