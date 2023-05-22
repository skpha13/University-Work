-- ex 1 a
select h.denumire, fa.denumire
from hotel h, facilitati_hotel fh, facilitate fa
where h.id = fh.id_hotel
and fh.id_facilitate = fa.id
and h.id in (select hot.id
            from hotel hot, camera cam, cazare caz
            where hot.id = cam.id_hotel
            and caz.id_camera = cam.id
            and to_char(caz.data_cazare, 'YYYY') = 2018);

-- ex 1 b
select h.id || ' ' || h.denumire
from hotel h, facilitati_hotel fh, facilitate fa
where h.id = fh.id_hotel and fh.id_facilitate = fa.id
group by h.id, h.denumire
having count(*) >= 2;

-- ex 2


-- ex 3
select max(count(*)) nrfac
from hotel h, facilitati_hotel fh, facilitate fa
where h.id = fh.id_hotel and fh.id_facilitate = fa.id
group by h.id;

with nrfac as (
    select h.id cod
    from hotel h, facilitati_hotel fh, facilitate fa
    where h.id = fh.id_hotel and fh.id_facilitate = fa.id
    group by h.id
    having count(*) = (select max(count(*))
                        from hotel h, facilitati_hotel fh, facilitate fa
                        where h.id = fh.id_hotel and fh.id_facilitate = fa.id
                        group by h.id)
    ),
nrturist as (
    select h.id cod , count(t.id_turist) nr
    from hotel h, camera c, cazare ca, turist_cazare t
    where h.id = c.id_hotel and ca.id_camera = c.id and t.id_cazare = ca.id
    and ( to_char(ca.data_cazare,'MM') = 7 or 
            to_char(ca.data_cazare,'MM') = 8 or
            to_char(ca.data_cazare,'MM') = 9)
    group by h.id
),
nrcapacitati as (
    select h.id cod, sum(c.capacitate) cap
    from hotel h, camera c
    where h.id = c.id_hotel
    group by h.id
)
select h.denumire, nt.nr, nc.cap
from hotel h, nrfac nf, nrturist nt, nrcapacitati nc
where h.id = nf.cod and h.id = nt.cod and h.id = nc.cod;
