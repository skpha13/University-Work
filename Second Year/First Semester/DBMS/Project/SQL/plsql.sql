--      ====== EX6 ======

-- pentru o subscriptie afisati toate filmele ei
-- + toti actorii fiecarui film

-- varray
create or replace type actori as varray(20) of varchar2(50);

CREATE OR REPLACE PROCEDURE filme_din_subscriptie(v_nume_subscriptie SUBSCRIPTIE.TIP%TYPE)
AS
    -- tablou indexat care retine numele filmelor
    type filme is table of FILM.denumire%type index by pls_integer;
    v_filme filme;

    -- tablou imbricat care retine id-ul filmelor
    type filme_id is table of ACTOR.nume%type;
    v_filme_id filme_id;

    -- varray care contine numele actorilor
    v_actori actori;

    v_subscriptie_id SUBSCRIPTIE.subscriptie_id%type;
BEGIN
    -- obtine id-ul subscriptiei
    select unique SUBSCRIPTIE_ID
    into v_subscriptie_id
    from SUBSCRIPTIE
    where TIP = v_nume_subscriptie;

    -- obtin toate numele filmelor si id-urile lor in tabloul indexat v_filme/v_filme_id
    select DENUMIRE, FILM.FILM_ID
    bulk collect into v_filme, v_filme_id
    from FILM
    join SUBSCRIPTIE_FILM on FILM.FILM_ID = SUBSCRIPTIE_FILM.FILM_ID
    where SUBSCRIPTIE_FILM.SUBSCRIPTIE_ID = v_subscriptie_id;

    DBMS_OUTPUT.PUT_LINE('      Subscriptia ' || v_nume_subscriptie || ' contine:');

    for i in v_filme_id.first..v_filme_id.last loop
        DBMS_OUTPUT.PUT_LINE('  ' || v_filme(i) || ': ');

        -- pentru fiecare film selectam actorii care joaca in el
        select nume
        bulk collect into v_actori
        from ACTOR
        join ROL_JUCAT on ACTOR.ACTOR_ID = ROL_JUCAT.ACTOR_ID
        where ROL_JUCAT.FILM_ID = v_filme_id(i);

        if v_actori.COUNT > 0 then
            for j in v_actori.first..v_actori.last loop
                DBMS_OUTPUT.PUT_LINE(v_actori(j));
            end loop;

            v_actori.DELETE;
        else
            DBMS_OUTPUT.PUT_LINE('Nu are actori');
        end if;

        end loop;
END;
/

begin
    filme_din_subscriptie('ultimate');
end;
/

-- =================================================================

--      ====== EX7 ======
-- pentru fiecare Serial cu id-ul intr-o lista afisati numele tuturor
-- episoadelor care apartin
create or replace type serialId as varray(10) of number(6);

-- functie ajutatoare pentru a verifica daca un serial apartine unui varray de seriale
-- am facut asta ca primeam o eroare ciudata si asta mi s-a parut un workaound destul de bun
create or replace function verifica_serial(v_serialId SERIAL.SERIAL_ID%TYPE, listaId serialId) RETURN NUMBER AS
    v_found number(1) := 0;
begin
    for i in 1..listaId.COUNT loop
        if v_serialId = listaId(i) then
            v_found := 1;
            return v_found;
        end if;
    end loop;

    return v_found;
end;
/

CREATE OR REPLACE PROCEDURE episoade_din_seriale(listaId serialId) AS
    v_id_ser SERIAL.serial_id%type;

    v_nume_ser SERIAL.denumire%type;
    v_nume_episod varchar2(50);
    v_areEpisod number(1) := 0;

    -- cursor clasic
    CURSOR seriale IS
        select SERIAL_ID, DENUMIRE
        from SERIAL
        WHERE verifica_serial(SERIAL_ID, listaId) = 1;

    -- cursor parametrizat dependent de cel anterior
    CURSOR episod(id number) IS
        select DENUMIRE
        from EPISOD
        where SERIAL_ID = id;

begin
    OPEN seriale;
    loop
        Fetch seriale into v_id_ser, v_nume_ser;
        exit when seriale%notfound;

        v_areEpisod := 0;

        DBMS_OUTPUT.PUT_LINE('Serialul: ' || v_nume_ser);

        -- deschidem noul cursor cu parametrul din cursorul anterior
        OPEN episod(v_id_ser);
        loop
            Fetch episod into v_nume_episod;
            exit when EPISOD%notfound;
            v_areEpisod := 1;
            DBMS_OUTPUT.PUT_LINE('  ' || v_nume_episod);
        end loop;

        close episod;

        if v_areEpisod = 0 then DBMS_OUTPUT.PUT_LINE('  Nu are episoade');
        end if;

    end loop;
    close seriale;
end;
/

declare
    v_lista_serialId serialId := serialId(1,3,6);
begin
    episoade_din_seriale(v_lista_serialId);
end;
/
-- =================================================================

--      ====== EX8 ======
-- pentru o subscriptie data sa se ia serialul cu durata cea mai mare si
-- sa se afiseze cati actori are
CREATE OR REPLACE FUNCTION durata_subscriptie(tip_subscriptie subscriptie.tip%type) return Number
AS
    type tipSubscriptie is table of SUBSCRIPTIE.TIP%type index by pls_integer;

    v_subscriptie_id SUBSCRIPTIE.subscriptie_id%type;
    v_tipuri_subscriptii tipSubscriptie;
    v_hasBeenFound boolean := false;
    v_maxSerialDuration number(4) := 0;
    v_idSerialMaxDuration SERIAL.SERIAL_ID%type;
    v_countActors number(3) := 0;
    v_foundActors boolean := false;

    -- cursor care ne ofera id-ul serialelor din subscriptia data ca parametru si duratat totala
    -- aflata adunand durata fiecarui episod din acel serial
    CURSOR durataEpisoade(id_subscriptie SUBSCRIPTIE.SUBSCRIPTIE_ID%type) IS
        SELECT ss.SERIAL_ID, SUM(EP.DURATA) AS suma
        FROM SUBSCRIPTIE_SERIAL ss
        JOIN EPISOD EP ON ss.SERIAL_ID = EP.SERIAL_ID
        JOIN SERIAL S ON ss.SERIAL_ID = S.SERIAL_ID
        WHERE ss.SUBSCRIPTIE_ID = v_subscriptie_id
        GROUP BY ss.SERIAL_ID
        ORDER BY suma DESC;

    -- cursor care ne da pentru fiecare serial cati actori are
    CURSOR actors IS
        select sa.SERIAL_ID id, count(*) nr
        from ACTOR a
                 Join SERIAL_ACTOR sa on a.ACTOR_ID = sa.ACTOR_ID
        group by sa.serial_id;

    type serial_info is table of durataEpisoade%rowtype index by pls_integer;
    v_infoSeriale serial_info;

    type actors_info is table of actors%rowtype index by pls_integer;
    v_infoActors actors_info;

    -- exceptii
    NAME_NOT_FOUND EXCEPTION;
    NO_ACTORS_FOUND EXCEPTION;
