--seful firmei =angajatii care nu au manager
select first_name, last_name
from employees
where manager_id is null; --Steven	King

--angajatii care nu au departament
select first_name
from employees
where department_id is null; --Kimberely


select first_name
from employees
where department_id = null; --nu este corect

--departamentele care nu au manager
select department_id, department_name
from departments
where manager_id is null; --16 rez

-------Functii de conversie
select to_date('26/02/2022', 'DD/MM/YYYY')
from dual; --26-FEB-22

select to_date('26/02/2022', 'DD/MON/YYYY')
from dual; --nu  --ORA-01843: not a valid month

select to_char(to_date('26/MAR/22', 'DD/MON/YY'), 'YYYY')
from dual; --2022

select substr('primavara', 4)
from dual; --mavara

select substr('primavara', 4, 1)
from dual; --m

select substr('primavara', 4, 2)
from dual; --ma

select substr('primavara', 1, 4)
from dual; --prim

select substr('primavara',-4)
from dual; --vara

select substr('primavara',length('primavara'))
from dual; --a

select substr('primavara',length('primavara')-3)
from dual; --vara
select substr('primavara',length('primavara')-3,4)
from dual; --vara

select rtrim('XXXprimavaraXXXX', 'X')
from dual; -- XXXprimavara

select rtrim('XXXprimavarXaXXXX', 'X')
from dual; -- XXXprimavarXa

select ltrim('XXXprimavarXaXXXX', 'X')
from dual; -- primavarXaXXXX

select trim( both 'X'  from 'XXXprimavarXaXXXX')
from dual; -- primavarXa

select rtrim('XXXprimavarXaXXXaXa', 'Xa')
from dual; -- XXXprimavar

select rtrim('XXXprimavarXaXbXXaXa', 'Xa')
from dual; -- XXXprimavarXaXb


select length('XXXprimavarXaXXXX       ')
from dual; --24
select length(rtrim('XXXprimavarXaXXXX       '))
from dual; -- XXXprimavarXaXXXX  --17

select (rtrim('XXXprimavarXaXXXX       '))
from dual; --XXXprimavarXaXXXX

select 'XXXprimavarXaXXXX       '
from dual;


select replace('XXXprimXavarXaXXXX', 'X')
from dual; -- primavara

select replace('XXXprimavarXaXXXX', 'X', '*')
from dual; -- ***primavar*a****

select replace('1212131', '12')
from dual; --131

select replace('1212131', '12', 'ab')
from dual; --abab131
select replace('1212131', '12', 'abc')
from dual; --abcabc131

select translate('1212131', '12', 'ab')
from dual; --ababa3a

select translate('1212131', '123', 'ab')
from dual; --ababaa

select translate('1212131', '123','abc')
from dual; --ababaca

select translate('1212131', '123','abcd')
from dual; --ababaca

select translate('141234123444444123', '1234','abcd')
from dual; --adabcdabcddddddabc

select replace('141234123444444123', '1234','abcd')
from dual; --14abcdabcd44444123

select replace('141234123444444123', '1234',10101)  --10101   '10101'
from dual; --14101011010144444123 --conversie implicita

select translate('141234123444444123', '1234',99998)
from dual; -- 999999999999999999 -ignora 8


select translate('141234123444444123', '1234',9)
from dual; -- 9999
select translate('141234123444444123', '123',9)
from dual; -- 949494444449
select replace('141234123444444123', '1234')
from dual; -- 1444444123

III. [Exerci?ii]
[Func?ii pe ?iruri de caractere]
1. Scrie?i o cerere care are urm?torul rezultat pentru fiecare angajat: 
<prenume angajat> <nume angajat> castiga <salariu> lunar 
dar doreste <salariu de 3 ori mai mare>.
Etichetati coloana “Salariu ideal”. Pentru concatenare, utiliza?i atât 
func?ia CONCAT cât ?i operatorul “||”.

SELECT CONCAT(CONCAt(first_name, ' '), last_name) ||' castiga '|| salary
 || ' lunar dar doreste ' || salary*3 ||'.' "Salariu ideal"
