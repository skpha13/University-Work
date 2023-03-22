select * from departments;

create table emp_mal as select * from employees;
create table dept_mal as select * from departments;

select * from emp_mal;
select * from dept_mal;

-- nu s-a copiat cheia primara
describe employees;
describe emp_mal;

alter table emp_mal
add constraint pk_emp_mal primary key(employee_id);

alter table dept_mal
add constraint pk_dept_mal primary key(department_id);

alter table emp_mal
add constraint fk_emp_DEPT_mal FOREIGN key(department_id) REFERENCES dept_mal(department_id);

describe emp_mal;
describe dept_mal;

select *
from user_constraints
where lower(table_name) = 'emp_mal';

select *
from user_constraints
where lower(table_name) = 'dept_mal';

insert into dept_mal(department_id,department_name)
values (300,'Programare');

select * from dept_mal where department_id = 300;

commit;

describe emp_mal;

insert into emp_mal(employee_id,last_name,first_name,email,hire_date,job_id,salary,department_id)
values (252,'Mincu','Adrian','mail@gmail.com',SYSDATE,'test_job',6000,300);

select * from emp_mal where employee_id = 252;

commit;

describe emp_mal;

insert into emp_mal
values(253,null,'Mincu','mail@gmail.com',null,sysdate,'test_job',null,null,null,300);

select * from emp_mal where employee_id = 253;

commit;

create table emp1_mal as select * from employees where 1=0;

insert into emp1_mal
select * from employees where commission_pct > 0.25;

select * from emp1_mal;

rollback;

drop table emp1_mal;

update emp_mal
set salary = nvl(salary *1.05,0);

select * from emp_mal;

rollback;

update emp_mal
set job_id = 'SA_REP'
where department_id = 80 and commission_pct != 0;

select * from emp_mal;