BEGIN
    -- selectarea tututor tipurilor si verificarea ca tipul dat ca parametru sa existe
    -- in aceasta lista
    select lower(tip)
    bulk collect into v_tipuri_subscriptii
    from SUBSCRIPTIE;

    for i in v_tipuri_subscriptii.first..v_tipuri_subscriptii.last loop
        if lower(tip_subscriptie) = v_tipuri_subscriptii(i) then
            v_hasBeenFound := true;
        end if;
    end loop;

    if v_hasBeenFound = false then
        RAISE NAME_NOT_FOUND;
    end if;
    -- ========================

    -- daca avem un tip corect ii aflam id-ul
    select SUBSCRIPTIE_ID
    into v_subscriptie_id
    from SUBSCRIPTIE
    where lower(TIP) = lower(tip_subscriptie);
    -- ===============

    -- colectam informatia pentru seriale, adica (id, durata totala)
    OPEN durataEpisoade(v_subscriptie_id);
    FETCH durataEpisoade bulk collect into v_infoSeriale;
    CLOSE durataEpisoade;

    -- parcurgem serialele si luam id-ul celui cu cea mai mare durata
    FOR i IN v_infoSeriale.FIRST..v_infoSeriale.LAST LOOP
        if v_maxSerialDuration < v_infoSeriale(i).suma then
            v_maxSerialDuration := v_infoSeriale(i).suma;
            v_idSerialMaxDuration := v_infoSeriale(i).SERIAL_ID;
        end if;
    END LOOP;

    -- colectam informatia pentru actori
    OPEN actors;
    FETCH actors bulk collect into v_infoActors;
    CLOSE actors;

    -- pentru fiecare serial vedem daca e egal cu cel aflat anterior
    -- daca da ii dam actualizam countActors
    for i in v_infoActors.first..v_infoActors.last loop
        if v_infoActors(i).id = v_idSerialMaxDuration then
            v_foundActors := true;
            v_countActors := v_infoActors(i).nr;
        end if;
        end loop;

    if v_foundActors = false then
        RAISE NO_ACTORS_FOUND;
    end if;

    return v_countActors;

exception
    when NAME_NOT_FOUND then
        DBMS_OUTPUT.PUT_LINE('Nu exista tipul introdus');
        return -1;

    when NO_ACTORS_FOUND then
        DBMS_OUTPUT.PUT_LINE('Nu am gasit actori pentru datele cerute');
        return -1;
end;
/

-- Nu au fost gasiti actori
declare
    v_tip_subscriptie SUBSCRIPTIE.TIP%TYPE := 'basic';
begin
    DBMS_OUTPUT.PUT_LINE(durata_subscriptie(v_tip_subscriptie));
end;
/

-- Nu exista tipul introdus
declare
    v_tip_subscriptie SUBSCRIPTIE.TIP%TYPE := 'test';
begin
    DBMS_OUTPUT.PUT_LINE(durata_subscriptie(v_tip_subscriptie));
end;
/

-- Functioneaza corect
declare
    v_tip_subscriptie SUBSCRIPTIE.TIP%TYPE := 'standard';
begin
    DBMS_OUTPUT.PUT_LINE(durata_subscriptie(v_tip_subscriptie));
end;
/
-- =================================================================

--      ====== EX9 ======
-- ni se da porcela unui utilizator, aflati toti actorii la care se poate uita
CREATE OR REPLACE PROCEDURE actori_utilizator(porecla_utilizator UTILIZATOR.PORECLA%TYPE)
AS
    v_idUtilizator UTILIZATOR.UTILIZATOR_ID%TYPE;
    v_firstIdUtilizator UTILIZATOR.UTILIZATOR_ID%TYPE;
    v_actorFound boolean := false;

    -- distinct pentru ca un actor poate juca in mai multe filme
    CURSOR getActori(idUtilizator UTILIZATOR.UTILIZATOR_ID%TYPE) IS
        select DISTINCT NUME
        from ACTOR a
        JOIN ROL_JUCAT rl on a.ACTOR_ID = rl.ACTOR_ID
        JOIN FILM f on rl.FILM_ID = f.FILM_ID
        JOIN SUBSCRIPTIE_FILM sf on f.FILM_ID = sf.FILM_ID
        JOIN SUBSCRIPTIE s on sf.SUBSCRIPTIE_ID = s.SUBSCRIPTIE_ID
        JOIN UTILIZATOR u on s.SUBSCRIPTIE_ID = u.SUBSCRIPTIE_ID
        WHERE u.UTILIZATOR_ID = idUtilizator;

    NO_ACTORS_FOUND EXCEPTION;

