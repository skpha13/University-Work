-- type = ia tipul unei variable, ajuta la string-uri/numere cu o anumita precizie
-- exceptii des intalnite: too many row, no data found
BEGIN
DBMS_OUTPUT.PUT_LINE('Invat PL/SQL');
END;
/

DECLARE
  v_dep departments.department_name%TYPE;
BEGIN
  SELECT department_name
  INTO   v_dep
  FROM   employees e, departments d
  WHERE  e.department_id=d.department_id
  GROUP BY department_name
  HAVING COUNT(*) <> (SELECT MAX(COUNT(*))
                     FROM   emp0_prof
                     GROUP BY department_id);
  DBMS_OUTPUT.PUT_LINE('Departamentul '|| v_dep);

exception
  when too_many_rows then
      DBMS_OUTPUT.PUT_LINE('mai multe linii!');
  when no_data_found then
      DBMS_OUTPUT.PUT_LINE('nicio multe linii!');
END;
/

-- variabila de legatur :var, adica variabila globala

DECLARE
    v_dep departments.department_name%TYPE;
    v_numar number;
BEGIN
    SELECT department_name, count(*)
    INTO v_dep,v_numar
    FROM employees e, departments d
    WHERE e.department_id=d.department_id
    GROUP BY department_name
    HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                        FROM employees
                        GROUP BY department_id);
    DBMS_OUTPUT.PUT_LINE('Departamentul '|| v_dep || ' ' || v_numar);
END;
/

SET VERIFY OFF
DECLARE
    v_cod employees.employee_id%TYPE:=&p_cod;
    v_bonus NUMBER(8);
    v_salariu_anual NUMBER(8);
BEGIN
    SELECT salary*12 INTO v_salariu_anual
    FROM employees
    WHERE employee_id = v_cod;
    IF v_salariu_anual>=200001
        THEN v_bonus:=20000;
    ELSIF v_salariu_anual BETWEEN 100001 AND 200000
        THEN v_bonus:=10000;
    ELSE v_bonus:=5000;
END IF;
    DBMS_OUTPUT.PUT_LINE('Bonusul este ' || v_bonus);
END;
/
SET VERIFY ON

DECLARE
    numar number(3):=100;
    mesaj1 varchar2(255):='text 1';
    mesaj2 varchar2(255):='text 2';
BEGIN
DECLARE
    numar number(3):=1;
    mesaj1 varchar2(255):='text 2';
    mesaj2 varchar2(255):='text 3';
BEGIN
    numar:=numar+1;
    mesaj2:=mesaj2||' adaugat in sub-bloc';
    DBMS_OUTPUT.PUT_LINE(numar || ' ' || mesaj1 || ' ' || mesaj2);
END;
    numar:=numar+1;
    mesaj1:=mesaj1||' adaugat un blocul principal';
    mesaj2:=mesaj2||' adaugat in blocul principal';
    DBMS_OUTPUT.PUT_LINE(numar || ' ' || mesaj1 || ' ' || mesaj2);
END;
/

with days as
    (select to_date('01.10.2023', 'DD.MM.YYYY') + level - 1 day_date
     from dual
    connect by level <= to_char(LAST_DAY(to_date('01.10.2023', 'DD.MM.YYYY')), 'DD'))
select to_char(d.day_date, 'dd-mm-yyyy'),
    (select count(*) from rental r where to_char(r.book_date, 'dd-mm-yyyy') like to_char(d.day_date, 'dd-mm-yyyy')) cnt
from days d;

create table octombrie_ami (
    id number(6) primary key,
    data date
);

declare
    aux_data date := '01.OCT.2023';
begin
    for count in 0..30 loop
        insert into octombrie_ami(id,data) values (count,aux_data + count);
        end loop;
end;
/

select * from octombrie_ami;

-- ex6 obligatoriu, 3,4,5 optionale