--S3+S4- Laborator3.pdf  - Join(+subcereri necorelate) + Union(all)+Operatii multimi(16-17+23-24/02.2022)

--crossjoin
select e.*, d.*
from   employees e, departments d;

select e.employee_id, d.department_name
from   employees e, departments d;

select e.*, d.*
from   employees e join departments d on e.department_id = d.department_id; --106 rez

---departametul (numele) in care lucreaza fiecare angajat
select e.last_name || ' '||e.first_name, d.department_name, e.department_id
from   employees e join departments d on e.department_id = d.department_id; --106 rez

--nu toate coloanele trebuie sa fie prefixate, doar cele care se gasesc in ambele tabele
select last_name || ' '||first_name, department_name, e.department_id
from   employees e join departments d on e.department_id = d.department_id; --106 rez

select e.last_name || ' '||e.first_name, d.department_name, department_id --atentie la dept_id
from   employees e join departments d on e.department_id = d.department_id; --ORA-00918: column ambiguously defined

---departametul (numele) in care lucreaza fiecare angajat
select e.last_name || ' '||e.first_name, d.department_name, department_id  --atentie dept_id
from   employees e  join departments d using(department_id); --106 rez 

--incorect
select e.last_name || ' '||e.first_name, d.department_name, d.department_id  --atentie dept_id
from   employees e  join departments d using(department_id); --106 rez 
--ORA-25154: column part of USING clause cannot have qualifier

select e.last_name || ' '||e.first_name, d.department_name, e.department_id  --atentie dept_id
from   employees e , departments d
where e.department_id = d.department_id;--106 rez

--incorect
select e.last_name || ' '||e.first_name, d.department_name, department_id  --atentie dept_id
from   employees e , departments d
where e.department_id = d.department_id;--ORA-00918: column ambiguously defined

--afisati si managerul direct si managerul de departament

select e.employee_id,e.last_name || ' '||e.first_name, d.department_name, e.department_id,
        e.manager_id managerul_direct, d.manager_id Manager_de_departament
from   employees e , departments d
where e.department_id = d.department_id;--106 rez

-----extra:
----afisati si managerul direct si managerul de departament
--select e.employee_id,e.last_name || ' '||e.first_name, d.department_name, e.department_id,
--        e.manager_id managerul_direct, 
--        (Select last_name from employees where employee_id =e.manager_id) Nume_manager_direct,--subcerere corelata
--        d.manager_id Manager_de_departament,
--        (Select last_name from employees where employee_id =d.manager_id) Nume_manager_departament
--from   employees e , departments d
--where e.department_id = d.department_id;--106 rez

ex3-1 Sa se afiseze numele, salariul, titlul job-ului, 
ora?ul ?i tara în care  lucreaz? angajatii 
condusi direct de managerul cu cod 100.

--v1
select e.last_name || ' '||e.first_name, j.job_title, l.city, c.country_name
from jobs j, employees e, departments d, locations l, countries c
where j.job_id = e.job_id
and e.department_id = d.department_id
and d.location_id = l.location_id
and l.country_id = c.country_id
and e.manager_id =100;--14 rez

--v2
select e.last_name || ' '||e.first_name, j.job_title, l.city, c.country_name
from jobs j join  employees e on  j.job_id = e.job_id
        join departments d on e.department_id = d.department_id
        join locations l on d.location_id = l.location_id
        join countries c on l.country_id = c.country_id
where e.manager_id =100;--14 rez

--v3
--incorect
select e.last_name || ' '||e.first_name, j.job_title, l.city, c.country_name, 
        manager_id, department_id
from jobs j  natural join  employees e 
       natural join departments d   --department_id, manager_id
         natural join locations l
       natural join countries c 
where manager_id =100;--2 rez

select manager_id  ---manageru-ul 100 pt dept 90
from departments
where department_id =90;

--corect
select e.last_name || ' '||e.first_name, j.job_title, l.city, c.country_name
from jobs j  join  employees e using (job_id)
        join departments d using (department_id)
         join locations l  using (location_id)
         join countries c using (country_id)
where e.manager_id =100;--14 rez

--natural join
--angajatii care au ca manager direct managerul departamentului in care lucreaza ei
select e.last_name || ' '||e.first_name, d.department_name
from   employees e natural join departments d ; --32 rez  --department_id, manager_id
--echivalent cu:
select e.last_name || ' '||e.first_name, d.department_name
from   employees e  join departments d using (department_id, manager_id); --32 rez  --department_id, manager_id


--nonequijoin
Sa se gaseasca toate titlurile de job-uri
care au maximul salariului (max_salary) mai mic decat 
salariul angajatului cu cod 100.

SELECT j.job_title , e.salary, j.max_salary
FROM JOBS j, EMPLOYEES e
WHERE j.max_salary<e.salary  
AND e.employee_id=100; --17 rez

SELECT j.job_title , e.salary, j.max_salary
FROM JOBS j JOIN EMPLOYEES e ON (j.max_salary<e.salary) 
WHERE e.employee_id=100;

--Salariul ang cu codul 100
select salary   --240000
from employees
where employee_id =100;

--nu este obligatoriu sa avem aliasul tabelei
SELECT j.job_title
FROM JOBS j
WHERE j.max_salary<(select salary   --240000
                    from employees
                    where employee_id =100); --subcerere necorelata, intoarce o singura coloana si un singur rezultat
--17 rez

--atentie!!
SELECT j.job_title , e.salary, j.max_salary, e.employee_id
FROM JOBS j JOIN EMPLOYEES e ON (j.max_salary<e.salary) ;

SELECT j.job_title , e.salary, j.max_salary
FROM JOBS j natural JOIN EMPLOYEES e 
where (j.max_salary<=e.salary) ; --1 rez pt ca fiecare sal are 
--salariul intre limitele salariale coresp jobului pe care lucreaza

