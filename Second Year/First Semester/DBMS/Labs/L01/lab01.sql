select table_name
from user_tables;

-- spool = genereaza automat fisiere (comenzi create, insert, drop)

set feedback off
spool 'D:\UNI CODE\Univeristy-Work\Second Year\First Semester\DBMS\Labs\L01\commands.sql'
select 'DROP TABLE ' || table_name || ';'
from user_tables;
spool off;
