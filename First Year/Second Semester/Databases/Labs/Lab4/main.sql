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

select last_name, salary
from employees 
where manager_id in (select employee_id
                    from employees
                    where manager_id is NULL);
                    
select last_name, department_id, salary
from employees
where department_id in (select department_id
                        from employees
                        where commission_pct is not NULL)
                    and salary in (select salary
                                    from employees
                                    where commission_pct is not NULL);
                                    
select last_name, salary
from employees
where salary > ANY (select salary
                    from employees
                    where upper(job_id) like '%CLERK%')
order by salary desc;

select last_name, salary
from employees
where salary > ALL (select salary
                    from employees
                    where upper(job_id) like '%CLERK%')
order by salary desc;
