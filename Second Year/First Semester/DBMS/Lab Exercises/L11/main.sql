-- ordine apelare trigger:
-- instructiune before, linie before, linie after, instructiune after

CREATE OR REPLACE TRIGGER trig1_ami
    BEFORE
INSERT OR
UPDATE OR
DELETE
ON emp_ami
BEGIN
    IF (TO_CHAR(SYSDATE, 'D') = 1)
        OR (TO_CHAR(SYSDATE, 'HH24') NOT BETWEEN 8 AND 20)
    THEN
        RAISE_APPLICATION_ERROR(-20001, 'tabelul nu poate fi actualizat');
    END IF;
END;
/
DROP TRIGGER trig1_ami;

CREATE OR REPLACE TRIGGER trig21_ami
    BEFORE
UPDATE OF salary
ON emp_ami
    FOR EACH ROW
BEGIN
--     nu putem apela cu numele tabelului, ex: emp_ami.salary
    IF (:NEW.salary < :OLD.salary) THEN
        RAISE_APPLICATION_ERROR(-20002, 'salariul nu poate fi micsorat');
    END IF;
END;
/
UPDATE emp_ami
SET salary = salary-100;
DROP TRIGGER trig21_ami;