FROM employees;

2. Scrie?i o cerere prin care s? se afi?eze prenumele salariatului cu prima 
litera majuscul? ?i toate celelalte litere minuscule, numele acestuia cu
majuscule ?i lungimea numelui, 
pentru angaja?ii al c?ror nume începe cu J sau M sau care au a treia liter? din nume A. 
Rezultatul va fi ordonat descresc?tor dup? lungimea numelui. Se vor eticheta 
coloanele corespunz?tor. Se cer 2 solu?ii (cu operatorul LIKE ?i func?ia SUBSTR).

select initcap(first_name), upper(last_name), length(last_name)
from employees
where upper(last_name) like 'J%' or upper(last_name) like 'M%' 
or upper(last_name) like '__A%'
order by length(last_name) desc; --15 rez

select initcap(first_name), upper(last_name), length(last_name) 
from employees 
where substr(upper(last_name),1,1)='J' or substr(upper(last_name),1,1)='M' 
or substr(upper(last_name),3,1)='A' 
order by length(last_name) desc; --15 rez

select initcap(first_name), upper(last_name), length(last_name) 
from employees 
where substr(upper(last_name),1,1) IN ('J','M') or substr(upper(last_name),3,1)='A' 
order by length(last_name) desc; --15 rez


3. S? se afi?eze, pentru angaja?ii cu prenumele „Steven”, codul ?i numele acestora, 
precum ?i codul departamentului în care lucreaz?. C?utarea trebuie s? nu fie 
casesensitive, iar eventualele blank-uri care preced sau urmeaz? numelui trebuie ignorate.

select employee_id, last_name, first_name, department_id
from employees 
where trim(both ' ' from lower(first_name)) = 'steven';

100	King	Steven	90
128	Markle	Steven	50

4. S? se afi?eze pentru to?i angaja?ii al c?ror nume se termin? cu litera 'e', codul, numele, 
lungimea numelui ?i pozi?ia din nume în care apare prima data litera 'a'.
Utiliza?i aliasuri corespunz?toare pentru coloane. 



select employee_id, last_name, first_name, length(last_name) lungime, instr(lower(last_name),'a')
from employees
where lower(last_name) like '%e'
order by lungime; --5 rez

select employee_id, last_name, first_name, length(last_name),  instr(lower(last_name),'a')
from employees
where substr(lower(last_name),-1) = 'e'; --5 rez

select employee_id, last_name, first_name, length(last_name),  instr(lower(last_name),'a')
from employees
where substr(lower(last_name),length(last_name)) = 'e'; --5 rez

select employee_id, last_name, first_name, length(last_name),  instr(lower(last_name),'a')
from employees
where substr(lower(last_name),length(last_name),1) = 'e'; --5 rez


--Functii pt date calendaristice
alter session set nls_language=American;

select next_day(sysdate, 'Monday')
from dual;  --06-MAR-23

select next_day('07/MAR/2023', 'Monday') --conversie implicita de la string la date
from dual;  --13-MAR-23


select next_day('08/MAR/2022', 'Monday')
from dual;  --14-MAR-22

select next_day('07/MAR/2022', 'Monday')
from dual;  --14-MAR-22

select Last_day('01-FEB-2022') --conversie implicita de la string la date
from dual; --28-FEB-22

select Last_day(sysdate)
from dual; --31-MAR-22

select Last_day('11-FEB-2024')
from dual; --29-FEB-24

select TO_CHAR(SYSDATE, 'dd/mm/yy HH24:MI') 
from dual; --28/02/23 19:04

select TRUNC(SYSDATE)
from dual; --02-MAR-22

select TO_CHAR(TRUNC(SYSDATE), 'dd/mm/yy HH24:MI') 
from dual; --02/03/22 00:00




[Func?ii aritmetice]
5. S? se afi?eze detalii despre salaria?ii care au lucrat un num?r întreg de s?pt?mâni 
pân? la data curent?. 
Obs: Solu?ia necesit? rotunjirea diferen?ei celor dou? date calendaristice. De ce este 
necesar acest lucru?

