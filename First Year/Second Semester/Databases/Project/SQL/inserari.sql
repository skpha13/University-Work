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

insert all
    into ACTOR(actor_id, nume, prenume, data_nastere, salariu) VALUES (10, 'Smith', 'John', '13/05/1980', 5000)
    into ACTOR(actor_id, nume, prenume, data_nastere, salariu) VALUES (11, 'Doe', 'Jane', '20/08/1990', 6000)
    into ACTOR(actor_id, nume, prenume, data_nastere, salariu) VALUES (12, 'Garcia', 'Maria', '15/04/1985', 4500)
    into ACTOR(actor_id, nume, prenume, data_nastere, salariu) VALUES (13, 'Kim', 'Soo', '01/10/1995', 5500)
    into ACTOR(actor_id, nume, prenume, data_nastere, salariu) VALUES (14, 'Wang', 'Lei', '22/07/1988', 7000)
    into ACTOR(actor_id, nume, prenume, data_nastere, salariu) VALUES (15, 'Singh', 'Rajesh', '10/12/1992', 4800)
    into ACTOR(actor_id, nume, prenume, data_nastere, salariu) VALUES (16, 'Lee', 'Ji-hye', '28/02/1987', 6500)
    into ACTOR(actor_id, nume, prenume, data_nastere, salariu) VALUES (17, 'Baker', 'William', '18/09/1983', 5200)
    into ACTOR(actor_id, nume, prenume, data_nastere, salariu) VALUES (18, 'Khan', 'Aamir', '14/03/1965', 9000)
    into ACTOR(actor_id, nume, prenume, data_nastere, salariu) VALUES (19, 'Santos', 'Pedro', '05/01/1998', 4000)
select 'worked' from dual;

insert all
    into FILM(film_id, director_id, denumire, nota, data_aparitie) VALUES (1, 100001, 'The Shawshank Redemption', 9.3, '14/09/1994')
    into FILM(film_id, director_id, denumire, nota, data_aparitie) VALUES (2, 100002, 'The Godfather', 9.2, '24/03/1972')
    into FILM(film_id, director_id, denumire, nota, data_aparitie) VALUES (3, 100003, 'The Dark Knight', 9.0, '14/07/2008')
    into FILM(film_id, director_id, denumire, nota, data_aparitie) VALUES (4, 100003, 'Schindler''s List', 8.9, '30/11/1993') -- 2 '' pentru a avea doar unul
    into FILM(film_id, director_id, denumire, nota, data_aparitie) VALUES (5, 100003, 'The Lord of the Rings: The Return of the King', 8.9, '17/12/2003')
    into FILM(film_id, director_id, denumire, nota, data_aparitie) VALUES (6, 100001, 'Pulp Fiction', 8.9, '21/05/1994')
    into FILM(film_id, director_id, denumire, nota, data_aparitie) VALUES (7, 100004, 'The Good, the Bad and the Ugly', 8.8, '23/12/1966')
    into FILM(film_id, director_id, denumire, nota, data_aparitie) VALUES (8, 100005, 'Fight Club', 8.8, '15/10/1999')
    into FILM(film_id, director_id, denumire, nota, data_aparitie) VALUES (9, 100004, 'Forrest Gump', 8.8, '06/07/1994')
    into FILM(film_id, director_id, denumire, nota, data_aparitie) VALUES (10, 100002, 'Inception', 8.7, '13/07/2010')
select 'worked' from dual;

insert all
    into SERIAL(serial_id, denumire, nota, data_aparitie) VALUES (1, 'Breaking Bad', 9.5, '20/01/2008')
    into SERIAL(serial_id, denumire, nota, data_aparitie) VALUES (2, 'Game of Thrones', 9.3, '17/04/2011')
    into SERIAL(serial_id, denumire, nota, data_aparitie) VALUES (3, 'The Office', 8.9, '24/03/2005')
    into SERIAL(serial_id, denumire, nota, data_aparitie) VALUES (4, 'Stranger Things', 8.8, '15/07/2016')
    into SERIAL(serial_id, denumire, nota, data_aparitie) VALUES (5, 'Narcos', 8.6, '28/08/2015')
select 'worked' from dual;

insert all
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (1,1,'Pilot',1,58)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (2,1,'Cat''s in the bag...',2,48)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (3,1,'...And the Bag''s in the river',3,47)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (4,2,'Winter Is Coming',1,60)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (5,2,'The Kingsroad',2,56)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (6,2,'Lord Snow',3,58)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (7,2,'Cripples, Bastards, and Broken Things',4,54)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (8,2,'The Wolf and the Lion',5,55)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (9,3,'Pilot',1,22)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (10,3,'Diversity Day',2,23)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (11,4,'Chapter One: The Vanishing of Will Byers',1,48)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (12,4,'Chapter Two: The Weirdo on Maple Street',2,55)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (13,4,'Chapter Three: Holly, Jolly',3,51)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (14,4,'Chapter Four: The Body',4,58)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (15,5,'Descenso',1,57)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (16,5,'The Sword of Simón Bolivar',2,50)
    into EPISOD(episod_id, serial_id, denumire, numar, durata) VALUES (17,5,'The Men of Always',3,46)
