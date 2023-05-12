S10 + S11 - Lab8.pdf 

1.	a) Sã se afiseze informatii despre angajatii al cãror salariu depãseste 
valoarea medie a salariilor colegilor sãi de departament.
SELECT  e.last_name, e.salary, e.department_id
FROM    employees e
WHERE   e.salary > (SELECT   AVG(salary)
        /*24000*/  FROM     employees
                  WHERE    department_id = e.department_id) --38 rez
                                              /*90*/
 order by 3;
 
  select avg(salary)
  from employees
  where department_id = 90; --19333,3333333333333333333333333333333333
  
  select *
  from employees
  where department_id = 90;
100	Steven	King	SKING	515.123.4567	17-06-1987	AD_PRES	24000			90
101	Neena	Kochhar	NKOCHHAR	515.123.4568	21-09-1989	AD_VP	17000		100	90
102	Lex	De Haan	LDEHAAN	515.123.4569	13-01-1993	AD_VP	17000		100	90
  
  select avg(salary)
  from employees
  group by department_id;
  
  
SELECT  last_name, salary, department_id, (SELECT   round(AVG(e2.salary))
                                            FROM     employees e2
                                            WHERE    e2.department_id = e.department_id) media
FROM    employees e
WHERE   salary > (SELECT   AVG(salary)
                  FROM     employees
                  WHERE    department_id = e.department_id)
order by 3,2;                  
                  
b) Analog cu cererea precedentã, afisându-se si numele departamentului, media salariilor 
acestuia si numãrul de angajati. Se cer 2 solu?ii
(cu subcerere nesincronizatã în clauza FROM ?i
cu subcerere sincronizatã în clauza SELECT).

 select count(*)
  from employees
  where department_id = 90;
   I -   subcerere sincronizatã în clauza SELECT
   
SELECT  last_name, salary, department_id,
        (SELECT   round(AVG(salary))
          FROM     employees
          WHERE    department_id = e.department_id) Media,
       (select department_name
       from departments
       where department_id = e.department_id)  Nume_dept,
       (select count(*)
       from employees
       where department_id = e.department_id ) nr_ang
FROM    employees e
WHERE   salary > (SELECT   AVG(salary)
                  FROM     employees
                  WHERE    department_id = e.department_id)
order by 1;  --38 rez 


---atentie --nuuuu
SELECT  last_name, salary, department_id,
        (SELECT   round(AVG(salary)), count(*)  ----ORA-00913: too many values
          FROM     employees
          WHERE    department_id = e.department_id) Media 
     
FROM    employees e
WHERE   salary > (SELECT   AVG(salary)
                  FROM     employees
                  WHERE    department_id = e.department_id)
order by 1;  --38 rez 
                  
     II -subcerere nesincronizatã în clauza FROM 
select last_name, salary, d.department_id, round(k.medie), d.department_name, k.nr_ang
from employees e,
    (select  department_id dep_id, count(employee_id) nr_ang, (avg(salary)) medie
    from employees
    group by department_id) k,
    departments d
where e.department_id = k.dep_id
and d.department_id = e.department_id
and e.salary > k.medie ; --38 rez

2.	Sã se afiseze numele si salariul angajatilor al cãror salariu este mai mare 
decât salariile medii din toate departamentele. 
Se cer 2 variante de rezolvare: cu operatorul ALL ?i cu functia MAX.
---media salariilor din fiecare departament
select (avg(salary))
from employees
group by department_id;

--maximul salariilor medii
select max(avg(salary))
from employees
group by department_id;
--19333.3333333333333333333333333333333333

--R:
select last_name, first_name, salary
from employees
where salary > (select max(avg(salary))
                from employees
                group by department_id); --King	Steven	24000

select last_name, first_name, salary
from employees
where salary > all (select (avg(salary))
                    from employees
                    group by department_id);     --King	Steven	24000           

--3.	Sã se afi?eze numele si salariul celor mai putin plãtiti angajati din fiecare departament 
--(3 solu?ii: cu ?i fãrã sincronizare, subcerere în clauza FROM).
--
--I - cu sincoronizare:

select e1.last_name, e1.first_name, e1.salary, e1.department_id
from employees e1
where e1.salary = ( select min(e2.salary)
                    from employees e2
                    where e2.department_id =  e1.department_id ); --12 rez
                    --nu folosim group by 

II - fara sincronizare
--fiecare dept cu salariul minim
select e2.department_id, min(e2.salary)
from employees e2
where department_id is not null
group by e2.department_id; --11 rez

