--Sapt5+6 - Laborator4.pdf
delete from departments where department_id in (111,112);

select * from departments;

commit;

rollback;

drop table DEPT_***;
drop table emp_***;

1. Sã se creeze tabelele EMP_***, DEPT_*** (în ºirul de caractere “ong”, p reprezintã 
prima literã a prenumelui, iar nu reprezintã primele douã litere ale numelui dumneavoastrã),
prin copierea structurii ºi conþinutului tabelelor EMPLOYEES, respectiv DEPARTMENTS. 
drop table emp_pnu;
drop table dept_pnu;

CREATE TABLE emp_*** AS SELECT * FROM employees;
CREATE TABLE DEPT_*** AS SELECT * FROM departments; --table DEPT_*** created.

select * from DEPT_***; --27 rez
select * from emp_***;

select *
from tab;

--commit;
drop table emp_***; --sterge tabelul emp_***
drop table DEPT_***;


--drop table dep_mta;--sterge tabelul impreuna cu informatiile din el

2. Listaþi structura tabelelor sursã ºi a celor create anterior. Ce se observã?

describe employees;
Name           Null     Type         
-------------- -------- ------------ 
EMPLOYEE_ID    NOT NULL NUMBER(6)    --PK : not null + unicitate
FIRST_NAME              VARCHAR2(20) 
LAST_NAME      NOT NULL VARCHAR2(25) 
EMAIL          NOT NULL VARCHAR2(25) 
PHONE_NUMBER            VARCHAR2(20) 
HIRE_DATE      NOT NULL DATE         
JOB_ID         NOT NULL VARCHAR2(10) 
SALARY                  NUMBER(8,2)  
COMMISSION_PCT          NUMBER(2,2)  
MANAGER_ID              NUMBER(6)    
DEPARTMENT_ID           NUMBER(4)  

describe emp_***;
Name           Null     Type         
-------------- -------- ------------ 
EMPLOYEE_ID             NUMBER(6)    --nu mai este setata cheia primara( si nici cea externa)
FIRST_NAME              VARCHAR2(20) 
LAST_NAME      NOT NULL VARCHAR2(25) 
EMAIL          NOT NULL VARCHAR2(25) 
PHONE_NUMBER            VARCHAR2(20) 
HIRE_DATE      NOT NULL DATE         
JOB_ID         NOT NULL VARCHAR2(10) 
SALARY                  NUMBER(8,2)  
COMMISSION_PCT          NUMBER(2,2)  
MANAGER_ID              NUMBER(6)    
DEPARTMENT_ID           NUMBER(4)    

desc departments;
Name            Null     Type         
--------------- -------- ------------ 
DEPARTMENT_ID   NOT NULL NUMBER(4)     --pk
DEPARTMENT_NAME NOT NULL VARCHAR2(30) 
MANAGER_ID               NUMBER(6)    
LOCATION_ID              NUMBER(4)    

desc DEPT_***;
Name            Null     Type         
--------------- -------- ------------ 
DEPARTMENT_ID            NUMBER(4)     --nu avem setata cheia primara
DEPARTMENT_NAME NOT NULL VARCHAR2(30) 
MANAGER_ID               NUMBER(6)    
LOCATION_ID              NUMBER(4) 
--
--delete from departments where department_id in (111,112);
--
--drop table DEPT_***;
--CREATE TABLE DEPT_*** AS SELECT * FROM departments;

3. Listaþi conþinutul tabelelor create anterior.
select * from emp_ms; --107 rez
select * from DEPT_ms; --27 dept
commit;


delete from dept_*** where department_id in (111,112);
4. Pentru introducerea constrângerilor de integritate, executaþi instrucþiunile LDD indicate în continuare. 
Prezentarea detaliatã a LDD se va face în cadrul laboratorului 5. 

ALTER TABLE emp_***
ADD CONSTRAINT pk_emp_*** PRIMARY KEY(employee_id);
    --- pk_emp_*** = nume unic de constrangere
    --punem cheia primara pe coloana employee_id a tabelei emp_***
