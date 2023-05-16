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

-- cine plateste subscriptie ultimate (subcereri nesincronizate in care intervin cel putin 3 tabele)
-- si in cat timp ii expira cardul
select datediff(month,getdate(), DATA_EXP )
from PLATA
where PLATA_ID in (
    select PLATA_ID
    from UTILIZATOR
    where SUBSCRIPTIE_ID = (
            select SUBSCRIPTIE_ID
            from SUBSCRIPTIE
            where TIP = lower('standard')
        )
    );

-- directorul cu cea mai mare medie a notelor filmelor
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

--pretul si numele subscriptiilor care au cel putin 4 filme
select TIP, COST
from SUBSCRIPTIE
where SUBSCRIPTIE_ID in (select SF.SUBSCRIPTIE_ID
                        from SUBSCRIPTIE
                        join SUBSCRIPTIE_FILM SF on SUBSCRIPTIE.SUBSCRIPTIE_ID = SF.SUBSCRIPTIE_ID
                        join FILM F on SF.FILM_ID = F.FILM_ID
                        group by SF.SUBSCRIPTIE_ID
                        having count(*) >= 4);

