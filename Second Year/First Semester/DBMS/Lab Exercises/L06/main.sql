-- ===== ex 4 =====
declare
    CURSOR angajat(idEmployee number) IS
        select FIRST_NAME, SALARY
        from EMPLOYEES
        where EMPLOYEE_ID = idEmployee or idEmployee is null;

    type tab_nume is table of varchar2(20) index by pls_integer;
    type tab_sal is table of number(8,2) index by pls_integer;

    v_nume angajat%rowtype;
    v_tab_nume tab_nume;
    v_tab_sal tab_sal;
begin
    OPEN angajat(111);
    LOOP
        FETCH angajat into v_nume;
        EXIT when angajat%notfound;
        DBMS_OUTPUT.PUT_LINE(v_nume.FIRST_NAME || ' ' || v_nume.SALARY);
    end loop;
    CLOSE angajat;

    OPEN angajat(111);
    fetch angajat bulk collect into v_tab_nume, v_tab_sal;
    CLOSE angajat;

    for i in v_tab_nume.first..v_tab_nume.last loop
        DBMS_OUTPUT.PUT_LINE(v_tab_nume(i) || ' ' || v_tab_sal(i));
        end loop;
end;
/
-- ===================================