select  employee_id, sysdate-hire_date
from employees
order by 1;
--28.02.2023 ora 19
100	13040.7968287037037037037037037037037037
101	12213.7968287037037037037037037037037037
102	11003.7968287037037037037037037037037037

--01.03.2023 ora 11
100	13041.4641435185185185185185185185185185
101	12214.4641435185185185185185185185185185
102	11004.4641435185185185185185185185185185

--01.03.2023 ora 12:43
100	13041.5278819444444444444444444444444444
101	12214.5278819444444444444444444444444444
102	11004.5278819444444444444444444444444444
--
100	13042,3899537037037037037037037037037037
101	12215,3899537037037037037037037037037037
102	11005,3899537037037037037037037037037037

100	13042,4652083333333333333333333333333333
101	12215,4652083333333333333333333333333333
102	11005,4652083333333333333333333333333333

select employee_id, trunc(sysdate) - trunc(hire_date)
from employees
order by 1;
-2022
100	12677
101	11850
102	10640

--2023
100	13041
101	12214
102	11004

select employee_id, trunc(sysdate) - trunc(hire_date) nr_zile
from employees
where mod(trunc(sysdate) - trunc(hire_date),7) =0; --21 rez --miercuri 02.03.2022
--17 rez  - joi 03.03.2022



select employee_id, trunc(sysdate) - trunc(hire_date) nr_zile
from employees
where mod(nr_zile,7) =0; 

-- nu cunoaste cn este acest alias pt ca nu a ajuns la caluza de select


--6. S? se afi?eze codul salariatului, numele, salariul, salariul m?rit cu 15%, exprimat cu 
--dou? zecimale ?i num?rul de sute al salariului nou rotunjit la 2 zecimale. Eticheta?i 
--ultimele dou? coloane “Salariu nou”, respectiv “Numar sute”. Se vor lua în considerare 
--salaria?ii al c?ror salariu nu este divizibil cu 1000.
--
--\
--Select employee_id, last_name, salary, salary*1.15 --, ceil(salary*1.15)
--from employees
--where mod(salary,1000) !=0;
--
--7. S? se listeze numele ?i data angaj?rii salaria?ilor care câ?tig? comision. S? se 
--eticheteze coloanele „Nume angajat”, „Data angajarii”. Utiliza?i func?ia RPAD pentru a 
--determina ca data angaj?rii s? aib? lungimea de 20 de caractere.

--functii diverse

select nvl(null, 1)
from dual; --1

select nvl(20, 1) --20 =/ null
from dual; -- 20


select nvl('a', 1)  --conversi implicita a lui 1 la '1'
from dual; --a

select nvl('', 1)  --conversi implicita a lui 1 la '1'
from dual; --1

select nvl(null, 1) 
from dual; --1 (number)

select nvl(1, 'ab')
from dual; --ORA-01722: invalid number

select nvl(1, '2')  --'2' poate fi covertit la number 2
from dual;--1 

select nvl(1, '2a')
from dual;--ORA-01722: invalid number


select nvl(1.50, 10.50)
from dual; --1,5  --> tip number

select nvl('1.50', '10.50')
from dual; --1.50   --> string

select nvl(1, 'a') --> nvl(number, string)
from dual; -- vrea sa converteasca 'a' la number -->eroare

select  nvl(to_char(1.50000), 'a') --> nvl( string, string); 1.50  este number
from dual; -- 1,5

--NVL2(exp1, exp2_daca_nu_este_null_exp1, exp3_Altfel)

select NVL2( 1, 20, 30) -- 1/= null
from dual; --20

select nvl(1,30) -- 1/= null
from dual;  --1

select NVL2( null, 20, 30)
from dual; --30

--obs:
select nvl(20, 1) --20 =/ null
from dual; -- 20

select nvl2(20,20, 1) --20 =/ null
from dual; --20



select employee_id, first_name, last_name,
    nvl(manager_id,  0), manager_id
from employees
order by 4;

NVL2(exp1, exp2_daca_nu_este_null_exp1, exp3_Altfel)

