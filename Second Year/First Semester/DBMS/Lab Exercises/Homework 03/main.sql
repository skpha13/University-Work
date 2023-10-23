-- tipul subscriptiei cu cele mai multe filme
DECLARE
v_subscriptie varchar2(50);
begin
    select s.tip
    into v_subscriptie
    from SUBSCRIPTIE s, SUBSCRIPTIE_FILM sf
    where s.SUBSCRIPTIE_ID = sf.SUBSCRIPTIE_ID
    group by s.tip
    having count(*) = (
        select max(count(*))
        from SUBSCRIPTIE_FILM s2
        group by s2.SUBSCRIPTIE_ID
        );
    DBMS_OUTPUT.PUT_LINE('Subscriptia ' || v_subscriptie);

exception
    when too_many_rows then DBMS_OUTPUT.PUT_LINE('There are too many subscriptions with same count of movies');
end;
/

-- determinare epoca filmului dat ca id de la tastatura
declare
    v_film_id number(6);
    v_an number(5);
    v_epoca varchar2(50);
begin
    v_film_id := &v_film_id;
    select to_char(DATA_APARITIE,'YYYY')
    into v_an
    from FILM
    where FILM_ID = v_film_id;

    if v_an >= 2000
        then v_epoca := 'New Era Movie';
    elsif v_an >= 1980
        then v_epoca := 'Old Era Movie';
    else v_epoca := 'Ancient Era Movie';
    end if;

    DBMS_OUTPUT.PUT_LINE('Era of movie with id: ' || v_film_id || ' is ' || v_epoca);
end;
/

-- cod actor, film , si un bonus si sa se mareasca salariul cu noul bonus
-- sa se mute actorul in filmul nou cu salariul marit cu bonusul dat
-- daca a mers sa se afiseze "Actualizare realizata" altfel "Nu exista un actor cu acest cod"
DEFINE v_actor_id = 19
DEFINE v_film_id = 1
DEFINE v_bonus = 1000
declare
    v_actor_id ACTOR.ACTOR_ID%type := &v_actor_id;
    v_film_id FILM.FILM_ID%type := &v_film_id;
    v_bonus NUMBER(6) := &v_bonus;
    v_rol_jucat_id ROL_JUCAT.FILM_ROL_ACTOR_ID%type;
begin
    select FILM_ROL_ACTOR_ID
    into v_rol_jucat_id
    from ROL_JUCAT
    where FILM_ID = v_film_id and ACTOR_ID = v_actor_id;

    update ROL_JUCAT
    set ACTOR_ID = v_actor_id,
        SALARIU = SALARIU + v_bonus
    where FILM_ROL_ACTOR_ID = v_rol_jucat_id;
    if sql%rowcount = 0 then DBMS_OUTPUT.PUT_LINE('Nu exista un actor cu acest id');
    else DBMS_OUTPUT.PUT_LINE('Actualizare realizata');
    end if;

exception
    when no_data_found then DBMS_OUTPUT.PUT_LINE('Nu au fost gasite date');
end;
/
ROLLBACK;