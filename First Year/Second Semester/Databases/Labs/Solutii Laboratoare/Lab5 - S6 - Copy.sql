 L5.pdf

IV. [Exerci?ii – definire tabele]
1. Sa se creeze tabelul ANGAJATI_*** (pnu se alcatuieste din prima litera din prenume 
si primele doua din numele studentului) corespunzator schemei relationale:
ANGAJATI_***(cod_ang number(4), nume varchar2(20), prenume varchar2(20), 
email char(15), data_ang date, job varchar2(10), cod_sef number(4), 
salariu number(8, 2), cod_dep number(2))
in urmatoarele moduri:
Se presupune ca valoarea implicita a coloanei data_ang este SYSDATE.
Observa?ie: Nu pot exista doua tabele cu acelasi nume in cadrul unei scheme,
deci recrearea unui tabel va fi precedata de suprimarea sa prin comanda:
DROP TABLE ANGAJATI_***;

a) fara precizarea vreunei chei sau constrangeri;

create table ANGAJATI_***(
  cod_ang number(4), 
  nume varchar2(20), 
  prenume varchar2(20), 
  email char(15), 
  data_ang date, 
  job varchar2(10), 
  cod_sef number(4), 
  salariu number(8, 2), 
  cod_dep number(2)); --table ANGAJATI_*** created.
  
  select * from angajati_***; --0 rez
  drop table angajati_***; --table ANGAJATI_*** dropped.
  
b) cu precizarea cheilor primare la nivel de coloana ?i a 
constrangerilor NOT NULL pentru coloanele nume si salariu;
Se presupune ca valoarea implicita a coloanei data_ang este SYSDATE.

create table ANGAJATI_***(
  cod_ang number(4) primary key, 
  nume varchar2(20) not null, 
  prenume varchar2(20), 
  email char(15), 
  data_ang date default sysdate, 
  job varchar2(10), 
  cod_sef number(4), 
  salariu number(8, 2) not null, 
  cod_dep number(2));
    
SELECT constraint_name, constraint_type, table_name
FROM     user_constraints
WHERE  lower(table_name) IN ('angajati_***');
--SYS_C00527493	C	ANGAJATI_***
--SYS_C00527492	C	ANGAJATI_***
--SYS_C00527494	P	ANGAJATI_***  
 drop table angajati_***;
--v2
create table ANGAJATI_***(
  cod_ang number(4) constraint pk_ang_*** primary key, 
  nume varchar2(20) constraint null_nume_*** not null, 
  prenume varchar2(20), 
  email char(15), 
  data_ang date default sysdate, 
  job varchar2(10), 
  cod_sef number(4), 
  salariu number(8, 2) not null, 
  cod_dep number(2));
  
--SYS_C00527502	C	ANGAJATI_*** --salariu
--NULL_NUME_***	C	ANGAJATI_*** --nume
--PK_ANG_***	P	ANGAJATI_***  ---cod_ang



c) cu precizarea cheii primare la nivel de tabel ?i 
a constrangerilor NOT NULL pentru coloanele nume si salariu.
Se presupune ca valoarea implicita a coloanei data_ang este SYSDATE.
;
  drop table angajati_***;

create table ANGAJATI_***(
  cod_ang number(4), 
  nume varchar2(20) constraint null_nume_*** not null, 
  prenume varchar2(20), 
  email char(15), 
  data_ang date default sysdate, 
  job varchar2(10), 
  cod_sef number(4), 
  salariu number(8, 2) constraint null_salariu_*** not null, 
  cod_dep number(2),
  constraint pk_ang_*** primary key(cod_ang)
  );
  
  select * from angajati_***;
  SELECT constraint_name, constraint_type, table_name
FROM     user_constraints
WHERE  lower(table_name) ='angajati_***';
  Observa?ie: Tipul constrangerilor este marcat prin:
• P – pentru cheie primara
• R – pentru constrangerea de integritate referentiala (cheie externa);
• U – pentru constrangerea de unicitate (UNIQUE);
• C – pentru constrangerile de tip CHECK.