--table emp_*** altered.

desc emp_***;
Name           Null     Type         
-------------- -------- ------------ 
EMPLOYEE_ID    NOT NULL NUMBER(6)     --pk
FIRST_NAME              VARCHAR2(20) 
LAST_NAME      NOT NULL VARCHAR2(25) 
EMAIL          NOT NULL VARCHAR2(25) 
PHONE_NUMBER            VARCHAR2(20) 
HIRE_DATE      NOT NULL DATE         
JOB_ID         NOT NULL VARCHAR2(10) 
SALARY                  NUMBER(8,2)  
COMMISSION_PCT          NUMBER(2,2)  
MANAGER_ID              NUMBER(6)    
DEPARTMENT_ID           NUMBER(4)    

--adaugam cheia primara pe coloana department_id din tabela de DEPT_***
ALTER TABLE DEPT_*** 
ADD CONSTRAINT pk_DEPT_*** PRIMARY KEY(department_id); 
--table DEPT_*** altered.

desc DEPT_***;
Name            Null     Type         
--------------- -------- ------------ 
DEPARTMENT_ID   NOT NULL NUMBER(4)     --pk
DEPARTMENT_NAME NOT NULL VARCHAR2(30) 
MANAGER_ID               NUMBER(6)    
LOCATION_ID              NUMBER(4) 

ALTER TABLE emp_***
ADD CONSTRAINT fk_emp_DEPT_*** FOREIGN KEY(department_id)   --dept_id din emp_***
                        REFERENCES DEPT_***(department_id);
--fiecare angajat lucreaza pe un departament care exista in tabela de departamente                                         
--table emp_*** altered.


----Atentie, daca nu este setata cheia primara pe tabela dept_***, atunci nu vom putea
--seta cheia externa pe tabela emp_***
--avem eroarea: ORA-02270: no matching unique or primary key for this column-list

drop table emp_pnu;
drop table dept_pnu;
--ce contrangeri avem pe o tabela
select *
from user_constraints
where lower(table_name) = 'emp_***';
--6 constrangeri : 4 x C (not null), 1 R (cheia externa), 1 P (cheia primara)

select *
from user_constraints
where lower(table_name) = 'dept_***';
--2 constrangeri

select *
from user_constraints
where lower(table_name) = 'employees';
--10 constrangeri

--Suplimentar:
alter table emp_***
drop constraint FK_EMP_DEPT_***;

alter table DEPT_***
drop constraint PK_DEPT_***;
--cheie externa: ORA-02270: nu exista chei primare sau unice potrivite pentru aceasta lista-coloana

--ce contrangeri avem pe o tabela
select *
from user_constraints
where lower(table_name) = 'emp_***';

select *
from user_constraints
where lower(table_name) = 'dept_***';

--pe ce coloane sunt setate constrangerile
select *
 from user_cons_columns
 where lower(table_name) = 'dept_***';

select *
 from user_cons_columns
 where lower(table_name) = 'emp_***';
 
Observa?ie: Ce constrângere nu am implementat?
--manager_id
commit;


Select * from emp_***;

5. Sã se insereze departamentul 300, cu numele Programare în DEPT_***.
Analizaþi cazurile, precizând care este soluþia corectã ºi explicând 
erorile celorlalte variante. 
Pentru a anula efectul instrucþiunii(ilor) corecte, utilizaþi comanda ROLLBACK.

describe DEPT_***;

Name            Null     Type         
--------------- -------- ------------ 
DEPARTMENT_ID   NOT NULL NUMBER(4)    
DEPARTMENT_NAME NOT NULL VARCHAR2(30) 
MANAGER_ID               NUMBER(6)    
LOCATION_ID              NUMBER(4)   
a)
INSERT INTO DEPT_***
VALUES (300, 'Programare');
--ORA-00947: valori prea putine
--corect
INSERT INTO DEPT_***
VALUES (300, 'Programare',null, null );
--1 row inserted.