II - fara sincronizare
select e1.last_name, e1.first_name, e1.salary, e1.department_id
from employees e1
where (e1.department_id,  e1.salary) IN (select e2.department_id, min(e2.salary)
                                        from employees e2
                                        where department_id is not null
                                        group by e2.department_id); --12 rez
--nuuuu                                       
 select e1.last_name, e1.first_name, e1.salary, e1.department_id, 
                  (select min(e2.salary)
                    from employees e2
                    where e1.department_id = e2.department_id) sal_minim_din_Dept
from employees e1
where ( e1.salary) IN (select  min(e2.salary)
                      from employees e2
                      group by e2.department_id); --26 rez
                      --afiseaza angajatii care au salariul egal cu minimul din orice departament
Mavris	Susan	6500	40	6500
Vollman	Shanta	6500	50	2100
Sarchand	Nandita	4200	50	2100                                        

III- Subcerere in clauza FROM
select e.last_name, e.salary, sal
from employees e, (select min(salary) as sal, department_id
                  from employees
                  group by department_id )aux
where  e.department_id = aux.department_id
and  aux.sal = e.salary ; --12 rez

IV- clauza With
-- 
with
dept_min_sal as
                  (select min(salary) as sal, department_id
                  from employees
                  group by department_id )
select e.last_name, e.salary
from employees e, dept_min_sal aux
where aux.sal = e.salary 
and e.department_id = aux.department_id; --12 rez               


4.	Pentru fiecare departament, sã se ob?inã denumirea acestuia ?i numele salariatului
având cea mai mare vechime din departament.
Sã se ordoneze rezultatul dupã numele departamentului.
I - cu sincronizare:
select d.department_name, e.last_name
from departments d, employees e
where e.department_id = d.department_id
and e.hire_date = (
                    select min(e1.hire_date)
                    from employees e1
                    where e1.department_id =  e.department_id 
                    )
 order by 1;--12 rez
 
 
 --atentie subcerea returneaza mai multe rezultate pt un departament
  --nu
select d.department_name, (select last_name
                            from employees e
                            where e.department_id =d.department_id 
                            and hire_date = ( select min(e1.hire_date)
                                                from employees e1
                                                where e.department_id = e1.department_id
                                                ))
from departments d
order by 1; --ORA-01427: single-row subquery returns more than one row
 
 II - fara sincronizare
select d.department_name, e.last_name
from departments d, employees e
where e.department_id = d.department_id
and (e.hire_date, e.department_id) in (select min(e1.hire_date), e1.department_id
                                        from employees e1
                                        where e1.department_id is not null
                                        group by e1.department_id)
order by 1; --12 rez

III- Subcerere in clauza FROM

select d.department_name, e.last_name, hire_date, d.department_id, dep_id, hire
from departments d, employees e, (select min(e1.hire_date) hire, e1.department_id dep_id
                                        from employees e1
                                        group by e1.department_id) aux
where e.department_id = d.department_id
and  e.department_id = aux.dep_id
and e.hire_date= aux.hire
order by 1; --12 rez


--afisati info si despre departamentele care nu au angajati

with 
ang_dept as  --care sunt agajatii cei mai vechi din fiecare departament
(select  e.last_name, e.department_id
from employees e, (select min(e1.hire_date) hire, e1.department_id dep_id
                                        from employees e1
                                        group by e1.department_id) aux
where  e.department_id = aux.dep_id
and e.hire_date= aux.hire)
--
select department_name, nvl(aux.last_name, 'Nu are angajati')
from departments d,ang_dept aux
where d.department_id= aux.department_id(+); --28 rez
--afisam info despre toate departamentele din firma

-----EXISTS------

8.	Sã se determine locatiile în care se aflã cel putin un departament.
Observa?ie: Ca alternativã a lui EXISTS, poate fi utilizat operatorul IN. Scrieti si aceastã variantã de rezolvare.
select l.location_id, l.city
from locations l
where exists (select 'x'
              from departments d
              where d.location_id = l.location_id); --7 rez
              
select distinct l.location_id, city
from locations l, departments d
where l.location_id = d.location_id;