--NULL_SALARIU_***	C	ANGAJATI_***
--NULL_NUME_***	C	ANGAJATI_***
--PK_ANG_***	P	ANGAJATI_***

2.	Adaugati urmatoarele inregistrari in tabelul ANGAJATI_***:

Cod_ang	Nume	Prenume	   Email	Data_ang	Job	        Cod_sef	Salariu	Cod_dep
    100	Nume1	Prenume1	Null	Null	    Director	null	20000	10
    101	Nume2	Prenume2	Nume2	02-02-2004	Inginer	    100	    10000	10
    102	Nume3	Prenume3	Nume3	05-06-2004	Analist	    101	    5000	20
    103	Nume4	Prenume4	Null	Null	    Inginer	    100	    9000	20
    104	Nume5	Prenume5	Nume5	Null	    Analist	    101	    3000	30
    
    
Prima si a patra inregistrare vor fi introduse specificand coloanele pentru care 
introduce?i date efectiv, iar celelalte vor fi inserate fara precizarea 
coloanelor in comanda INSERT.
Salva?i comenzile de inserare.

insert into angajati_***(Cod_ang,Nume,Prenume,Email,Data_ang,Job,Cod_sef,Salariu,Cod_dep)
values( 100	,'Nume1',	'Prenume1',	Null	,Null,	'Director',	null,	20000	,10);
select * from angajati_***;

insert into angajati_***
values (101, 'Nume2','Prenume2','Nume2@gmail.com',
        to_date('02-02-2004', 'dd-mm-yyyy'), 'Inginer',	100,10000,10);
        
insert into angajati_***
values (102, 'Nume3', 'Prenume3', 'Nume3@gmail.com', 
        to_date('05-06-2004', 'dd-mm-yyyy'), 'Programator', 101, 5000, 20);
--ORA-12899: value too large for column "GRUPA33"."ANGAJATI_***"."JOB" (actual: 11, maximum: 10)
-- job varchar2(10)

insert into angajati_***
values (102, 'Nume3', 'Prenume3', 'Nume3@gmail.com', 
        to_date('05-06-2004', 'dd-mm-yyyy'), 'Analist', 101, 5000, 20);

insert into angajati_*** (Cod_ang, Nume, Prenume, Job, Cod_sef, Salariu, Cod_dep)
values (103, 'Nume4', 'Prenume4', 'Inginer', 100, 9000, 20);
--atentie la data de angajare a lui 103 

insert into angajati_***
values (104, 'Nume5', 'Prenume5', 'Nume5@gmail.com', Null, 'Analist', 101, 3000, 30);

select * from angajati_***;
commit;

100	Nume1	Prenume1			                    Director    20000	10
101	Nume2	Prenume2	Nume2@gmail.com	02-FEB-04	Inginer	100	10000	10
102	Nume3	Prenume3	Nume3@gmail.com	05-JUN-04	Analist	101	5000	20
103	Nume4	Prenume4		            06-APR-22	Inginer	100	9000	20
104	Nume5	Prenume5	Nume5@gmail.com		        Analist	101	3000	30

100	Nume1	Prenume1			Director		20000	10
101	Nume2	Prenume2	Nume2@gmail.com	02-FEB-04	Inginer	100	10000	10
102	Nume3	Prenume3	Nume3@gmail.com	05-JUN-04	Analist	101	5000	20
103	Nume4	Prenume4		28-MAR-23	Inginer	100	9000	20
104	Nume5	Prenume5	Nume5@gmail.com		Analist	101	3000	30

truncate table angajati_***;
rollback;
select * from angajati_***;

delete from angajati_***;

3. Creati tabelul ANGAJATI10_***, prin copierea angajatilor din departamentul 10 
din tabelul ANGAJATI_***. Listati structura noului tabel. Ce se observa?

create table angajati10_*** as
  Select * from angajati_*** where cod_dep =10;
  
  select * from angajati10_***; --2 rez
  
  
