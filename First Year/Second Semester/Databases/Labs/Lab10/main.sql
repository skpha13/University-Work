select LAST_NAME
from EMPLOYEES
where DEPARTMENT_ID in (select DEPARTMENT_ID
                        from EMPLOYEES
                        where salary = (select max(SALARY)
                                        from EMPLOYEES
                                        where DEPARTMENT_ID = 30));

select *
from EMPLOYEES
where EMPLOYEE_ID in (select MANAGER_ID
                      from EMPLOYEES
                      where manager_id is not null
                      group by MANAGER_ID
                      having count(*) >= 2);

select EMPLOYEE_ID, MANAGER_ID
from EMPLOYEES
where LAST_NAME like 'King' and FIRST_NAME like 'Steven';

select DEPARTMENT_ID
from EMPLOYEES
where EMPLOYEE_ID = 100;

with subord_directi as (select EMPLOYEE_ID, LAST_NAME, FIRST_NAME, HIRE_DATE
                        from EMPLOYEES e, DEPARTMENTS d
                        where e.EMPLOYEE_ID = d.DEPARTMENT_ID and e.MANAGER_ID in (select DEPARTMENT_ID
                                                                                  from EMPLOYEES
                                                                                  where e.EMPLOYEE_ID = (select EMPLOYEE_ID
                                                                                                         from EMPLOYEES
                                                                                                         where LAST_NAME like 'King' and FIRST_NAME like 'Steven')))
select *
from subord_directi
order by 4;

-- NU FACEM ASA pentru ca order by se executa dupa rownum
select EMPLOYEE_ID
from EMPLOYEES
where ROWNUM <= 10
order by SALARY desc;

-- ASA DA
select *
from (select EMPLOYEE_ID, SALARY
      from EMPLOYEES
      order by SALARY desc)
where rownum <= 10;

select avg(SALARY)
from JOBS j, EMPLOYEES e
where e.JOB_ID = j.JOB_ID
group by e.JOB_ID;

select *
from (select avg(SALARY) med
        from JOBS j, EMPLOYEES e
        where e.JOB_ID = j.JOB_ID
        group by e.JOB_ID
        order by med)
where rownum <= 3;


select *
from (select JOB_ID, avg(SALARY) medie
      from EMPLOYEES
      group by JOB_ID
      order by medie)
where ROWNUM <= 3;

select JOB_TITLE
from JOBS;


DEFINE var;
select LAST_NAME, DEPARTMENT_ID, SALARY
from EMPLOYEES e, JOBS j
where e.employee_id = j.job_id and lower('&var') = lower(j.JOB_TITLE);