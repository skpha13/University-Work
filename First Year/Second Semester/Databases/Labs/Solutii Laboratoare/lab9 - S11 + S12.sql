--S11 - var de subst
--S12 - division
ALTER SESSION SET NLS_LANGUAGE=Romanian; 
drop table works_on;
drop table project;

create table PROJECT(
	project_id number(4) primary key, 
	project_name varchar2(30), 
	budget number(6), 
	start_date date, 
	deadline date,
	delivery_date date,
	project_manager number(4) references employees(employee_id)); 

create table WORKS_ON(
	project_id number(4) references project(project_id),
	employee_id number(6) references employees(employee_id),
	start_date date, 
	end_date date,
	primary key(project_id, employee_id));
	
insert into project values (1, 'ALFA', 20000, '2-IAN-2006', '30-MAR-2006', '7-APR-2006', 102);
insert into project values (2, 'BETA', 10000, '5-MAI-2006', '15-IUL-2006', '15-IUL-2006', 103); 
insert into project values (3, 'GAMA', 10000, '11-DEC-2006', '15-IAN-2007', '17-IAN-2007', 102); 

insert into works_on values(1, 125, '1-FEB-2006', '7-APR-2006');
insert into works_on values(1, 136, '2-IAN-2006', '30-MAR-2006');
insert into works_on values(1, 140, '15-FEB-2006', '7-APR-2006');
insert into works_on values(2, 145, '6-MAI-2006', '15-IUL-2006');
insert into works_on values(2, 125, '6-MAI-2006', '15-IUL-2006');
insert into works_on values(2, 101, '6-MAI-2006', '15-IUL-2006');
insert into works_on values(2, 148, '14-MAI-2006', '10-IUL-2006');
insert into works_on values(2, 200, '6-MAI-2006', '15-IUL-2006');
insert into works_on values(3, 145, '15-DEC-2007', '15-IAN-2007');
insert into works_on values(3, 148, '14-DEC-2006', '17-IAN-2007');
insert into works_on values(3, 150, '14-DEC-2006', '17-IAN-2007');
insert into works_on values(3, 162, '20-DEC-2006', '17-IAN-2007');
insert into works_on values(3, 101, '20-DEC-2006', '17-IAN-2007');
insert into works_on values(3, 176, '20-DEC-2006', '17-IAN-2007');
insert into works_on values(3, 200, '20-DEC-2006', '17-IAN-2007');
insert into works_on values(3, 140, '15-DEC-2006', '7-IAN-2007');

insert into works_on values(1, 101, '5-MAI-2006', '1-IUL-2006');
commit;


select * 
  from project;
  
1	ALFA	20000	02-IAN-06	30-MAR-06	07-APR-06	102
2	BETA	10000	05-MAI-06	15-IUL-06	15-IUL-06	103
3	GAMA	10000	11-DEC-06	15-IAN-07	17-IAN-07	102
  
select *
  from works_on;
  
1	125	01-FEB-06	07-APR-06
1	136	02-IAN-06	30-MAR-06
1	140	15-FEB-06	07-APR-06
2	145	06-MAI-06	15-IUL-06
2	125	06-MAI-06	15-IUL-06
2	101	06-MAI-06	15-IUL-06
2	148	14-MAI-06	10-IUL-06
2	200	06-MAI-06	15-IUL-06
3	145	15-DEC-07	15-IAN-07
3	148	14-DEC-06	17-IAN-07
3	150	14-DEC-06	17-IAN-07
3	162	20-DEC-06	17-IAN-07
3	101	20-DEC-06	17-IAN-07
3	176	20-DEC-06	17-IAN-07
3	200	20-DEC-06	17-IAN-07
3	140	15-DEC-06	07-IAN-07



select *
from works_on
order by employee_id;
 
2	101	06-MAI-06	15-IUL-06
3	101	20-DEC-06	17-IAN-07   ---101
1	101	05-MAI-06	01-IUL-06

1	125	01-FEB-06	07-APR-06
2	125	06-MAI-06	15-IUL-06

1	136	02-IAN-06	30-MAR-06

1	140	15-FEB-06	07-APR-06
3	140	15-DEC-06	07-IAN-07

3	145	15-DEC-07	15-IAN-07   ---145
2	145	06-MAI-06	15-IUL-06