Pt toti salariatii afisati daca au manager sau nu folosind functia nvl2 
Afisati 1 pt cei care au manager si 0 pt cei care nu au manager.

select employee_id, first_name, last_name,
    nvl2(manager_id, 1, 0), manager_id
from employees
order by 4;

select employee_id, first_name, last_name, 
        nvl2(manager_id, 'are manager', 'nu are manager'), manager_id
from employees
order by 4;

--folositi nvl pt a afisa id-ul manager-ului,
--iar in caz contrat scrieti :nu are manager

select employee_id, first_name, last_name, 
        nvl(manager_id, 'nu are manager'), manager_id
from employees
order by 4; --ORA-01722: invalid number

select employee_id, first_name, last_name, 
        nvl(to_char(manager_id), 'nu are manager') manager, manager_id
from employees
order by 4 desc; 

179	Charles	Johnson	149	149
202	Pat	Fay	        201	201
206	William	Gietz	205	205
100	Steven	King	nu are manager	


select employee_id, first_name, last_name, 
        nvl2(manager_id, manager_id,'nu are manager') manager, manager_id
from employees
order by 4;  --ORA-01722: invalid number
--manager_id -- number

select employee_id, first_name, last_name, 
        nvl2(manager_id, to_char(manager_id),'nu are manager') manager, manager_id
from employees
order by 4; 

select employee_id, first_name, last_name, 
        nvl2(manager_id,'are manager',0) manager, manager_id
from employees
order by 4;  ---conversie implicita din sumber 0 la string '0'

[Func?ii ?i opera?ii cu date calendaristice]
8. S? se afi?eze data (numele lunii, ziua, anul, ora, minutul si secunda) de peste 30 zile.

select  to_char(sysdate, 'Month,Day, DD_MM_YYYY HH24:MI:SS') AZI,
        to_char(sysdate+30, 'Month,Day, DD_MM_YYYY HH24:MI:SS') "Peste 30 de zile"
from dual;  

March    ,Wednesday, 02_03_2022 13:35:49	April    ,Friday   , 01_04_2022 13:35:49
March    ,Wednesday, 01_03_2023 09:27:00	March    ,Friday   , 31_03_2023 09:27:00


9. Sã se afiºeze numãrul de zile rãmase pânã la sfârºitul anului.

Select to_date('31-DEC-2023') - trunc(sysdate), to_char(sysdate, 'dd-mm-yyyy HH24:MI')
from dual; 
--304	02-03-2022 13:37
--303	03-03-2022 15:38

Select to_date('31-DEC-'||to_char(sysdate, 'YYYY')) - trunc(sysdate), to_char(sysdate, 'dd-mm-yyyy HH24:MI')
from dual; --305	01-03-2023 13:17

Select round( to_date('31-DEC-2022') - (sysdate),2), to_char(sysdate, 'dd-mm-yyyy HH24:MI')
from dual; 
--303.43	02-03-2022 13:39
--303.35	02-03-2022 15:41

select to_char(sysdate, 'DDD')
from dual; --60

Select to_date('31-DEC-2021') - trunc(sysdate)
from dual;

select 365 - to_char(sysdate, 'DDD') "zile ramase" , to_char(sysdate, 'DDD') "ziua din an"--31+28+1
from dual; -- 305
--31(ian)+28(feb)+1(mar) = 60
--365-60

Select to_char(to_date('31-DEC-'||to_char(sysdate, 'YYYY')), 'DDD') - to_char(sysdate, 'DDD') "zile ramase" ,
    to_char(to_date('31-DEC-'||to_char(sysdate, 'YYYY')), 'DDD')  "ultima zi din an" 
    --(conversie automata de la stringul '365' la numarul 365)
from dual; --305	365

select  to_char(to_date('31-DEC-2022'),'DDD') - to_char(sysdate, 'DDD') "zile ramase" ,
        to_char(sysdate, 'DDD') "ziua din an", --
        to_char(to_date('31-DEC-2021'),'DDD') "ultima zi din an"
from dual;  --304	061	365


