-- numele celui care plateste, utilizatorii care au cea mai ieftina subsciptie, si caruia ii
-- expira cardul cat mai curand
-- bloc de cerere with
-- !!! am schimbat proiectul, acest query nu mai merge
/*select NUME || ' ' || PRENUME Nume
from PLATA
where DATA_EXP in ( select min(plt.DATA_EXP)
                    from PLATA plt
                    where plt.PLATA_ID in (with sub as (select s.SUBSCRIPTIE_ID
                                                        from SUBSCRIPTIE s
                                                        where s.COST in (select min(cost)
                                                                         from SUBSCRIPTIE))
                                            select p.PLATA_ID
                                            from PLATA p
                                            join UTILIZATOR u on p.PLATA_ID = u.PLATA_ID
                                            join sub on u.SUBSCRIPTIE_ID = sub.SUBSCRIPTIE_ID));*/

-- pretul si numele subscriptiilor care au cel putin 4 filme
-- grupari de date cu subcereri nesincronizate in care intervin cel putin 3 tabele, functii grup, filtrare
-- la nivel de grupuri (in cadrul aceleiasi cereri)
select TIP, COST
from SUBSCRIPTIE
where SUBSCRIPTIE_ID in (select SF.SUBSCRIPTIE_ID
                        from SUBSCRIPTIE
                        join SUBSCRIPTIE_FILM SF on SUBSCRIPTIE.SUBSCRIPTIE_ID = SF.SUBSCRIPTIE_ID
                        join FILM F on SF.FILM_ID = F.FILM_ID
                        group by SF.SUBSCRIPTIE_ID
                        having count(*) >= 4);

-- numele celor care fac plata utilizatorilor care sunt abonati la o subscriptie
-- si cate zile mai sunt pana cand le expira cardul si cate zile sunt pana le expira abonamentul
-- subcereri sincronizate cu 3 tabele, subcere nesincronizata in clauza from
-- 2 functii pe string uri, 2 pe date
-- !!! am schimbat proiectul, acest query nu mai merge
/*select concat(concat(initcap(p.nume),' '),initcap(p.prenume)) "NUME", round((data_exp-sysdate)) as Days, Zile.exp
from plata p, ( select P1.PLATA_ID cod, U2.DATA_EXP_SUB exp
                from UTILIZATOR U2, PLATA P1
                where P1.PLATA_ID = U2.PLATA_ID) Zile
where plata_id in ( select plata_id
                    from utilizator u
                    where p.plata_id = u.plata_id and exists ( select 1
                                                               from subscriptie s
                                                               where u.subscriptie_id = s.subscriptie_id))
and Zile.cod = p.PLATA_ID;*/

-- sa se afiseze numele, nota, daca a aparut in 1944 si daca este recomandat pentru fiecare film (recomandat <=> nota > 5)
-- nvl, decode, case
select denumire, nvl(nota,1) as nota, decode(to_char(DATA_APARITIE,'YYYY'),'1994','A aparut in 1944','Nu a aparut in 1944'),
case
    when nvl(nota,1) > 5 then 'Recomandat'
    else 'Nerecomandat'
end as Recomandat
from FILM;

-- pentru fiecare subscriptie sa se afiseze ce serial are si cat dureaza
-- ordonate dupa durata si numele subscriptiei descrescator
with durataEpisod as (
    select S2.SERIAL_ID, S2.DENUMIRE nume, sum(DURATA) suma
    from EPISOD
    join SERIAL S2 on S2.SERIAL_ID = EPISOD.SERIAL_ID
    group by S2.SERIAL_ID, S2.DENUMIRE
)
select sub.tip, de.nume ,de.suma
from SUBSCRIPTIE sub
join SUBSCRIPTIE_SERIAL ss on ss.SUBSCRIPTIE_ID = sub.SUBSCRIPTIE_ID
join durataEpisod de on de.SERIAL_ID = ss.SERIAL_ID
order by sub.tip desc, de.suma desc;


-- 13 suprimare si updatare

-- schimbare filmelor cu nota null in nota 10
update FILM
set NOTA = 10
where denumire in (select DENUMIRE
                   from FILM
                    where nota is null);

select * from DIRECTOR;
-- stergerea directorului cu cea mai mica nota
delete from DIRECTOR
where NOTA in (select min(nota)
               from DIRECTOR);

-- stergearea ultimului episod care apartine serialului cu cea mai mare durata
delete from EPISOD
where NUMAR in (select max(NUMAR)
                from EPISOD
                group by SERIAL_ID
                having sum(DURATA) = (select max(sum(DURATA))
                                    from EPISOD
                                    group by SERIAL_ID));

