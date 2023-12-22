-- Definiti un pachet care sa obtina serialul cu durata maxima
-- Si lista serialelor care au durata mai mica decat cea maxima

create or replace package info as
    function durataSeriale(mxDurata number) return sys_refcursor;
    function durataMaxima return number;
end info;

create or replace package body info as
    function durataMaxima return number is
        v_maxim number;
    begin
        select max(sum(EPISOD.DURATA))
        into v_maxim
        from SERIAL
        join EPISOD on SERIAL.SERIAL_ID = EPISOD.SERIAL_ID
        group by EPISOD.SERIAL_ID;

        return v_maxim;
    end durataMaxima;

    function durataSeriale(mxDurata number) return sys_refcursor is
        v_cursor sys_refcursor;
    begin
        open v_cursor for
            select s.*
            from SERIAL s
            join (
                select e.SERIAL_ID, sum(e.DURATA) as durata
                from EPISOD e
                group by e.SERIAL_ID
            ) infoSerial on s.SERIAL_ID = infoSerial.SERIAL_ID
            where infoSerial.durata <= mxDurata;

        return v_cursor;
    end durataSeriale;
end info;

declare
    v_max number;
    v_cursor sys_refcursor;
    v_serial_info SERIAL%rowtype;
begin
    v_max := info.durataMaxima();
    v_cursor := info.durataSeriale(v_max);

    loop
        fetch v_cursor into v_serial_info;
        exit when v_cursor%notfound;
        DBMS_OUTPUT.PUT_LINE(v_serial_info.SERIAL_ID || ' ' || v_serial_info.DENUMIRE);
    end loop;
    close v_cursor;
end;