BEGIN
    DBMS_OUTPUT.PUT_LINE('UTILIZATORUL: ' || porecla_utilizator);

    -- ia id-ul utilizatorului cu porecla data | TOO_MANY_ROWS/NO_DATA_FOUND
        -- alt bloc in caz ca exista doi sau mai multi utilizatori cu aceeasi porecla
        -- daca se intampla asta il luam pe primul
    BEGIN
        select UTILIZATOR_ID
        into v_idUtilizator
        from UTILIZATOR
        where lower(porecla_utilizator) = lower(porecla);
    EXCEPTION
        when TOO_MANY_ROWS then
            SELECT UTILIZATOR_ID
            INTO v_firstIdUtilizator
            FROM (
                SELECT UTILIZATOR_ID
                FROM UTILIZATOR
                WHERE lower(porecla_utilizator) = lower(porecla)
                AND ROWNUM = 1
            );
            v_idUtilizator := v_firstIdUtilizator;
    end;

    -- daca trecem de toate verificarile afisam toti actorii utilizatorului
    for i in getActori(v_idUtilizator) loop
        v_actorFound := true;
        DBMS_OUTPUT.PUT_LINE('  ' || i.NUME);
        end loop;

    -- verificam daca am gasit actori in cursor
    if v_actorFound = false then RAISE NO_ACTORS_FOUND;
    end if;
exception
    when NO_DATA_FOUND then
        DBMS_OUTPUT.PUT_LINE('  Nu au fost gasiti utilizatori cu porecla data');

    when NO_ACTORS_FOUND then
        DBMS_OUTPUT.PUT_LINE('  Acest utilizator nu se poate uita la niciun film cu actori');
end;
/

-- TOO_MANY_ROWS
begin
    actori_utilizator('skpha');
end;

-- NO_DATA_FOUND
begin
    actori_utilizator('test');
end;

-- NO_ACTORS_FOUND
declare
    type porecle is table of UTILIZATOR.porecla%type index by pls_integer;
    v_porecleUtilizatori porecle;
begin
    actori_utilizator('OnePiece');
end;

-- Functioneaza corect
begin
    actori_utilizator('Matoka26');
end;
/
-- =================================================================

--      ====== EX10 ======
-- Trigger care sa nu ne lase sa inseram mai multe decat 6
CREATE OR REPLACE TRIGGER nr_maxim_subscriptii
    BEFORE INSERT ON SUBSCRIPTIE
DECLARE
    v_nrSubscriptii number(2);
BEGIN
    -- punem numarul subscriptiilor in variabila
    select count(*)
    into v_nrSubscriptii
    from SUBSCRIPTIE;

    -- daca sunt sase deja, aruncam eroarea
    if v_nrSubscriptii >= 6 then
        RAISE_APPLICATION_ERROR(-20001,'Numarul maxim de subscriptii a fost atins');
    end if;
end;
/

begin
    insert into SUBSCRIPTIE(subscriptie_id, tip, cost) values (100000,'baSIC',99);
end;
/

drop trigger nr_maxim_subscriptii;
select count(*) from SUBSCRIPTIE;
delete from SUBSCRIPTIE where SUBSCRIPTIE_ID = 99999;
-- =================================================================

--      ====== EX11 ======
create or replace type subscriptii as varray(6) of number(6);

-- tabela pentru a retine daca filmul a fost deja inserat de trigger
create table film_trigger (
    film_id number(6)
);

-- functie ajutatoare pentru a verifica daca un film se afla in film_trigger
CREATE OR REPLACE FUNCTION verificaFilm(v_filmId FILM.FILM_ID%TYPE) return boolean AS
    v_count number(2) := 0;
BEGIN
    select count(*)
    into v_count
    from film_trigger
    where film_id = v_filmId;

    if v_count > 0 then
        return TRUE;
    end if;

    return false;
END;
/

CREATE OR REPLACE TRIGGER inserare_filme
    BEFORE INSERT
    ON SUBSCRIPTIE_FILM
    FOR EACH ROW
DECLARE
    v_tipuriSubscriptii subscriptii;
    v_subscriptieCurenta boolean := false;
BEGIN
    -- obtinem id-urile subscriptiilor in functie de cost
    -- asta pentru a le avea in ordinea ierarhica corecta
    select SUBSCRIPTIE_ID
    bulk collect into v_tipuriSubscriptii
    from SUBSCRIPTIE
    order by COST;

    -- parcurgem toate subscriptiile
    if VERIFICAFILM(:NEW.FILM_ID) = false then
        insert into film_trigger(film_id) values (:NEW.FILM_ID);

        for i in v_tipuriSubscriptii.first..v_tipuriSubscriptii.last loop
            -- daca anterior gasisem subscriptia inserata atunci o inseram si in restul
            if v_subscriptieCurenta = true then
                insert into SUBSCRIPTIE_FILM(subscriptie_film_id, film_id, subscriptie_id)
                        values (INCREMENTARE_film.nextval, :NEW.FILM_ID, v_tipuriSubscriptii(i));
            end if;

            if :NEW.SUBSCRIPTIE_ID = v_tipuriSubscriptii(i) then
                v_subscriptieCurenta := true;
            end if;
            end loop;

    end if;
end;
/

select SUBSCRIPTIE_ID
from SUBSCRIPTIE_FILM
where FILM_ID = 999;

delete from SUBSCRIPTIE_FILM where FILM_ID = 999;

insert into SUBSCRIPTIE_FILM(subscriptie_film_id, film_id, subscriptie_id) values (INCREMENTARE_FILM.nextval,999,55245);
drop trigger inserare_filme;
-- =================================================================

--      ====== EX12 ======
create table audit_tabele (
    utilizator varchar2(30),
    nume_bazadate varchar2(50),
    eveniment varchar2(20),
    nume_obiect varchar2(30),
    data date
);

CREATE OR REPLACE TRIGGER trigger_audit
    after create or drop or alter on schema
BEGIN
    insert into audit_tabele values (
        sys.LOGIN_USER(),
        sys.DATABASE_NAME(),
        sys.SYSEVENT(),
        sys.DICTIONARY_OBJ_NAME(),
        sysdate
    );
end;
/

create table test (tip varchar2(20));
drop table test;

select * from audit_tabele;

drop trigger trigger_audit;
-- =================================================================