SELECT constraint_name, constraint_type, table_name
FROM     user_constraints
WHERE  lower(table_name) IN ('angajati10_***');
--SYS_C00527544	C	ANGAJATI10_***
--SYS_C00527543	C	ANGAJATI10_***
--doar contrangerile de not null peste coloanele nume si salriu au fost copiate
desc angajati10_***;
Name     Null     Type         
-------- -------- ------------ 
COD_ANG           NUMBER(4)    --lipseste pk
NUME     NOT NULL VARCHAR2(20) 
PRENUME           VARCHAR2(20) 
EMAIL             CHAR(15)     
DATA_ANG          DATE         
JOB               VARCHAR2(10) 
COD_SEF           NUMBER(4)    
SALARIU  NOT NULL NUMBER(8,2)  
COD_DEP           NUMBER(2)    

desc angajati_***;

Name     Null     Type         
-------- -------- ------------ 
COD_ANG  NOT NULL NUMBER(4)    --este setata PK
NUME     NOT NULL VARCHAR2(20) 
PRENUME           VARCHAR2(20) 
EMAIL             CHAR(15)     
DATA_ANG          DATE         
JOB               VARCHAR2(10) 
COD_SEF           NUMBER(4)    
SALARIU  NOT NULL NUMBER(8,2)  
COD_DEP           NUMBER(2) 



4. Introduceti coloana comision in tabelul ANGAJATI_***. 
Coloana va avea tipul de date NUMBER(4,2).

alter table angajati_***
add (comision number(4,2));

select * from angajati_***;

5. Este posibila modificarea tipului coloanei comision in NUMBER(6,2)?
alter table angajati_***
modify (comision number(6,2));

--Table ANGAJATI_*** altered.

--apoi pot sa micsorez?
alter table angajati_***
modify (comision number(4,2));
--table ANGAJATI_*** altered. (toate infomatiiile din coloana comision sunt nule)

select * from angajati_***;
5" .	Este posibil? modificarea tipului coloanei salariu in NUMBER(6,2)?
-- SALARIU  NOT NULL NUMBER(8,2) 
alter table angajati_***
modify (salariu number(6,2));
-- SQL Error: ORA-01440: coloana de modificat trebuie sa fie goala pentru a micsora precizia sau scala

-- 6. Setati o valoare DEFAULT pentru coloana salariu.

alter table angajati_***
modify(salariu default 1111);

-- lipseste salariul 

insert into angajati_*** (Cod_ang, Nume, Prenume, Job, Cod_sef, Cod_dep) 
values (105, 'Nume6', 'Prenume6', 'Inginer', 100, 20);

insert into angajati_*** (Cod_ang, Nume, Prenume, Job, Cod_sef, Cod_dep, salariu)
values (106, 'Num76', 'Prenume76', 'Inginer', 100, 20, 2222);

select * from angajati_***;

-- 105	Nume6	Prenume6		06-APR-22	Inginer	100	1111	20	
-- 106	Num76	Prenume76		06-APR-22	Inginer	100	2222	20	

7. Modificati tipul coloanei comision in NUMBER(2, 2) si 
al coloanei salariu in NUMBER(10,2), 
in cadrul aceleiasi instructiuni.
desc angajati_***;

-- inainte
SALARIU  NOT NULL NUMBER(8,2)  
COD_DEP           NUMBER(2)    
COMISION          NUMBER(4,2)  

alter table angajati_***
modify ( salariu number(10,2),
          comision number(2,2)
          );

-- dupa: 
SALARIU  NOT NULL NUMBER(10,2) 
COD_DEP           NUMBER(2)    
COMISION          NUMBER(2,2)       
--
--update angajati_***
--set comision= null
--where lower(job)  like 'i%';

--8. Actualiza?i valoarea coloanei comision, setand-o la valoarea 0.1 pentru 
--salariatii al caror job incepe cu litera I. (UPDATE)
--select * from angajati_***;

update angajati_***
set comision=0.1
where lower(job)  like 'i%';

select * from angajati_***;

-- atentie