select * from DEPT_*** where department_id = 300;
rollback;

commit;

delete from DEPT_*** where department_id =300;

delete from DEPT_*** where department_id in (111,112);
b)
INSERT INTO DEPT_*** (department_id, department_name)
VALUES (300, 'Programare');
--1 rows inserted.
select * from DEPT_*** where department_id =300;
--300	Programare null null 
--s-a pus null implicit pt colonale care lipseau din lista de coloane 
--INSERT INTO DEPT_*** (department_id, department_name)
--incerc sa mai rulez inca odata insert-ul => eroare: ORA-00001: restrictia unica (GRUPA33.PK_DEPT_***) nu este respectata
--(avem cheia primara setata pe tabelul dept)
rollback;
select * from DEPT_***; --27 rez


c) 
INSERT INTO DEPT_*** (department_name, department_id)
VALUES (300, 'Programare'); 
--Programare --ORA-01722: numar nevalid

--corect
INSERT INTO DEPT_*** (department_name, department_id)
VALUES ( 'Programare', 300); 
cc)
INSERT INTO DEPT_*** (department_name, department_id)
VALUES (300, 111); --converis implicita pt 300 la '300'

select * from DEPT_*** where department_id = 111;
commit;
rollback;

delete from dept_*** where department_id=111;

d)
INSERT INTO DEPT_*** (department_id, department_name, location_id)
VALUES (300, 'Programare', null);
--1 rows inserted
--explicit pun null pt location_id
--implicit sa puna null pt manager_id
select * from DEPT_*** where department_id =300;
--300	Programare	null null
rollback;
e) 
INSERT INTO DEPT_*** (department_name, location_id)
VALUES ('Programare', null);
--ORA-01400: nu poate fi inserat NULL în ("GRUPA33"."DEPT_***"."DEPARTMENT_ID")

Executaþi varianta care a fost corectã de douã ori. Ce se obþine ºi de ce?
--avem chia primara setata


select * from dept_iac  where department_id =300;
commit;

--In final, vom adauga dept 300 in tabela DEPT_***
INSERT INTO DEPT_*** (department_id, department_name)
VALUES (300, 'Programare');

delete from DEPT_*** where department_id =300;

commit;

rollback;

6. Sã se insereze un angajat corespunzãtor departamentului introdus anterior în tabelul emp_***,
precizând valoarea NULL pentru coloanele a cãror valoare nu este cunoscutã la inserare 
(metoda implicitã de inserare). Determinaþi ca efectele instrucþiunii sã devinã permanente.
Atenþie la constrângerile NOT NULL asupra coloanelor tabelului!

commit;
--id ang 252

describe emp_***;

Name           Null     Type         
-------------- -------- ------------ 
EMPLOYEE_ID    NOT NULL NUMBER(6)    
FIRST_NAME              VARCHAR2(20) 
LAST_NAME      NOT NULL VARCHAR2(25) 
EMAIL          NOT NULL VARCHAR2(25) 
PHONE_NUMBER            VARCHAR2(20) 
HIRE_DATE      NOT NULL DATE         
JOB_ID         NOT NULL VARCHAR2(10) 
SALARY                  NUMBER(8,2)  
COMMISSION_PCT          NUMBER(2,2)  
MANAGER_ID              NUMBER(6)    
DEPARTMENT_ID           NUMBER(4)   

--delete from emp_*** where employee_id =252;
insert into emp_***
values (252, null, 'nume', 'nume@gmail.com', null, sysdate, 'test_job', null, null, null, 300); 
--null explicit
--test_job -- nu am setat cheia externa catre tabela de jobs
--ROLLBACK;
commit;

--atentie!
insert into emp_***
values (253, null, null, 'nume@gmail.com', null, sysdate, 'test_job', null, null, null, 300); 
--ORA-01400: cannot insert NULL into ("GRUPA32"."EMP_***"."LAST_NAME")