--      ====== EX13 ======
CREATE OR REPLACE PACKAGE pachet_netflix AS
    -- 6
    PROCEDURE filme_din_subscriptie(v_nume_subscriptie SUBSCRIPTIE.TIP%TYPE);
    -- 7 functie ajutatoare + procedura
    FUNCTION verifica_serial(v_serialId SERIAL.SERIAL_ID%TYPE, listaId serialId) RETURN NUMBER;
    PROCEDURE episoade_din_seriale(listaId serialId);
    -- 8
    FUNCTION durata_subscriptie(tip_subscriptie subscriptie.tip%type) RETURN NUMBER;
    -- 9
    PROCEDURE actori_utilizator(porecla_utilizator UTILIZATOR.PORECLA%TYPE);
END pachet_netflix;

CREATE OR REPLACE PACKAGE BODY pachet_netflix AS
    -- ===== 6 =====
    PROCEDURE filme_din_subscriptie(v_nume_subscriptie SUBSCRIPTIE.TIP%TYPE)
    AS
        -- tablou indexat care retine numele filmelor
        type filme is table of FILM.denumire%type index by pls_integer;
        v_filme filme;

        -- tablou imbricat care retine id-ul filmelor
        type filme_id is table of ACTOR.nume%type;
        v_filme_id filme_id;

        -- varray care contine numele actorilor
        v_actori actori;

        v_subscriptie_id SUBSCRIPTIE.subscriptie_id%type;

    BEGIN
        -- obtine id-ul subscriptiei
        select unique SUBSCRIPTIE_ID
        into v_subscriptie_id
        from SUBSCRIPTIE
        where TIP = v_nume_subscriptie;

        -- obtin toate numele filmelor si id-urile lor in tabloul indexat v_filme/v_filme_id
        select DENUMIRE, FILM.FILM_ID
        bulk collect into v_filme, v_filme_id
        from FILM
        join SUBSCRIPTIE_FILM on FILM.FILM_ID = SUBSCRIPTIE_FILM.FILM_ID
        where SUBSCRIPTIE_FILM.SUBSCRIPTIE_ID = v_subscriptie_id;

        DBMS_OUTPUT.PUT_LINE('      Subscriptia ' || v_nume_subscriptie || ' contine:');

        for i in v_filme_id.first..v_filme_id.last loop
            DBMS_OUTPUT.PUT_LINE('  ' || v_filme(i) || ': ');

            -- pentru fiecare film selectam actorii care joaca in el
            select nume
            bulk collect into v_actori
            from ACTOR
            join ROL_JUCAT on ACTOR.ACTOR_ID = ROL_JUCAT.ACTOR_ID
            where ROL_JUCAT.FILM_ID = v_filme_id(i);

            if v_actori.COUNT > 0 then
                for j in v_actori.first..v_actori.last loop
                    DBMS_OUTPUT.PUT_LINE(v_actori(j));
                end loop;

                v_actori.DELETE;
            else
                DBMS_OUTPUT.PUT_LINE('Nu are actori');
            end if;

            end loop;
    END filme_din_subscriptie;
    -- =============

    -- ===== 7 =====
    function verifica_serial(v_serialId SERIAL.SERIAL_ID%TYPE, listaId serialId) RETURN NUMBER AS
        v_found number(1) := 0;
    begin
        for i in 1..listaId.COUNT loop
            if v_serialId = listaId(i) then
                v_found := 1;
                return v_found;
            end if;
        end loop;

        return v_found;
    end verifica_serial;

    PROCEDURE episoade_din_seriale(listaId serialId) AS
        v_id_ser SERIAL.serial_id%type;

        v_nume_ser SERIAL.denumire%type;
        v_nume_episod varchar2(50);
        v_areEpisod number(1) := 0;

        -- cursor clasic
        CURSOR seriale IS
            select SERIAL_ID, DENUMIRE
            from SERIAL
            WHERE verifica_serial(SERIAL_ID, listaId) = 1;

        -- cursor parametrizat dependent de cel anterior
        CURSOR episod(id number) IS
            select DENUMIRE
            from EPISOD
            where SERIAL_ID = id;

    begin
        OPEN seriale;
        loop
            Fetch seriale into v_id_ser, v_nume_ser;
            exit when seriale%notfound;

            v_areEpisod := 0;

            DBMS_OUTPUT.PUT_LINE('Serialul: ' || v_nume_ser);

            -- deschidem noul cursor cu parametrul din cursorul anterior
            OPEN episod(v_id_ser);
            loop
                Fetch episod into v_nume_episod;
                exit when EPISOD%notfound;
                v_areEpisod := 1;
                DBMS_OUTPUT.PUT_LINE('  ' || v_nume_episod);
            end loop;

            close episod;

            if v_areEpisod = 0 then DBMS_OUTPUT.PUT_LINE('  Nu are episoade');
            end if;

        end loop;
        close seriale;
    end episoade_din_seriale;
    -- =============

    -- ===== 8 =====
    FUNCTION durata_subscriptie(tip_subscriptie subscriptie.tip%type) return Number
    AS
        type tipSubscriptie is table of SUBSCRIPTIE.TIP%type index by pls_integer;

        v_subscriptie_id SUBSCRIPTIE.subscriptie_id%type;
        v_tipuri_subscriptii tipSubscriptie;
        v_hasBeenFound boolean := false;
        v_maxSerialDuration number(4) := 0;
        v_idSerialMaxDuration SERIAL.SERIAL_ID%type;
        v_countActors number(3) := 0;
        v_foundActors boolean := false;

        -- cursor care ne ofera id-ul serialelor din subscriptia data ca parametru si duratat totala
        -- aflata adunand durata fiecarui episod din acel serial
        CURSOR durataEpisoade(id_subscriptie SUBSCRIPTIE.SUBSCRIPTIE_ID%type) IS
            SELECT ss.SERIAL_ID, SUM(EP.DURATA) AS suma
            FROM SUBSCRIPTIE_SERIAL ss
            JOIN EPISOD EP ON ss.SERIAL_ID = EP.SERIAL_ID
            JOIN SERIAL S ON ss.SERIAL_ID = S.SERIAL_ID
            WHERE ss.SUBSCRIPTIE_ID = v_subscriptie_id
            GROUP BY ss.SERIAL_ID
            ORDER BY suma DESC;

        -- cursor care ne da pentru fiecare serial cati actori are
            -- sau e bine si asa?
        CURSOR actors IS
            select sa.SERIAL_ID id, count(*) nr
            from ACTOR a
                     Join SERIAL_ACTOR sa on a.ACTOR_ID = sa.ACTOR_ID
            group by sa.serial_id;

        type serial_info is table of durataEpisoade%rowtype index by pls_integer;
        v_infoSeriale serial_info;

        type actors_info is table of actors%rowtype index by pls_integer;
        v_infoActors actors_info;

        -- exceptii
        NAME_NOT_FOUND EXCEPTION;
        NO_ACTORS_FOUND EXCEPTION;
    BEGIN
        -- selectarea tututor tipurilor si verificarea ca tipul dat ca parametru sa existe
        -- in aceasta lista
        select lower(tip)
        bulk collect into v_tipuri_subscriptii
        from SUBSCRIPTIE;

        for i in v_tipuri_subscriptii.first..v_tipuri_subscriptii.last loop
            if lower(tip_subscriptie) = v_tipuri_subscriptii(i) then
                v_hasBeenFound := true;
            end if;
        end loop;

        if v_hasBeenFound = false then
            RAISE NAME_NOT_FOUND;
        end if;
        -- ========================

        -- daca avem un tip corect ii aflam id-ul
        select SUBSCRIPTIE_ID
        into v_subscriptie_id
        from SUBSCRIPTIE
        where lower(TIP) = lower(tip_subscriptie);
        -- ===============

        -- colectam informatia pentru seriale, adica (id, durata totala)
        OPEN durataEpisoade(v_subscriptie_id);
        FETCH durataEpisoade bulk collect into v_infoSeriale;
        CLOSE durataEpisoade;

        -- parcurgem serialele si luam id-ul celui cu cea mai mare durata
        FOR i IN v_infoSeriale.FIRST..v_infoSeriale.LAST LOOP
            if v_maxSerialDuration < v_infoSeriale(i).suma then
                v_maxSerialDuration := v_infoSeriale(i).suma;
                v_idSerialMaxDuration := v_infoSeriale(i).SERIAL_ID;
            end if;
        END LOOP;

        -- colectam informatia pentru actori
        OPEN actors;
        FETCH actors bulk collect into v_infoActors;
        CLOSE actors;

        -- pentru fiecare serial vedem daca e egal cu cel aflat anterior
        -- daca da ii dam actualizam countActors
        for i in v_infoActors.first..v_infoActors.last loop
            if v_infoActors(i).id = v_idSerialMaxDuration then
                v_foundActors := true;
                v_countActors := v_infoActors(i).nr;
            end if;
            end loop;

        if v_foundActors = false then
            RAISE NO_ACTORS_FOUND;
        end if;

        return v_countActors;

    exception
        when NAME_NOT_FOUND then
            DBMS_OUTPUT.PUT_LINE('Nu exista tipul introdus');
            return -1;

        when NO_ACTORS_FOUND then
            DBMS_OUTPUT.PUT_LINE('Nu am gasit actori pentru datele cerute');
            return -1;

    end durata_subscriptie;
    -- =============

    -- ===== 9 =====
    PROCEDURE actori_utilizator(porecla_utilizator UTILIZATOR.PORECLA%TYPE)
    AS
        v_idUtilizator UTILIZATOR.UTILIZATOR_ID%TYPE;
        v_firstIdUtilizator UTILIZATOR.UTILIZATOR_ID%TYPE;
        v_actorFound boolean := false;

        -- distinct pentru ca un actor poate juca in mai multe filme
        CURSOR getActori(idUtilizator UTILIZATOR.UTILIZATOR_ID%TYPE) IS
            select DISTINCT NUME
            from ACTOR a
            JOIN ROL_JUCAT rl on a.ACTOR_ID = rl.ACTOR_ID
            JOIN FILM f on rl.FILM_ID = f.FILM_ID
            JOIN SUBSCRIPTIE_FILM sf on f.FILM_ID = sf.FILM_ID
            JOIN SUBSCRIPTIE s on sf.SUBSCRIPTIE_ID = s.SUBSCRIPTIE_ID
            JOIN UTILIZATOR u on s.SUBSCRIPTIE_ID = u.SUBSCRIPTIE_ID
            WHERE u.UTILIZATOR_ID = idUtilizator;

        NO_ACTORS_FOUND EXCEPTION;

    BEGIN
        DBMS_OUTPUT.PUT_LINE('UTILIZATORUL: ' || porecla_utilizator);

        -- ia id-ul utilizatorului cu porecla data | TOO_MANY_ROWS/NO_DATA_FOUND
            -- alt bloc in caz ca exista doi sau mai multi utilizatori cu aceeasi porecla
            -- daca se intampla asta il luam pe primul
        BEGIN
            select UTILIZATOR_ID
            into v_idUtilizator
            from UTILIZATOR
            where lower(porecla_utilizator) = lower(porecla);
        EXCEPTION
            when TOO_MANY_ROWS then
                SELECT UTILIZATOR_ID
                INTO v_firstIdUtilizator
                FROM (
                    SELECT UTILIZATOR_ID
                    FROM UTILIZATOR
                    WHERE lower(porecla_utilizator) = lower(porecla)
                    AND ROWNUM = 1
                );
                v_idUtilizator := v_firstIdUtilizator;
        end;

        -- daca trecem de toate verificarile afisam toti actorii utilizatorului
        for i in getActori(v_idUtilizator) loop
            v_actorFound := true;
            DBMS_OUTPUT.PUT_LINE('  ' || i.NUME);
            end loop;

        -- verificam daca am gasit actori in cursor
        if v_actorFound = false then RAISE NO_ACTORS_FOUND;
        end if;
    exception
        when NO_DATA_FOUND then
            DBMS_OUTPUT.PUT_LINE('  Nu au fost gasiti utilizatori cu porecla data');

        when NO_ACTORS_FOUND then
            DBMS_OUTPUT.PUT_LINE('  Acest utilizator nu se poate uita la niciun film cu actori');
    end actori_utilizator;
    -- =============

