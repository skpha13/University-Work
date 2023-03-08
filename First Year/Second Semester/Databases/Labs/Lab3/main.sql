describe employees;
describe department;

select e.last_name || ' ' || e.first_name, e.manager_id, d.department_name, d.manager_id
from employees e, departments d
where e.manager_id = d.manager_id;


select e.last_name || ' ' || e.first_name, d.department_name, d.manager_id, e.manager_id managerul_direct, d.manager_id Manager_de_departament
from employees e, departments d
where e.department_id = d.department_id;

select e.last_name || ' ' || e.last_name, e.salary, j.job_title, c.country_name, l.city
from employees e, jobs j, departments d, countries c, locations l
where e.manager_id = 100 and e.job_id = j.job_id and e.department_id = d.department_id and d.location_id = l.location_id and l.country_id = c.country_id;

-- salariul angajatului cu codul 100
select salary
from employees
where employee_id = 100;

-- cerere necorelata
select j.job_title
from jobs j
where j.max_salary<(select salary
                    from employees
                    where employee_id = 100);
                    