Observa?ie: Ca alternativã a lui EXISTS, poate fi utilizat operatorul IN. 
Scrieti si aceastã variantã de rezolvare.
select l.location_id, l.city
from locations l
where l.location_id in  (select location_id
                        from departments d
                       );
 /*
 
5. S? se ob?in? numele salaria?ilor care lucreaz? într-un departament în care exist? cel 
pu?in un angajat cu salariul egal cu salariul maxim din departamentul 30.
SELECT last_name, salary, department_id
FROM employees e   --caut daca in departamentul liniei candidat exista vreun salariat care
WHERE EXISTS (SELECT 1 
             FROM employees
             WHERE e.department_id = department_id 
             AND salary = (SELECT MAX(salary)   --are salariul egal cu sal maxim din dept 30
                          FROM employees
                          WHERE department_id =30));  --40 rez
Observa?ie: Deoarece nu este necesar ca instruc?iunea SELECT interioar? (subcererea) s? 
returneze o anumit? valoare, se poate selecta o constant? (‘x’, 1 etc.). De altfel, din punct 
de vedere al performan?ei, selectarea unei constante este mai eficient? decât selectarea 
unei coloane, nemaifiind necesar? accesarea datei respective.
*/



5.	Sã se ob?inã numele salariatilor care lucreazã într-un departament în care existã 
cel pu?in un angajat cu salariul egal cu salariul maxim din departamentul 30.

SELECT last_name, salary, department_id
FROM    employees e  --e.department_id
WHERE EXISTS (SELECT 1    
              FROM  employees
              WHERE department_id = e.department_id   -- in acelasi departament cu linia candidat
              AND salary = (SELECT MAX(salary) --salariul maxim din departamentul 30 = 11000
                            FROM    employees
                            WHERE department_id =30))
order by 3,2;    --40 rez
--Raphaely	11000	30
--Cambrault	11000	80
--Abel	11000	80

Observa?ie: Deoarece nu este necesar ca instructiunea SELECT interioarã 
(subcererea) sã returneze o anumitã valoare, se poate selecta o constantã (‘x’, 1 etc.).
De altfel, din punct de vedere al performantei, selectarea unei constante este mai
eficientã decât selectarea unei coloane, nemaifiind necesarã accesarea datei respective.
SELECT distinct department_id   
              FROM  employees
              --WHERE e.department_id = department_id 
              where   salary = (SELECT MAX(salary)
                              FROM    employees
                            WHERE department_id =30);
                            30,80
                            
--v2:
SELECT last_name, salary, department_id
FROM    employees e  --e.department_id
WHERE e.department_id in (SELECT department_id    
                          FROM  employees
                          where salary = (SELECT MAX(salary) --salariul maxim din departamentul 30 = 11000
                                        FROM    employees
                                        WHERE department_id =30))
order by 3,2;    --40 rez

9.	Sã se determine departamentele în care nu existã nici un angajat.
Observa?ie: Se va utiliza NOT EXISTS. Acest exemplu poate fi rezolvat si printr-o subcerere necorelatã, 
utilizând operatorul NOT IN (vezi laboratorul 3). Atentie la valorile NULL! (fie puneti conditia
IS NOT NULL în subcerere, fie utilizati functia NVL). Scrieti si aceastã variantã de rezolvare.

select department_id, department_name
from departments d -- d.department_id
where not exists ( select employee_id  --select 1
                  from employees e
                  where e.department_id = d.department_id); --16 dep
                  
                  select employee_id  --select 1
                  from employees e
                  where e.department_id = 220; --null
    --not exists (null) => TRUE   
    --not exists(subcererea returneaza cel putin o linie) => FALSE
                  
 select distinct department_id 
 from employees; --apare null
 
 select department_id, department_name
from departments d
where department_id not in (select distinct department_id 
                             from employees
                             where department_id is not null
                             ); 
select department_id
from departments d
minus
select distinct department_id 
from employees
where department_id is not null; --16 rez


select d.department_id, count(employee_id)
from departments d, employees e
where d.department_id =e.department_id(+)
group by d.department_id
having count(employee_id) =0;

/*
--Pt fiecare angajat sa afisam id-ul si numele sau complet impreuna cu
-- id-ul si numele  managerului sau.

Select e.employee_id, e.last_name||' '||e.first_name,e. manager_id,
        (select m.last_name||' '||m.first_name
        from employees m
        where m.employee_id =e.manager_id)
from employees e; --107 linii
*/


7.	Sã se afiseze codul, numele si prenumele angajatilor care au cel putin doi subord_directi. 

--managerii cu numarul de subord_directi
select manager_id, count(*)
from employees
where manager_id is not null
group by manager_id
order by 1;--18 rezultate

select *
from(select manager_id, count(*) nr
      from employees
      where manager_id is not null
      group by manager_id) aux
where aux.nr >=2
order by 1; --15 rezultate