END pachet_netflix;

declare
    v_lista_serialId serialId := serialId(1,3,6);
begin
    DBMS_OUTPUT.PUT_LINE('          FILM DIN SUBSCRIPTIE: ');
    pachet_netflix.filme_din_subscriptie('ultimate');

    DBMS_OUTPUT.PUT_LINE('      EPISOADE DIN SERIALE: ');
    pachet_netflix.episoade_din_seriale(v_lista_serialId);

    DBMS_OUTPUT.PUT_LINE('      COUNT ACTORI SUBSCRIPTIE CU DURATA MAXIMA: ');
    DBMS_OUTPUT.PUT_LINE(pachet_netflix.durata_subscriptie('premium'));

    DBMS_OUTPUT.PUT_LINE('      ACTORI PENTRU UTILIZATOR: ');
    pachet_netflix.actori_utilizator('skpha');
end;
/
-- =================================================================

--      ====== EX14 ======
-- care rep. toate filmele/serialele si actorii la care se poate uita un user
    -- [X] 2 proceduri, toate filmele/serialele
    -- [X] 1 procedura toti actorii
    -- [X] 1 function cu record pentru a obtine filmul cu nota maxima
    -- [X] 1 functie filtrare, cu notamin notamax parametrii default restul bool uri (ordonare cresc sau nu)
