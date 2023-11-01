DECLARE
    v_cod  employees.employee_id%TYPE;
    v_nume employees.last_name%TYPE;
    v_nr   NUMBER(4);
    CURSOR c IS
        SELECT sef.employee_id    cod,
               MAX(sef.last_name) nume,
               count(*)           nr
        FROM employees sef,
             employees ang
        WHERE ang.manager_id = sef.employee_id
        GROUP BY sef.employee_id
        ORDER BY nr DESC;
BEGIN
    OPEN c;
    LOOP
        FETCH c INTO v_cod,v_nume,v_nr;
        EXIT WHEN c%ROWCOUNT > 3 OR c%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('Managerul ' || v_cod ||
                             ' avand numele ' || v_nume ||
                             ' conduce ' || v_nr || ' angajati');
    END LOOP;
    CLOSE c;
END;
/

SELECT sef.employee_id    cod,
       MAX(sef.last_name) nume,
       count(*)           nr
FROM employees sef,
     employees ang
WHERE ang.manager_id = sef.employee_id
GROUP BY sef.employee_id
ORDER BY nr DESC;

select * from Jobs;

declare
    v_existsEmployees number(1) := 0;
    v_numarOrdine number(2);
    v_lunara number(6) := 0;
begin
    for v_job in (select JOB_TITLE, JOB_ID
                  from JOBS)
    loop
        DBMS_OUTPUT.PUT_LINE('JOB: ' || v_job.JOB_TITLE);
        DBMS_OUTPUT.NEW_LINE();
        v_existsEmployees := 0;
        v_numarOrdine := 0;
        v_lunara := 0;
        for v_emp in (select LAST_NAME, SALARY
                        from EMPLOYEES
                        where JOB_ID = v_job.JOB_ID)
        loop
            v_existsEmployees := 1;
            v_lunara := v_lunara + v_emp.SALARY;
            DBMS_OUTPUT.PUT_LINE('  ' || v_numarOrdine || ': ' || v_emp.LAST_NAME || ' ' || v_emp.SALARY);
            v_numarOrdine := v_numarOrdine + 1;
            end loop;
        if v_existsEmployees = 0 then DBMS_OUTPUT.PUT_LINE('  NU are employees acest JOB');
        else
            DBMS_OUTPUT.PUT_LINE('Numar angajati: ' || (v_numarOrdine));
            DBMS_OUTPUT.PUT_LINE('Valoare lunara: ' || v_lunara);
            DBMS_OUTPUT.PUT_LINE('Valoare medie: ' || v_lunara/(v_numarOrdine));
            end if;
        end loop;
end;