--      Un trigger care va actualiza automat campurile din informatiile unui serial
-- atunci cand se insereaza/sterge/updateaza un episod

create table info_serial (
    serial_id number(6),
    -- cate episoade are in total serialul
    numar_episoade number(3),
    -- suma duratei fiecarui episod
    durata_totala number(5)
);

INSERT INTO info_serial (serial_id, numar_episoade, durata_totala)
SELECT s.serial_id, COUNT(e.episod_id) AS numar_episoade, SUM(e.durata) AS durata_totala
FROM serial s
JOIN episod e ON s.serial_id = e.serial_id
GROUP BY s.serial_id;

CREATE OR REPLACE PROCEDURE update_info(
    v_id info_serial.SERIAL_ID%TYPE,
    v_count integer,
    v_durata info_serial.durata_totala%TYPE
) AS
BEGIN
    UPDATE info_serial
    SET numar_episoade = numar_episoade + v_count,
        durata_totala  = durata_totala + v_durata
    WHERE serial_id = v_id;
END;
/

create or replace trigger update_info_serial
    AFTER INSERT OR DELETE OR UPDATE ON EPISOD
    FOR EACH ROW
BEGIN
    IF DELETING THEN
        update_info(:OLD.SERIAL_ID, -1, -1*:OLD.DURATA);
    elsif UPDATING THEN
        update_info(:OLD.SERIAL_ID, 0, :NEW.DURATA - :OLD.DURATA);
    else
        update_info(:NEW.SERIAL_ID, 1, :NEW.DURATA);
    end if;
end;

select * from info_serial;

select * from EPISOD;

insert into EPISOD values (21, 6, 'Extreme', 4, 12);

delete from EPISOD where EPISOD_ID = 21;

update EPISOD set durata = 100 where EPISOD_ID = 20;