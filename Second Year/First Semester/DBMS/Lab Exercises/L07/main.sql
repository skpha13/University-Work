DECLARE
v_nume employees.last_name%TYPE := Initcap('Fay');
FUNCTION f1 RETURN NUMBER IS
    salariu employees.salary%type;
BEGIN
    SELECT salary
    INTO salariu
    FROM employees
    WHERE last_name = v_nume;
    RETURN salariu;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Nu exista angajati cu numele dat');
    WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE('Exista mai multi angajati ' ||
                             'cu numele dat');
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Alta eroare!');
END f1;

BEGIN
    DBMS_OUTPUT.PUT_LINE('Salariul este ' || f1);
    --EXCEPTION
    -- WHEN OTHERS THEN
    -- DBMS_OUTPUT.PUT_LINE('Eroarea are codul = '||SQLCODE
    -- || ' si mesajul = ' || SQLERRM);
END;
/

CREATE OR REPLACE FUNCTION f2_ami(v_nume employees.last_name%TYPE DEFAULT 'Bell')
    RETURN NUMBER IS
    salariu employees.salary%type;
BEGIN
    SELECT salary
    INTO salariu
    FROM employees
    WHERE last_name = v_nume;
    RETURN salariu;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        RAISE_APPLICATION_ERROR(-20000, 'Nu exista angajati cu numele dat');
        return -1;
    WHEN TOO_MANY_ROWS THEN
        RAISE_APPLICATION_ERROR(-20001, 'Exista mai multi angajati cu numele dat');
        return -1;
    WHEN OTHERS THEN
        RAISE_APPLICATION_ERROR(-20002, 'Alta eroare!');
        return -1;
END f2_ami;
/
-- metode de apelare
-- 1. bloc plsql
BEGIN
    DBMS_OUTPUT.PUT_LINE('Salariul este ' || f2_ami);
END;
/
BEGIN
    DBMS_OUTPUT.PUT_LINE('Salariul este ' || f2_ami('King'));
END;
/

-- 2. SQL
SELECT f2_ami
FROM DUAL;

SELECT f2_ami('King')
FROM DUAL;

-- 3. SQL*PLUS CU VARIABILA HOST
VARIABLE nr NUMBER
EXECUTE :nr := f2_ami('Bell');
PRINT nr

DECLARE
    nume employees.last_name%TYPE;
    PROCEDURE p6(rezultat OUT employees.last_name%TYPE,
                 comision IN employees.commission_pct%TYPE := NULL,
                 cod IN employees.employee_id%TYPE := NULL)
        IS
    BEGIN
        IF (comision IS NOT NULL) THEN
            SELECT last_name
            INTO rezultat
            FROM employees
            WHERE commission_pct = comision;
            DBMS_OUTPUT.PUT_LINE('numele salariatului care are
comisionul ' || comision || ' este ' || rezultat);
        ELSE
            SELECT last_name
            INTO rezultat
            FROM employees
            WHERE employee_id = cod;
            DBMS_OUTPUT.PUT_LINE('numele salariatului avand codul ' ||
                                 cod || ' este ' || rezultat);
        END IF;
    END p6;
BEGIN
    p6(nume, 0.4);
    p6(nume, cod=>200);
END;
/

DECLARE
    medie1 NUMBER(10, 2);
    medie2 NUMBER(10, 2);
    FUNCTION medie(v_dept employees.department_id%TYPE)
        RETURN NUMBER IS
        rezultat NUMBER(10, 2);
    BEGIN
        SELECT AVG(salary)
        INTO rezultat
        FROM employees
        WHERE department_id = v_dept;
        RETURN rezultat;
    END;
    FUNCTION medie(v_dept employees.department_id%TYPE,
                   v_job employees.job_id %TYPE)
        RETURN NUMBER IS
        rezultat NUMBER(10, 2);
    BEGIN
        SELECT AVG(salary)
        INTO rezultat
        FROM employees
        WHERE department_id = v_dept
          AND job_id = v_job;
        RETURN rezultat;
    END;
BEGIN
    medie1 := medie(80.02);
    DBMS_OUTPUT.PUT_LINE('Media salariilor din departamentul 80'
        || ' este ' || medie1);
    medie2 := medie(80, 'SA_MAN');
    DBMS_OUTPUT.PUT_LINE('Media salariilor managerilor din'
        || ' departamentul 80 este ' || medie2);
END;
/

CREATE OR REPLACE FUNCTION factorial_ami(n NUMBER)
    RETURN INTEGER IS
BEGIN
    IF (n <= 0) THEN
        RETURN 1;
    ELSE
        RETURN n * factorial_ami(n - 1);
    END IF;
END factorial_ami;
/

-- integer is of size 128 bits => max number to calculate factorial is 33
begin
    DBMS_OUTPUT.PUT_LINE(factorial_ami(33));
end;
/

create table info_ami (
    utilizator varchar2(50),
    data date,
    comanda varchar2(50),
    nr_linii number(3),
    eroare varchar2(50)
);

CREATE OR REPLACE FUNCTION f2_ami(v_nume employees.last_name%TYPE DEFAULT 'Bell')
    RETURN NUMBER IS
    salariu employees.salary%type;
BEGIN

    SELECT salary
    INTO salariu
    FROM employees
    WHERE last_name = v_nume;

    insert into info_ami values (
        sys.LOGIN_USER(),
        sysdate,
        sys.SYSEVENT(),
        1,
        'No error'
    );

    RETURN salariu;

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        insert into info_ami values (
            sys.LOGIN_USER(),
            sysdate,
            sys.SYSEVENT(),
            0,
            'Nu exista angajati cu numele dat'
        );
        RAISE_APPLICATION_ERROR(-20000,'Nu exista angajati cu numele dat');
        return -1;
    WHEN TOO_MANY_ROWS THEN
        insert into info_ami values (
            sys.LOGIN_USER(),
            sysdate,
            sys.SYSEVENT(),
            0,
            'Exista mai multi angajati cu numele dat'
        );
        RAISE_APPLICATION_ERROR(-20001,'Exista mai multi angajati cu numele dat');
        return -1;
    WHEN OTHERS THEN
        insert into info_ami values (
            sys.LOGIN_USER(),
            sysdate,
            sys.SYSEVENT(),
            0,
            'Alta eroare!'
        );
        RAISE_APPLICATION_ERROR(-20002, 'Alta eroare!');
        return -1;
END f2_ami;
/

begin
    DBMS_OUTPUT.PUT_LINE(f2_ami('test'));
end;
/

select * from info_ami;