3	148	14-DEC-06	17-IAN-07   --148
2	148	14-MAI-06	10-IUL-06

3	150	14-DEC-06	17-IAN-07

3	162	20-DEC-06	17-IAN-07

3	176	20-DEC-06	17-IAN-07

3	200	20-DEC-06	17-IAN-07   ---200
2	200	06-MAI-06	15-IUL-06

--Lista angajatialor care lucreaza la proiecte
select distinct employee_id
from works_on
order by 1; --10 rezultate
101
125
136
140
145
148
150
162
176
200 
--Lista angajatilor care lucreaza la proiecte cu buget de 10000.
--(lucreaza pe cel putin un proiect cu bugetul de 10000).
select distinct employee_id
from works_on
where project_id in (select project_id
                    from project
                    where budget = 10000)
order by employee_id;

select distinct w.employee_id
from works_on  w, project p
where w.project_id=p.project_id
and p.budget=10000
order by 1; --9 angjati

101
125
140
145
148
150
162
176
200


---angajatii pot lucra pe mai multe proiecte cu bugetul de 10000.
select  employee_id, project_id
from works_on
where project_id in (select project_id
                    from project
                    where budget = 10000)
order by employee_id;

--Exemplu: S? se ob?in? codurile salaria?ilor ata?a?i tuturor proiectelor
--pentru care s-a alocat un buget egal cu 10000.
Metoda 1 (utilizând de 2 ori NOT EXISTS):

1	140	15-FEB-06	07-APR-06
3	140	15-DEC-06	07-IAN-07

SELECT	DISTINCT employee_id
FROM		works_on a   --a.employee_id =140
WHERE NOT EXISTS  ---false
       (SELECT	project_id                                --nu exista un proiect cu bugetul de 10000 
        FROM	project p  -- p.project_id={2,3}              pe care angajatul afisat sa nu lucreze
        WHERE	budget=10000
        AND NOT EXISTS                --p1 - p.project_id =3, Ultimul select returneaza ceva => not exists ceva returnat -> false
                                      --deci proiectul 3 nu va fi returnat de al doilea select
                    (SELECT	project_id         --p2 - p.project_id =2, Ultimul select nu returneaza nimic -> not exist de nimic= true
                     FROM 	works_on b         -- DEci, proiectul 2 va fi returnat de al doilea select
                     WHERE	b.project_id =p.project_id
                     AND b.employee_id=a.employee_id));
 --Nu exista proiecte cu bugetul de 10000 pe care angajatul a.employee_id sa nu lucreze                    
                     
 Care sunt proiectele cu buget de 10000 pe care angajatul 140 nu lucreaza?
 
 select project_id
 from project p   --p.project_id
 where budget=10000
 and not exists ( ---lista de proiecte cu buget de 10000 pe care lucreaza angajatul 140
                  select project_id
                  from works_on b
                  where b.employee_id =140
                  and b.project_id = p.project_id);  -- proiectul 2
                     
1	140	15-FEB-06	07-APR-06
3	140	15-DEC-06	07-IAN-07                     
                     
SELECT	 employee_id
FROM		(select distinct employee_id from works_on) a  -- a.employee_id=148
WHERE NOT EXISTS   --true  (not exists de nimic = true)
       (SELECT	1
        FROM	project p               --- p.project_id={2,3}
        WHERE	budget=10000        --p.project_id =2 -> false  -> proiectul 2 nu este returnat in al doilea select
                                 --p.project_id =3 -> false  -> proiectul 3 nu este returnat in al doilea select
        AND NOT EXISTS    
                    (SELECT	'x'                      
                     FROM 	works_on b
                     WHERE	b.project_id =p.project_id
                     AND b.employee_id=a.employee_id)
          );                
  
3	148	14-DEC-06	17-IAN-07
2	148	14-MAI-06	10-IUL-06  


148
101
200
145

SELECT a.employee_id
FROM (select distinct employee_id from works_on) a
WHERE NOT EXISTS
        (SELECT 1
        FROM project p
        WHERE budget = 10000 AND
              (p.project_id, a.employee_id) not in (select project_id, employee_id
                                                    from works_on));


SELECT a.employee_id, project_id
FROM (select distinct employee_id from works_on) a
WHERE NOT EXISTS
        (SELECT 1
        FROM project p
        WHERE budget = 10000 AND
              (p.project_id, a.employee_id) not in (select project_id, employee_id
                                                    from works_on));

