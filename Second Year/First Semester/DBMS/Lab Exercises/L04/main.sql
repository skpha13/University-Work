DECLARE
    x NUMBER(1) := 5;
    y x%TYPE    := NULL;
BEGIN
    IF x <> y THEN
        DBMS_OUTPUT.PUT_LINE('valoare <> null este = true');
    ELSE
        DBMS_OUTPUT.PUT_LINE('valoare <> null este != true');
    END IF;
    x := NULL;
    IF x = y THEN
        DBMS_OUTPUT.PUT_LINE('null = null este = true');
    ELSE
        DBMS_OUTPUT.PUT_LINE('null = null este != true');
    END IF;
END;
/

-- intr-un record valorile nedefinite sunt automat null,
--      folosim default daca vrem alte valori

-- SELECT employee_id, salary, job_id
-- INTO v_ang
-- merge doar ca select urile trebuie trecute in ordinea din record

-- tablou index by -> tablou indexat
-- tablou fara index by -> tablou imbricat

-- INTREBARI ????
-- exista loc cu toate exceptiile posibile ?

DECLARE
    TYPE tablou_indexat IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
    t tablou_indexat;
BEGIN
    -- punctul a
    FOR i IN 1..10
        LOOP
            t(i) := i;
        END LOOP;
    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT || ' elemente: ');
    FOR i IN t.FIRST..t.LAST
        LOOP
            DBMS_OUTPUT.PUT(t(i) || ' ');
        END LOOP;
    DBMS_OUTPUT.NEW_LINE;
-- punctul b
    FOR i IN 1..10
        LOOP
            IF i mod 2 = 1 THEN
                t(i) := null;
            END IF;
        END LOOP;
    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT || ' elemente: ');
    FOR i IN t.FIRST..t.LAST
        LOOP
            DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' ');
        END LOOP;
    DBMS_OUTPUT.NEW_LINE;
-- punctul c
    t.DELETE(t.first);
    t.DELETE(5, 7);
    t.DELETE(t.last);
    DBMS_OUTPUT.PUT_LINE('Primul element are indicele ' || t.first ||
                         ' si valoarea ' || nvl(t(t.first), 0));
    DBMS_OUTPUT.PUT_LINE('Ultimul element are indicele ' || t.last ||
                         ' si valoarea ' || nvl(t(t.last), 0));
    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT || ' elemente: ');
    FOR i IN t.FIRST..t.LAST
        LOOP
            IF t.EXISTS(i) THEN
                DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' ');
            END IF;
        END LOOP;
    DBMS_OUTPUT.NEW_LINE;
-- punctul d
    t.delete();
    DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT || ' elemente.');
END;
/

-- delete(5,7) -> sterge toate elementele de la 5 la 7

DECLARE
    TYPE tablou_imbricat IS TABLE OF NUMBER;
    t tablou_imbricat := tablou_imbricat();
BEGIN
    -- punctul a
    FOR i IN 1..10
        LOOP
            t.extend;
            t(i) := i;
        END LOOP;
    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT || ' elemente: ');
    FOR i IN t.FIRST..t.LAST
        LOOP
            DBMS_OUTPUT.PUT(t(i) || ' ');
        END LOOP;
    DBMS_OUTPUT.NEW_LINE;
-- punctul b
    FOR i IN 1..10
        LOOP
            IF i mod 2 = 1 THEN
                t(i) := null;
            END IF;
        END LOOP;
    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT || ' elemente: ');
    FOR i IN t.FIRST..t.LAST
        LOOP
            DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' ');
        END LOOP;
    DBMS_OUTPUT.NEW_LINE;
-- punctul c
    t.DELETE(t.first);
    t.DELETE(5, 7);
    t.DELETE(t.last);
    DBMS_OUTPUT.PUT_LINE('Primul element are indicele ' || t.first ||
                         ' si valoarea ' || nvl(t(t.first), 0));
    DBMS_OUTPUT.PUT_LINE('Ultimul element are indicele ' || t.last ||
                         ' si valoarea ' || nvl(t(t.last), 0));
    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT || ' elemente: ');
    FOR i IN t.FIRST..t.LAST
        LOOP
            IF t.EXISTS(i) THEN
                DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' ');
            END IF;
        END LOOP;
    DBMS_OUTPUT.NEW_LINE;
