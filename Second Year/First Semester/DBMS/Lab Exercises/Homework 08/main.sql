-- Sa se afiseze numarul de seriale care au durata mai mare decat o valoare data.
-- Daca exista => exceptie

declare
    v_count integer := 0;
    v_val integer := 100;
    v_durata integer;
    no_data exception;
    CURSOR durata IS
        select sum(durata)
        from SERIAL
        join EPISOD on SERIAL.SERIAL_ID = EPISOD.SERIAL_ID
        group by EPISOD.SERIAL_ID;
begin
    OPEN durata;
    LOOP
        fetch durata into v_durata;
        exit when durata%notfound;
        if v_durata > v_val then
            v_count := v_count + 1;
        end if;
    end loop;
    CLOSE durata;
    if v_count = 0 then
        raise no_data;
    else
        DBMS_OUTPUT.PUT_LINE('Numar seriale: ' || v_count);
    end if;

EXCEPTION
    When no_data then
        DBMS_OUTPUT.PUT_LINE('Nu exista seriale');
    when others then
        DBMS_OUTPUT.PUT_LINE('Eroare necunoscuta intalnita');
end;