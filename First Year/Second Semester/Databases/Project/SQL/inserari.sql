insert all
    into PLATA(plata_id, nume, prenume, cod, data_exp, cvv) values (1001,'Ray','Daniel',4305502398704683,'12/06/2026',756)
    into PLATA(plata_id, nume, prenume, cod, data_exp, cvv) values (1002,'Hartley','Savannah',5294873964130870,'25/05/2024',343)
    into PLATA(plata_id, nume, prenume, cod, data_exp, cvv) values (1003,'Duncan','Thomas',378025662328088,'02/07/2025',988)
    into PLATA(plata_id, nume, prenume, cod, data_exp, cvv) values (1004,'Munoz','Benjamin',4837805598641283,'10/05/2028',693)
    into PLATA(plata_id, nume, prenume, cod, data_exp, cvv) values (1005,'Stephenson','James',6011268343169923,'08/11/2027',405)
    into PLATA(plata_id, nume, prenume, cod, data_exp, cvv) values (1006,'Howard','Joshua',4929293360545801,'28/10/2026',655)
    into PLATA(plata_id, nume, prenume, cod, data_exp, cvv) values (1007,'Holland','Scarlet',4539982107813850,'03/02/2024',234)
    into PLATA(plata_id, nume, prenume, cod, data_exp, cvv) values (1008,'Martin','Samuel',5172220647992689,'13/06/2023',871)
    into PLATA(plata_id, nume, prenume, cod, data_exp, cvv) values (1009,'Christensen','Ava',5465157413570982,'21/08/2028',990)
select 'worked' from dual;

insert all
    into SUBSCRIPTIE(subscriptie_id, tip, cost) values (55245,'basic',5)
    into SUBSCRIPTIE(subscriptie_id, tip, cost) values (39959,'standard',10)
    into SUBSCRIPTIE(subscriptie_id, tip, cost) values (94030,'normal',15)
    into SUBSCRIPTIE(subscriptie_id, tip, cost) values (67933,'premium',20)
    into SUBSCRIPTIE(subscriptie_id, tip, cost) values (78477,'ultimate',25)
select 'worked' from dual;

insert all
    into UTILIZATOR(utilizator_id, subscriptie_id, plata_id, porecla, mail, parola, data_exp_sub) values (101,55245,1001,'NovaFire','handsomeDaniel@gmail.com','RD_2003','14/06/2023')
    into UTILIZATOR(utilizator_id, subscriptie_id, plata_id, porecla, mail, parola, data_exp_sub) values (102,55245,1002,'Dingo','din.go@yahoo.com','39hsrda9','05/05/2023')
    into UTILIZATOR(utilizator_id, subscriptie_id, plata_id, porecla, mail, parola, data_exp_sub) values (103,55245,1003,'Zed999','duncan_thomas@yahoo.com','Zed_MY_life','27/05/2023')
    into UTILIZATOR(utilizator_id, subscriptie_id, plata_id, porecla, mail, parola, data_exp_sub) values (104,39959,1004,'Lulu','mun.benj@yahoo.com','Aida_2022','22/05/2023')
    into UTILIZATOR(utilizator_id, subscriptie_id, plata_id, porecla, mail, parola, data_exp_sub) values (105,39959,1005,'Kirby','stepehnson14@gmail.com','kirby1306','14/05/2023')
    into UTILIZATOR(utilizator_id, subscriptie_id, plata_id, porecla, mail, parola, data_exp_sub) values (106,39959,1006,'Joshuuuuua','josh.h@gmail.com','netflixPassword','18/05/2023')
    into UTILIZATOR(utilizator_id, subscriptie_id, plata_id, porecla, mail, parola, data_exp_sub) values (107,39959,1007,'happydog1234','happy.dog123@yahoo.com','dogggsAREsweet','10/06/2023')
    into UTILIZATOR(utilizator_id, subscriptie_id, plata_id, porecla, mail, parola, data_exp_sub) values (108,67933,1008,'RoninHack','martin_net@yahoo.com','genshin001','01/06/2023')
    into UTILIZATOR(utilizator_id, subscriptie_id, plata_id, porecla, mail, parola, data_exp_sub) values (109,67933,1009,'Matoka26','avaiscool@gmail.com','Mihai1234568','08/06/2023')
    into UTILIZATOR(utilizator_id, subscriptie_id, plata_id, porecla, mail, parola, data_exp_sub) values (110,78477,1001,'skpha','ray.ana@gmail.com','VulturViteaz','15/06/2023')
select 'worked' from dual;

insert all
    into DIRECTOR(director_id, nume, prenume, data_nastere, nota) VALUES (100001,'Tanner','Stella','28/12/1992',7.5)
    into DIRECTOR(director_id, nume, prenume, data_nastere, nota) VALUES (100002,'Summers','Armand','23/04/2000',8)
    into DIRECTOR(director_id, nume, prenume, data_nastere, nota) VALUES (100003,'Batlle','Ingrid','25/10/1999',9.2)
    into DIRECTOR(director_id, nume, prenume, data_nastere, nota) VALUES (100004,'Gordon','Boris','02/06/2001',6.75)
    into DIRECTOR(director_id, nume, prenume, data_nastere, nota) VALUES (100005,'Mcintosh','Julian','14/10/1996',9.6)
select 'worked' from dual;

insert all
    into ROL(rol_id, nume, descriere, importanta) VALUES (111,'Principal','Va juca cel mai mult',10)
    into ROL(rol_id, nume, descriere, importanta) VALUES (112,'Secundar','Va participa destul de des',9.5)
    into ROL(rol_id, nume, descriere, importanta) VALUES (113,'Erou','Cel care ii va salva pe toti',9.75)
    into ROL(rol_id, nume, descriere, importanta) VALUES (114,'Raufacator','Cel care va incerca sa ii distruga pe toti',8.8)
    into ROL(rol_id, nume, descriere, importanta) VALUES (115,'Fundal','Doar va aparea pe fundalul filmului pentru a popula scena cu oameni',4.5)
select 'worked' from dual;

select * from ROL;