-- punctul d
--     t.delete;
    -- aici merge pentru ca cele imbricate exista constructor da la cele indexate nu
    -- dar la cele imbricate trebuie explicit spus constructorul
    t := tablou_imbricat();
    DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT || ' elemente.');
END;
/

-- la vector ordinea elementor este importanta si nr. de elemente este cunoscut de la declarare

-- metodele DELETE(n), DELETE(m,n) nu sunt valabile pentru vectori!!!
-- din vectori nu se pot sterge elemente individuale!!!

create or replace type tip_orase_ami is varray(10) of varchar2(20);
create or replace type excursiiMinime is varray(10) of number;

create table excursie_ami (
    cod_excursie number(4) primary key ,
    denumire varchar2(20),
    orase tip_orase_ami,
    status varchar2(20) default 'disponibila' check (lower(status) in ('disponibila','anulata'))
);

insert all
    into excursie_ami values (1,'paradis',tip_orase_ami('napoli','capri','positano'),'disponibila')
    into excursie_ami values (2,'vis',tip_orase_ami('paris','lyon'),'anulata')
    into excursie_ami values (3,'munte',tip_orase_ami('sinaia','busteni','predeal','brasov'),'disponibila')
    into excursie_ami values (4,'mare',tip_orase_ami('constinesti'),'disponibila')
    into excursie_ami values (5,'excelent',tip_orase_ami('ploiesti','bucuresti'),'anulata')
select 'worked' from dual;

declare
    v_excursie_id excursie_ami.cod_excursie%type := 1;
    v_orase excursie_ami.orase%type;
    v_nume_oras_1 varchar2(20) := 'napoli';
    v_nume_oras_2 varchar2(20) := 'positano';
    i number(4);
    index1 number(4);
    index2 number(4);
    tempSwap varchar2(20);
    v_excursiiMinime excursiiMinime;
begin
    select orase
    into v_orase
    from excursie_ami
    where cod_excursie = v_excursie_id;

    v_orase.extend();
    v_orase(v_orase.last) := 'roma';

    for i in v_orase.first..v_orase.last loop
        DBMS_OUTPUT.PUT(v_orase(i) || ' ');
        end loop;

    DBMS_OUTPUT.NEW_LINE();

    v_orase.extend();
    i := v_orase.last;
    while i > 2 loop
        v_orase(i) := v_orase(i-1);
        i := i-1;
        end loop;
    v_orase(2) := 'salermo';

    for i in v_orase.first..v_orase.last loop
        DBMS_OUTPUT.PUT(v_orase(i) || ' ');
        end loop;

    DBMS_OUTPUT.NEW_LINE();

    for i in v_orase.first..v_orase.last loop
        if v_orase(i) = v_nume_oras_1 then index1 := i;
            end if;
        if v_orase(i) = v_nume_oras_2 then index2 := i;
            end if;
        end loop;

    tempSwap := v_orase(index1);
    v_orase(index1) := v_orase(index2);
    v_orase(index2) := tempSwap;

    for i in v_orase.first..v_orase.last loop
        DBMS_OUTPUT.PUT(v_orase(i) || ' ');
        end loop;

    DBMS_OUTPUT.NEW_LINE();

    DBMS_OUTPUT.PUT('Excursie ' || v_excursie_id || ', Nr. Orase ' || v_orase.COUNT || ': ');
    for i in v_orase.first..v_orase.last loop
        DBMS_OUTPUT.PUT(v_orase(i) || ' ');
        end loop;

    DBMS_OUTPUT.NEW_LINE();

    select denumire, orase
    from excursie_ami;

    -- nu stiu cum sa pun toate codurile in array
    with ExcursieCounts as (select e.cod_excursie, count(*) as orase_count
                            from excursie_ami e,
                                 table ( e.orase ) t
                            group by e.cod_excursie)
    select cod_excursie
    bulk collect into v_excursiiMinime
    from ExcursieCounts
    where orase_count = (select min(orase_count) from ExcursieCounts);
end;
/