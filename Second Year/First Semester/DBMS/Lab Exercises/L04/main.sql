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

create or replace type tip_orase_ami is varray(10) of varchar2(20)

create table excursie_ami (
    cod_excursie number(4),
    denumire varchar2(20),
    orase tip_orase_ami,
    status check ('disponibila','anulata')
);