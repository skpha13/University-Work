-- ===== EX 2 =====
-- pentru o subscriptie (al carei nume este dat)
-- sa se obtina nr de filme pe care il are

create or replace function nrFilme(v_nume_subscriptie SUBSCRIPTIE.TIP%TYPE) return number as
    v_subscriptie_id SUBSCRIPTIE.subscriptie_id%type;
    v_countFilme number(3) := 0;
begin
    select unique SUBSCRIPTIE_ID
    into v_subscriptie_id
    from SUBSCRIPTIE
    where lower(TIP) = lower(v_nume_subscriptie);

    select count(*)
    into v_countFilme
    from FILM
    join SUBSCRIPTIE_FILM on FILM.FILM_ID = SUBSCRIPTIE_FILM.FILM_ID
    where SUBSCRIPTIE_FILM.SUBSCRIPTIE_ID = v_subscriptie_id;

    return v_countFilme;
exception
    WHEN NO_DATA_FOUND THEN
        raise_application_error(-20001, 'Nu exista subscriptie cu numele dat');
        return -1;

    WHEN TOO_MANY_ROWS THEN
        raise_application_error(-20002, 'Prea multe subscriptii cu acelasi nume');
        return -1;
end;
/

-- corect
begin
    DBMS_OUTPUT.PUT_LINE(nrFilme('basic'));
end;

-- no data found
begin
    DBMS_OUTPUT.PUT_LINE(nrFilme('test'));
end;

-- too many rows
begin
    DBMS_OUTPUT.PUT_LINE(nrFilme('ultimate'));
end;
-- ===============================

-- ===== EX4 =====
create or replace procedure nrFilmeProc(v_nume_subscriptie SUBSCRIPTIE.TIP%TYPE) AS
    v_subscriptie_id SUBSCRIPTIE.subscriptie_id%type;
    v_countFilme number(3) := 0;
begin
    select unique SUBSCRIPTIE_ID
    into v_subscriptie_id
    from SUBSCRIPTIE
    where lower(TIP) = lower(v_nume_subscriptie);

    select count(*)
    into v_countFilme
    from FILM
    join SUBSCRIPTIE_FILM on FILM.FILM_ID = SUBSCRIPTIE_FILM.FILM_ID
    where SUBSCRIPTIE_FILM.SUBSCRIPTIE_ID = v_subscriptie_id;

    DBMS_OUTPUT.PUT_LINE(v_countFilme);

exception
    WHEN NO_DATA_FOUND THEN
        raise_application_error(-20001, 'Nu exista subscriptie cu numele dat');

    WHEN TOO_MANY_ROWS THEN
        raise_application_error(-20002, 'Prea multe subscriptii cu acelasi nume');
end;
/

-- corect
begin
    nrFilmeProc('basic');
end;

-- no data found
begin
    nrFilmeProc('test');
end;

-- too many rows
begin
    nrFilmeProc('ultimate');
end;
-- ===============================