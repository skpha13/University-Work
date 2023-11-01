-- exercitiul 9

create or replace type filme as varray(5) of number(6);

create table subscrpitii (
    id number(6) primary key,
    nume varchar2(20),
    lista_filme filme
);

declare
    v_filme filme := filme(1,2,3);
    v_lista_filme subscrpitii.lista_filme%type;
begin
    insert into subscrpitii values (1,'basic',v_filme);
    insert into subscrpitii values (2,'normal',filme(2,3,4));
    insert into subscrpitii values (3,'premium',filme(1,5));

    for i in 1..3 loop
        select lista_filme
        into v_lista_filme
        from subscrpitii
        where id = i;

        DBMS_OUTPUT.PUT('Subscriptia ' || i || ': ');

        for j in v_lista_filme.first..v_lista_filme.last loop
            DBMS_OUTPUT.PUT(v_lista_filme(j) || ' ');
            end loop;

        DBMS_OUTPUT.NEW_LINE();
        end loop;

    delete subscrpitii;
end;

drop table subscrpitii;
drop type filme;

-- exercitiul 10

create table utilizator_test as
    select UTILIZATOR_ID, PORECLA
    from UTILIZATOR
    where ROWNUM <= 2;

create or replace type tip_telefon is table of varchar(12);

alter table utilizator_test
add (telefon tip_telefon)
nested table telefon store as tabel_telefon;

insert into utilizator_test values (120,'El Dorado',tip_telefon('074XXX', '0213XXX', '037XXX'));

update utilizator_test
set telefon = tip_telefon('073XXX', '0214XXX')
where UTILIZATOR_ID = 120;

select u.UTILIZATOR_ID, t.*
from utilizator_test u, table (u.telefon) t;

drop table utilizator_test;
drop type tip_telefon;