--------------------------------------------------------------------------------------------
Metoda 2 (simularea diviziunii cu ajutorul func?iei COUNT):

Care sunt angajatii care lucreaza pe proiecte cu bugetul de 10000. 
Afisati si proiectele.
SELECT	employee_id, project_id 
FROM		works_on
WHERE	project_id IN
                  (SELECT	project_id 
                   FROM  	project
                   WHERE	budget=10000)
order by 1,2;                   

101	2
101	3
125	2
140	3
145	2
145	3
148	2
148	3
150	3
162	3
176	3
200	2
200	3

Numaram pt fiecare angajat pe cate proiecte cu bugetul de 10000 lucreaza acesta:
SELECT	employee_id, count(project_id) 
FROM		works_on
WHERE	project_id IN
                  (SELECT	project_id   ---luam in considerare numai proiectele de buget de 10000
                   FROM  	project
                   WHERE	budget=10000)
GROUP BY	employee_id;  

148	2
162	1
125	1
101	2
200	2
140	1
145	2
176	1
150	1

Care sunt proiectele cu bujetul de 10000?
select *
from project 
where budget=10000;

Cate proiecte au bugetul de 10000?
select count(*)
from project 
where budget=10000;

Rezolvare:   
SELECT	employee_id, count(project_id) 
FROM		works_on
WHERE	project_id IN
                  (SELECT	project_id   ---luam in considerare numai proiectele de buget de 10000
                   FROM  	project
                   WHERE	budget=10000)
GROUP BY	employee_id
HAVING	COUNT(project_id)=    
                        (SELECT 	COUNT(*) --2 proiecte cu buget de 10000
                         FROM 	project    -- numarul total de proiecte cu bugetul de 10000
                         WHERE 	budget=10000);
                         

                         
 --pt fiecare angajat verificat pe cate proiecte cu bugetul de 100000 lucreaza el.
-- Afisam angajatul, daca numarul de proiecte cu buget de 10000(pe care lucreaza el) 
-- este egal cu numarul total de proiecte pt care s-a alocat buget de 10000.             
                         
1	140	15-FEB-06	07-APR-06
3	140	15-DEC-06	07-IAN-07
--------------------------------------------------------------------------------------------
Metoda 3 (operatorul MINUS):
Faceti un cross-join intre toate proiectele cu bugetul de 10000
si angajatii care lucreaza pe proiecte(nu neaparat pe proiecte cu buget de 10000):

SELECT employee_id, project_id  --toate variantele ca angajatii sa lucreze la proiectele 2 si 3(cu buget de 10000)
FROM (SELECT DISTINCT employee_id FROM works_on) t1,
    (SELECT project_id FROM project WHERE budget=10000) t2
order by 1,2;
101	2
101	3
125	2
125	3
136	2
136	3
140	2
140	3

SELECT employee_id , project_id  --returneaza angajatii si proiectul cu buget de 10000 pe care ei nu lucreaza
from -- = angajatii care nu lucreaza la toate proiectele cu buget de 10000 = ori lucreaza la un singur poiect cu bujet de 10000 sau nu lucreaza la niciunul cu buget de 10000
    ( SELECT employee_id, project_id  
      FROM (SELECT DISTINCT employee_id FROM works_on) t1,
          (SELECT project_id FROM project WHERE budget=10000) t2
         --order by 1,2
      MINUS
      SELECT employee_id, project_id FROM works_on 
    ) t3;

--rezolvare:
SELECT employee_id 
FROM    works_on
MINUS
SELECT employee_id 
from  --angajatii care nu lucreaza la ambele proiecte cu buget de 10000 = ori lucreaza la un singur poiect cu bujet de 10000 sau nu lucreaza la niciunul cu buget de 10000
    ( SELECT employee_id, project_id  --toate variantele ca angajatii sa lucreze la proiectele 2 si 3(cu buget de 10000)
      FROM (SELECT DISTINCT employee_id FROM works_on) t1,
          (SELECT project_id FROM project WHERE budget=10000) t2
         --order by 1,2
      MINUS
      SELECT employee_id, project_id FROM works_on -- proiectele la care lucreaza in realitate
    ) t3;
{140 2 , 140 3 } \{140 1, 140 3}  ={140 2} --proiectele cu buget de 10000 la cere ei nu lucreaza
{101 2, 101 3} \ {101 1, 101 2, 101 3} = {}

