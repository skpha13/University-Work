drop table note cascade constraints;
drop table curs cascade constraints;
drop table student cascade constraints;
drop table profesor cascade constraints;

create table student(cod_student number(4) primary key,
                      nume varchar2(20),
		      prenume varchar2(20),
		      data_nasterii date,
		      nr_matricol varchar2(20),
		      grupa varchar2(3),
		      an number,
                      CNP varchar2(13),
		      sectie varchar2(20));

create table profesor(cod_profesor number(4) primary key,
		      nume varchar2(20),
		      prenume varchar2(20),
                      data_nasterii date,
                      data_angajarii date,
                      titlu varchar2(20),
		      salariu number(10));


create table curs (cod_curs number(4) primary key, 
                     denumire varchar2(20), 
		      nr_credite number(4), 
		      cod_profesor number(4) references profesor(cod_profesor));  			 

					
create table note(cod_student number(4) references student(cod_student), 
                    	  cod_curs number(4) references curs(cod_curs), 
			  nota number(4),
			  data_examinare date,
			  PRIMARY KEY(cod_student,cod_curs,data_examinare));

insert into student
values(1,'Barbu','Lavinia',TO_DATE('01-02-1983','dd-mm-yyyy'),'156',421,4,'2830201893510','mate-info');


insert into student
values(8,'Sandulescu','Xenia',TO_DATE('01-02-1983','dd-mm-yyyy'),'156',421,4,'2830201893510','mate-info');

insert into student
values(2,'Anton','Maria',TO_DATE('03-03-1981','dd-mm-yyyy'),'6589',211,2,'2810303907818','mate');

insert into student
values(3,'Anton','Catalin',TO_DATE('04-05-1981','dd-mm-yyyy'),'136',221,2,'2810504568564','mate-info');

insert into student
values(4,'Busuioc','Gigi',TO_DATE('15-12-1980','dd-mm-yyyy'),'248',221,2,'2801215873510','info');

insert into student
values(5,'Antonescu','Teodor',TO_DATE('01-02-1983','dd-mm-yyyy'),'156',211,2,'2830201893510','mate-info');

insert into student
values(6,'Dragan','Dan',TO_DATE('22-05-1989','dd-mm-yyyy'),'0890',111,1,'2890522893510','mate');

insert into student
values(7,'Roman','Daniel',TO_DATE('07-06-1985','dd-mm-yyyy'),'1786',421,4,'2850706893510','mate-info');

insert into profesor
values(11,'Todorache','Petre',TO_DATE('21-03-1950','dd-mm-yyyy'),TO_DATE('01-08-1973','dd-mm-yyyy'),'profesor',3000);

insert into profesor
values(12,'Dumitrescu','Dorin',TO_DATE('24-05-1980','dd-mm-yyyy'),TO_DATE('01-08-2004','dd-mm-yyyy'),'asistent',1300);

insert into profesor
values(13,'Gheorghe','Stefan',TO_DATE('20-02-1975','dd-mm-yyyy'),TO_DATE('24-09-2000','dd-mm-yyyy'),'lector',2100);

insert into profesor
values(14,'Mares','Madalina',TO_DATE('24-06-1975','dd-mm-yyyy'),NULL,'conferentiar',4000);

insert into curs
values (31,'ecuatii',6,11);

insert into curs
values (32,'ecuatii der par',7,11);

insert into curs
values (33, 'analiza matematica',4,12);

insert into curs
values (34, 'analiza functionala', 6,12);

insert into curs
values(35,'baze de date',7, 13);

insert into curs
values(36,'retele',7,13);

insert into curs
values(37,'interfete',5,NULL);

insert into curs
values(38,'poo',15,NULL);

insert into curs
values(39,'algebra',NULL,NULL);

insert into note
values(2,32,7,TO_DATE('01-06-2007','dd-mm-yyyy'));

insert into note
values(4,33,8,TO_DATE('25-05-2006','dd-mm-yyyy'));

insert into note
values(4,34,9,TO_DATE('20-05-2007','dd-mm-yyyy'));

insert into note
values(4,35,10,TO_DATE('21-05-2007','dd-mm-yyyy'));

insert into note
values(4,36,9,TO_DATE('22-05-2007','dd-mm-yyyy'));


insert into note
values(2,33,6,TO_DATE('03-05-2007','dd-mm-yyyy'));

insert into note
values(1,35,4,TO_DATE('03-05-2005','dd-mm-yyyy'));


insert into note
values(1,35,5,TO_DATE('03-10-2005','dd-mm-yyyy'));

insert into note
values(1,36,4,TO_DATE('03-01-2004','dd-mm-yyyy'));

insert into note
values(1,36,4,TO_DATE('01-02-2004','dd-mm-yyyy'));

insert into note
values(1,36,6,TO_DATE('03-07-2004','dd-mm-yyyy'));

insert into note
values(7,35,10,TO_DATE('03-05-2005','dd-mm-yyyy'));


insert into note
values(8,35,4,TO_DATE('03-05-2005','dd-mm-yyyy'));

insert into note
values(8,37,4,TO_DATE('03-05-2005','dd-mm-yyyy'));

insert into note
values(8,37,5,TO_DATE('04-05-2005','dd-mm-yyyy'));

insert into note
values(8,36,3,TO_DATE('05-05-2006','dd-mm-yyyy'));

commit;