CREATE OR REPLACE PACKAGE pachet_utilizator AS
    -- verifica daca un utilizator are un abonament valid (data de expirare a subscriptiei nu a expirat inca)
    function verifica_subscriptie(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE) RETURN BOOLEAN;
    -- face insert-urile necesare pentru o plata a unui utilizator
    procedure inserare_plata(v_utilizatorId UTILIZATOR.UTILIZATOR_ID%TYPE,
                             v_plataId PLATA.PLATA_ID%TYPE,
                             v_nume PLATA.NUME%TYPE,
                             v_prenume PLATA.PRENUME%TYPE,
                             V_cod PLATA.COD%TYPE,
                             v_data_exp PLATA.DATA_EXP%TYPE,
                             v_cvv PLATA.CVV%TYPE);
    -- daca data curenta este aceeasi cu data cand utilizatorul si a facut contul ii oferim o luna gratis
    procedure verifica_aniversare(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE);

    -- 2 cursoare, unul care ia toate filmele si actorii la care se poate uita un user
        -- si celalalt toate seriale si actorii respectivi la care se poate uita un user
    CURSOR filme_actori(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE) IS
        SELECT f.DENUMIRE AS FILM, a.NUME AS ACTOR, f.NOTA as NOTA
        FROM UTILIZATOR u
        JOIN SUBSCRIPTIE s ON u.SUBSCRIPTIE_ID = s.SUBSCRIPTIE_ID
        JOIN SUBSCRIPTIE_FILM sf ON s.SUBSCRIPTIE_ID = sf.SUBSCRIPTIE_ID
        JOIN FILM f ON sf.FILM_ID = f.FILM_ID
        LEFT JOIN ROL_JUCAT rl ON f.FILM_ID = rl.FILM_ID
        LEFT JOIN ACTOR a ON rl.ACTOR_ID = a.ACTOR_ID
        WHERE u.UTILIZATOR_ID = v_userId;

    CURSOR seriale_actori(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE) IS
        SELECT ser.DENUMIRE AS SERIAL, a.NUME AS ACTOR
        FROM UTILIZATOR u
        JOIN SUBSCRIPTIE s ON u.SUBSCRIPTIE_ID = s.SUBSCRIPTIE_ID
        JOIN SUBSCRIPTIE_SERIAL ss ON s.SUBSCRIPTIE_ID = ss.SUBSCRIPTIE_ID
        JOIN SERIAL ser ON ss.SERIAL_ID = ser.SERIAL_ID
        LEFT JOIN SERIAL_ACTOR sa ON ser.SERIAL_ID = sa.SERIAL_ID
        LEFT JOIN ACTOR a ON sa.ACTOR_ID = a.ACTOR_ID
        WHERE u.UTILIZATOR_ID = v_userId;

    -- ia toate filmele distincte din cursorul filme_actori
    procedure toate_filmele(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE);
    -- ia toate serialele distincte din cursorul seriale_actori
    procedure toate_serialele(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE);
    -- ia toti actorii distincti din cursorul filme_actori reunit cu cursorul seriale_actori
    procedure toti_actorii(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE);

    -- tip de record pentru a retine numele filmului si nota lui maxima
    type film_record is record(nume film.denumire%type, nota film.nota%type);
    -- functie de returnare a filmului cu nota maxima la care se poate uita un utilizator
    function film_nota_maxima(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE) return film_record;

    -- filtrare filme pe care le poate vedea un utilizator
    TYPE cursor_filtrare IS REF CURSOR RETURN FILM%ROWTYPE;
    function filtreaza_filme(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE,
                             v_nota_min FILM.NOTA%TYPE DEFAULT 0,
                             v_nota_max FILM.NOTA%TYPE DEFAULT 10,
                             v_crescator boolean DEFAULT false,
                             v_descrescator boolean DEFAULT false)
    return cursor_filtrare;
END pachet_utilizator;