Metoda 4 (A include B => B\A = multime vida): 

B\A = Din multimnea de proiecte cu bugetul de 10000 le scot pe cele la care lucreza angajatul nostru
v1-Daca rezultatul este o multime goala, inseamna ca angajatul lucreza pe toate proiectele cu bugetul de 10000
v2-Daca se returneaza cel putin un element, atunci angajatul nu lucreaza pe toate proiectele cu buget de 10000.


SELECT a.employee_id
FROM		(select distinct employee_id from works_on) a  --a.employee_id
WHERE NOT EXISTS (
                 (SELECT	project_id  --toate proiectle cu buget de 10000
                  FROM	project p
                  WHERE	budget=10000)
                       MINUS
                  (SELECT	b.project_id   -- toate proiectele pe care lucreaza angajatul a.employee_id                   
                   FROM works_on b
                   WHERE b.employee_id=a.employee_id));

101-> {2,3} \{1,2,3} ={}
140 ->{2,3} \{1,3} ={2}

SELECT	DISTINCT employee_id
FROM		works_on a
WHERE NOT EXISTS (
                   (SELECT	project_id   --proiecte cu buget de 100000
                    FROM	project p
                      WHERE	budget=10000)
                      MINUS
                      (SELECT	p.project_id     --toate proiectele pe care lucreaza angajatul
                       FROM	project p2, works_on b
                       WHERE	b.project_id= p2.project_id
                       AND b.employee_id = a.employee_id));
                                         


--1 1.	Sa se listeze informa?ii despre angaja?ii care au lucrat în toate 
--proiectele demarate în primele 6 luni ale anului 2006. 
--Implementa?i toate variantele.


---atentie: nu
--aici obtinem angajatii care lucreaza pe proiecte (nu pe toate) demarate în primele 6 luni ale anului 2006. 
--ei pot lucra pe 1, 2... proiecte  demarate în primele 6 luni ale anului 2006. 
--nu stiu ca lucreaza pe TOATE proiectele  demarate în primele 6 luni ale anului 2006. 
select distinct employee_id
from works_on
where project_id in (
                    SELECT project_id
                    FROM project p
                    WHERE to_char(start_date, 'mm') <= 6 
                    AND to_char(start_date, 'yyyy') = 2006
                    ); --- 7 rez


--proiectele demarate în primele 6 luni ale anului 2006. 
--Proiectele:1, 2
SELECT project_id
FROM project p
WHERE to_char(start_date, 'mm') <= 6 
AND to_char(start_date, 'yyyy') = 2006;
  
  
--1 metoda1
SELECT DISTINCT employee_id
FROM works_on a
WHERE NOT EXISTS
               (SELECT project_id
                FROM project p
                WHERE to_char(start_date, 'mm') <= 6 AND 
                      to_char(start_date, 'yyyy') = 2006
                AND NOT EXISTS
                              (SELECT employee_id
                              FROM works_on b
                              WHERE a.employee_id = b.employee_id
                              AND p.project_id = b.project_id));
                              
SELECT a.employee_id
FROM (select distinct employee_id from works_on) a
WHERE NOT EXISTS
              (SELECT 1
              FROM project p
              WHERE to_char(p.start_date, 'mm') <= 6 and
              to_char(p.start_date, 'yyyy') = 2006 and
              (p.project_id, a.employee_id) not in (select b.project_id, b.employee_id
                                                    from works_on b));                              
                              
select *
from employees
where not exists
              (select p.project_id
              from project p
              where to_char(start_date, 'yyyy') = 2006 and to_char(start_date, 'MM') <= 6
              and not exists (select 1
                              from works_on
                              where p.project_id = works_on.project_id 
                              and works_on.employee_id = employees.employee_id));

            
--1 metoda 2
SELECT employee_id
FROM works_on
WHERE project_id IN
                  (SELECT project_id
                  FROM project
                  WHERE  to_char(start_date, 'mm') <= 6 AND 
                  to_char(start_date, 'yyyy') = 2006)
GROUP BY employee_id
HAVING COUNT(project_id)=
                        (SELECT COUNT(*)
                        FROM project
                        WHERE  to_char(start_date, 'mm') <= 6 
                        AND to_char(start_date, 'yyyy') = 2006);
               
               