SELECT j.job_title
FROM JOBS j
WHERE j.max_salary<(select salary   --240000
                    from employees
                    where employee_id =100); --subcerere necorelata
            

SELECT distinct j.job_title
FROM JOBS j, EMPLOYEES e
WHERE j.max_salary<e.salary  
AND e.manager_id=100;

--
--Pt toti salariatii din firma afisati numele angajatului, limitele salariale ale job-ului 
--pe care lucreaza(max_salary, min_salary)  si denumirea departamentului in care
--lucreaza fiecare salariat.
--
----v1
--select e.last_name || ' '||e.first_name, j.max_salary, j.min_salary,d.department_name
--from jobs j, employees e, departments d
--where j.job_id = e.job_id
--and e.department_id = d.department_id; --106 rez
----v2
--select e.last_name || ' '||e.first_name, j.max_salary, j.min_salary,d.department_name
--from  jobs j join  employees e on  j.job_id = e.job_id  
--        join departments d on e.department_id = d.department_id; --106 rez
        
        

-- Self join de tip nonequijoin
S? se afi?eze numele ?i data angaj?rii pentru salaria?ii
care au fost  angaja?i dup? Gates.

--data angajarii lui 'Gates'
SELECT E2.hire_date
FROM  EMPLOYEES E2
WHERE initcap(e2.last_name)='Gates' ;  --11-JUL-98

--rezolvare:
SELECT E.last_name, E.hire_date
FROM EMPLOYEES E, EMPLOYEES E2   ---self-join
WHERE initcap(e2.last_name)='Gates'  AND E.hire_date>E2.hire_date;  --nonequijoin
--34 rez
-- E2.hire_date = 11-JUL-98
--in E2 avem informatii despre Gates

SELECT E.last_name, E.hire_date
FROM EMPLOYEES E JOIN EMPLOYEES E2       -- self-join
            ON (E.hire_date>E2.hire_date)  --nonequijoin
WHERE initcap(e2.last_name)='Gates'; 

--subcerere necorelata
SELECT E.last_name, E.hire_date
FROM EMPLOYEES E
WHERE E.hire_date > ( SELECT E2.hire_date   --subcererea necorelata returneaza o singura 
                    FROM  EMPLOYEES E2  -- linie si o singura coloana
                    WHERE initcap(e2.last_name)='Gates' );
 --34 rez                   

--Self join de tip equijoin

ex1- Scrieti o cerere pentru a se afisa numele, luna (în litere) ?i
anul (cifre) angaj?rii pentru toti salariatii din acelasi departament cu Gates,
al  c?ror nume con?ine litera “a”.


--in ce dept lucreaza Gates
SELECT e2.department_id
FROM employees e2  
WHERE initcap(e2.last_name)='Gates';
--dept 50

SELECT e.last_name, to_char(e.hire_date,'MONTH') as "luna", 
    to_char(e.hire_date,'YYYY') as "anul"
FROM employees e, employees e2  
WHERE initcap(e2.last_name)='Gates'
AND e.department_id=e2.department_id   --conditie de join
AND lower(e.last_name) LIKE '%a%'
--and initcap(e.last_name) <> 'Gates'; --23 rez
--and initcap(e.last_name) not like 'Gates'; --23 rez
and not (initcap(e.last_name) like 'Gates'); --23 rez
--e2.department_id =50

alter session set nls_language=American;

SELECT e.last_name, to_char(e.hire_date,'MONTH') as "luna", 
        to_char(e.hire_date,'YYYY') as "anul"
FROM employees e
WHERE lower(e.last_name) LIKE '%a%'
and initcap(e.last_name) != 'Gates'
and e.department_id = (SELECT e2.department_id  --subcerere necorelata, folosim = pt ca stim ca avem un singut Gates
                        FROM employees e2  
                        WHERE e2.last_name='Gates');--23 rez
                        --nu este nevoie de alias-uri


SELECT e.last_name, to_char(e.hire_date,'MONTH') as "luna", 
        to_char(e.hire_date,'YYYY') as "anul"
FROM employees e
WHERE lower(e.last_name) LIKE '%a%'
and initcap(e.last_name) != 'Gates'
and e.department_id in (SELECT e2.department_id  --subcerere necorelata, nu stim sigur cati salariati cu numele Gates avem
                        FROM employees e2  
                        WHERE e2.last_name='Gates');--23 rez
                        --nu este nevoie de alias-uri
Sa se afiseze codul ?i numele angaja?ilor care lucreaz? în 
acelasi departament cu cel pu?in un angajat al c?rui nume  con?ine litera “t”.

In ce departamente(id+nume) lucreaza angajatii  al c?ror nume con?in litera “t”.

SELECT  e.department_id
FROM EMPLOYEES E
where lower(E.last_name) LIKE '%t%'; --32 rez (pt ca unul dintre angajati nu are setata departamentul)

SELECT DISTINCT e.department_id --lista de departamente
FROM EMPLOYEES E
where lower(E.last_name) LIKE '%t%'; --8 rez (pt ca unul dintre angajati nu are setata departamentul)

SELECT DISTINCT e.department_id
FROM EMPLOYEES E
where lower(E.last_name) LIKE '%t%'
and department_id is not null; --7 rez (pt ca unul dintre angajati nu are setata departamentul)

SELECT DISTINCT d.department_id, d.department_name
FROM EMPLOYEES E, departments d
WHERE E.department_id= d.department_id
AND lower(E.last_name) LIKE '%t%'; --7 rez


Sa se afiseze codul ?i numele angaja?ilor care lucreaz? în 
acelasi departament cu cel pu?in un angajat al c?rui nume 
con?ine litera “t”.

SELECT DISTINCT E.employee_id, E.last_name 
FROM EMPLOYEES E, EMPLOYEES E2
WHERE E.department_id= E2.department_id
AND lower(E2.last_name) LIKE '%t%'; --100 rez
---e2 angajatii care contin in nume litera t
--distict pt ca avem agajati al caror nume contine t in acelasi departament

