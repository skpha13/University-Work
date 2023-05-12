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
 