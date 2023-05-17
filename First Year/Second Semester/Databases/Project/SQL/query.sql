/*
select NUME || ' ' || PRENUME Nume
from PLATA
where DATA_EXP in ( select min(plt.DATA_EXP)
                    from PLATA plt
                    where plt.PLATA_ID in (with sub as (select s.SUBSCRIPTIE_ID
                                                        from SUBSCRIPTIE s
                                                        where s.COST = (select min(cost)
                                                                        from SUBSCRIPTIE))
                                            select p.PLATA_ID
                                            from PLATA p
                                            join UTILIZATOR u on p.PLATA_ID = u.PLATA_ID
                                            join sub on u.SUBSCRIPTIE_ID = sub.SUBSCRIPTIE_ID));
*/

-- numele celui care plateste, utilizatorii care au cea mai ieftina subsciptie, si caruia ii
-- expira cardul cat mai curand
-- subcerere nesincronizata in clauza from, bloc de cerere with
select NUME || ' ' || PRENUME Nume
from PLATA
where DATA_EXP in ( select min(plt.DATA_EXP)
                    from PLATA plt
                    where plt.PLATA_ID in (with sub as (select SUBSCRIPTIE_ID
                                                        from (select s.SUBSCRIPTIE_ID
                                                              from SUBSCRIPTIE s
                                                              where s.COST in (select min(cost)
                                                                               from SUBSCRIPTIE)))
                                            select p.PLATA_ID
                                            from PLATA p
                                            join UTILIZATOR u on p.PLATA_ID = u.PLATA_ID
                                            join sub on u.SUBSCRIPTIE_ID = sub.SUBSCRIPTIE_ID));

-- Numele intreg al persoanelor care platesc subscriptie Ultimate si au numele inceapd cu Ho si se termina in d
-- (subcereri sincronizate in care intervin cel putin 3 tabele, 2 functii pe string uri una pe date)
select concat(concat(nume,' '),prenume) , round((data_exp - sysdate)) as days
from PLATA
where PLATA_ID in (
    select PLATA_ID
    from UTILIZATOR
    where SUBSCRIPTIE_ID = (
            select SUBSCRIPTIE_ID
            from SUBSCRIPTIE
            where TIP = lower('standard')
        )
    ) and NUME like 'Ho%d';

-- directorul cu cea mai mare medie a notelor filmelor
-- ma gandesc daca sa o pastrez
select NUME
from DIRECTOR
where DIRECTOR_ID in (with average as (
                        select avg(nota) n, DIRECTOR_ID id
                        from FILM
                        group by DIRECTOR_ID)
                    select id
                    from average
                    where average.n = (select max(n)
                                        from (select avg(nota) n
                                              from FILM
                                              group by DIRECTOR_ID)));

/*select *
from SUBSCRIPTIE_FILM
order by SUBSCRIPTIE_ID;

select SF.SUBSCRIPTIE_ID
from SUBSCRIPTIE
join SUBSCRIPTIE_FILM SF on SUBSCRIPTIE.SUBSCRIPTIE_ID = SF.SUBSCRIPTIE_ID
join FILM F on SF.FILM_ID = F.FILM_ID
group by SF.SUBSCRIPTIE_ID
having count(*) >= 4;*/

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

-- sa se afiseze numele, nota, daca a aparut in 1944 si daca este recomandat pentru fiecare film (recomandat <=> nota > 5)
-- nvl, decode, case
select denumire, nvl(nota,1) as nota, decode(to_char(DATA_APARITIE,'YYYY'),'1994','A aparut in 1944','Nu a aparut in 1944'),
case
    when nvl(nota,1) > 5 then 'Recomandat'
    else 'Nerecomandat'
end as Recomandat
from FILM;

-- 13 suprimare si updatare
select *
from FILM;
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

/*select max(NUMAR)
from EPISOD
group by SERIAL_ID
having sum(DURATA) = (select max(sum(DURATA))
                    from EPISOD
                    group by SERIAL_ID);*/

-- stergearea ultimului episod care apartine serialului cu cea mai mare durata,
delete from EPISOD
where NUMAR in (select max(NUMAR)
                from EPISOD
                group by SERIAL_ID
                having sum(DURATA) = (select max(sum(DURATA))
                                    from EPISOD
                                    group by SERIAL_ID));

select *
from EPISOD;