select  to_char(Last_day('01-DEC-2022'),'DDD') - to_char(sysdate, 'DDD') "zile ramase" ,
        to_char(sysdate, 'DDD') "ziua din an", 
        to_char(to_date('31-DEC-2021'),'DDD') "ultima zi din an"
from dual;  --304	061	365

select  to_char(Last_day('01-DEC-2022'),'DDD')         
from dual;  --365


select  to_char(Last_day('01-DEC-2024'),'DDD')         
from dual;  --366


select  to_char(Last_day('01-DEC-'||to_char(sysdate, 'YYYY')),'DDD') 
from dual; --365

select  to_char(Last_day (to_date('01-DEC-'||to_char(sysdate, 'YYYY'))),'DDD')  
            -to_char(sysdate, 'DDD')
from dual; --303

10. a) S? se afi?eze data si ora de peste 12 ore.


select to_char(sysdate+1/2, 'dd-mm-yyyy hh24:mi:ss'),  to_char(sysdate, 'dd-mm-yyyy hh24:mi:ss')
from dual; --04-03-2022 03:43:19	03-03-2022 15:43:19

b) S? se afi?eze data de peste 5 minute
Obs: Cât reprezint? 5 minute dintr-o zi?

--10. b
select to_char(sysdate+1/24/60*5, 'dd-mm-yyyy hh24:mi:ss')
from dual;

select to_char(sysdate+5/(24*60), 'dd-mm-yyyy hh24:mi:ss'), to_char(sysdate, 'dd-mm-yyyy hh24:mi:ss')
from dual; 03-03-2022 15:50:32	03-03-2022 15:45:32





select to_char(sysdate, 'YYYY')

select  to_char(to_date('31-DEC-'|| to_char(sysdate,'YYYY')),'DDD') - to_char(sysdate, 'DDD') "zile ramase" ,
        to_char(sysdate, 'DDD') "ziua din an", --31+28+10
        to_char(to_date('31-DEC-'|| to_char(sysdate,'YYYY')),'DDD') "ultima zi din an",
        to_date('31-DEC-'|| to_char(sysdate,'YYYY')) "Data ultimei zile din an"
from dual; --296
--295	070	365	31-12-2021

--data_calendaristica + nr_de_zile => noua data calendaristica



[Funcþii diverse]


--14. S? se afi?eze numele angaja?ilor ?i comisionul. Dac? un angajat nu câ?tig? comision, 
--s? se scrie “Fara comision”. Eticheta?i coloana “Comision”.

select last_name, nvl(commission_pct,'Fara comision') --ORA-01722: invalid number
from employees;

select last_name, nvl(commission_pct,0) 
from employees; --107 rez

--corect
select last_name, nvl(to_char(commission_pct),'Fara comision') 
from employees; --107 rez 

select last_name, nvl2(to_char(commission_pct), '0'||to_char(commission_pct),'Fara comision') 
from employees; --107 rez

select last_name, nvl2(commission_pct, '0'||to_char(commission_pct),'Fara comision') 
from employees; --107 rez


select last_name, nvl2(commission_pct, '0'||commission_pct,'Fara comision') 
from employees; --107 rez  --conversie implicita a lui commission_pct din number la string


select last_name || ' ' || first_name nume,nvl(to_char(commission_pct,'0.9999'),'Fara comision') comision
from employees;

select 1 + null, 2 * null
from dual; --null, null

15. S? se listeze numele, salariul ,
  commission_pct , valoare calculata a comisionului 
  si venitul lunar pt
 toti angajatii al c?ror venit lunar 
(salariu + valoare comision) dep??e?te 10000. 

;
---gresit, atentie la cei care au comision null
select last_name, salary, commission_pct, salary*COMMISSION_PCT +salary
from employees
where salary+salary*COMMISSION_PCT > 10000; --21 rez


--corect
select last_name, salary, commission_pct, 
        salary*COMMISSION_PCT +salary GRESIT,
        salary+salary*nvl(COMMISSION_PCT,0) CORECT
from employees
where salary+salary*nvl(COMMISSION_PCT,0) > 10000
order by employee_id; --28 rez