--v1:
select e.employee_id, e.last_name, e.first_name
from(select manager_id, count(*) nr
      from employees
      where manager_id is not null
      group by manager_id) aux, employees e
where aux.nr >=2
and e.employee_id =aux.manager_id
order by 1; --15 rez


--v2
SELECT employee_id, last_name, first_name
FROM employees e
WHERE 2 <= (SELECT COUNT(*)    -- subcererea numara pt fiecare linie candidat 
            FROM employees p   -- cati subord_directi are respectivul angajat
            WHERE p.manager_id = e.employee_id);
                           --15 rezultate     
--v3:          
SELECT employee_id, last_name, first_name
FROM employees e
WHERE exists (SELECT 'x'
            FROM employees
            WHERE manager_id = e.employee_id
            having count(*)>=2); -- 15 rez
            
--v4

select *
from employees
where employee_id in (select manager_id
                        from employees
                        where manager_id is not null
                        group by manager_id
                        having count(*) >=2);--15 rez

            
 IV. [Clauza WITH]
• Cu ajutorul clauzei WITH se poate defini un bloc de cerere înainte ca acesta
sã fie utilizat într-o interogare.
• Clauza permite reutilizarea aceluiasi bloc de cerere într-o instructiune SELECT complexã. 
Acest lucru este util atunci când o cerere face referintã de mai multe ori la acelasi bloc de cerere, 
care contine operatii join si functii agregat.

10. Utilizând clauza WITH, sã se scrie o cerere care afiseazã numele departamentelor 
si valoarea totalã a salariilor din cadrul acestora. 
Se vor considera departamentele a cãror valoare totalã a salariilor 
este mai mare decât media valorilor totale ale salariilor tuturor angajatilor.(sum(sal_dep)/nr_dept)
WITH val_dep AS (
                  select department_name, sum(salary) as suma_Per_dept
                  from departments d, employees e
                  where e.department_id =d.department_id
                  group by department_name ),
val_medie AS (select sum(suma_Per_dept)/count(*) as medie   --count(*) =11
              from val_dep )  --62218,1818181818181818181818181818181818
SELECT * 
FROM val_dep
WHERE suma_Per_dept > (SELECT medie FROM val_medie) 
ORDER BY department_name;     --2 rez 
--Sales	304500
--Shipping	156400


--unde:
WITH val_dep AS (
                  select department_name, sum(salary) as suma_Per_dept
                  from departments d, employees e
                  where e.department_id =d.department_id
                  group by department_name ),
val_medie AS (select sum(suma_Per_dept)/count(*) as medie   --count(*) =11
              from val_dep )
select *
from val_medie; --62218.1818181818181818181818181818181818




11. Sã se afiseze codul, prenumele si numele (pe aceeasi coloanã), codul job-ului si data angajãrii,
ale subordonatilor directi ai lui Steven King care au cea mai mare vechime.
--rez:
with subord_directi as (select employee_id, last_name, first_name, hire_date
                        from employees
                        where manager_id = (select employee_id
                                            from employees
                                            where initcap(first_name) ='Steven'
                                            and initcap(last_name) ='King')), --14 rez
 vechime_maxima as ( select min(hire_date) maxim
                    from subord_directi) --21-09-1989
select * 
from subord_directi
where hire_date = (select maxim from vechime_maxima);
--101	Kochhar	Neena	21-09-1989

--v2:

select * 
from (select employee_id, last_name, first_name, hire_date
      from employees
      where manager_id = (select employee_id
                        from employees
                        where initcap(first_name) ='Steven'
                        and initcap(last_name) ='King')) subord_directi
where hire_date = ( select min( hire_date)
                    from employees
                    where manager_id = (select employee_id
                                        from employees
                                        where initcap(first_name) ='Steven'
                                        and initcap(last_name) ='King'));

                    
--care este cea mai mare vechime a subordonatilor lui steven king
select min(hire_date)
from employees
where manager_id = (select employee_id
                    from employees
                    where initcap(first_name) ='Steven'
                    and initcap(last_name) ='King'); --21-SEP-89
                    

----care sunt subordonatii cu aceasta vechime cea mai mare
select employee_id, last_name, first_name, hire_date
from employees  --nu ma asigura ca salariatii afisati sunt si subordonati ai lui steven king
where hire_date =
                    (select min(hire_date)
                    from employees
                    where manager_id = (select employee_id
                                        from employees
                                        where initcap(first_name) ='Steven'
                                        and initcap(last_name) ='King')); 
                                        
