select PROJECT_ID
from PROJECT;

select * from EMPLOYEES;

select count(project_id) as PROIECT, employee_id
from works_on
group by employee_id;

-- sau

select EMPLOYEE_ID, count(PROJECT_ID)
from WORKS_ON
group by EMPLOYEE_ID;

-- cate proiecte are fiecare employee
select e.employee_id, count(w.project_id)
from employees e, works_on w
where e.employee_id = w.employee_id(+)
group by e.employee_id;

-- cu subcereri corelate
-- nu punem count(*) ca ia in considerare NULL
select e.employee_id, (select count(w.project_id)
                       from works_on w
                       where w.employee_id = e.employee_id) nr
from employees e;


select EMPLOYEE_ID, count(PROJECT_ID)
from WORKS_ON
group by EMPLOYEE_ID
having count(PROJECT_ID) = (with tab as(select count(project_id) nr, employee_id
                                        from works_on
                                        group by employee_id)
                            select max(nr)
                            from tab);
-- fara max(select...

select distinct EMPLOYEE_ID
from WORKS_ON wr
where not exists(
    select PROJECT_ID
    from PROJECT p
    where to_char(p.START_DATE,'MM') <= 6 and to_char(p.START_DATE, 'YYYY') = 2006
    minus
    select p.project_id
    from PROJECT p, WORKS_ON w
    where p.PROJECT_ID = w.PROJECT_ID and w.EMPLOYEE_ID = wr.EMPLOYEE_ID
);