select last_name, salary, commission_pct 
from employees
where nvl(salary+salary*COMMISSION_PCT,salary) > 10000
order by employee_id; --28 rez

select 1+null
from dual;

select 10*null
from dual;

--------------------final s2



select decode('b', 'a', 'bbbbbb') 
from dual;
 --null (lipseste else)

select decode('b', 'a', 'bbbbbb', 'c')  --c
from dual;

select decode('b', 'a', 'bbbbbb', 'c', 'ddd') --null (lipseste else)
from dual;


select decode('b', 'a', 'bbbbbb', 'c', 'ddd', 'bjhafkas') --are ramura de else
from dual; --bjhafkas

[Instrucþiunea CASE, comanda DECODE]

16. Sã se afiºeze numele, codul job-ului, salariul ºi
o coloanã care sã arate salariul dupã mãrire.
Se presupune cã pentru IT_PROG are loc o mãrire de 20%,
pentru SA_REP creºterea este de 25%, 
iar pentru SA_MAN are loc o mãrire de 35%. 
Pentru ceilalþi angajaþi nu se acordã mãrire. 
Sã se denumeascã coloana "Salariu renegociat".


SELECT last_name, job_id, salary, 
        Case upper(job_id)
        WHEN 'IT_PROG' THEN salary* 1.2
        WHEN 'SA_REP' THEN salary*1.25
        WHEN 'SA_MAN' THEN salary*1.35
        ELSE salary
        end 
        AS "Salariu renegociat"
FROM employees; ---107 rez

--nu
SELECT last_name, job_id, salary, 
        Case upper(job_id)
        WHEN 'IT_PROG' THEN salary* 1.2
        WHEN 'SA_REP' THEN salary*1.25
        WHEN 'SA_MAN' THEN salary*1.35
       -- ELSE salary
        end 
        AS "Salariu renegociat"
FROM employees; ---107 rez  dar cu null pe "Salariu renegociat"


--corect  -case
SELECT last_name, job_id, salary, 
        Case 
        WHEN upper(job_id)='IT_PROG' THEN salary* 1.2
        WHEN upper(job_id)='SA_REP' THEN salary*1.25
        WHEN upper(job_id)='SA_MAN' THEN salary*1.35
        ELSE salary
        end 
        AS "Salariu renegociat"
FROM employees;


--corect - decode
SELECT last_name, job_id, salary, 
        decode (upper(job_id),
        'IT_PROG', salary*1.2,
        'SA_REP', salary*1.25,
        'SA_MAN', salary*1.35,
        salary)
        AS "Salariu renegociat"
FROM employees;

--Matos	ST_CLERK	2600	2600
--Vargas	ST_CLERK	2500	2500
--Russell	SA_MAN	14000	18900
--Partners	SA_MAN	13500	18225


SELECT last_name, job_id, salary, 
        salary * decode (upper(job_id),
                                    'IT_PROG', 1.2,
                                    'SA_REP', 1.25,
                                    'SA_MAN',1.35,
                                    1)
        AS "Salariu renegociat"
FROM employees;


--daca facem si ordonare 
--v1
SELECT last_name, job_id, salary, 
        decode (upper(job_id),
        'IT_PROG', salary*1.2,
        'SA_REP', salary*1.25,
        'SA_MAN', salary*1.35,
        salary)
        AS "Salariu renegociat"
FROM employees
order by 4;
--v2
SELECT last_name, job_id, salary, 
        decode (upper(job_id),
        'IT_PROG', salary*1.2,
        'SA_REP', salary*1.25,
        'SA_MAN', salary*1.35,
        salary)
        AS "Salariu renegociat"
FROM employees
order by "Salariu renegociat";
--v3

SELECT last_name, job_id, salary, 
        decode (upper(job_id),
        'IT_PROG', salary*1.2,
        'SA_REP', salary*1.25,
        'SA_MAN', salary*1.35,
        salary)
        AS "Salariu renegociat"