--v2:
select employee_id, last_name, first_name, hire_date
from employees  
where hire_date =
                    (select min(hire_date)
                    from employees
                    where manager_id = (select employee_id
                                        from employees
                                        where initcap(first_name) ='Steven'
                                        and initcap(last_name) ='King'))
and  manager_id = (select employee_id ---aici verific ca cei afisati sunt subordonati ai lui steven king
                    from employees
                    where initcap(first_name) ='Steven'
                    and initcap(last_name) ='King')  ;                                   
--101	Kochhar	Neena	21-SEP-89


--atentie:
with subord_directi as (select employee_id, last_name, first_name, hire_date
                        from employees
                        where manager_id = (select employee_id
                                            from employees
                                            where initcap(first_name) ='&prenume'
                                            and initcap(last_name) ='&nume')), --14 rez
 vechime_maxima as ( select min(hire_date) maxim
                    from subord_directi) --21-09-1989
select * 
from subord_directi
where hire_date = (select maxim from vechime_maxima);

--pt: Alexander Hunold	
--104	Ernst	Bruce	21-MAY-91
11-2. Sã se afiseze codul, prenumele si numele (pe aceeasi coloanã), codul job-ului si data angajãrii,
ale subalternii subordonatilor directi ai lui Steven King care au cea mai mare vechime.  
--subalternii  au cea mai mare vechime.  

with subord_directi as (select employee_id, last_name, first_name, hire_date
                    from employees
                    where manager_id = (select employee_id
                                        from employees
                                        where initcap(first_name) ='Steven'
                                        and initcap(last_name) ='King')), --14 rez
 subalterni as (select employee_id, last_name, first_name, hire_date, manager_id
               from employees
               where manager_id in (select employee_id
                                    from subord_directi)),     --82 rez                                  
 vechime_maxima as ( select min(hire_date) maxim
                    from subalterni)  --17-SEP-87
select * 
from subalterni
where hire_date = (select * from vechime_maxima); --200	Whalen	Jennifer	17-09-1987
 --200 il are ca sef pe 101, care il are ca sef pe Steven King


--care sunt subalternii subordonatilor lui Steven King

with subord_directi as (select employee_id, last_name, first_name, hire_date
                    from employees
                    where manager_id = (select employee_id
                                        from employees
                                        where initcap(first_name) ='Steven'
                                        and initcap(last_name) ='King')),
 subalterni as (select employee_id, last_name, first_name, hire_date
               from employees
               where manager_id in (select employee_id
                                    from subord_directi))
 select *
 from subalterni
 order by hire_date asc; --82 rez
 
 -------------------sapt 10 (grupa133-miercuri)
V. [Analiza top-n]
Pentru aflarea primelor n rezultate ale unei cereri, este utilã func?ia ROWNUM. 
Aceasta returneazã numãrul de ordine al unei linii în rezultat. Condi?ia ce utilizeazã 
aceastã func?ie trebuie aplicatã asupra unei mul?imi ordonate de înregistrãri. Cum ob?inem acea mul?ime?

-- care sunt primele 10 randuri din employees?

select employee_id, last_name, first_name, salary
from employees
where rownum <=10;

100	King	Steven	24000
101	Kochhar	Neena	17000
102	De Haan	Lex	17000
103	Hunold	Alexander	9000
104	Ernst	Bruce	6000
105	Austin	David	4800
106	Pataballa	Valli	4800
107	Lorentz	Diana	4200
108	Greenberg	Nancy	12000
109	Faviet	Daniel	9000

select employee_id, last_name, first_name, salary
from employees
order by salary desc; --107 rez

100	King	Steven	24000
101	Kochhar	Neena	17000
102	De Haan	Lex	17000
145	Russell	John	14000
146	Partners	Karen	13500
201	Hartstein	Michael	13000
108	Greenberg	Nancy	12000
147	Errazuriz	Alberto	12000
205	Higgins	Shelley	12000
168	Ozer	Lisa	11500
174	Abel	Ellen	11000
148	Cambrault	Gerald	11000


12. S? se detemine primii 10 cei mai bine pl?ti?i angaja?i.

--NUUUUUUUU
select employee_id, last_name, first_name, salary
from employees
where rownum <=10
order by salary desc;

100	King	Steven	24000
101	Kochhar	Neena	17000
102	De Haan	Lex	17000
108	Greenberg	Nancy	12000
103	Hunold	Alexander	9000
109	Faviet	Daniel	9000
104	Ernst	Bruce	6000
105	Austin	David	4800
106	Pataballa	Valli	4800
107	Lorentz	Diana	4200