select 'worked' from dual;

-- secventa nu merge cu insert all, da aceeasi valoare
insert into SUBSCRIPTIE_SERIAL(subscriptie_serial_id, serial_id, subscriptie_id) VALUES (INCREMENTARE_SERIAL.nextval,1,78477);
insert into SUBSCRIPTIE_SERIAL(subscriptie_serial_id, serial_id, subscriptie_id) VALUES (INCREMENTARE_SERIAL.nextval,2,67933);
insert into SUBSCRIPTIE_SERIAL(subscriptie_serial_id, serial_id, subscriptie_id) VALUES (INCREMENTARE_SERIAL.nextval,2,78477);
insert into SUBSCRIPTIE_SERIAL(subscriptie_serial_id, serial_id, subscriptie_id) VALUES (INCREMENTARE_SERIAL.nextval,3,55245);
insert into SUBSCRIPTIE_SERIAL(subscriptie_serial_id, serial_id, subscriptie_id) VALUES (INCREMENTARE_SERIAL.nextval,3,39959);
insert into SUBSCRIPTIE_SERIAL(subscriptie_serial_id, serial_id, subscriptie_id) VALUES (INCREMENTARE_SERIAL.nextval,3,94030);
insert into SUBSCRIPTIE_SERIAL(subscriptie_serial_id, serial_id, subscriptie_id) VALUES (INCREMENTARE_SERIAL.nextval,3,67933);
insert into SUBSCRIPTIE_SERIAL(subscriptie_serial_id, serial_id, subscriptie_id) VALUES (INCREMENTARE_SERIAL.nextval,3,78477);
insert into SUBSCRIPTIE_SERIAL(subscriptie_serial_id, serial_id, subscriptie_id) VALUES (INCREMENTARE_SERIAL.nextval,4,67933);
insert into SUBSCRIPTIE_SERIAL(subscriptie_serial_id, serial_id, subscriptie_id) VALUES (INCREMENTARE_SERIAL.nextval,4,78477);
insert into SUBSCRIPTIE_SERIAL(subscriptie_serial_id, serial_id, subscriptie_id) VALUES (INCREMENTARE_SERIAL.nextval,5,94030);
insert into SUBSCRIPTIE_SERIAL(subscriptie_serial_id, serial_id, subscriptie_id) VALUES (INCREMENTARE_SERIAL.nextval,5,67933);
insert into SUBSCRIPTIE_SERIAL(subscriptie_serial_id, serial_id, subscriptie_id) VALUES (INCREMENTARE_SERIAL.nextval,5,78477);

insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,9,78477);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,8,67933);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,8,78477);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,3,55245);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,3,39959);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,3,94030);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,3,67933);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,3,78477);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,10,94030);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,7,55245);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,1,39959);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,2,67933);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,4,55245);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,5,55245);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,5,39959);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,5,94030);
insert into SUBSCRIPTIE_film(subscriptie_film_id, film_id, subscriptie_id) VALUES (INCREMENTARE_film.nextval,6,94030);

insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,1,10);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,1,11);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,1,12);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,2,10);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,2,13);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,2,14);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,3,19);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,3,18);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,3,17);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,3,16);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,3,15);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,4,10);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,4,11);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,4,12);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,5,12);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,5,13);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,5,14);
insert into SERIAL_ACTOR(serial_actor_id, serial_id, actor_id) VALUES (INCREMENTARE_ACTOR.nextval,5,18);

insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,1,111,10,80);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,1,112,11,35);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,1,115,12,10);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,1,115,13,5);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,2,113,14,67);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,2,114,15,55);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,3,111,16,72);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,3,113,17,48);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,3,114,18,37);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,4,111,18,57);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,4,113,18,43);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,4,114,19,23);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,5,111,15,66);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,5,112,13,43);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,5,113,12,52);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,5,115,10,12);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,6,111,11,12);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,6,112,16,12);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,6,115,17,12);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,6,115,15,22);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,6,115,13,10);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,7,111,14,57);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,7,114,14,63);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,7,112,13,44);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,8,113,19,77);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,8,114,18,82);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,9,111,12,93);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,9,115,17,23);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,9,115,13,44);
insert into ROL_JUCAT(film_rol_actor_id, film_id, rol_id, actor_id, timp_ecran) VALUES (INCREMENTARE_ROL_JUCAT.nextval,10,111,19,123);

insert into FILM(film_id, director_id, denumire, nota, data_aparitie) VALUES (11, 100002, 'Top Gun: Maverick', NULL, '23/11/2021');
insert into FILM(film_id, director_id, denumire, nota, data_aparitie) VALUES (12, 100003, 'Avengers: Endgame', NULL, '23/11/2021');
commit;