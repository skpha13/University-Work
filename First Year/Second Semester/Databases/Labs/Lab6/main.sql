-- truncate are commit implicit, delete ul nu are (se poate da rollback si recupera informatiile)

create table ANGAJATI_mal (
    cod_ang number(4) primary key,
    nume varchar2(20) not null,
    prenume varchar2(20),
    email char(15),
    data_ang date default sysdate,
    job varchar2(10),
    cod_sef number(4),
    salariu number(8,2),
    cod_dep number(2)
);

select * from user_constraints
where lower(table_name) in ('angajati_mal');

insert into ANGAJATI_mal(cod_ang,nume,prenume,email,data_ang,job,cod_sef,salariu,cod_dep)
values (100,'Nume1','Prenume1',null,null,'Director',null,20000,10);

insert into ANGAJATI_mal(cod_ang,nume,prenume,email,data_ang,job,cod_sef,salariu,cod_dep)
values (101,'Nume2','Prenume2','nume2','02-02-2014','Inginer',100,10000,10);

insert into ANGAJATI_mal(cod_ang,nume,prenume,email,data_ang,job,cod_sef,salariu,cod_dep)
values (102,'Nume3','Prenume3','nume3','05-06-2010','Analist',101,5000,20);

insert into ANGAJATI_mal(cod_ang,nume,prenume,email,data_ang,job,cod_sef,salariu,cod_dep)
values (103,'Nume4','Prenume4',null,null,'Inginer',100,9000,20);

insert into ANGAJATI_mal(cod_ang,nume,prenume,email,data_ang,job,cod_sef,salariu,cod_dep)
values (104,'Nume5','Prenume2','nume5',null,'Analist',101,3000,30);

select * from angajati_mal;

alter table angajati_mal
add (comision number(4,2));

alter table angajati_mal
modify (comision number(6,2));

alter table angajati_mal
modify (comision number(4,2));

-- modify merge doar daca facem datele mai mari sau daca tabela e goala sau daca toate val sunt null

alter table angajati_mal
modify (comision number(2,2),salariu number(10,2));

update angajati_mal
set comision = 0.1
where lower(job) like 'i%';

select * from angajati_mal;

create table departamente_mal
(
    cod_dep number(2),
    nume varchar2(15) constraint NL_nume_mal not null,
    cod_director number(4)
);

select * from departamente_mal;

insert into departamente_mal
values (10,'Administrativ',100);

insert into departamente_mal
values (20,'Proiectare',101);

insert into departamente_mal
values (30,'Programare',null);

alter table departamente_mal
add constraint pk_depart_mal primary key(cod_dep); -- nu merge cod_director ca are o valoare null

-- adaugare constrangere cu suprimare
alter table angajati_mal
add constraint fk_angajati_mal foreign key(cod_dep) references departamente_mal(cod_dep);

create table ANGAJATI_mal(
  cod_ang number(4), 
  nume varchar2(20) constraint null_nume_mal not null, 
  prenume varchar2(20), 
  email char(15), 
  data_ang date default sysdate, 
  job varchar2(10), 
  cod_sef number(4), 
  salariu number(8, 2),
  cod_dep number(2), 
  comision number(4,2),
  
  constraint unq_nume_pren_mal unique(nume, prenume),
  constraint ck_sal_com_mal check( salariu>comision *100),
  constraint fk_ang_depart_mal foreign key(cod_dep) references departamente_mal(cod_dep),--se poate punse si la nivel de coloana
  constraint pk_ang_mal primary key(cod_ang),
  constraint unq_email_mal unique(email),
  constraint ck_cod_dep_mal check(cod_dep>0),
  constraint fk_ang_ang_mal foreign key(cod_sef) references angajati_mal(cod_ang)
);