SELECT employee_id
FROM works_on
WHERE project_id IN
              (SELECT project_id
                FROM project
                WHERE to_char(start_date, 'mm') <= 6 AND 
                      to_char(start_date, 'yyyy') = 2006)
GROUP BY employee_id
HAVING COUNT(project_id)=
                        (SELECT COUNT(*)
                        FROM PROJECT
                        WHERE to_char(start_date, 'mm') <= 6 AND 
                              to_char(start_date, 'yyyy') = 2006);
                              
SELECT employee_id, COUNT(project_id)
FROM works_on
WHERE project_id IN
              (SELECT project_id
                FROM project
                WHERE to_char(start_date, 'mm') <= 6 AND 
                      to_char(start_date, 'yyyy') = 2006)
GROUP BY employee_id ;     



--1 metoda 3           
SELECT employee_id
FROM works_on
MINUS
SELECT employee_id FROM
                 ( SELECT employee_id, project_id
                 FROM (SELECT DISTINCT employee_id FROM works_on) t1,
                      (SELECT project_id FROM project WHERE to_char(start_date, 'mm') <= 6 AND 
                                                      to_char(start_date, 'yyyy') = 2006) t2
                  MINUS
                  SELECT employee_id, project_id FROM works_on
                  ) t3;


--metoda 4

--125
--101

SELECT DISTINCT a.employee_id
FROM works_on a
WHERE NOT EXISTS (
          (SELECT project_id
          FROM project p
          WHERE to_char(start_date, 'mm') <= 6 
          AND  to_char(start_date, 'yyyy') = 2006) --1 si 2
          MINUS
          (SELECT b.project_id
          FROM  works_on b
          WHERE  b.employee_id=a.employee_id));


--2	101	06-MAI-06	15-IUL-06
--3	101	20-DEC-06	17-IAN-07
--1	101	05-MAI-06	01-IUL-06
--
--1	125	01-FEB-06	07-APR-06
--2	125	06-MAI-06	15-IUL-06


SELECT DISTINCT employee_id
FROM works_on a
WHERE NOT EXISTS (
          (SELECT project_id
          FROM project p
          WHERE to_char(start_date, 'mm') <= 6 AND 
                            to_char(start_date, 'yyyy') = 2006) --1 si 2
          MINUS
          (SELECT p.project_id
          FROM project p, works_on b
          WHERE p.project_id=b.project_id
          AND b.employee_id=a.employee_id));