FROM employees
order by decode (upper(job_id),
        'IT_PROG', salary*1.2,
        'SA_REP', salary*1.25,
        'SA_MAN', salary*1.35,
        salary);
        
[Join]

--Sa se obtina lista tuturor posibilitatilor de amplasare a departamentelor firmei  in orase.
select department_id,  city
from departments, locations;  --cross join --621 rez


--In ce oras este amplasat fiecare departament.
select department_id, city
from departments, locations
where departments.location_id = locations.location_id; --27 rez

select departments.department_id, locations.city
from departments, locations
where departments.location_id = locations.location_id; --27 rez


--folosim alias-uri pt tabele
select department_id, city
from departments d, locations l
where d.location_id = l.location_id; --27 rez

select department_id, city
from departments d join locations l 
on  d.location_id = l.location_id; --27 rez

--vrem sa afisam si location_id
select department_id,  location_id , city
from departments d, locations l
where d.location_id = l.location_id; --ORA-00918: column ambiguously defined


select department_id, city, d.location_id "din dept", l.location_id "din locations"
from departments d, locations l
where d.location_id = l.location_id; --27 rez


17. Sã se afiºeze numele salariatului, 
codul ºi numele departamentului pentru toþi angajaþii.
(care lucreaza in departamente).
;
SELECT last_name, employees.department_id, departments.department_name
FROM employees, departments
WHERE employees.department_id=departments.department_id; --join-ul dintre cele 2 tabele
--106 rez
sau

SELECT last_name, e.department_id, d.department_name
FROM employees e, departments d
WHERE e.department_id=d.department_id; --corect
--106 rez

SELECT last_name, employees.department_id, d.department_name
FROM employees e, departments d
WHERE e.department_id=d.department_id; --ORA-00904: "EMPLOYEES"."DEPARTMENT_ID": invalid identifier


select *
from employees
where department_id is null;
--178	Kimberely	Grant	KGRANT	011.44.1644.429263	24-MAY-99	SA_REP	7000	0.15	149	 null

SELECT e.last_name, e.department_id, e.department_name
FROM employees e, departments d
WHERE e.department_id=d.department_id; --incorect
--ORA-00904: "E"."DEPARTMENT_NAME": invalid identifier


Obs: Am realizat operaþia de join între tabelele employees ºi departments, 
pe baza coloanei comune department_id. 
Observaþi utilizarea alias-urilor. Ce se întâmplã dacã eliminãm condiþia de join?
Obs: Numele sau alias-urile tabelelor sunt obligatorii în dreptul coloanelor care 
au acelaºi nume în mai multe tabele. Altfel, nu sunt necesare dar este
recomandatã utilizarea lor pentru o mai bunã claritate a cererii.

SELECT e.*, d.* --afisam toate coloanele din employees si din departments
FROM employees e, departments d
WHERE e.department_id=d.department_id;

SELECT *--afisam toate coloanele din employees si din departments
FROM employees e, departments d
WHERE e.department_id=d.department_id;


SELECT last_name, department_id, d.department_name
FROM employees e, departments d
WHERE e.department_id=d.department_id; --department_id este coloana definita ambiguu


SELECT last_name, e.department_id Id_dep_din_EMP,
d.department_id ID_DEPT_DIN_DEPARTMENTS, d.department_name
FROM employees e, departments d
WHERE e.department_id=d.department_id;


SELECT employee_id,last_name, e.department_id Id_dep_din_EMP,d.department_id ID_DEPT_DIN_DEPARTMENTS, d.department_name, 
    e.manager_id "Mng_direct_al_ang",
    d.manager_id "Mng dept _in_care_lucreaza_ang"
FROM employees e, departments d
WHERE e.department_id=d.department_id
order by 3; --106

--Lorentz	60	60	IT	103	103
--Greenberg	100	100	Finance	101	108
--Faviet	100	100	Finance	108	108


--afisati id-ul managerului direct al fiecarui angajat.

SELECT employee_id,last_name, e.department_id Id_dep_din_EMP,d.department_id ID_DEPT_DIN_DEPARTMENTS, d.department_name, 
    e.manager_id "Mng_direct_al_ang"
