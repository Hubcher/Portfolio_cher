SELECT generated_date AS missing_days FROM v_generated_dates
EXCEPT
SELECT visit_date FROM person_visits
ORDER BY missing_days;