SELECT  E.employee_id, E.last_name 
FROM EMPLOYEES E
WHERE E.department_id in ( SELECT DISTINCT e.department_id
                        FROM EMPLOYEES E
                        WHERE lower(E.last_name) LIKE '%t%'); --100 rez

SELECT  E.employee_id, E.last_name 
FROM EMPLOYEES E
WHERE E.department_id in ( SELECT  e.department_id
                        FROM EMPLOYEES E
                        WHERE lower(E.last_name) LIKE '%t%'); --100 rez                        
                        
  --incorect
SELECT  E.employee_id, E.last_name 
FROM EMPLOYEES E
WHERE E.department_id = ( SELECT DISTINCT e.department_id  --- atentie la =
                        FROM EMPLOYEES E
                        WHERE lower(E.last_name) LIKE '%t%'); 
                        -- ORA-01427: single-row subquery returns more than one row
                        
  --incorect                      
SELECT  E.employee_id, E.last_name 
FROM EMPLOYEES E
WHERE E.department_id in (SELECT DISTINCT d.department_id, d.DEPARTMENT_NAME --ORA-00913: too many values
                            FROM EMPLOYEES E, departments d
                            WHERE E.department_id= d.department_id
                            AND lower(E.last_name) LIKE '%t%'); --100 rez

SELECT  E.employee_id, E.last_name 
FROM EMPLOYEES E
WHERE E.department_id in (SELECT DISTINCT d.department_id
                            FROM EMPLOYEES E, departments d
                            WHERE E.department_id= d.department_id
                            AND lower(E.last_name) LIKE '%t%'); --100 rez
                            
SELECT  E.employee_id, E.last_name 
FROM EMPLOYEES E
WHERE E.department_id in (SELECT  d.department_id   
                            FROM EMPLOYEES E, departments d
                            WHERE E.department_id= d.department_id
                            AND lower(E.last_name) LIKE '%t%'); --100 rez
--subcererea necorelata returneaza o coloana, dar mai multe linii


SELECT	e.*, d.* 
FROM departments d, employees e
WHERE d.department_id= e.department_id;
---outer join

S? se afi?eze numele salaria?ilor ?i numele departamentelor în 
care lucreaz?. Se vor afi?a ?i salaria?ii care nu au asociat un  departament.

SELECT	e.*, d.* 
FROM departments d, employees e
WHERE d.department_id(+) = e.department_id
order by d.department_id desc;
--107 rez

SELECT	last_name, department_name
FROM	departments d RIGHT OUTER JOIN employees e 
ON d.department_id = e.department_id; --107 rez

---exista angajatul si vrem sa completeze cu null la info-le legate de departament


q)S? se afi?eze numele departamentelor ?i numele salaria?ilor care  
lucreaz? în ele. Se vor afi?a ?i departamentele care nu au salaria?i.

SELECT	e.*, d.* 
FROM departments d, employees e
WHERE d.department_id = e.department_id(+)
order by d.department_id desc;

--16 dep in care nu lucreaza niciun angajat +106 ang care lucreaza in departamente
--122 rez

SELECT	last_name, department_name
FROM	departments d Left OUTER JOIN employees e 
ON d.department_id = e.department_id; --122 rez

SELECT	last_name, department_name
FROM	employees e right OUTER JOIN departments d
ON d.department_id = e.department_id; --122 rez


Scrieti o cerere care afiseaza departamentele, chiar ?i cele f?r? 
func?ionari, ?i func?ionarii, chiar ?i cei care nu sunt asigna?i 
nici  unui departament

---NUUUUUU
SELECT	e.*, d.* 
FROM departments d, employees e
WHERE d.department_id(+) = e.department_id(+)
order by d.department_id desc;
--ORA-01468: a predicate may reference only one outer-joined table

--v1 corecta
SELECT employee_id,last_name, department_name  FROM employees e, departments d
WHERE e.department_id = d.department_id(+)   --inclusiv ang care nu au dept
UNION
SELECT employee_id,last_name, department_name  FROM employees e, departments d
WHERE e.department_id(+) = d.department_id;  --inclusiv departamentele care nu au ang

--106 ang cu dept
--16 dept pe care nu lucreaza ang
--1 ang fara dept
--123
--
--{1,2,3} union {2,3,4} ={1,2,3,4}
--
--{1,2,3,1,3} union {2,4} ={1,2,3,4}

--atentie la angajatii cu acelasi nume
SELECT last_name, department_name  
FROM employees e, departments d
WHERE e.department_id = d.department_id(+)   --inclusiv ang care nu au dept
UNION
SELECT last_name, department_name  
FROM employees e, departments d
WHERE e.department_id(+) = d.department_id;  --inclusiv departamentele care nu au ang
--121 rez --incorect

--v2 corecta 
SELECT last_name, department_name  
FROM employees e FULL OUTER JOIN departments d
ON e.department_id = d.department_id; --123 rez

-------------------------------------------------------------------------------------------s4 --134(marti)