select * from emp_***; --108 ang
commit;

--stergem angajatul 252
delete from emp_***
where employee_id =252;

select * from emp_***
where employee_id =252;

ROLLBACK;

--insert 252 + ROLLBACK => se sterge angajatul 252
--insert 252 + commit; Daca dam ROLLBACK, nu se sterge angajatul 252
--La final facem Insert 252 + commit

7. Sã se mai introducã un angajat corespunzãtor departamentului 300, precizând dupã numele
tabelului lista coloanelor în care se introduc valori (metoda explicitã de inserare). 
Se presupune cã data angajãrii acestuia este cea curentã (SYSDATE). Salvaþi înregistrarea.

---null dat explicit
insert into emp_*** (employee_id, first_name, last_name, email, phone_number, hire_date, job_id,
                      salary, commission_pct, manager_id, department_id)
values (253, null, 'nume', 'nume@gmail.com', null, sysdate, 'test_job', null, null, null, 300); --null explicit


--null atribuit implicit
insert into emp_*** (employee_id, last_name, email,  hire_date, job_id,
                        department_id)
values (254, 'nume', 'nume@gmail.com', sysdate, 'test_job', 300); --null implicit

--atentie! --dept 301 nu exista in tabela de dept_***
insert into emp_*** (employee_id, last_name, email,  hire_date, job_id,
                        department_id)
values (255, 'nume', 'nume@gmail.com', sysdate, 'test_job', 301); 
--integrity constraint (GRUPA33.FK_EMP_DEPT_***) violated - parent key not found

select * from emp_***
where employee_id in (252, 253, 254,255);

select * from dept_***;

delete from dept_*** where department_id =301;

commit;
rollback;
----Am facut Insert 252 + commit +rollback => a ramas doar angajatul 252
----Am facut Insert 252 + commit + Inseram 253, 254 + rollback => a ramas doar angajatul 252

----Am facut Insert 252 + commit + Inseram 253, 254 + commit + rollback 
      -- => In emp_*** se gasesc toti cei 3 ang: 252, 253, 254

--atentie la departament
insert into emp_*** (employee_id, last_name, email,  hire_date, job_id,
                        department_id)
values (255, 'nume', 'nume@gmail.com', sysdate, 'test_job', 600); 
--ORA-02291: constrângere de integritate (GRUPA33.FK_EMP_DEPT_***) violata - cheia parinte negasita
--departamentul 600 nu exista
commit;

--
--delete from emp_*** where employee_id =252;
--commit;
--drop table emp_pnu;
--INSERT INTO emp_*** (employee_id, last_name, email, hire_date,
-- job_id, salary, commission_pct) 
--VALUES (252, 'Nume252', 'nume252@emp.com',SYSDATE, 'SA_REP', 5000, NULL);
--SELECT employee_id, last_name, email, hire_date, job_id, salary, commission_pct 
--FROM emp_***
--WHERE employee_id=252;
--ROLLBACK;
--
--INSERT INTO 
-- (SELECT employee_id, last_name, email, hire_date, job_id, salary, commission_pct 
-- FROM emp_***) 
--VALUES (252, 'Nume252', 'nume252@emp.com',SYSDATE, 'SA_REP', 5000, NULL);
--
--SELECT employee_id, last_name, email, hire_date, job_id, salary, commission_pct 
--FROM emp_***
--WHERE employee_id=252;
--
--ROLLBACK;

10. Creaþi un nou tabel, numit EMP1_***, care va avea aceeaºi structurã ca ºi EMPLOYEES, 
dar nicio înregistrare. 
Copiaþi în tabelul EMP1_*** salariaþii (din tabelul EMPLOYEES) 
al cãror comision depãºeºte 25% din salariu. 
 
