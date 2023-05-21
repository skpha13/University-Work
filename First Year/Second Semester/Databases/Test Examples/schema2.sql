drop table album cascade constraints;
drop table castiga cascade constraints;
drop table premiu cascade constraints;
drop table formatie cascade constraints;

CREATE TABLE formatie (
id_formatie NUMBER(5),
nume VARCHAR2(25) NOT NULL,
data_lansare DATE NOT NULL,
data_retragere DATE,
website VARCHAR2(30),
tara_prov VARCHAR2(30) NOT NULL,
CONSTRAINT formatie_cp PRIMARY KEY (id_formatie)
);

insert into formatie values (2,'Feist',TO_DATE('10-01-1990','dd-mm-yyyy'),NULL,'www.feist.com','SUA');
insert into formatie values (3,'The Decemberists',TO_DATE('10-05-1992','dd-mm-yyyy'),NULL,'www.thedecemberists.com','UK');
insert into formatie values (4,'Dido',TO_DATE('11-05-1988','dd-mm-yyyy'),NULL,'www.dido.com','UK');
insert into formatie values (1,'Radiohead',TO_DATE('11-05-1998','dd-mm-yyyy'),NULL,'www.radiohead.com','UK');
insert into formatie values (5,'Coldplay',TO_DATE('11-06-1998','dd-mm-yyyy'),NULL,'www.coldplay.com','UK');
insert into formatie values (6,'Backstreet Boys',TO_DATE('11-06-1990','dd-mm-yyyy'),TO_DATE('11-06-2000','dd-mm-yyyy'),'www.bb.com','UK');


CREATE TABLE premiu (
id_premiu NUMBER(5),
concurs VARCHAR2(25) NOT NULL,
sectiune VARCHAR2(25) NOT NULL,
frecventa VARCHAR2(15) NOT NULL,
tara_prov VARCHAR2(30) NOT NULL,
CONSTRAINT premiu_cp PRIMARY KEY (id_premiu)
);

insert into premiu values (1,'MTV Music Awards','Pop','Anual','UK' );
insert into premiu values (2,'MTV Music Awards','Live','Anual','UK' );
insert into premiu values (3,'EMI Music Award','Rock','Anual','UK' );
insert into premiu values (4,'Sony Music Awards','Pop','Bianual','USA' );



CREATE TABLE castiga (
id_premiu NUMBER(5) REFERENCES premiu(id_premiu),
id_formatie NUMBER(5) REFERENCES formatie(id_formatie),
data_d DATE NOT NULL,
loc_ocupat VARCHAR2(30) NOT NULL,
recompensa NUMBER(5),
CONSTRAINT castiga_cp PRIMARY KEY (id_premiu, id_formatie,data_d)
);

insert into castiga values (1,1,TO_DATE('10-05-2008','dd-mm-yyyy'),'Locul I',2000);
insert into castiga values (1,3,TO_DATE('10-06-2009','dd-mm-yyyy'),'Locul II',1000);
insert into castiga values (2,3,TO_DATE('10-08-2009','dd-mm-yyyy'),'Mentiune',2000);
insert into castiga values (3,4,TO_DATE('12-03-2008','dd-mm-yyyy'),'Locul I',5000);
insert into castiga values (3,6,TO_DATE('12-03-2009','dd-mm-yyyy'),'Locul II',4000);
insert into castiga values (4,5,TO_DATE('12-04-2008','dd-mm-yyyy'),'Locul II',2000);
insert into castiga values (4,6,TO_DATE('12-03-1996','dd-mm-yyyy'),'Locul III',200);

CREATE TABLE album (
id_album NUMBER(5),
id_formatie NUMBER(5) REFERENCES formatie(id_formatie),
gen VARCHAR2(20) NOT NULL,
nume VARCHAR2(30) NOT NULL,
data_l DATE NOT NULL,
pret NUMBER(3) NOT NULL,
CONSTRAINT album_cp PRIMARY KEY (id_album)
);

insert into album values (1,1,'Electronic','In Rainbows',TO_DATE('11-05-2000','dd-mm-yyyy'),40);
insert into album values (2,1,'Electronic','Hail to the Thief',TO_DATE('11-05-2004','dd-mm-yyyy'),50);
insert into album values (3,2,'Pop','Feist',TO_DATE('11-03-1995','dd-mm-yyyy'),20);
insert into album values (4,3,'Indie','Nothing special',TO_DATE('13-02-2000','dd-mm-yyyy'),30);
insert into album values (5,4,'Pop','First time',TO_DATE('13-02-1991','dd-mm-yyyy'),24);
insert into album values (6,5,'Alternative Rock','Viva la vida',TO_DATE('13-02-2008','dd-mm-yyyy'),50);
insert into album values (7,6,'Pop Rock','You are special',TO_DATE('13-09-1994','dd-mm-yyyy'),15);

commit;