--se executa mai intai clauza FROM dupa WHERE dupa SELECT si dupa order by
select employee_id, salary sal
from employees
where sal > 10000
order by sal desc;

describe employees;

select employee_id,first_name || ' ' || last_name as NAME,job_id,hire_date
from employees;


select employee_id,first_name || ' ' || last_name || ', ' || job_id || ', ' || hire_date as final
from employees;

select 1+2
from dual;

select sysdate
from dual;

select to_char(sysdate, 'DAY/MM/YEAR') data
from dual;

--order by 1 asc, 2 desc; pentru a ordona prima coloana crescator si a doua descrecator

select first_name, salary, commission_pct
from employees
order by commission_pct desc; --afiseaza pe primii cu null

select first_name, salary, commission_pct, nvl(commission_pct,0) comis
from employees
order by comis desc; --pentru a scapa de null si a afisa 0 in loc de el

select to_char(sysdate,'DD/MM/YYYY') data,to_char(sysdate,'HH24:MI:SS') timp
from dual;

select employee_id,last_name
from employees
where lower(last_name) like '__a%';

select last_name,first_name
from employees
where lower(last_name) like '%l%l%' and (department_id = 30 or manager_id = 102);


select last_name,first_name,job_id,salary
from employees
where (lower(job_id) like '%clerk%' or lower(job_id) like '%rep%') and salary not in (3200,2700,2500,3100,6200);