--V1: Creaþi un nou tabel, numit EMP1_***, care va avea aceeaºi structurã ca ºi EMPLOYEES, dar nicio înregistrare. 
CREATE TABLE emp1_*** AS SELECT * FROM employees WHERE 1=0;  --comanda are commit implicit

select * from emp1_***; --0 rez

--stergem tabelul emp1
drop table emp1_***;

--V2: Creaþi un nou tabel, numit EMP1_***, care va avea aceeaºi structurã ca ºi EMPLOYEES, dar nicio înregistrare. 
CREATE TABLE emp1_*** AS SELECT * FROM employees; --commit implicit
select * from emp1_***; --107 rez
DELETE FROM emp1_***; --necesar daca nu aveam clauza WHERE de mai sus
--107 rows deleted.
select * from emp1_***; --0 rez

--salariaþii (din tabelul EMPLOYEES) al cãror comision depãºeºte 25% din salariu. 
SELECT * FROM employees WHERE commission_pct > 0.25; --11 rez
drop table emp1_pnu;

--Copiaþi în tabelul EMP1_*** salariaþii (din tabelul EMPLOYEES)
--al cãror comision depãºeºte 25% din salariu.
INSERT INTO emp1_*** 
SELECT * FROM employees WHERE commission_pct > 0.25; 
--11 rows inserted.

--adaugati salariatii al cãror comision depãºeºte 25% din salariu 
--cu informatii cate sunt strict necesare
desc emp1_***;
--incorect
INSERT INTO emp1_*** (last_name, email,  hire_date, job_id)
SELECT *  --aici este pb
FROM employees WHERE commission_pct > 0.25; 
--SQL Error: ORA-00913: too many values

--corect
INSERT INTO emp1_*** (last_name, email,  hire_date, job_id)
SELECT last_name, email,  hire_date, job_id
FROM employees WHERE commission_pct > 0.25; 

INSERT INTO emp1_*** (employee_id, last_name, email,  hire_date, job_id, department_id)
SELECT employee_id, last_name, email,  hire_date, job_id, department_id 
FROM employees WHERE commission_pct > 0.25;  --implicit valori de null pt restul coloanelor
--11 rows inserted

alter table emp1_***
add constraint pk_emp1 primary key(employee_id);

SELECT employee_id, last_name, salary, commission_pct FROM emp1_***; --33 rez

Ce va con?ine tabelul EMP1_*** în urma acestei succesiuni de comenzi?
ROLLBACK;

SELECT employee_id, last_name, salary, commission_pct FROM emp1_***; 
--107 rez (tabel creat cu a doua varianta)

SELECT employee_id, last_name, salary, commission_pct FROM emp1_***; 
--0 rez (tabel creat prin varianta 1)

desc emp1_***;

drop table emp1_***;


drop table departments;
--Table EMP1_*** dropped.



---atentie
CREATE TABLE emp1_*** AS SELECT * FROM employees WHERE commission_pct >0.25 ; 

commit;
---Update

update emp_***
set salary =10000; 
--110 rows updated.

select * from emp_***;

update emp_***
set salary =700
where lower(job_id) like 'test%';
--3 rows updated.  --252,253,254

rollback;


-- daca datele nu sunt corecte in tabelul emp_***( le suprascriu cu cele din employees, atentie la 252, 253, 254)
update emp_*** e
set e.salary = (select a.salary
                from employees a
                where a.employee_id = e.employee_id);
--110 rows updated
commit;

select a.salary
from employees a
where a.employee_id = 252;
--atentie
update emp_*** e
set e.salary = nvl((select a.salary
                from employees a
                where a.employee_id = e.employee_id),0);
--110 rows updated.  pune 0 la angajatii care nu se gasesc in employees

select a.salary
from emp_*** a
where a.employee_id = 252;
--atentie
update emp_*** e
set e.salary = nvl((select a.salary
                from employees a
                where a.employee_id = e.employee_id),0)
where e.employee_id in (Select employee_id
                        from employees); --107 rows updated.