/*
--2 2.	S? se listeze informa?ii despre proiectele la care au participat to?i
--angaja?ii care au de?inut alte 2 posturi în firm?.

select employee_id
from job_history 
group by employee_id
having count(*) >=2;

SELECT employee_id 
FROM (SELECT employee_id, count(job_id) c1
           FROM job_history b 
           GROUP BY employee_id) x
WHERE c1 = 2 ;


SELECT project_id , project_name
FROM project a
WHERE NOT EXISTS
    (SELECT employee_id 
     FROM (SELECT employee_id, count(job_id) c1
           FROM job_history b 
           GROUP BY employee_id) x
    WHERE c1 = 2 
    AND NOT EXISTS            
            (SELECT employee_id
            FROM works_on d
            WHERE d.employee_id = x.employee_id
              AND a.project_id = d.project_id));
3	GAMA


select project_id
  from works_on
  where employee_id in
          (select employee_id
            from job_history
            group by employee_id
            having count(job_id) = 2)
  group by project_id
  having count(employee_id) = (select sum(count(distinct employee_id))
                              from job_history 
                              group by employee_id
                              having count(job_id) = 2);
  
5.	S? se listeze angaja?ii (codul ?i numele acestora) care au lucrat pe cel pu?in dou? proiecte nelivrate la termen.
select *
from project
where delivery_date >deadline;


10.	Se cer informa?ii (nume, prenume, salariu, num?r proiecte) despre managerii de proiect care au condus 2 proiecte.
select count(*),p.PROJECT_MANAGER, e.last_name
from project p, employees e
where p.PROJECT_MANAGER =e.EMPLOYEE_ID
group by p.PROJECT_MANAGER, e.last_name
having count(*) >1;

--16
SELECT last_name,  department_id,  salary*12
FROM employees
WHERE job_id = '&p_cod';

--17
SELECT last_name,  department_id,  salary*12
FROM employees
where hire_date> to_date('&data');

--18
SELECT &coloana
from &tabel
where &conditie
order by 1;


--2 
SELECT DISTINCT w.project_id, p.project_name
FROM works_on w, project p
WHERE NOT EXISTS
(SELECT employee_id
FROM job_history
GROUP BY employee_id
HAVING COUNT(*) >= 2
MINUS
SELECT employee_id
FROM works_on
WHERE project_id = p.project_id
and p.project_id = w.project_id);

2	101	06-MAI-06	15-IUL-06
3	101	20-DEC-06	17-IAN-07
1	101	05-MAI-06	01-IUL-06

1	125	01-FEB-06	07-APR-06
2	125	06-MAI-06	15-IUL-06

1	136	02-IAN-06	30-MAR-06

1	140	15-FEB-06	07-APR-06
3	140	15-DEC-06	07-IAN-07

3	145	15-DEC-07	15-IAN-07
2	145	06-MAI-06	15-IUL-06

3	148	14-DEC-06	17-IAN-07
2	148	14-MAI-06	10-IUL-06

3	150	14-DEC-06	17-IAN-07

3	162	20-DEC-06	17-IAN-07

3	176	20-DEC-06	17-IAN-07

3	200	20-DEC-06	17-IAN-07
2	200	06-MAI-06	15-IUL-06


12.	a) S? se ob?in? numele angaja?ilor care au lucrat cel pu?in pe acelea?i 
proiecte ca ?i angajatul având  codul 200.
Obs: Incluziunea dintre 2 mul?imi se testeaz? cu ajutorul propriet??ii 
„A inclus în B => A-B =Ø”. Cum putem implementa acest lucru în SQL? 
Pentru rezolvarea exerci?iului, trebuie selecta?i angaja?ii pentru care este 
vid? lista proiectelor pe care a lucrat angajatul 200 mai pu?in lista 
proiectelor pe care au lucrat acei angaja?i.

select distinct a.employee_id, e.last_name
from works_on a, employees e
where e.employee_id=a.employee_id
and not exists 
          (select b.project_id
            from works_on b, project c
            where b.project_id=c.project_id
            and b.employee_id=200
        minus
            (select b.project_id
            from works_on b, project c
            where b.project_id=c.project_id
            and b.employee_id=a.employee_id))
and a.employee_id !=200;
  
101	Kochhar  {2, 3} \{1,2,3} ={}
148	Cambrault
145	Russell


125  {2,3} \{1,2} ={3}


b) S? se ob?in? numele angaja?ilor care au lucrat cel mult pe acelea?i proiecte ca ?i angajatul având codul 200.

select distinct a.employee_id, e.last_name
from works_on a, employees e
where e.employee_id=a.employee_id
and not exists 
          (
            select b.project_id
            from works_on b, project c
            where b.project_id=c.project_id
            and b.employee_id=a.employee_id
            minus
            select b.project_id
            from works_on b, project c
            where b.project_id=c.project_id
            and b.employee_id=200) 
 and a.employee_id !=200;
 
148	Cambrault
176	Taylor  {3} \{2,3} ={}
145	Russell
150	Tucker
162	Vishney


101 {1,2,3}\{2,3}={1}
140 {1,3}\{2,3}={1}

13.	S? se ob?in? angaja?ii care au lucrat pe acelea?i proiecte ca ?i angajatul având codul 200.
Obs: Egalitatea între dou? mul?imi se testeaz? cu ajutorul propriet??ii „A=B => A-B=Ø ?i B-A=Ø”.


select distinct a.employee_id, e.last_name
from works_on a, employees e
where e.employee_id=a.employee_id
and not exists 
          (
            select b.project_id
            from works_on b, project c
            where b.project_id=c.project_id
            and b.employee_id=a.employee_id
            minus
            select b.project_id
            from works_on b, project c
            where b.project_id=c.project_id
            and b.employee_id=200) 
and not exists 
          (select b.project_id
            from works_on b, project c
            where b.project_id=c.project_id
            and b.employee_id=200
        minus
            (select b.project_id
            from works_on b, project c
            where b.project_id=c.project_id
            and b.employee_id=a.employee_id)) 
and a.employee_id !=200;

148	Cambrault
145	Russell*/

