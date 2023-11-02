-- pentru fiecare Serial cu id-ul in (1,3,6) afisati numele tutor
-- episoadelor care apartin

-- cursor clasic
declare
    v_id_ser SERIAL.serial_id%type;
    v_nume_ser SERIAL.denumire%type;
    v_nume_episod varchar2(50);
    v_areEpisod number(1) := 0;

    CURSOR seriale IS
        select SERIAL_ID, DENUMIRE
        from SERIAL
        WHERE SERIAL_ID IN (1,3,6);

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

-- ciclu cursor
declare
    v_areEpisod number(1) := 0;

    CURSOR seriale IS
        select SERIAL_ID, DENUMIRE
        from SERIAL
        WHERE SERIAL_ID IN (1,3,6);

    CURSOR episod(id number) IS
        select DENUMIRE
        from EPISOD
        where SERIAL_ID = id;
begin
    for serial in seriale loop
        v_areEpisod := 0;
        DBMS_OUTPUT.PUT_LINE('Serialul: ' || serial.DENUMIRE);
        for ep in episod(serial.SERIAL_ID) loop
            v_areEpisod := 1;
            DBMS_OUTPUT.PUT_LINE('  ' || ep.denumire);
            end loop;
        if v_areEpisod = 0 then DBMS_OUTPUT.PUT_LINE('  Nu are episoade');
        end if;
        end loop;
end;
/

-- ciclu cursor cu subcereri
declare
    v_areEpisod number(1) := 0;
begin
    for serial in (select SERIAL_ID, DENUMIRE
                  from SERIAL
                  WHERE SERIAL_ID IN (1, 3, 6))
    loop
        v_areEpisod := 0;
        DBMS_OUTPUT.PUT_LINE('Serialul: ' || serial.DENUMIRE);
        for ep in (select DENUMIRE
                   from EPISOD
                   where SERIAL_ID = serial.SERIAL_ID)
        loop
            v_areEpisod := 1;
            DBMS_OUTPUT.PUT_LINE('  ' || ep.denumire);
            end loop;
        if v_areEpisod = 0 then DBMS_OUTPUT.PUT_LINE('  Nu are episoade');
        end if;
        end loop;
end;

-- expresii cursor
declare
    TYPE refcursor is REF CURSOR;
    CURSOR seriale IS
    select DENUMIRE,
           CURSOR (select DENUMIRE
                   from EPISOD
                   where SERIAL_ID = serial.SERIAL_ID)
    from SERIAL
    where SERIAL_ID in (1,3,6);
    v_nume_serial SERIAL.denumire%type;
    v_nume_ep EPISOD.denumire%type;
    v_cursor refcursor;
    v_areEpisod number(1) := 0;
begin
    open seriale;
    loop
        fetch seriale into v_nume_serial, v_cursor;
        exit when seriale%notfound;
        v_areEpisod := 0;
        DBMS_OUTPUT.PUT_LINE('Serialul: ' || v_nume_serial);

        loop
            fetch v_cursor into v_nume_ep;
            exit when v_cursor%notfound;
            v_areEpisod := 1;
            DBMS_OUTPUT.PUT_LINE('  ' || v_nume_ep);
        end loop;

        if v_areEpisod = 0 then DBMS_OUTPUT.PUT_LINE('  Nu are episoade');
        end if;
    end loop;
end;
/