commit;
rollback;

*/
--UPDATE


15. Mãriþi salariul tuturor angajaþilor din tabelul EMP_*** cu 5%. 
Vizualiza?i, iar apoi anulaþi modificãrile.

select employee_id, salary
from emp_***;
100	24000
101	17000
102	17000
103	9000
rollback;

update emp_***
set salary = salary + 0.05*salary; 
--set salary =  salary *1.05;
rollback;
--110 rows updated. 107+3 ang noi
--set salary =  salary *1.05
select employee_id, salary
from emp_***;
100	25200
101	17850
102	17850
103	9450
253	null
252	null
254	null

--luam in considerare ca avem si salary = null
update emp_***
set salary = nvl(salary + 0.05*salary, 0); --110 rows updated. 107+3 ang noi
100	26460
101	18742,5
102	18742,5
103	9922,5
253	0
252	0
254	0

select null+1, 2*null
from dual; --null null

rollback; --revenim la valorile initiale
100	24000
101	17000
102	17000
103	9000

16. Schimbaþi jobul tuturor salariatilor din departamentul 80 care au comision în 'SA_REP'.
Anulaþi modificãrile.

--salariaþii din departamentul 80 care au comision
select employee_id, department_id,commission_pct, job_id
from emp_***
where department_id =80
and commission_pct is not null; --34 rez

145	80	0,4	SA_MAN
146	80	0,3	SA_MAN
147	80	0,3	SA_MAN

--rezolvarea:
update emp_***
set job_id = 'SA_REP'
where department_id =80
and commission_pct is not null; --34 rows updated.

select employee_id, department_id,commission_pct, job_id from emp_***
where department_id =80
and commission_pct is not null;

145	80	0,4	SA_REP
146	80	0,3	SA_REP
147	80	0,3	SA_REP
 rollback;
 
------------------------------------------------------------------------------------------------------------------final S5
17. Sã se promoveze Douglas Grant la func?ia de manager în departamentul 20, 
având o creºtere de salariu de 1000. Se poate realiza modificarea prin 
intermediul unei singure comenzi?

select employee_id, salary
from emp_***
where lower(first_name) = 'douglas'
and lower(last_name) = 'grant'; --199 2600

select manager_id
from DEPT_***
where department_id =20; --201 
--initial mang pt dept 20 era 201, dupa update va fi 199

UPDATE nume_tabel [alias]
SET (col1,col2,...) = (subcerere)
[WHERE conditie];

update DEPT_***
set manager_id = (select employee_id
                  from emp_***
                  where lower(first_name) = 'douglas'
                  and lower(last_name) = 'grant')
where department_id =20;
--1 row updated.
 
 
update emp_***
set salary = salary+1000, department_id =20
where employee_id = (select employee_id
                  from emp_***
                  where lower(first_name) = 'douglas'
                  and lower(last_name) = 'grant');
 --199	3600                  
 --sau
update emp_***
set salary = salary+1000,  department_id =20
where lower(first_name) = 'douglas'
and lower(last_name) = 'grant';                 
-- 199	4600

 rollback;
 
 18. Schimba?i salariul ?i comisionul celui mai prost pl?tit salariat din firm?, 
 astfel încât s? devin? egale cu salariul ?i comisionul mediu. ?ine?i cont de 
 liniile introduse anterior în calculul mediei (media se va calcula raportat 
 la num?rul total de angaja?i).
 
 update emp_***
 set (salary, commission_pct) = ( Select avg(salary), avg(commission_pct)
                                    from emp_***)
 where salary = (select min(salary)
                    from emp_***);
      rollback;  

select min(salary)
from emp_***; --2100

select * 
from emp_***
 where salary = (select min(salary)
                    from emp_***);
 --132	TJ	Olson	TJOLSON	650.124.8234	10-APR-99	ST_CLERK	2100		121	50