CREATE OR REPLACE PACKAGE BODY pachet_utilizator AS
    function verifica_subscriptie(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE) RETURN BOOLEAN AS
        v_expired boolean := false;
        v_expiry_date UTILIZATOR.DATA_EXP_SUB%TYPE;
    begin
        select DATA_EXP_SUB
        into v_expiry_date
        from UTILIZATOR
        where UTILIZATOR.UTILIZATOR_ID = v_userId;

        if v_expiry_date < SYSDATE then
            v_expired := true;
        end if;

        return v_expired;

    EXCEPTION
        WHEN NO_DATA_FOUND then
            return false;

    END verifica_subscriptie;

    procedure inserare_plata(v_utilizatorId UTILIZATOR.UTILIZATOR_ID%TYPE,
                             v_plataId PLATA.PLATA_ID%TYPE,
                             v_nume PLATA.NUME%TYPE,
                             v_prenume PLATA.PRENUME%TYPE,
                             V_cod PLATA.COD%TYPE,
                             v_data_exp PLATA.DATA_EXP%TYPE,
                             v_cvv PLATA.CVV%TYPE)
    AS

    BEGIN
        insert into PLATA values(v_plataId, v_nume, v_prenume, v_cod, v_data_exp, v_cvv);
        insert into LISTA_CARDURI values(INCREMENTARE_LISTA_CARDURI.nextval, v_plataId, v_utilizatorId);
    END inserare_plata;

    procedure verifica_aniversare(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE) AS
        v_expiry_date UTILIZATOR.DATA_EXP_SUB%TYPE;
        different_date exception;
    BEGIN
        select DATA_EXP_SUB
        into v_expiry_date
        from UTILIZATOR
        where v_userId = UTILIZATOR.UTILIZATOR_ID;

        if to_char(v_expiry_date,'DD/MM/YYYY') = to_char(SYSDATE,'DD/MM/YYYY') then
            v_expiry_date := ADD_MONTHS(v_expiry_date, 1);

            UPDATE UTILIZATOR
            SET DATA_EXP_SUB = v_expiry_date
            WHERE UTILIZATOR_ID = v_userId;
        else
            RAISE different_date;
        end if;

    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('Utilizatorul nu a fost gasit');

        WHEN different_date then
            DBMS_OUTPUT.PUT_LINE('Nu este eligibil pentru bonus');

    END verifica_aniversare;

    procedure toate_filmele(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE) AS
        TYPE row_filme is TABLE OF FILM.DENUMIRE%TYPE;
        TYPE row_actori is TABLE OF ACTOR.NUME%TYPE;
        type row_note is table of FILM.NOTA%TYPE;

        v_filme row_filme;
        v_actori row_actori;
        v_note row_note;

        v_filme_distincte row_filme;

        v_id number := -1;
        user_doesnt_exist exception;
    BEGIN
        select UTILIZATOR_id
        into v_id
        from UTILIZATOR
        where UTILIZATOR_ID = v_userId;

        if v_id = -1 then
            raise user_doesnt_exist;
        end if;

        OPEN filme_actori(v_userId);
        Fetch filme_actori bulk collect into v_filme, v_actori, v_note;
        CLOSE filme_actori;

        -- pentru a obtine filmele distincte
        v_filme_distincte := SET(v_filme);

        for iterator in v_filme_distincte.FIRST..v_filme_distincte.LAST LOOP
            DBMS_OUTPUT.PUT_LINE(v_filme_distincte(iterator));
            end loop;
    EXCEPTION
        WHEN NO_DATA_FOUND then
            DBMS_OUTPUT.PUT_LINE('Userul nu exista');

        WHEN USER_DOESNT_EXIST then
            DBMS_OUTPUT.PUT_LINE('Userul nu exista');
    END toate_filmele;

    procedure toate_serialele(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE) AS
        TYPE row_seriale is TABLE OF SERIAL.DENUMIRE%TYPE;
        TYPE row_actori is TABLE OF ACTOR.NUME%TYPE;

        v_seriale row_seriale;
        v_actori row_actori;

        v_seriale_distincte row_seriale;

        v_id number := -1;
        user_doesnt_exist exception;
    BEGIN
        select UTILIZATOR_id
        into v_id
        from UTILIZATOR
        where UTILIZATOR_ID = v_userId;

        if v_id = -1 then
            raise user_doesnt_exist;
        end if;

        OPEN seriale_actori(v_userId);
        Fetch seriale_actori bulk collect into v_seriale, v_actori;
        CLOSE seriale_actori;

        -- pentru a obtine filmele distincte
        v_seriale_distincte := SET(v_seriale);

        for iterator in v_seriale_distincte.FIRST..v_seriale_distincte.LAST LOOP
            DBMS_OUTPUT.PUT_LINE(v_seriale_distincte(iterator));
            end loop;

    EXCEPTION
        WHEN NO_DATA_FOUND then
            DBMS_OUTPUT.PUT_LINE('Userul nu exista');

        WHEN USER_DOESNT_EXIST then
            DBMS_OUTPUT.PUT_LINE('Userul nu exista');
    END toate_serialele;

    procedure toti_actorii(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE) AS
        TYPE row_filme is TABLE OF FILM.DENUMIRE%TYPE;
        TYPE row_actori is TABLE OF ACTOR.NUME%TYPE;
        type row_note is table of FILM.NOTA%TYPE;

        v_filme row_filme;
        v_actori_filme row_actori;
        v_actori_seriale row_actori;
        v_note row_note;

        v_actori_distincti row_actori;

        v_id number := -1;
        user_doesnt_exist exception;
    BEGIN
        select UTILIZATOR_id
        into v_id
        from UTILIZATOR
        where UTILIZATOR_ID = v_userId;

        if v_id = -1 then
            raise user_doesnt_exist;
        end if;

        OPEN filme_actori(v_userId);
        Fetch filme_actori bulk collect into v_filme, v_actori_filme, v_note;
        CLOSE filme_actori;

        OPEN seriale_actori(v_userId);
        Fetch seriale_actori bulk collect into v_filme, v_actori_seriale;
        CLOSE seriale_actori;

        -- pentru a face o reuniune distincta intre actori
        v_actori_distincti := v_actori_filme MULTISET UNION DISTINCT v_actori_seriale;

        for iterator in v_actori_distincti.FIRST..v_actori_distincti.LAST LOOP
            DBMS_OUTPUT.PUT_LINE(v_actori_distincti(iterator));
            end loop;
    EXCEPTION
        WHEN NO_DATA_FOUND then
            DBMS_OUTPUT.PUT_LINE('Userul nu exista');

        WHEN USER_DOESNT_EXIST then
            DBMS_OUTPUT.PUT_LINE('Userul nu exista');
    END toti_actorii;

    function film_nota_maxima(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE) return film_record AS
        v_film_max film_record;
    BEGIN
        v_film_max.nume := 'Nu exista film peste aceasta nota';
        v_film_max.nota := 0;
        for iterator in filme_actori(v_userId) LOOP
            if v_film_max.nota < iterator.NOTA then
                v_film_max.nota := iterator.NOTA;
                v_film_max.nume := iterator.FILM;
            end if;
            end loop;

        return v_film_max;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('Userul nu exista');
            return NULL;
    END film_nota_maxima;

    function filtreaza_filme(v_userId UTILIZATOR.UTILIZATOR_ID%TYPE,
                             v_nota_min FILM.NOTA%TYPE DEFAULT 0,
                             v_nota_max FILM.NOTA%TYPE DEFAULT 10,
                             v_crescator boolean DEFAULT false,
                             v_descrescator boolean DEFAULT false)
    return cursor_filtrare AS
        nota_min_invalida exception;
        nota_max_invalida exception;
        nota_relatie_invalida exception;
        sortare_invalida exception;

        v_cursor cursor_filtrare;
        v_order_by varchar2(50);
    BEGIN
        if v_nota_min < 0 or v_nota_min > 10 then
            raise nota_min_invalida;
        end if;

        if v_nota_max < 0 or v_nota_max > 10 then
            raise nota_max_invalida;
        end if;

        if v_nota_min > v_nota_max then
            raise nota_relatie_invalida;
        end if;

        if v_crescator = true and v_descrescator = true then
            raise sortare_invalida;
        end if;

        if v_crescator = true then
            v_order_by := 'ORDER BY FILM.NOTA ASC';
        ELSIF v_descrescator = true then
            v_order_by := 'ORDER BY FILM.NOTA DESC';
        end if;

        if v_crescator = false and v_descrescator = false then
            OPEN v_cursor FOR
                SELECT film.*
                FROM film
                JOIN SUBSCRIPTIE_FILM on film.FILM_ID = SUBSCRIPTIE_FILM.FILM_ID
                JOIN SUBSCRIPTIE on SUBSCRIPTIE_FILM.SUBSCRIPTIE_ID = SUBSCRIPTIE.SUBSCRIPTIE_ID
                JOIN UTILIZATOR on SUBSCRIPTIE.SUBSCRIPTIE_ID = UTILIZATOR.SUBSCRIPTIE_ID
                WHERE UTILIZATOR_ID = v_userId and
                      film.nota between v_nota_min and v_nota_max
                || v_order_by;
        end if;

        return v_cursor;

    EXCEPTION
        WHEN nota_min_invalida then
            DBMS_OUTPUT.PUT_LINE('Nota minima invalida');
            return null;

        WHEN nota_max_invalida then
            DBMS_OUTPUT.PUT_LINE('Nota maxima invalida');
            return null;

        WHEN nota_relatie_invalida then
            DBMS_OUTPUT.PUT_LINE('Nota minima este mai mare decat nota maxima');
            return null;

        WHEN sortare_invalida then
            DBMS_OUTPUT.PUT_LINE('Nu se poate sorta si crescator si descrescator');
            return null;

        WHEN NO_DATA_FOUND then
            DBMS_OUTPUT.PUT_LINE('Userul nu exista');
            return null;

    END filtreaza_filme;