12. Sã se detemine primii 10 cei mai bine plãtiti angajati.

select *
from (select employee_id, last_name, first_name, salary
      from employees
      order by salary desc) t
where rownum<=10;

100	King	Steven	24000
101	Kochhar	Neena	17000
102	De Haan	Lex	17000
145	Russell	John	14000
146	Partners	Karen	13500
201	Hartstein	Michael	13000
108	Greenberg	Nancy	12000
147	Errazuriz	Alberto	12000
205	Higgins	Shelley	12000
168	Ozer	Lisa	11500


Care sunt top 7 salarii cele mai mari si cine este platit cu acele salarii?

with salarii7 as ( select * 
                  from (select distinct salary
                          from employees 
                          order by salary desc) --57 rez
                  where rownum<=7)
select employee_id, salary
from employees
where salary in (select * from salarii7); --10 angajati
            


--top 10 salary si angajatii care le detin
with salarii10 as ( select * 
                  from (select distinct salary
                          from employees 
                          order by salary desc) --57 rez
                  where rownum<=10)
select employee_id, salary
from employees
where salary in (select * from salarii10); --19 rez

13. Sã se determine cele mai slab plãtite 3 job-uri, 
din punct de vedere al mediei salariilor acestora.
select *
from (select job_id, avg(salary) medie
      from employees  --19 rez
      group by job_id
      order by medie asc
) where rownum < 4;

--PU_CLERK	2780
--ST_CLERK	2785
--SH_CLERK	3215

13-2-1 13. Sã se determine cele mai slab plãtite 14 job-uri, 
din punct de vedere al mediei salariilor acestora.
select *
from (select job_id, avg(salary) medie
      from employees  
      group by job_id
      order by medie asc
) where rownum <=14;

13-2-2: top 14 valori medii ale salariilor  (problema de dinainte) si 
job-urile cu acele valori medii

with sal_14 as
(select *
from (Select avg(salary) medie
      from employees  
      group by job_id
      order by medie asc
) where rownum <=14)
select job_id, avg(salary)
from employees 
group by job_id
having avg(salary) in (select medie from sal_14)
order by avg(salary);

PU_CLERK	2780
ST_CLERK	2785
SH_CLERK	3215
AD_ASST	4400
IT_PROG	5760
MK_REP	6000
HR_REP	6500
ST_MAN	7280
FI_ACCOUNT	7920
AC_ACCOUNT	8300
SA_REP	8350
PR_REP	10000
PU_MAN	11000
AC_MGR	12000
FI_MGR	12000



---lab9.pdf
20. S? se afi?eze codul, numele, salariul ?i codul departamentului din care face
parte un angajat al carui cod este introdus de utilizator de la tastatura. 
Analiza?i diferen?ele dintre cele 4 posibilit??i prezentate mai jos :

I.
SELECT
    employee_id,
    last_name,
    salary,
    department_id
FROM
    employees
WHERE
    employee_id = &p_cod;
    
    
II. 
DEFINE p_cod; 
// Ce efect are? 
SELECT employee_id, last_name, salary, department_id 
FROM employees 
WHERE employee_id = &p_cod; 
UNDEFINE p_cod;


III
DEFINE p_cod=100;

SELECT
    employee_id,
    last_name,
    salary,
    department_id
FROM
    employees
WHERE
    employee_id = &&p_cod;

UNDEFINE p_cod;
IV. 
accept p_cod prompt "cod=";

SELECT
    employee_id,
    last_name,
    salary,
    department_id
FROM
    employees
WHERE
    employee_id = &p_cod;
    
--21. S? se afi?eze numele, codul departamentului ?i salariul anual pentru to?i
--angaja?ii care au un anumit job.

SELECT
    employee_id,
    last_name,
    salary,
    department_id, salary *12 sal_anual
FROM
    employees
WHERE
    upper(job_id)= upper('&v_job');
    
    --SA_MAN -- 5 rez
    --Sa_maN -- 5 rez
    
 23. S? se afi?eze o coloan? aleas? de utilizator, dintr-un tabel ales de utilizator,
 ordonând dup? aceea?i coloan? care se afi?eaz?. De asemenea, este obligatorie 
 precizarea unei condi?ii în clauza WHERE. 
 
 SELECT &&p_coloana 
 FROM &p_tabel 
 WHERE &p_where 
 ORDER BY &p_coloana;   
