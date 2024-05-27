### 10.2

**PART 1:**

**2.f.** DNS

### 10.4

**1.**

| Destination                       | Average Round Trip Time (ms) | TTL/Hop Limit      |
|-----------------------------------|------------------------------|--------------------|
| 192.168.1.10                      | 2                            | 128                |
| 2001:db8:acad:1::10               | 3                            | 128                |
| 192.168.1.1 (R1)                  | 0                            | 255                |
| 2001:db8:acad:1::1 (R1)           | 1                            | 255                |
| 192.168.1.2 (S1)                  | 0                            | 255                |
| 2001:db8:acad:1::2 (S1)           | 0                            | 255                |
| 64.100.0.2 (R1)                   | 1                            | 255                |
| 2001:db8:acad::2 (R1)             | 0                            | 255                |
| 64.100.0.1 (ISP)                  | 0                            | 254                |
| 2001:db8:acad::1 (ISP)            | 0                            | 254                |
| 209.165.200.225 (ISP G0/0/1)      | HOST UNREACHABLE             |                    |
| 2001:db8:acad:200::225 (ISP G0/0/1)| REQUEST TIMED OUT            |                    |
| 209.165.200.226 (External)        | HOST UNREACHABLE             |                    |
| 2001:db8:acad:200::226 (External) | REQUEST TIMED OUT            |                    |

**2.** ping-urile catre ipv4 au rezultat in host unreachable si cele catre ipv6 in request timed out

**PART 4:**

**1.g.** Destination host unreachable

**2.b.** 209.165.200.226

**Reflection Questions:**

**1.** un antivirus sau firewall

**2.** request timed out. ar trebui sa verificam daca interfata e up, daca ip-urile sunt corecte

**3.** destination host unreachable. ne spune ca nu exista nicio cale catre adresa la care am dat ping.

### 10.5

**PART 1:**

**1.**

| Device | Interface | IP Address/Prefix | Default Gateway |
|--------|-----------|-------------------|-----------------|
| PC1    | NIC       | 10.10.1.98/27     | 10.10.1.97      |
| PC3    | NIC       | 10.10.1.18/28     | 10.10.1.17      |

**2.a.** 10.10.1.97

**2.c.** 10.10.1.17

**2.f.** 10.10.1.6

**2.g.** 10.10.1.4/30 si 10.10.1.6/32

**2.h.**
   - 10.10.1.10
   - 10.10.1.8/30 si 10.10.1.10/32

**2.j.**
   - Serial 0/0/0 10.10.1.2
   - Serial 0/0/1 10.10.1.9

**3.**
   - problema: la interfata serial 0/0/0 pe router-ul R2 este gresit ip-ul, trebuia sa fie 10.10.1.5/30
   - solutie: schimbam ip-ul la cel corect

**5.** da 

**PART 2:**

**1.**

| Device | Interface | IP Address/Prefix | Default Gateway |
|--------|-----------|-------------------|-----------------|
| PC2    | NIC       | 2001:db8:1:1::2/64| fe80::1         |
| PC4    | NIC       | 2001:db8:1:4::2/64| fe80::2         |

**2.a.** 2001:db8:1:3::2

**2.c.** nu a avut nicio adresa, a dat request timed out din prima

**2.f.** da

**3.** 
   - problema: PC4 are default gateway-ul gresit, ar trebuie sa fie FE80::3
   - solutia: schibam default gateway-ul lui PC4 la FE80::3

**5.** da
