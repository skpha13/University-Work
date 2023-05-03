select JOB_ID,decode(DEPARTMENT_ID,30,sum(SALARY),0) DEP30, decode(department_id,50,sum(SALARY),0) DEP50, decode(department_id,80,sum(SALARY),0) DEP80
from EMPLOYEES
group by JOB_ID, DEPARTMENT_ID;

select LAST_NAME, SALARY, DEPARTMENT_ID, (select round(avg(SALARY))
                                            from EMPLOYEES
                                            where e.DEPARTMENT_ID = DEPARTMENT_ID) media,
                                        (select count(*)
                                         from EMPLOYEES e
                                         where e.DEPARTMENT_ID = DEPARTMENT_ID) Numar,
                                        (select DEPARTMENT_NAME
                                        from DEPARTMENTS
                                        where e.DEPARTMENT_ID = DEPARTMENT_ID) as "DEP NAME"

from EMPLOYEES e
where SALARY > (select round(avg(SALARY))
                from EMPLOYEES
                where e.DEPARTMENT_ID = DEPARTMENT_ID)
order by 3,2;

select LAST_NAME, SALARY
from EMPLOYEES e
where SALARY = (select min(salary)
                from EMPLOYEES e2
                where e2.DEPARTMENT_ID = e.DEPARTMENT_ID);

select LAST_NAME
from EMPLOYEES
where DEPARTMENT_ID in (select DEPARTMENT_ID
                        from EMPLOYEES e
                        where salary = (select max(SALARY)
                                        from EMPLOYEES
                                        where DEPARTMENT_ID = 30));

select LAST_NAME
from EMPLOYEES e
where exists(select 1
             from EMPLOYEES
             where e.DEPARTMENT_ID = DEPARTMENT_ID
             and salary = (select max(SALARY)
                           from EMPLOYEES
                           where DEPARTMENT_ID = 30));

select DEPARTMENT_ID, DEPARTMENT_NAME
from DEPARTMENTS d
where not exists(select 1
                from EMPLOYEES
                where EMPLOYEE_ID = d.DEPARTMENT_ID);
-- not exists(null) => true