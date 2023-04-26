select d.DEPARTMENT_ID, d.DEPARTMENT_NAME, sum(e.SALARY)
from EMPLOYEES e, departments d
where e.DEPARTMENT_ID=d.DEPARTMENT_ID
group by d.department_id, d.department_name;

select min(sum(e.salary))
from EMPLOYEES e, DEPARTMENTS d
where e.DEPARTMENT_ID=d.DEPARTMENT_ID
group by d.DEPARTMENT_ID,d.DEPARTMENT_NAME;

select d.department_id, d.department_name, sum(e.salary)
from EMPLOYEES e, DEPARTMENTS d
where e.DEPARTMENT_ID=d.DEPARTMENT_ID
group by d.DEPARTMENT_ID,d.DEPARTMENT_NAME
having sum(e.SALARY) = (select min(sum(e.salary))
                        from EMPLOYEES e, DEPARTMENTS d
                        where e.DEPARTMENT_ID=d.DEPARTMENT_ID
                        group by d.DEPARTMENT_ID,d.DEPARTMENT_NAME);

select d.DEPARTMENT_ID, d.DEPARTMENT_NAME, avg(e.SALARY)
from EMPLOYEES e, departments d
where e.DEPARTMENT_ID=d.DEPARTMENT_ID
group by d.department_id, d.department_name;

select max(avg(e.SALARY))
from EMPLOYEES e, departments d
where e.DEPARTMENT_ID=d.DEPARTMENT_ID
group by d.department_id, d.department_name;


select d.DEPARTMENT_ID, d.DEPARTMENT_NAME, round(avg(e.SALARY))
from EMPLOYEES e, departments d
where e.DEPARTMENT_ID=d.DEPARTMENT_ID
group by d.department_id, d.department_name
having round(avg(e.salary)) = (select max(round(avg(e.SALARY)))
                                from EMPLOYEES e, departments d
                                where e.DEPARTMENT_ID=d.DEPARTMENT_ID
                                group by d.department_id, d.department_name);

-- aici nu se calculeaza de doua ori
with
aux as (select d.DEPARTMENT_ID, d.DEPARTMENT_NAME, round(avg(e.SALARY)) media
        from EMPLOYEES e, departments d
        where e.DEPARTMENT_ID=d.DEPARTMENT_ID
        group by d.department_id, d.department_name) ,
maximul as (
    select max(media) maxim
    from aux )
select *
from aux;

select d.DEPARTMENT_NAME, min(e.SALARY) Salariu
from EMPLOYEES e, departments d
where e.DEPARTMENT_ID=d.DEPARTMENT_ID
group by d.department_id, d.department_name
having round(avg(e.salary)) = (select max(round(avg(e.SALARY)))
                                from EMPLOYEES e, departments d
                                where e.DEPARTMENT_ID=d.DEPARTMENT_ID
                                group by d.department_id, d.department_name);

-- 4.a
-- left outer join pentru a afisa si departamentele cu 0 angajati
select d.DEPARTMENT_ID,d.DEPARTMENT_NAME, count(e.EMPLOYEE_ID) as "Nr. Angajati"
from EMPLOYEES e, DEPARTMENTS d
where e.DEPARTMENT_ID(+)=d.DEPARTMENT_ID
group by d.DEPARTMENT_ID,d.DEPARTMENT_NAME
having count(*) < 4;

select j.JOB_TITLE,(j.MAX_SALARY+j.MIN_SALARY)/2 as "Medie Aritmetica", (j.MAX_SALARY-j.MIN_SALARY) Diferenta
from JOBS j
group by j.JOB_ID, j.JOB_TITLE, j.MAX_SALARY, j.MIN_SALARY;

select d.DEPARTMENT_NAME,e.FIRST_NAME || ' ' || e.LAST_NAME as Nume, e.SALARY
from DEPARTMENTS d, EMPLOYEES e
where d.DEPARTMENT_ID = e.EMPLOYEE_ID and e.SALARY = (select min(e.SALARY)
                                                        from EMPLOYEES e
                                                        where e.DEPARTMENT_ID = DEPARTMENT_ID);