update angajati_***
set comision=1.1 
where lower(job)  like 'i%';
-- ORA-01438: value larger than specified precision allowed for this column

update angajati_***
set comision=0.129345 
where lower(job)  like 'i%';

-- 100	Nume1	Prenume1			                    Director	20000	10	
-- 101	Nume2	Prenume2	Nume2@gmail.com	02-FEB-04	Inginer	100	10000	10	0.13
-- 102	Nume3	Prenume3	Nume3@gmail.com	05-JUN-04	Analist	101	5000	20	
-- 103	Nume4	Prenume4		            06-APR-22	Inginer	100	9000	20	0.13
-- 104	Nume5	Prenume5	Nume5@gmail.com             Analist	101	3000	30	
-- 105	Nume6	Prenume6		            06-APR-22	Inginer	100	1111	20	0.13
-- 106	Num76	Prenume76		            06-APR-22	Inginer	100	2222	20	0.13

12. Redenumiti tabelul ANGAJATI_*** in ANGAJATI3_***.
rename angajati_*** to angajati3_***; 
-- angajati_*** TO succeeded.
select * from angajati_***; -- ORA-00942: tabelul sau vizualizarea nu exista
select * from angajati3_***; 
desc angajati3_***;

13. Consultati vizualizarea TAB din dictionarul datelor. Redenumiti angajati3_*** in angajati_***.
select * from tab;
rename angajati3_*** to angajati_***;
--Table renamed.
select * from angajati_***;
select * from angajati3_***;  --ORA-00942: tabelul sau vizualizarea nu exista

14. Suprimati continutul tabelului angajati10_***, fara a suprima structura acestuia.

create table angajati10_*** as
  Select * from angajati_*** where cod_dep =10;
  
  select * from angajati10_***;
  
  delete from angajati10_***; --tabela goala
  rollback; -- avem cele 2 inregistrari
  
  truncate table angajati10_***; --se pastreaza structura tabelei (DELETE+COMMIT)
  rollback; -- in continuare tabela este goala
  
  drop table angajati10_***;
  select * from angajati10_***; -- ORA-00942: tabelul sau vizualizarea nu exista
  
-- 15. Creati tabelul DEPARTAMENTE_***, corespunzator schemei relationale:
-- DEPARTAMENTE_*** (cod_dep# number(2), nume varchar2(15), cod_director number(4))
-- specificand doar constrangerea NOT NULL pentru nume
-- (nu precizati deocamdata constrangerea de cheie primara). 

CREATE TABLE departamente_*** 
(cod_dep number(2), 
nume varchar2(15) constraint NL_nume_*** NOT NULL, 
cod_director number(4)); 

DESC departamente_***;

/*
Name         Null     Type         
------------ -------- ------------ 
COD_DEP               NUMBER(2)    
NUME         NOT NULL VARCHAR2(15) 
COD_DIRECTOR          NUMBER(4)   

16. Introduceti urmatoarele inregistrari in tabelul DEPARTAMENTE_pnu:
Cod_dep	Nume	Cod_director
10	Administrativ	100
20	Proiectare	101
30	Programare	Null
*/

insert into departamente_***
values(10,	'Administrativ',	100);
insert into departamente_***
values(20, 'Proiectare',	101);
insert into departamente_***
values(30,	'Programare',	Null);
-- atentie
insert into departamente_***
values(30,	'DE_STERS',	Null);

select * from departamente_***;
/*
10	Administrativ	100
20	Proiectare	101
30	Programare	
30	DE_STERS	
*/

alter table departamente_***
add constraint pk_depart_*** primary key (cod_dep); 

-- SQL Error: ORA-02437: (GRUPA32.PK_DEPART_***) nu a putut fi validata - cheia primara a fost violata
--*Cause:    attempted to validate a primary key with duplicate values or null
--           values.
--*Action:   remove the duplicates and null values before enabling a primary
--           key.
;
delete from departamente_***
where nume = 'DE_STERS'; -- 1 rows deleted.

select * from departamente_***;
commit;

17. Introduce?i constangerea de cheie primara asupra coloanei cod_dep,
fara suprimarea si recrearea tabelului 
(comanda ALTER).
Observa?ie:
o Introducerea unei constrangeri dupa crearea tabelului presupune ca toate liniile existente in tabel la 
momentul respectiv satisfac noua constrangere.
o Specificarea constrangerilor permite numirea acestora.
o In situatia in care constrangerile sunt precizate la nivel de coloana sau tabel 
(in CREATE TABLE) ele vor primi implicit nume atribuite de sistem, daca nu se specifica vreun alt nume 
intr-o clauza CONSTRAINT.
Exemplu : CREATE TABLE alfa (
X NUMBER CONSTRAINT nn_x NOT NULL,
Y VARCHAR2 (10) NOT NULL
);

-- atentie
alter table departamente_***  --PK = Unique + NOT NULL
add constraint pk_depart_*** primary key (cod_director);
--SQL Error: ORA-01449: coloana contine valori NULL; nu se poate modifica in NOT NULL


alter table departamente_***
add constraint pk_depart_*** primary key (cod_dep); 

--table DEPARTAMENTE_*** altered.

--alter table departamente_***
--drop constraint pk_depart_***;


desc departamente_***;
18. Sa se precizeze constrangerea de cheie externa pentru coloana cod_dep din ANGAJATI_pnu:
a) fara suprimarea tabelului (ALTER TABLE);

