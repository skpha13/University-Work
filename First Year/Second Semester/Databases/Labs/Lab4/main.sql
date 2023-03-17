select * from departments;

select l.city, d.department_name dep
from locations l, departments d
where l.location_id = d.location_id(+);

select l.city, d.department_name dep
from locations l full outer join departments d
on (l.location_id = d.department_id);

SELECT d.department_id
FROM departments d ---lista tututor departamentelor din firma
MINUS
SELECT department_id
FROM employees; -- departamentele in care lucreaza angajatii

select department_id
from departments 
where lower(department_name) like '%re%'
INTERSECT
select department_id
from employees
where upper(job_id) = 'HR_REP';