END pachet_utilizator;

-- ======== EXCEPTII ========
declare
    v_result boolean;
    v_film_cursor pachet_utilizator.cursor_filtrare;
    v_param_cresc_desc boolean := true;
begin
    -- ===== VERIFICA_SUBSCRIPTIE =====
    -- pentru true ex user id: 111
    -- NO_DATA_FOUND pentru fiecare functioneaza la fel, un utilizator_id care nu exista
    v_result := pachet_utilizator.verifica_subscriptie(111111);
    if v_result = true then
        DBMS_OUTPUT.PUT_LINE('true');
    else
        DBMS_OUTPUT.PUT_LINE('false');
    end if;
    -- ================================

    -- ===== FILTREAZA FILM =====
    v_film_cursor := pachet_utilizator.filtreaza_filme(111,-1,10);
    v_film_cursor := pachet_utilizator.filtreaza_filme(111, 2,11);
    v_film_cursor := pachet_utilizator.filtreaza_filme(111,7,3);
    v_film_cursor := pachet_utilizator.filtreaza_filme(111,2,5,v_param_cresc_desc,v_param_cresc_desc);
    -- ==========================

    pachet_utilizator.toate_filmele(11111);
    pachet_utilizator.toate_serialele(11111);
    pachet_utilizator.toti_actorii(11111);
end;
-- ==========================

begin
    pachet_utilizator.inserare_plata(111,
                                     1010,
                                     'TEST',
                                     'TEST',
                                     123456789,
                                     SYSDATE,
                                     123);
end;

select * from PLATA;
select *
from LISTA_CARDURI
where UTILIZATOR_ID = 111 and PLATA_ID=1010;

declare
    v_film_cursor pachet_utilizator.cursor_filtrare;
    v_film_row FILM%ROWTYPE;
    v_film pachet_utilizator.film_record;
begin
    pachet_utilizator.verifica_aniversare(111);
    pachet_utilizator.toate_filmele(111);
    pachet_utilizator.toate_serialele(111);
    pachet_utilizator.toti_actorii(111);

    v_film := pachet_utilizator.FILM_NOTA_MAXIMA(111);
    DBMS_OUTPUT.PUT_LINE(v_film.nume || ' ' || v_film.nota);

    v_film_cursor := pachet_utilizator.filtreaza_filme(111,11);

    if v_film_cursor is not null then
        for it in v_film_cursor loop
            v_film_row := it;
            DBMS_OUTPUT.PUT_LINE(v_film_row.FILM_ID || ' ' || v_film_row.DENUMIRE || ' ' || v_film_row.NOTA);
            end loop;
    end if;
end;
-- =================================================================

-- TODO: in/out parameters
-- TODO: ALTER PROCEDURE <name> COMPILE;
-- TODO: liniar lists of default parameters for functions or procedures you can use <name> => <value>