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

select upper(substr(first_name,1,1)) || lower(substr(first_name,2,length(first_name))) 'Nume'
from employees;