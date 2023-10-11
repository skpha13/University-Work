select * from title;

SELECT category, COUNT(*)
FROM title
GROUP BY category;

select category, count(distinct title), count(*), count(r.copy_id)
from   rental r, title t
where  r.title_id = t.title_id
group by category
having count(*) = (select max(count(*))
                   from   rental r, title t
                   where  r.title_id = t.title_id
                   group by category);

select * from TITLE_COPY;

select count(*)
from title t, TITLE_COPY tc
where tc.TITLE_ID = t.TITLE_ID
group by status
having status = 'AVAILABLE';

select t.TITLE, r.ACT_RET_DATE, tc.STATUS, decode(r.ACT_RET_DATE, null, 'RENTED', 'AVAILABLE') as "STATUS CORECT"
from rental r, TITLE_COPY tc, title t
where r.TITLE_ID = tc.TITLE_ID and t.TITLE_ID = r.TITLE_ID;

with status as (select t.TITLE,r.ACT_RET_DATE,tc.STATUS as STATUS_SETAT,decode(r.ACT_RET_DATE, null, 'RENTED', 'AVAILABLE') as STATUS_CORECT
              from rental r,
                   TITLE_COPY tc,
                   title t
              where r.TITLE_ID = tc.TITLE_ID
                and t.TITLE_ID = r.TITLE_ID)
select status.TITLE as title
from status
where status.STATUS_CORECT <> status.STATUS_SETAT;

select count(*) from (
           Select a.title_id, title, copy_id, status status_setat,
       case
           when (a.title_id, copy_id) not in (select title_id, copy_id
                                              From rental
                                              Where act_ret_date is null)
               then 'AVAILABLE'
           else 'RENTED'
           end status_corect
From  title_copy a, title b
Where  a.title_id = b.title_id
           )
where status_setat <> status_corect;

Create table title_copy_ami
as select * from title_copy;

select t.TITLE, r.ACT_RET_DATE, tc.STATUS, decode(r.ACT_RET_DATE, null, 'RENTED', 'AVAILABLE') as "STATUS CORECT"
from rental r, TITLE_COPY tc, title t
where r.TITLE_ID = tc.TITLE_ID and t.TITLE_ID = r.TITLE_ID;

update title_copy_ami p
set status = case
                when (p.title_id, copy_id) not in (select title_id, copy_id
                                              From rental
                                              Where act_ret_date is null)
               then 'AVAILABLE'
               else 'RENTED'
               end
where status <> case
                when (p.title_id, copy_id) not in (select title_id, copy_id
                                              From rental
                                              Where act_ret_date is null)
               then 'AVAILABLE'
               else 'RENTED'
               end;

select decode(count(rez),0,'DA','NU') as raspuns
from (
    select BOOK_DATE as rez
    from RENTAL
    MINUS
    select RES_DATE
    from RESERVATION
    );

select m.FIRST_NAME || ' ' || m.LAST_NAME as nume, t.TITLE, count(t.title)
from MEMBER m
right JOIN rental r ON m.member_id = r.member_id
right JOIN title t ON r.title_id = t.title_id
group by m.FIRST_NAME || ' ' || m.LAST_NAME, t.TITLE;

select m.FIRST_NAME || ' ' || m.LAST_NAME as nume, t.TITLE ,count(tc.TITLE_ID) as nr_exmemplare
from MEMBER m
right JOIN rental r ON m.member_id = r.member_id
right JOIN title t ON r.title_id = t.title_id
join TITLE_COPY tc on tc.TITLE_ID = t.TITLE_ID
group by m.FIRST_NAME || ' ' || m.LAST_NAME, t.TITLE ,tc.TITLE_ID;