-- 15

-- primele 3 subscriptii care contin filmele cu cei mai buni directori(nota medie a directorilor)
-- analiza top n
with tabela as (
    select SUBSCRIPTIE.tip nume, avg(DIRECTOR.nota) val
    from SUBSCRIPTIE_FILM
    join FILM on SUBSCRIPTIE_FILM.FILM_ID = FILM.FILM_ID
    join DIRECTOR on FILM.DIRECTOR_ID = DIRECTOR.DIRECTOR_ID
    join SUBSCRIPTIE on SUBSCRIPTIE_FILM.SUBSCRIPTIE_ID = SUBSCRIPTIE.SUBSCRIPTIE_ID
    group by SUBSCRIPTIE.tip
    order by 2 desc
)
select nume
from tabela
where ROWNUM <= 3;

-- aflati poreclele utilizatorilor care se pot uita la toate filmele care au nota 10
-- division
select PORECLA
from UTILIZATOR
where SUBSCRIPTIE_ID in (select DISTINCT SUBSCRIPTIE_ID
                        from SUBSCRIPTIE_FILM s1
                        where not exists((select FILM_ID
                                          from FILM
                                          where NOTA = 10)
                                    MINUS
                                        (select f.FILM_ID
                                         from SUBSCRIPTIE_FILM s2, film f
                                         where f.FILM_ID = s2.FILM_ID
                                         and s2.SUBSCRIPTIE_ID = s1.SUBSCRIPTIE_ID)));

-- se cer actorii, numele serialelor asociate si subsciptiile acestor seriale, incluzand chiar si actorii care nu joaca in niciun serial
-- outer join pe 4 tabele
select NUME, DENUMIRE, (select TIP
                        from SUBSCRIPTIE s3
                        where s3.SUBSCRIPTIE_ID = SS.SUBSCRIPTIE_ID) as "Nume Subscriptie"
from ACTOR
left outer join SERIAL_ACTOR on ACTOR.ACTOR_ID = SERIAL_ACTOR.ACTOR_ID
left outer join SERIAL S2 on SERIAL_ACTOR.SERIAL_ID = S2.SERIAL_ID
left outer join SUBSCRIPTIE_SERIAL SS on S2.SERIAL_ID = SS.SERIAL_ID;

-- 16
-- numele directorilor care au filme cu nota peste 9 si au aparut dupa anul 2000
select distinct d.NUME
from DIRECTOR D, FILM F
where f.FILM_ID in (
        select FILM_ID
        from FILM
        where NOTA >= 9 and f.DATA_APARITIE >= '01/01/2000'
    ) and d.DIRECTOR_ID = f.DIRECTOR_ID;

-- R1 = PRODUCT(DIRECTOR, FILM)
-- R2 = SELECT(R1, f.nota >= 9 and data_aparitie >= 01/01/2000 and d.director_id = f.director_id)
-- REZULTAT = R3 = PROJECT(R3, nume)

with film2 as (
    select DIRECTOR_ID
    from FILM
    where NOTA >= 9 and DATA_APARITIE >= '01/01/2000'
)
select distinct d.nume
from DIRECTOR d
join film2 f on d.DIRECTOR_ID = f.DIRECTOR_ID;

-- R1 = SELECT(FILM, nota >= 9 and data_aparitie >= 01/01/2000)
-- R2 = PROJECT(DIRECTOR, nume)
-- REZULTAT = R3 = JOIN(R1,R2)

-- exista o subscriptie care sa contina toate filmele cu nota 10? Sa se afiseze DA sau NU corespunzator.
select DISTINCT SUBSCRIPTIE_ID
from SUBSCRIPTIE_FILM s1
where not exists((select FILM_ID
                  from FILM
                  where NOTA = 10)
            MINUS
                (select f.FILM_ID
                 from SUBSCRIPTIE_FILM s2, film f
                 where f.FILM_ID = s2.FILM_ID
                 and s2.SUBSCRIPTIE_ID = s1.SUBSCRIPTIE_ID));

-- exista o subscriptie care sa contina toate filmele cu nota 10? Sa se afiseze DA sau NU corespunzator.
select case when not exists(
    (select FILM_ID
    from FILM
    where NOTA = 10)
MINUS
    (select f.FILM_ID
     from SUBSCRIPTIE_FILM s2, film f
     where f.FILM_ID = s2.FILM_ID))
then 'DA'
else 'NU'
end Exista
from dual;