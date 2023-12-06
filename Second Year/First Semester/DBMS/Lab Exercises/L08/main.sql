-- daca vrem o functie dintr un pachet apelare: <nume_pache>.<nume_functie>
-- daca avem insert uri sau update uri sau delete uri in pachete trebuie sa dam si commit

DECLARE
-- paramentrii de tip OUT pt procedura GET_LINE
    linie1 VARCHAR2(255);
    stare1 INTEGER;
    linie2 VARCHAR2(255);
    stare2 INTEGER;
    linie3 VARCHAR2(255);
    stare3 INTEGER;
    v_emp  employees.employee_id%TYPE;
    v_job  employees.job_id%TYPE;
    v_dept employees.department_id%TYPE;
BEGIN
    SELECT employee_id, job_id, department_id
    INTO v_emp,v_job,v_dept
    FROM employees
    WHERE last_name = 'Lorentz';
    -- se introduce o linie in buffer fara caracter
-- de terminare linie
    DBMS_OUTPUT.PUT(' 1 ' || v_emp || ' ');
    -- se incearca extragerea liniei introdusa
-- in buffer si starea acesteia
    DBMS_OUTPUT.GET_LINE(linie1, stare1);
-- se depunde informatie pe aceeasi linie in buffer
    DBMS_OUTPUT.PUT(' 2 ' || v_job || ' ');
    -- se inchide linia depusa in buffer si se extrage
-- linia din buffer
    DBMS_OUTPUT.NEW_LINE;
    DBMS_OUTPUT.GET_LINE(linie2, stare2);
    -- se introduc informatii pe aceeasi linie
-- si se afiseaza informatia
    DBMS_OUTPUT.PUT_LINE(' 3 ' || v_emp || ' ' || v_job);
    DBMS_OUTPUT.GET_LINE(linie3, stare3);
-- se afiseaza ceea ce s-a extras
    DBMS_OUTPUT.PUT_LINE('linie1 = ' || linie1 ||
                         '; stare1 = ' || stare1);
    DBMS_OUTPUT.PUT_LINE('linie2 = ' || linie2 ||
                         '; stare2 = ' || stare2);
    DBMS_OUTPUT.PUT_LINE('linie3 = ' || linie3 ||
                         '; stare3 = ' || stare3);
END;
/

DECLARE
-- parametru de tip OUT pentru NEW_LINES
-- tablou de siruri de caractere
    linii    DBMS_OUTPUT.CHARARR;
-- paramentru de tip IN OUT pentru NEW_LINES
    nr_linii INTEGER;
    v_emp    employees.employee_id%TYPE;
    v_job    employees.job_id%TYPE;
    v_dept   employees.department_id%TYPE;
BEGIN
    SELECT employee_id, job_id, department_id
    INTO v_emp,v_job,v_dept
    FROM employees
    WHERE last_name = 'Lorentz';
-- se mareste dimensiunea bufferului
    DBMS_OUTPUT.ENABLE(1000000);
    DBMS_OUTPUT.PUT(' 1 ' || v_emp || ' ');
    DBMS_OUTPUT.PUT(' 2 ' || v_job || ' ');
    DBMS_OUTPUT.NEW_LINE;
    DBMS_OUTPUT.PUT_LINE(' 3 ' || v_emp || ' ' || v_job);
    DBMS_OUTPUT.PUT_LINE(' 4 ' || v_emp || ' ' ||
                         v_job || ' ' || v_dept);
-- se afiseaza ceea ce s-a extras
    nr_linii := 4;
    DBMS_OUTPUT.GET_LINES(linii, nr_linii);
    DBMS_OUTPUT.put_line('In buffer sunt ' ||
                         nr_linii || ' linii');
    FOR i IN 1..nr_linii
        LOOP
            DBMS_OUTPUT.put_line(linii(i));
        END LOOP;
    -- nr_linii := 4;
-- DBMS_OUTPUT.GET_LINES(linii,nr_linii);
-- DBMS_OUTPUT.put_line('Acum in buffer sunt '||
--     nr_linii || ' linii');
    -- FOR i IN 1..nr_linii LOOP
-- DBMS_OUTPUT.put_line(linii(i));
-- END LOOP;
--
---- DBMS_OUTPUT.disable;
---- DBMS_OUTPUT.enable;
----
---- nr_linii := 4;
---- DBMS_OUTPUT.GET_LINES(linii,nr_linii);
---- DBMS_OUTPUT.put_line('Acum in buffer sunt '||
---- nr_linii || ' linii');
END;
/

declare
    v_file UTL_FILE.FILE_TYPE;
    director Varchar2(255) := 'D:\UNI CODE\Univeristy-Work\Second Year\First Semester\DBMS\Lab Exercises\L08';
begin
    v_file := UTL_FILE.FOPEN(director, 'test.txt', 'w');
    UTL_FILE.PUTF(v_file, 'test\n');
    UTL_FILE.NEW_LINE(v_file);

    UTL_FILE.FCLOSE(v_file);
end;