desc angajati_***;

select * from angajati_***;
delete from angajati_***
where cod_ang in (105,106);


alter  table angajati_***
add  constraint fk_ang_depart_*** foreign key(cod_dep) references departamente_***(cod_dep);

--Posibile erori:
-- ORA-02270: no matching unique or primary key for this column-list (pt ca nu este setata cheia primara pe tabela de departamente

--ORA-02298: cannot validate (GRUPA34.FK_ANG_DEPART_***) - parent keys not found
--02298. 00000 - "cannot validate (%s.%s) - parent keys not found"
-- angajatii lucreaza pe departamente care nu se gasesc in tabela departamente_***
--insert  into angajati_***
--values (105, 'Nume6', 'Prenume6', 'Nume6@gmail.com', Null, 'Analist', 101, 3000, 50, 0.2);
delete from angajati_***
where cod_ang =105;

SELECT constraint_name, constraint_type, table_name
FROM     user_constraints
WHERE  lower(table_name) = 'angajati_***';

NULL_SALARIU_***	C	ANGAJATI_***
NULL_NUME_***	C	ANGAJATI_***
FK_ANG_DEPART_***	R	ANGAJATI_*** --FK
PK_ANG_***	P	ANGAJATI_***  --PK

b) prin suprimarea si recrearea tabelului, cu precizarea noii constrangeri la nivel de coloana 
({DROP, CREATE} TABLE). De asemenea, se vor mai preciza constrangerile (la nivel de coloana, 
in masura in care este posibil):
- PRIMARY KEY pentru cod_ang;
- FOREIGN KEY pentru cod_sef;
- UNIQUE pentru combinatia nume + prenume;
- UNIQUE pentru email;
- NOT NULL pentru nume;
- verificarea cod_dep > 0;
- verificarea ca salariul sa fie mai mare decat comisionul*100.

--drop table departamente_***; --SQL Error: ORA-02449: cheile unice/primare din tabela sunt referite de cheile externe

drop table angajati_***; --table ANGAJATI_*** dropped.

create table ANGAJATI_***(
  cod_ang number(4) constraint pk_ang_*** primary key, 
  nume varchar2(20) constraint null_nume_*** not null, 
  prenume varchar2(20), 
  email char(15) constraint unq_email_*** unique, 
  data_ang date default sysdate, 
  job varchar2(10), 
  cod_sef number(4) constraint fk_ang_ang_*** references angajati_***(cod_ang), 
  salariu number(8, 2),
  cod_dep number(2) constraint ck_cod_dep_*** check(cod_dep>0), 
  comision number(4,2),
  constraint unq_nume_pren_*** unique(nume, prenume),
  constraint ck_sal_com_*** check( salariu>comision *100),
  constraint fk_ang_depart_*** foreign key(cod_dep) references departamente_***(cod_dep)--se poate punse si la nivel de coloana
    );


