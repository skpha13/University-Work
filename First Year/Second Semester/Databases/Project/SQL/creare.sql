create table PLATA (
    plata_id number(6) constraint pk_plata primary key,
    nume varchar2(50) constraint nume_null not null ,
    prenume varchar2(50) constraint prenume_null not null ,
    cod number(16) constraint cod_null not null ,
    data_exp date constraint date_null not null ,
    cvv number(3) constraint cvv_null not null
);

create table SUBSCRIPTIE (
    subscriptie_id number(6) constraint pk_subscritpie primary key ,
    data_exp date not null ,
    tip varchar2(20) check ( lower(tip) in ('standard', 'normal', 'premium') ),
    cost number(3) check ( cost >= 100 and cost <= 999 )
);

create table UTILIZATOR (
    utilizator_id number(6) constraint pk_utilizator primary key ,
    subscriptie_id number(6) not null ,
    plata_id number(6) not null ,
    porecla varchar2(50) constraint porecla_null not null ,
    mail varchar2(255) constraint mail_null not null ,
    parola varchar2(255) constraint parola_null not null,
    data_creare date default current_date,
    constraint fk_subscriptie foreign key (subscriptie_id) references SUBSCRIPTIE(subscriptie_id),
    constraint fk_plata foreign key (plata_id) references PLATA(plata_id)
);

create table SERIAL (
    serial_id number(6) constraint pk_serial primary key ,
    denumire varchar2(50) constraint denumire_null not null ,
    nota number(2,2) constraint nota_check check ( nota >= 1 and nota <= 10 ),
    data_aparitie date
);

create table EPISOD (
    episod_id number(6) constraint pk_episod primary key ,
    serial_id number(6) not null ,
    denumire varchar2(50)constraint denumire_episod_null not null ,
    numar number(2),
    durata number(3) constraint durata_null not null ,
    constraint fk_serial foreign key (serial_id) references SERIAL(serial_id)
);

create table  SUBSCRIPTIE_SERIAL (
    serial_id number(6) not null ,
    subscriptie_id number(6) not null ,
    primary key (serial_id, subscriptie_id) ,
    constraint fk_subscriptie_asoc foreign key (subscriptie_id) references SUBSCRIPTIE(subscriptie_id) ,
    constraint fk_serial_asoc foreign key (serial_id) references SERIAL(serial_id)
);

create table DIRECTOR (
    director_id number(6) constraint pk_director primary key ,
    nume varchar2(50) constraint nume_dir_null not null ,
    prenume varchar2(50) ,
    data_nastere date ,
    nota number(2,2) constraint nota_director_check check ( nota >= 1 and nota <= 10 )
);

create table FILM (
    film_id number(6) constraint pk_film primary key ,
    director_id number(6) not null ,
    denumire varchar2(50) constraint denumire_film_null not null ,
    nota number(2,2) constraint nota_film_check check ( nota >= 1 and nota <= 10 ) ,
    data_aparitie date ,
    constraint fk_director foreign key (director_id) references DIRECTOR(director_id)
);

create table  SUBSCRIPTIE_FILM (
    film_id number(6) not null ,
    subscriptie_id number(6) not null ,
    primary key (film_id, subscriptie_id) ,
    constraint fk_subscriptie_asocf foreign key (subscriptie_id) references SUBSCRIPTIE(subscriptie_id) ,
    constraint fk_serial_asocf foreign key (film_id) references FILM(film_id)
);

create table ROL (
    rol_id number(6) constraint pk_rol primary key ,
    nume_caracter varchar2(50) constraint caracter_null not null ,
    descriere varchar2(255) ,
    importanta number(2,2) constraint imp_check check ( importanta >= 1 and importanta <= 10 )
);

create table ACTOR (
    actor_id number(6) constraint pk_actor primary key ,
    nume varchar2(50) constraint nume_act_null not null ,
    prenume varchar2(50) constraint prenume_act_null not null ,
    data_nastere  date ,
    biografie varchar2(200) ,
    salariu number(7) default 3000 ,
    timp_ecran number(3)
);

create table SERIAL_ACTOR (
    serial_id number(6) not null ,
    actor_id number(6) not null ,
    primary key (serial_id, actor_id) ,
    constraint fk_actor_asocA foreign key (actor_id) references ACTOR(actor_id) ,
    constraint fk_serial_asocA foreign key (serial_id) references SERIAL(serial_id)
);

create table ROL_JUCAT (
    film_id number(6) not null ,
    actor_id number(6) not null ,
    rol_id number(6) not null ,
    constraint fk_film_asocRJ foreign key (film_id) references FILM(film_id) ,
    constraint fk_actor_asocRJ foreign key (actor_id) references ACTOR(actor_id) ,
    constraint fk_rol foreign key (rol_id) references ROL(rol_id)
);

/*
select constraint_name, constraint_type, TABLE_NAME
from SYS.USER_CONSTRAINTS
where lower(table_name) = 'utilizator';*/
