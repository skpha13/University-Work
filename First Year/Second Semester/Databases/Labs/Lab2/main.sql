describe employees;

SELECT first_name,last_name
FROM employees
WHERE manager_id is null;

select to_date('26/10/2022','DD/MM/YYYY')
from dual;

select to_char(to_date('26/MAR/22','DD/MON/YY'),'YYYY')
from dual;

select substr('primavara',4)
from dual;

select substr('primavara',-4)
from dual;

select first_name || ' ' || last_name || ' castiga ' || salary || ' lunar dar doreste ' || salary*3 as "Salariu Ideal"
from employees;

select INITCAP(first_name) as Prenume,upper(last_name) as Nume,length(last_name) as "Lungime Nume"
from employees
where lower(substr(last_name,-1)) = 'j' or lower(substr(last_name,-1))='m' or lower(substr(last_name,3,1)) = 'a'
order by length(last_name) desc;

select INITCAP(first_name) as Prenume,upper(last_name) as Nume,length(last_name) as "Lungime Nume"
from employees
where lower(last_name) like 'j%' or lower(last_name) like 'm%' or lower(last_name) like '__a%' 
order by length(last_name) desc;

select employee_id,last_name,department_id
from employees
where lower(trim(both ' ' from first_name)) = 'steven';

select employee_id,last_name,instr(lower(last_name),'a')
from employees
where lower(substr(last_name,-1)) = 'e';

select last_name,first_name,nvl2(manager_id,1,0)
from employees;

select last_name,first_name,nvl2(manager_id,'Are manager','Nu are manager')
from employees;

select to_char(sysdate+30,'DD/MON/YYYY HH:MM')
from dual;

--to_date pune automat ora la 00:00
select to_char(to_date('31/12/2023')-trunc(sysdate))
from dual;

select to_date('31-12' || to_char(sysdate,'YYYY')) - trunc(sysdate)
from dual;

select 365 - to_char(sysdate,'DDD')
from dual;

select last_name,salary,salary*nvl(commission_pct,1),commission_pct
from employees
where salary + nvl(commission_pct,0) > 10000;