SELECT constraint_name, constraint_type, table_name
FROM     user_constraints
WHERE  lower(table_name) IN ('angajati_***');

CK_SAL_COM_***	C	ANGAJATI_***
CK_COD_DEP_***	C	ANGAJATI_***
NULL_NUME_***	C	ANGAJATI_***
FK_ANG_DEPART_***	R	ANGAJATI_***
FK_ANG_ANG_***	R	ANGAJATI_***
UNQ_NUME_PREN_***	U	ANGAJATI_***
UNQ_EMAIL_***	U	ANGAJATI_***
PK_ANG_***	P	ANGAJATI_***

19. Suprimati si recreati tabelul, specificand toate constrangerile la nivel de tabel 
(in masura in care este posibil).
/
--
drop table angajati_***;

---de adaugat
    drop table ANGAJATI_***;

  SELECT * FROM USER_CONSTRAINTS WHERE lower(TABLE_NAME) = 'angajati_***';

CK_COD_DEP_***	C
CK_SAL_COM_***	C
NULL_NUME_***	C
FK_DEPART_***	R
FK_ANG_ANG_***	R
UNQ_EMAIL_***	U
UNQ_NUME_PREN_***	U
PK_ANG_***	P

insert into angajati_***(Cod_ang,	Nume	,Prenume,	Email,	Data_ang	,Job,	Cod_sef,	Salariu,	Cod_dep)
values( 100	,'Nume1',	'Prenume1',	Null	,Null,	'Director',	null,	20000	,10);
select * from angajati_***;

insert into angajati_***
values (101, 	'Nume2',	'Prenume2',	'Nume2@gmail.com', to_date(	'02-02-2004', 'dd-mm-yyyy'), 	'Inginer',	100,	10000	,10, 0.1);

insert into angajati_***
values (102, 'Nume3', 'Prenume3', 'Nume3@gmail.com', to_date('05-06-2004', 'dd-mm-yyyy'), 'Analist', 101, 5000, 20, null);

insert into angajati_*** (Cod_ang, Nume, Prenume, Job, Cod_sef, Salariu, Cod_dep)
values (103, 'Nume4', 'Prenume4', 'Inginer', 100, 9000, 20);
--atentie la data de angajare a lui 103 

insert into angajati_***
values (104, 'Nume5', 'Prenume5', 'Nume5@gmail.com', Null, 'Analist', 101, 3000, 30, 0.2);

select * from angajati_***;
commit;

delete from angajati_***;
rollback;

insert into angajati_***  --inserare prin copiere din tabela mea
select * from angajati_***;
-----
insert into angajati_***(Cod_ang, Nume ,Prenume, Email, Data_ang ,Job, Cod_sef, Salariu, Cod_dep)
values( 100 ,'Nume1', 'Prenume1', Null ,Null, 'Director', null, 20000 ,10);
select * from angajati_***;
insert into angajati_***
values (101, 'Nume2', 'Prenume2', 'Nume2@gmail.com', to_date( '02-02-2004', 'dd-mm-yyyy'), 'Inginer', 100, 10000 ,10, 0.1);
insert into angajati_***
values (102, 'Nume3', 'Prenume3', 'Nume3@gmail.com', to_date('05-06-2004', 'dd-mm-yyyy'), 'Analist', 101, 5000, 20, null);
insert into angajati_*** (Cod_ang, Nume, Prenume, Job, Cod_sef, Salariu, Cod_dep)
values (103, 'Nume4', 'Prenume4', 'Inginer', 100, 9000, 20);
--atentie la data de angajare a lui 103
insert into angajati_***
values (104, 'Nume5', 'Prenume5', 'Nume5@gmail.com', Null, 'Analist', 101, 3000, 30, 0.2);
-----------
commit;