FROM employees e, departments d
WHERE e.department_id=d.department_id
order by 3; --106

--afisati id-ul managerului de departament in care lucreaza fiecare angajat.

SELECT employee_id,last_name, e.department_id Id_dep_din_EMP,d.department_id ID_DEPT_DIN_DEPARTMENTS, d.department_name, 
    d.manager_id "Mng dept _in_care_lucreaza_ang"
FROM employees e, departments d
WHERE e.department_id=d.department_id
order by 3; --106

18. S? se listeze codurile ?i denumirile job-urilor care exist? în departamentul 30.
(in clauza where putem testa si alte conditii, pe langa conditia de  join)

;
select e.employee_id, e.job_id, j.job_id, j.job_title
from jobs j, employees e
where  e.department_id=30
order by employee_id;
;
--afisam job-ul pe are lucreaza fiecare angajat
select j.job_id, j.job_title
from jobs j, employees e
where j.job_id = e.job_id
order by employee_id; --107 rez --avem duplicate


--lista cu toate job-urile pe care lucreaza salariatii
select distinct j.job_id, j.job_title
from jobs j, employees e
where j.job_id = e.job_id; --19 rez

--R:  S? se listeze codurile ?i denumirile job-urilor care exist? în departamentul 30.
--(in clauza where putem testa si alte conditii, pe langa conditia de  join)

select distinct j.job_id, j.job_title
from jobs j, employees e
where j.job_id = e.job_id
and e.department_id =30; --2 rez
--PU_MAN	Purchasing Manager
--PU_CLERK	Purchasing Clerk


--21. S? se	afi?eze	numele ,	job-ul (id),	
-- codul	?i	numele	departamentului 
--pentru to?i angaja?ii care lucreaz? în Oxford.

SELECT	e.last_name, e.job_id, d.department_id, d.department_name
FROM EMPLOYEES e, DEPARTMENTS d, LOCATIONS l
WHERE	e.department_id=d.department_id  
AND d.location_id= l.location_id
AND initcap(l.city)='Oxford'; --34 rez


SELECT	e.last_name, e.job_id, d.department_id, d.department_name
FROM (EMPLOYEES e join DEPARTMENTS d 
        on e.department_id=d.department_id )
                                            join LOCATIONS l
                                                on d.location_id= l.location_id
where initcap(l.city)='Oxford'; --34 rez

--nuuuu
SELECT	e.last_name, e.job_id, d.department_id, d.department_name
FROM (LOCATIONS l join DEPARTMENTS d 
        on e.department_id=d.department_id )
                                            join EMPLOYEES e
                                                on d.location_id= l.location_id
where initcap(l.city)='Oxford'; 



--21'. S?	se	afi?eze	numele,	job-ul (id-ul si titlul),	codul	?i	numele	departamentului 
--pentru to?i angaja?ii care lucreaz? în Oxford.
SELECT	e.last_name, e.job_id, d.department_id, d.department_name
FROM jobs j, EMPLOYEES e, DEPARTMENTS d, LOCATIONS l
WHERE	e.department_id=d.department_id  
AND d.location_id= l.location_id
AND initcap(l.city)='Oxford'; --nu  --646 raspunsuri



19. S? se afi?eze numele angajatului, numele departamentului ?i ora?ul pentru to?i 
angaja?ii care câ?tig? comision.
20. S? se afi?eze numele salariatului ?i numele departamentului pentru to?i salaria?ii care 
au litera A inclus? în nume
Crea?i o cerere prin care s? se afi?eze numele angajatului,
codul  job-ului, titlul job-ului, numele departamentului ?i salariul  
angaja?ilor avand salariu sub 2500 $ sau care au fost angajati in  anul 1987.


SELECT e.last_name,j.job_id,j.job_title, d.department_name , salary
FROM JOBS j,EMPLOYEES e, DEPARTMENTS d
WHERE j.job_id=e.job_id
AND e.department_id=d.department_id  AND (e.salary<2500
OR to_char(e.hire_date,'YYYY')='1987');