Sa se afiseze codurile de tara,locatie,departament,angajat
inclusiv pt tarile, locatiile si departamentele in care nu lucreaza nimeni
`

--nuu
SELECT E.EMPLOYEE_ID,D.DEPARTMENT_ID,L.LOCATION_ID,C.COUNTRY_ID , c.country_name 
FROM EMPLOYEES E, DEPARTMENTS D, LOCATIONS L, COUNTRIES C  
WHERE L.COUNTRY_ID(+)=C.COUNTRY_ID
AND D.LOCATION_ID=L.LOCATION_ID
AND E.DEPARTMENT_ID=D.DEPARTMENT_ID;

---corect
/
SELECT E.EMPLOYEE_ID,D.DEPARTMENT_ID,L.LOCATION_ID,C.COUNTRY_ID , c.country_name 
FROM EMPLOYEES E, DEPARTMENTS D, LOCATIONS L, COUNTRIES C  
WHERE L.COUNTRY_ID(+)=C.COUNTRY_ID
AND D.LOCATION_ID(+)=L.LOCATION_ID
AND E.DEPARTMENT_ID(+)=D.DEPARTMENT_ID; ---149 rez
/

SELECT E.EMPLOYEE_ID,D.DEPARTMENT_ID,L.LOCATION_ID,C.COUNTRY_ID , c.country_name 
FROM   COUNTRIES C  left outer join LOCATIONS L on L.COUNTRY_ID=C.COUNTRY_ID
        left outer join DEPARTMENTS D on D.LOCATION_ID=L.LOCATION_ID
        left outer join EMPLOYEES E on E.DEPARTMENT_ID=D.DEPARTMENT_ID; ---149 rez
        
SELECT E.EMPLOYEE_ID,D.DEPARTMENT_ID,L.LOCATION_ID,C.COUNTRY_ID , c.country_name 
FROM   EMPLOYEES E right outer join DEPARTMENTS D  on E.DEPARTMENT_ID=D.DEPARTMENT_ID
        right outer join LOCATIONS L  on D.LOCATION_ID=L.LOCATION_ID
        right outer join COUNTRIES C on L.COUNTRY_ID=C.COUNTRY_ID;
        
        --nu
SELECT E.EMPLOYEE_ID,D.DEPARTMENT_ID,L.LOCATION_ID,C.COUNTRY_ID , c.country_name 
FROM   COUNTRIES C  full outer join LOCATIONS L on L.COUNTRY_ID=C.COUNTRY_ID
        full outer join DEPARTMENTS D on D.LOCATION_ID=L.LOCATION_ID
        full outer join EMPLOYEES E on E.DEPARTMENT_ID=D.DEPARTMENT_ID; ---150 rez (152 cand adaugam si departamentele fara locatii)
------------------------------------------------------------------------------------------

--Se cer codurile departamentelor al c?ror nume con?ine sirul “re”
--sau în care lucreaz? angaja?i având codul job-ului “SA_REP”.
--
---- codurile departamentelorîn care lucreaz? angaja?i având codul job-ului “SA_REP”.
--SELECT department_id "Cod departament" 
--FROM employees
--WHERE upper(job_id)='SA_REP'   --80, null  ---30 rez
--UNION
----codurile departamentelor al c?ror nume con?ine ?irul “re”
--SELECT department_id  
--FROM departments
--WHERE lower(department_name) LIKE '%re%';   ---7 rez 
----40,70,120,140,150,250,260
----in total 9 rez
--;
--
--SELECT department_id "Cod departament" 
--FROM employees
--WHERE upper(job_id)='SA_REP'   --80, null  ---30 rez
--UNION all
--SELECT department_id  
--FROM departments
--WHERE lower(department_name) LIKE '%re%';   ---7 rez 
----40,70,120,140,150,250,260
----in total 37 rez

/*
--discutii:
Se cer codurile departamentelor al c?ror nume con?ine sirul “re”
sau în care lucreaz? angaja?i având codul job-ului “SA_REP”.
--folosind outer join

SELECT  distinct d.department_id "Cod departament" 
FROM employees e full outer join departments d on (e.department_id =d.department_id)
WHERE  (upper(job_id)='SA_REP'  or lower(department_name) LIKE '%re%'); 
-- 9 rez

Se cer codurile departamentelor  pe care lucreaza angajati si 
(al c?ror nume de departament con?ine sirul “re” 
sau în care lucreaz? angaja?i având codul job-ului “SA_REP”).

SELECT distinct d.department_id "Cod departament" 
FROM employees e, departments d
WHERE e.department_id = d.department_id
and (upper(job_id)='SA_REP'  or lower(department_name) LIKE '%re%');
--70, 80, 40


---nu
SELECT distinct d.department_id "Cod departament" 
FROM employees e, departments d
WHERE  (upper(job_id)='SA_REP'  or lower(department_name) LIKE '%re%');

select * from employees where department_id =260;
*/



--select job_id 
--from jobs
--where job_id not in (select job_id
--                     from employees);




----------------------------------------------------------------------------
-- lucram pe 193.226.51.37

desc departments;

Name            Null?    Type         
--------------- -------- ------------ 
DEPARTMENT_ID   NOT NULL NUMBER(4)    
DEPARTMENT_NAME NOT NULL VARCHAR2(30) 
MANAGER_ID               NUMBER(6)    
LOCATION_ID              NUMBER(4)

insert into departments values (111, 'Test dept1', null, null);
insert into departments values (112, 'Test dept2', null, null);

delete from departments
where department_id in (111,112);

commit;

select * from departments;

Saptamana 4

Afisati informatii despre orasele(city) si departamentele(department_name)
care se gasesc in acele locatii (orase).Se vor afisa informatii chiar
si despre locatiile(orasele) in care nu se gasesc departamente.


select l.city, d.department_name dep
from locations l, departments d
where l.location_id = d.location_id(+)
order by dep desc;  --43 rez (16 locatii fara dept)

select l.city, d.department_name dep
from locations l left outer join departments d
on l.location_id = d.location_id
order by dep desc; --43 rez

--atentie
Select l.city, d.department_name dep
from locations l full outer join departments d 
on ( l.location_id = d.location_id);
--43 vad studentii inainte de a da eu commit dupa cele 2 insert-uri de la inceput
--commit;
--corect:
--45 rez (16 locatii fara dept, 2 dept fara locatii)
-- se afiseaza si locatiile fara departamente, dar si departamentele fara locatii

10.	Se cer codurile departamentelor al cãror nume conþine sirul “re” sau în care 
lucreazã angajati având codul job-ului “SA_REP”.

--codurile departamentelor al c?ror nume con?ine ?irul “re”
SELECT department_id  "codul"
FROM departments
WHERE lower(department_name) LIKE '%re%'  ---7 rez --40,70,120,140,150,250,260
Union
-- codurile departamentelor în care lucreaz? angaja?i având codul job-ului “SA_REP”.
SELECT department_id "Cod departament" 
FROM employees
WHERE upper(job_id)='SA_REP' ;  --80, null  ---30 rez
--in total 9 rez

--corect
--codurile departamentelor al c?ror nume con?ine ?irul “re”
SELECT department_id  "codul"
FROM departments
WHERE lower(department_name) LIKE '%re%'  ---7 rez --40,70,120,140,150,250,260
Union
-- codurile departamentelor în care lucreaz? angaja?i având codul job-ului “SA_REP”.
SELECT department_id "Cod departament" 
FROM employees
WHERE upper(job_id)='SA_REP' 
and department_id is not null;  --80  ---29 rez
--in total 8 rez


--atentie apare aliasul "Cod departament" 
SELECT department_id "Cod departament" 
FROM employees
WHERE upper(job_id)='SA_REP'   --80, null  ---30 rez
UNION all
SELECT department_id  
FROM departments
WHERE lower(department_name) LIKE '%re%';   ---7 rez  --40,70,120,140,150,250,260

--in total 37 rez


10.1.	Se cer codurile si numele departamentelor al cãror nume 
conþine ºirul “re” sau în care 
lucreazã angajaþi având codul job-ului “SA_REP”.
--corect
--numele departamentelor al cãror nume conþine ºirul “re”
select department_name "Nume departamente", department_id
from departments
where lower(department_name) like '%re%'
Union
-- numele departamentelor în care lucreazã angajaþi având codul job-ului “SA_REP”.
select department_name "Nume2", e.department_id --29 rez
from employees e, departments d
where lower(job_id) like 'sa_rep'
and e.department_id = d.department_id; 
--Final : 8 rez

--atentie, dispare : Grant	SA_REP	null
select last_name, job_id, department_id
from employees
where lower(job_id) = 'sa_rep'
and department_id is null;

---facem outer join
--numele departamentelor al cãror nume conþine ºirul “re”
select department_name "Nume departamente", department_id
from departments
where lower(department_name) like '%re%' -- 7 rez
Union
-- numele departamentelor în care lucreazã angajaþi având codul job-ului “SA_REP”.
select department_name "Nume2", e.department_id --30 rez
from employees e, departments d
where lower(job_id) like 'sa_rep'
and e.department_id = d.department_id(+); 
--final 9 rez



--ATENTIE!!!!
--ORA-01790: expresia trebuie sa aiba acelasi tip de data ca si expresia corespondenta
--din cealata cerere!
--numele departamentelor al cãror nume conþine ºirul “re”
select department_name "Nume departamente"
from departments
where lower(department_name) like '%re%'
Union
-- codurile departamentelor în care lucreazã angajaþi având codul job-ului “SA_REP”.
select d.department_id "Nume2"
from employees e, departments d
where lower(job_id) like 'sa_rep'
and e.department_id = d.department_id; 

--ruleaza corect
--numele departamentelor al cãror nume conþine ºirul “re”
select department_name "Nume departamente"
from departments
where lower(department_name) like '%re%'
Union
-- codurile departamentelor în care lucreazã angajaþi având codul job-ului “SA_REP”.
select to_char(d.department_id) "Idul2"
from employees e, departments d
where lower(job_id) like 'sa_rep'
and e.department_id = d.department_id; 

--ATENTIE!!!!
--functioneaza
--numele si id-ul departamentelor al cãror nume conþine ºirul “re”
select department_name "Nume departamente", To_char(department_id)
from departments
where lower(department_name) like '%re%' -- 7 rez
Union
--numele angajatilor si id-ul jobului pt salariatii având codul job-ului “SA_REP”.
select last_name "Nume angajat", job_id  -- 29 rez
from employees e, departments d
where lower(job_id) like 'sa_rep'
and e.department_id = d.department_id;
--final --35 rez

select last_name "Nume angajat", job_id  -- 29 rez
from employees e, departments d
where lower(job_id) like 'sa_rep'
and e.department_id = d.department_id
order by 1;

select  distinct last_name "Nume angajat", job_id  -- 28 rez
from employees e, departments d
where lower(job_id) like 'sa_rep'
and e.department_id = d.department_id
order by 1;  -- smith

desc employees;

--atentie: nr de coloane identic
select department_name "Nume departamente", To_char(department_id), manager_id
from departments
where lower(department_name) like '%re%'
Union
--numele angajaþilor si id-ul jobului pt salariatii având codul job-ului “SA_REP”.
select last_name "Nume angajat", job_id
from employees e, departments d
where lower(job_id) like 'sa_rep'
and e.department_id = d.department_id; --ORA-01789: query block has incorrect number of result columns

select department_name "Nume departamente", To_char(department_id), manager_id
from departments
where lower(department_name) like '%re%'
Union
--numele angajaþilor si id-ul jobului pt salariatii având codul job-ului “SA_REP”.
select last_name "Nume angajat", job_id, null
from employees e, departments d
where lower(job_id) like 'sa_rep'
and e.department_id = d.department_id; --35 rez


--atentie
--numele departamentelor al cãror nume conþine ºirul “re” si in care lucreaza angajati
select department_name "Nume departamente", d.department_id
from employees e, departments d
where lower(department_name) like '%re%'
and e.department_id = d.department_id   -- 2 rez
Union
-- numele departamentelor în care lucreazã angajaþi având codul job-ului “SA_REP”.
select department_name "Nume2", e.department_id --29 rez
from employees e, departments d
where lower(job_id) like 'sa_rep'
and e.department_id = d.department_id; 

/*
11.	Sã se ob?inã codurile departamentelor în care nu lucreazã nimeni 
(nu este introdus nici un salariat în tabelul employees).
Se cer douã soluþii (MINUS, NOT IN).
Observa?ie: Operatorii pe mulþimi pot fi utilizaþi în subcereri. 
Coloanele care apar în clauza WHERE a interogãrii trebuie sã corespundã, 
ca numãr ºi tip de date, celor din clauza SELECT a subcererii. 
Comenta?i necesitatea tratãrii valorilor null în varianta utilizãrii 
operatorului NOT IN. 

Solu?ie:
*/

--{1,2,3} \ {1,1,2,2, null} = {3}
--{1,2,3} \{1,2} = {3}

SELECT d.department_id
FROM departments d ---lista tututor departamentelor din firma
MINUS
SELECT department_id
FROM employees; -- departamentele in care lucreaza angajatii
--18 rez

SELECT d.department_id
FROM departments d ---lista tututor departamentelor din firma
MINUS
SELECT UNIQUE department_id
FROM employees; --lista departamentelor in care lucreaza angajatii
--18 rez

SELECT d.department_id
FROM departments d ---lista tututor departamentelor din firma
MINUS
SELECT distinct department_id
FROM employees; --lista departamentelor in care lucreaza angajatii


SELECT d.department_id
FROM departments d ---lista tututor departamentelor din firma
MINUS
SELECT distinct e.department_id         --in 11 dept lucreaza angajatii
FROM employees e, departments d
where e.department_id = d.department_id; -- departamentele in care lucreaza angajatii


111
112
120
130
140
150
160
170
180
190
200
210
220
230
240
250
260
270
select distinct department_id
from employees; --12 (11 dept pe care lucreaza ang + null (un ang care nu are setat departamentul) )

-subcerere

--incorect
select d.department_id
from departments d
where d.department_id not in ( SELECT UNIQUE department_id
                                 FROM employees e); --contine null
                                 --0 rez

--corect
select d.department_id
from departments d
where d.department_id not in ( SELECT UNIQUE dd.department_id   --- subcere:11 dept in care lucreaza ang
                                 FROM employees e, departments dd
                                 where e.department_id = dd.department_id);        

SELECT department_id
FROM departments
WHERE department_id NOT IN (
                              SELECT d.department_id
                              FROM departments d
                              JOIN employees e ON(d.department_id=e.department_id)
                              );
                              
select d.department_id
from departments d
where d.department_id not in ( SELECT UNIQUE e.department_id
                                 FROM employees e
                                 where e.department_id is not null);  
                                 --18 dept (2 departamente adaugate de noi astazi) 


12.	Se cer codurile departamentelor al cãror nume conþine ºirul “re” SI în care 
lucreazã angajaþi având codul job-ului “HR_REP”. 

--codurile departamentelor al cãror nume conþine ºirul “re”
select department_id "Id de departamente"
from departments
where lower(department_name) like '%re%' -- 7 rez
Intersect
-- codurile departamentelor în care lucreazã angajaþi având codul job-ului “HR_REP”.
select d.department_id "Id2"
from employees e, departments d  --- aici nu e nevoie si de tabela de departments
where lower(job_id) like 'hr_rep'
and e.department_id = d.department_id; 
-- final  1 rez : Dep 40


select d.department_id "Id2", d.department_name
from employees e, departments d
where lower(job_id) = 'hr_rep'
and e.department_id = d.department_id
and  lower(department_name) like '%re%'; -- 1 rez : Dep 40

select department_id
from departments d
where lower(d.department_name) LIKE '%re%' 
and d.department_id in (select e.department_id
                            from employees e
                            where upper(job_id) = 'HR_REP');


--Subcerei necorelate 

15. Folosind subcereri, s? se afi?eze numele ?i data angaj?rii pentru salaria?ii care 
au fost angaja?i dup? Gates.
SELECT last_name, hire_date
FROM employees
WHERE hire_date > (SELECT hire_date --11-07-1998
                    FROM employees
                    WHERE INITCAP(last_name)='Gates')
order by 2; --34 rez
--15". Folosind subcereri, s? se afi?eze numele ?i data angaj?rii pentru salaria?ii 
--care au fost angaja?i dup? Gates 
--si au salariul mai mare decat el.

SELECT last_name, hire_date, salary
FROM employees
WHERE hire_date > (SELECT hire_date
                    FROM employees
                    WHERE INITCAP(last_name)='Gates')
and salary > ( SELECT salary --2900
                    FROM employees
                    WHERE INITCAP(last_name)='Gates') 
order by 3,2;  --19 rez   

SELECT last_name, hire_date
FROM employees
WHERE (hire_date, salary) IN (SELECT hire_date, salary
                              FROM employees
                              WHERE INITCAP(last_name)='Gates');   
                              
--atentie la nr de rezultate returnat de subcerere                              
SELECT last_name, hire_date
FROM employees
WHERE hire_date > (SELECT hire_date
                    FROM employees
                    WHERE INITCAP(last_name)='King');
                    --ORA-01427: o subinterogare de o singura linie returneaza mai mult decât o linie                         
                              
--avem 2 King
17-06-1987
30-01-1996

Daca subcererea intoarce o multime de valori, se va folosi in cererea
parinte unul din operatorii IN, NOT IN, ANY, ALL.
WHERE col1 = ANY (SELECT …)  == WHERE col1 IN (SELECT …)
WHERE col1 > ANY (SELECT …) ==  mai mare ca minimul;
WHERE col1 < ANY (SELECT …) == mai mic ca maximul;
WHERE col1 > ALL (SELECT …) == mai mare ca maximul;
WHERE col1 < ALL (SELECT …) == mai mic ca minimul;
WHERE col 1 != ALL (SELECT …)  == WHERE col1 NOT IN (SELECT …)
                              
SELECT last_name, hire_date
FROM employees
WHERE hire_date >any (SELECT hire_date  --mai mare ca minimul
                      FROM employees
                      WHERE INITCAP(last_name)='King')
order by hire_date;   --106 rez
Whalen	17-09-1987
Kochhar	21-09-1989
Hunold	03-01-1990
Ernst	21-05-1991
De Haan	13-01-1993
Mavris	07-06-1994
Higgins	07-06-1994
.....

SELECT last_name, hire_date
FROM employees
WHERE hire_date >all (SELECT hire_date  --mai mare ca maximul (30-01-1996)
                        FROM employees
                        WHERE INITCAP(last_name)='King')
order by hire_date;  --88 ang

Bell	04-02-1996
Hartstein	17-02-1996
Sully	04-03-1996
Abel	11-05-1996
Mallin	14-06-1996
Weiss	18-07-1996
McEwen	01-08-1996
Russell	01-10-1996
Partners	05-01-1997
Davies	29-01-1997

---extra
SELECT last_name, hire_date
FROM employees
WHERE hire_date > (SELECT max(hire_date) --mai mare ca maximul (30-01-1996)
                        FROM employees
                        WHERE INITCAP(last_name)='King')
order by hire_date;  --88 ang

Daca subcererea intoarce o multime de valori, se va folosi in cererea
parinte unul din operatorii IN, NOT IN, ANY, ALL.
WHERE col1 = ANY (SELECT …)  == WHERE col1 IN (SELECT …)
WHERE col1 > ANY (SELECT …) ==  mai mare ca minimul;
WHERE col1 < ANY (SELECT …) == mai mic ca maximul;
WHERE col1 > ALL (SELECT …) == mai mare ca maximul;
WHERE col1 < ALL (SELECT …) == mai mic ca minimul;
WHERE col 1 != ALL (SELECT …)  == WHERE col1 NOT IN (SELECT …)

2. Folosind subcereri, scrie?i o cerere pentru a afi?a numele 
?i salariul pentru to?i colegii (din acela?i departament)
lui Gates. Se va exclude Gates.

--corect
SELECT last_name, salary
FROM employees
WHERE department_id In (SELECT department_id -- = 
                        FROM employees
                        WHERE LOWER(last_name)='gates')
AND LOWER(last_name) <> 'gates';  --44 rez

SELECT last_name, salary
FROM employees
WHERE department_id = (SELECT department_id 
                        FROM employees
                        WHERE LOWER(last_name)='gates')
AND LOWER(last_name) <> 'gates';  --44 rez

--King

SELECT last_name, salary, department_id
FROM employees
WHERE department_id In (SELECT department_id  -- nu merege pt =
                        FROM employees
                        WHERE LOWER(last_name)='king')
AND LOWER(last_name) <> 'king';

--incorect
SELECT last_name, salary, department_id
FROM employees
WHERE department_id = (SELECT department_id  -- nu merege pt =
                        FROM employees
                        WHERE LOWER(last_name)='king')
AND LOWER(last_name) <> 'king';
--ORA-01427: o subinterogare de o singura linie returneaza mai mult decât o linie

17. Folosind subcereri, s? se afi?eze numele ?i salariul angaja?ilor condu?i direct de pre?edintele 
companiei (acesta este considerat angajatul care nu are manager).

select last_name, salary
from employees
where manager_id = (select employee_id
                      from employees
                      where manager_id is null); --14 rez
                      
select last_name, salary
from employees
where manager_id in (select employee_id
                      from employees
                      where manager_id is null); --14 rez      

/*
3" Afisati denumirile departamentor in care lucreaza angajati care contin litera 't' in nume.
(v1:join
v2:subcerere necorelate) --7 rez
*/
                

18. Scrie?i o cerere pentru a afi?a numele, codul departamentului ?i salariul angaja?ilor 
al c?ror cod de departament ?i salariu coincid cu codul departamentului ?i salariul
unui angajat care câ?tig? comision.




SELECT department_id, salary 
FROM employees 
WHERE commission_pct IS NOT NULL ; -- 35 rez

SELECT last_name, department_id, salary
FROM employees 
WHERE (department_id, salary) IN ( SELECT department_id, salary 
                                    FROM employees 
                                    WHERE commission_pct IS NOT NULL ); --34 REZ    
                                    
--atentie cautarea salariului se face independent de departamentul in care lucreaza acel salariat
SELECT last_name, department_id, salary
FROM employees 
WHERE salary in (SELECT salary
                FROM employees 
                WHERE commission_pct IS NOT NULL )
and department_id IN ( SELECT department_id
                        FROM employees 
                        WHERE commission_pct IS NOT NULL );   --34 rez --dar daca se schimba datele, abtinem altceva
                        
  Exemplu: sa prespunem ca avem urmatoarele departamante si salarii ale angajatilor care castiga comision
  Dept_id   Comision
  80        1200
  70        1110
  
  In acest caz se va afisa si salariatul care lucreaza in departamentul 70, dar are salariul 1200.
                        
                        
                        
                                    
 --conteaza ordinea coloanelor                                   
SELECT last_name, department_id, salary
FROM employees 
WHERE (salary, department_id) IN ( SELECT department_id, salary 
                                    FROM employees 
                                    WHERE commission_pct IS NOT NULL ); --0 REZ                                     
                                    
--atentie
SELECT last_name, department_id, salary
FROM employees 
WHERE salary in (SELECT salary
                FROM employees 
                WHERE commission_pct IS NOT NULL )
or department_id IN ( SELECT department_id
                        FROM employees 
                        WHERE commission_pct IS NOT NULL );    --42 rez
                
                                   
                                    
--5. s? se afi?eze codul, numele ?i salariul tuturor angaja?ilor care ca?tig? mai mult 
--decât salariul mediu pentru job-ul corespunz?tor ?i lucreaz? într-un departament cu cel pu?in unul 
--dintre angaja?ii al c?ror nume con?ine litera “t”. Vom considera salariul mediu al unui job ca fiind egal 
--cu media aritmetic? a limitelor sale admise 
--(specificate în coloanele min_salary, max_salary din tabelul JOBS).
--
--SELECT  e.employee_id,e.last_name,e.salary 
--FROM employees e 
--WHERE e.salary > ( SELECT (j.min_salary+j.max_salary)/2  --angaja?ilor care ca?tig? mai mult decât salariul mediu pentru job-ul corespunz?tor
--                  FROM jobs j 
--                  WHERE j.job_id=e.job_id )
--AND e.department_id IN ( SELECT distinct department_id
--                          FROM employees 
--                          WHERE  LOWER(last_name) LIKE '%t%' ); --24 rez
--                          
--                          
----fara cerere corelata
--SELECT (j.min_salary+j.max_salary)/2 , job_id
--FROM jobs j
--order by 2;  --pt fiacre job am calculat media salariilor
--7000	IT_PROG
--6600	FI_ACCOUNT
--15000	SA_MAN
--9000	SA_REP
--4000	SH_CLERK
--3500	ST_CLERK
--
--SELECT  e.employee_id,e.last_name,e.salary, e.job_id
--FROM employees e 
--WHERE (e.salary ,e.job_id) in ( SELECT (j.min_salary+j.max_salary)/2, job_id
--                                from jobs j )
--AND e.department_id IN ( SELECT distinct department_id
--                          FROM employees 
--                          WHERE  LOWER(last_name) LIKE '%t%' );
--
--192	Bell	4000	SH_CLERK
--141	Rajs	3500	ST_CLERK
--158	McEwen	9000	SA_REP
--152	Hall	9000	SA_REP
--
--
----atentie
--SELECT  e.employee_id,e.last_name,e.salary, e.job_id
--FROM employees e 
--WHERE e.salary in ( SELECT (j.min_salary+j.max_salary)/2
--                                from jobs j )
--AND e.department_id IN ( SELECT distinct department_id
--                          FROM employees 
--                          WHERE  LOWER(last_name) LIKE '%t%' );
--103	Hunold	9000	IT_PROG
--109	Faviet	9000	FI_ACCOUNT  
--
--SELECT e.employee_id,e.last_name,e.salary 
--FROM employees e 
--WHERE e.salary > ( SELECT (j.min_salary+j.max_salary)/2 
--                  FROM jobs j 
--                  WHERE j.job_id=e.job_id )
--AND e.job_id IN ( SELECT job_id     
--                  FROM employees m 
--                  WHERE e.department_id=m.department_id 
--                  AND LOWER(m.last_name) LIKE '%t%' ); --21 rez
--
-- -- lucreaza pe acelasi job ca si colegii de departament care contin litera t                  
 
 /*                 
20. Scrieti o cerere pentru a afi?a angaja?ii care câ?tig? mai mult decât oricare func?ionar 
(job-ul con?ine ?irul “CLERK”). Sorta?i rezultatele dupa salariu, în ordine descresc?toare.
Ce rezultat este returnat dac? se înlocuie?te “ALL” cu “ANY”?*/

SELECT * 
FROM employees e 
WHERE salary > ALL ( SELECT salary  ---mai mare ca maximul  --2100...4200
                    FROM employees 
                    WHERE upper(job_id) LIKE '%CLERK%' )
order by salary desc;     
---4400 .... 24000               
--61 rez

SELECT salary  ---mai mare ca maximul
                    FROM employees 
                    WHERE upper(job_id) LIKE '%CLERK%' 
                                       
order by salary desc;

--extra
SELECT * 
FROM employees e 
WHERE salary > ( SELECT max(salary)  ---mai mare ca maximul
                    FROM employees 
                    WHERE upper(job_id) LIKE '%CLERK%' )
order by salary desc;  --61 rez

sELECT salary 
FROM employees 
WHERE upper(job_id) LIKE '%CLERK%'
order by 1; --2100.....4200

SELECT * 
FROM employees e 
WHERE salary > any ( SELECT salary  ---mai mare ca minimul
                    FROM employees 
                    WHERE upper(job_id) LIKE '%CLERK%' )
order by salary; --2200 -24000
--106 rez

----------------------------------------------------------------------------------------------final sapt 4

7. Scrie?i o cerere pentru a afi?a numele, numele departamentului ?i salariul angaja?ilor 
care nu câ?tig? comision, dar al c?ror ?ef direct câ?tig? comision

select last_name, first_name, department_name, commission_pct, e.manager_id
from employees e, departments d
where e.department_id = d.department_id
--and e.commission_pct is null  -- 0 rez
and e.manager_id in (select employee_id
                     from employees
                     where commission_pct is not null);

select last_name, first_name, department_name, commission_pct, 
        e.manager_id, 
        (Select commission_pct from employees where employee_id = e.manager_id) comision_manager
        --am afisat si comisionul managerului direct print-o subcerere corelata in clauza de SELECT
from employees e, departments d
where e.department_id = d.department_id
--and e.commission_pct is null  -- 0 rez
and e.manager_id in (select employee_id
                     from employees
                     where commission_pct is not null);      --29 rez               

7". Scrie?i o cerere pentru a afi?a numele, numele departamentului ?i salariul angaja?ilor 
care au salariu mai mare decât salariul mediu pentru job-ul corespunz?tor , 
dar al c?ror ?ef direct câ?tig? comision.   

select last_name, first_name, department_name, commission_pct
from employees e, departments d
where e.department_id = d.department_id
and e.salary > ( SELECT (j.min_salary+j.max_salary)/2 
                  FROM jobs j 
                  WHERE j.job_id=e.job_id )
and e.manager_id in (select employee_id
                     from employees
                     where commission_pct is not null);
                                    
                                    