select *
from emp_***
where employee_id =132;
--dupa update:  
--132	TJ	Olson	TJOLSON	650.124.8234	10-APR-99	ST_CLERK	6461.68	0.22	121	50

 VIII. [Exerci?ii – DELETE]
20. ªtergeþi toate înregistrãrile din tabelul DEPT_***. Ce înregistrãri se pot ºterge? Anulaþi modificãrile.

delete from DEPT_***;
--SQL Error: ORA-02292: constrângerea de integritate (GRUPA33.FK_EMP_DEPT_***) violata - gasita înregistrarea copil
--02292. 00000 - "integrity constraint (%s.%s) violated - child record found"



commit;


22. Suprimaþi departamentele care un au nici un angajat. Anulaþi modificãrile.
 --v1
 --care sunt departamentele la care nu lucreaza niciun angajat?
 select department_id
 from DEPT_***
 minus
 select distinct department_id  --lista departamenteor in care lucreaza angajati
 from emp_***
 where department_id is not null; --16 dept
 
select department_id
 from DEPT_*** 
 where department_id not in (select distinct department_id  --lista departamenteor in care lucreaza angajati
                             from emp_***
                             where department_id is not null);
 
 delete from DEPT_***
 where department_id in ( select department_id
                           from DEPT_***
                           minus
                           select department_id 
                           from emp_***
                           where department_id is not null); --16 rows deleted.
  select * from DEPT_***; --12 rez  
--90	Executive	100	1700
--100	Finance	108	1700
--110	Accounting	205	1700
--300	Programare		
  rollback;
 --28 de dept in DEPT_***
 
 --v2
 --stergem departamnele care nu se gasesc in lista de departamente in care LUCREZA angajati
 delete from DEPT_***
 where department_id not in (select department_id 
                           from emp_***
                           where department_id is not null); --16 rows deleted.
rollback;                         

--atentie
delete from DEPT_***
 where department_id not in (select department_id 
                           from employees
                           where department_id is not null);
--ORA-02292: integrity constraint (GRUPA32.FK_EMP_DEPT_***) violated - child record found                           
                           select distinct department_id 
                           from employees
                           where department_id is not null; --11 rez 
                           
                                                      
                           select distinct department_id 
                           from emp_***
                           where department_id is not null; --12 rez (apare si dept 300)
                           rollback;
--   delete from emp_*** 
--   where employee_id in (252,253,254);
                           
21. Stergeti angajatii care nu au comision. Anulati modificãrile.

delete from emp_***
where commission_pct is null; --75 rows deleted.

select * from emp_***; --au ramas 35 ang
rollback;

 IX. [Exerci?ii – LMD, LCD]
23. Sã se ºteargã un angajat din tabelul EMP_***. Modificãrile vor deveni permanente.

--stergeti angajatul 254
delete from emp_***
where employee_id =254; --1 rows deleted.
commit;

select * from emp_***; --109 ang

--select count(*)
--from emp_***; --109 ang

24. Sã se mai introducã o linie in tabel.

insert into emp_*** (employee_id, last_name, email,  hire_date, job_id,
                        department_id)
values (255, 'nume', 'nume@gmail.com', sysdate, 'test_job', 300); --null implicit

25. Sã se marcheze un punct intermediar in procesarea tranzacþiei.
SAVEPOINT acum;

26. Sã se ºteargã tot conþinutul tabelului. Listaþi conþinutul tabelului.
delete from emp_***; --110 rows deleted.

27. Sã se renunþe la cea mai recentã operaþie de ºtergere, fãrã a renunþa la operaþia precedentã de introducere.
ROLLBACK; --anuleaza atata delete+ insert 255  => 109 ang = 107ang + cei 2 adaugati de noi cu id-urile 252, 253
rollback to acum; --am anulat doar delete
28. Listaþi conþinutul tabelului. Determinaþi ca modificãrile sã devinã permanente.
select * from emp_***; --110 ang : 252, 253, 255 
 commit;
 
 
 
 
 
 
 
 