20. Sa se afiseze codul, numele, salariul si codul departamentului din care
face parte pentru un angajat al carui cod este introdus de utilizator de la 
tastatura. Analizati diferentele dintre cele 4 posibilitati prezentate mai jos : 
I.
SELECT employee_id, last_name, salary, department_id
FROM   employees
WHERE  employee_id = &p_cod;


II. 
set verify on;
DEFINE p_cod; 
--Ce efect are?
--Symbol P_COD is UNDEFINED( Nu am definit inca variabila p_cod
SELECT employee_id, last_name, salary, department_id
FROM   employees
WHERE  employee_id = &p_cod;
UNDEFINE p_cod;

III. 
DEFINE p_cod=100;
SELECT employee_id, last_name, salary, department_id
FROM   employees
WHERE  employee_id = &p_cod;

DEFINE p_cod;
--DEFINE P_COD =  100 (NUMBER)

define var=101;
define;

--DEFINE VAR =  101 (NUMBER)
--DEFINE P_COD =  100 (NUMBER)
UNDEFINE p_cod;
--Symbol P_COD is UNDEFINED

IV. 

set verify on;
ACCEPT p_cod PROMPT "Introduceti un cod de angajat:";
SELECT employee_id, last_name, salary, department_id
FROM   employees
WHERE  employee_id = &p_cod;

--set verify on;
--old:SELECT employee_id, last_name, salary, department_id
--FROM   employees
--WHERE  employee_id = &p_cod
--new:SELECT employee_id, last_name, salary, department_id
--FROM   employees
--WHERE  employee_id = 101
DEFINE p_cod;
--DEFINE P_COD =  101 (NUMBER)
UNDEFINE p_cod;

undefine var;
--21	Sa se afiseze numele angajatului, codul departamentului si salariul anual pentru toti
--angajatii care au un anumit job. 
AD_VP

ad_Vp

UNDEFINE p_cod;


--nu
select e.last_name, e.department_id, e.salary*12
from employees e
where e.job_id =  '&p_cod';


Rezolvarea:
select e.last_name, e.department_id, e.salary*12
from employees e
where lower(e.job_id) =lower('&p_cod');


undefine p_cod;
--lower('ad_&p_cod');

AD_VP
Kochhar	90	204000
De Haan	90	204000

--17
17.	Sa se afiseze numele, codul departamentului si salariul anual pentru toti 
angajatii care au fost angajati dupa o anumita data calendaristica. 

10-feb-1999


ACCEPT p_cod PROMPT "Dati data";
select e.last_name, d.department_name, e.salary*12, hire_date
from employees e, departments d
where e.department_id = d.department_id
and e.hire_date >= to_date ('&p_cod');


define p_cod;
ACCEPT p_cod PROMT "hire_date= ";
SELECT employee_id, last_name, salary*12, department_id, job_id, hire_date
from employees
where LOWER(TO_CHAR(hire_date)) > LOWER(TO_CHAR(TO_DATE('&p_cod')));--sir de caractere

define p_cod;
10-feb-2000
Markle	Shipping	26400	08-MAR-00
Kumar	Sales	73200	21-APR-00
Banda	Sales	74400	21-APR-00
Ande	Sales	76800	24-MAR-00
Lee	Sales	81600	23-FEB-00

--18.	Sa se afiseze o coloana aleasa de utilizator, dintr-un tabel ales de
--utilizator, ordonand dupa aceeasi coloana care se afiseaza. De asemenea,
--este obligatorie precizarea unei conditii WHERE.

SELECT   &&p_coloana  -- && determina ca valoarea lui p_coloana san nu mai
--fie ceruta si pentru clauza ORDER BY, urmand sa 
--fie utilizata valoarea introdusa aici pentru toate 
--aparitiile ulterioare ale lui &p_coloana
FROM     &p_tabel
WHERE    &p_where
ORDER BY &p_coloana;


undefine p_coloana;
define;

SELECT   &p_coloana, department_id 
FROM     &p_tabel
WHERE    &p_where
ORDER BY &p_coloana;

select &col as coloana 
from &tabel
where &cond
order by coloana;


--19.	Sa se afiseze numele angajatului, codul job-ului, salariul si numele 
--departamentului pentru salariatii care lucreaza intr-o locatie(oras) 
--data de utilizator. Va fi permisa cautarea case-insensitive. 

ACCEPT c_city prompt "dati orasul = ";
select e.employee_id, e.last_name, e.job_id, e.salary, d.department_name
from employees e, locations l, departments d
where l.location_id = d.location_id
and d.department_id = e.department_id
and lower(l.city) = lower( '&c_city');

--34 rezultate Oxford



--20.	S? se afi?eze numele, job-ul ?i data angaj?rii salaria?ilor care
--au început lucrul între 2 date calendaristice introduse de utilizator. 
--S? se concateneze numele ?i job-ul, separate prin spa?iu ?i virgul?, ?i s? se 
--eticheteze coloana "Angajati". Se vor folosi comanda ACCEPT ?i formatul pentru
--data calendaristica MM/DD/YY. 


ACCEPT data_inceput PROMPT "Introduceti data de inceput ";
ACCEPT  data_sfarsit PROMPT "Introduceti data de sfarsit ";
SELECT first_name || ' ' ||last_name|| ' , ' ||job_id Angajati, hire_date
FROM employees
WHERE hire_date BETWEEN TO_DATE('&data_inceput', 'mm/dd/yy') 
                    AND TO_DATE('&data_sfarsit', 'mm/dd/yy');
                 
select last_name, department_id, salary*12
from employees
where hire_date>=to_date('&p_cod');              
     */            
 
 
 
 ---recapitulare:
 ---pe cate proiecte lucreaza fiecare angajat(din cei care lucreaza pe proiecte)
 
 select employee_id, count(project_id)
 from works_on
 group by employee_id;--10 rez
 
select e.employee_id, count(w.project_id)
 from works_on w, employees e
 where w.employee_id= e.employee_id
 group by e.employee_id;--10 rez
 
select e.last_name, count(w.project_id)
 from works_on w, employees e
 where w.employee_id= e.employee_id
 group by e.last_name, e.employee_id;--10 rez  (tin cont ca pot exista 2 ang cu
                                    --acelasi last_name, deci este nevoie
                                    -- sa grupez si dupa employee_id)
 
  
 ---pe cate proiecte lucreaza fiecare angajat(pt toti angajatii din firma)
 select e.employee_id, count(w.project_id)
 from works_on w, employees e
 where w.employee_id(+)= e.employee_id
 group by e.employee_id
 order by 2,1;--107 rez
 
 select e.employee_id, (Select count(*) 
                        from works_on
                        where employee_id = e.employee_id) nr_proiecte
 from employees e
 order by nr_proiecte, 1;
 
---atentie:
 ---pe cate proiecte lucreaza fiecare angajat(pt toti angajatii din firma)
 select e.employee_id, count(*)
 from works_on w, employees e
 where w.employee_id(+)= e.employee_id
 group by e.employee_id
 order by 2,1;--107 rez
 
 
 --dintre cei care lucreaza pe proiecte, afisati angajatii care lucreaza 
 --pe cele mai multe proiecte


--p1: -nr maxim de poiecte pe care lucreaza angajatii
 select max(count(project_id))
 from works_on
 group by employee_id;

--rezolvare: 
 select employee_id, count(project_id)
 from works_on
 group by employee_id
 having count(project_id) = (  select max(count(project_id))
                                 from works_on
                                 group by employee_id);
 --101	3                                
                                 
 ---afisam si orasul in care lucreaza folosind subcerere corelata
 
  select employee_id, count(project_id), (select city 
                                        from employees e, departments d, locations l
                                        where e.employee_id= w.employee_id
                                        and e.department_id = d.department_id
                                        and d.location_id = l.location_id) oras
 from works_on w
 group by employee_id
 having count(project_id) = (  select max(count(project_id))
                                 from works_on
                                 group by employee_id);  -- doar daca un ang lucreaza intr-un singur oras



---functioneaza si daca angajatul lucreaza in mai multe locatii
with aux as ( select employee_id, count(project_id)
             from works_on
             group by employee_id
             having count(project_id) = (  select max(count(project_id))
                                             from works_on
                                             group by employee_id))
select aux.employee_id, city
from employees e, departments d, locations l, aux 
where e.employee_id= aux.employee_id
and e.department_id = d.department_id
and d.location_id = l.location_id;
                                             