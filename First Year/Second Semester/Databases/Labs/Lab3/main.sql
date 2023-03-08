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
                    
select E.last_name, E.hire_date
from employees E
join employees E2 on(E.hire_date>E2.hire_date)
where initcap(E2.last_name) = 'Gates';

select e.last_name,to_char(e.hire_date,'Month'),to_char(e.hire_date,'YYYY')
from employees e
where e.department_id = (select e2.department_id -- putem folosi egal pentru ca e doar un Gates
                        from employees e2
                        where initcap(e2.last_name) = 'Gates') 
    and lower(e.last_name) like '%a%' and e.last_name != 'Gates';
    
select e.last_name,to_char(e.hire_date,'Month'),to_char(e.hire_date,'YYYY')
from employees e
join employees e2 using(department_id)
where initcap(e2.last_name) = 'Gates' and lower(e.last_name) like '%a%';

-- daca cererea necorelata are mai multe rezultate nu mai merege cu = < >
-- dar putem folosi in
-- in subcerere necorelata nu returnam mai mult de 1 coloana, doar 1

-- select e.* afiseaza toate coloanele pentru employees

-- union face reuniunea, dar elimina duplicatele

select e.last_name || ' ' || e.first_name Nume, c.country_name, l.location_id
from employees e, departments d, countries c, locations l
where l.country_id(+) = c.country_id
and d.location_id(+) = l.location_id
and e.department_id(+) = d.department_id;

