### 13.1

**1.a**

| Device | IP Address   |
|--------|--------------|
| S1     | 192.168.10.1 |
| S2     | 192.168.11.1 |
| PC1    | 192.168.10.1 |
| PC2    | 192.168.10.1 |
| PC3    | 192.168.11.1 |
| PC4    | 192.168.11.1 |

**1.b**

| Test        | Successful? | Issues                 | Solution                      | Verified |
|-------------|-------------|------------------------|-------------------------------|----------|
| PC1 to PC2  | No          | IP address on PC1      | Change PC1 IP address         | Yes      |
| PC1 to S1   | Yes         | -                      | -                             | Yes      |
| PC1 to R1   | Yes         | -                      | -                             | Yes      |
| PC3 to PC4  | Yes         | -                      | -                             | Yes      |
| PC3 to S2   | No          | Vlan1 has no IP address| Assign IP address to Vlan1    | Yes      |
| PC3 to R1   | Yes         | -                      | -                             | Yes      |
| PC4 to S2   | Yes         | -                      | -                             | Yes      |


**1.c**

| Test        | Successful? | Issues                           | Solution                              | Verified |
|-------------|-------------|----------------------------------|---------------------------------------|----------|
| PC1 to PC4  | No          | S1 doesn't have default gateway | Assign default gateway for S1         | Yes      |
| PC1 to PC4  | No          | PC4 has wrong default gateway   | Assign correct gateway for PC4        | Yes      |

### 13.2

**1.**

| Device | IPv4 Address | Subnet Mask     | Default Gateway |
|--------|--------------|-----------------|-----------------|
| PC1    | 10.10.1.98   | 255.255.255.224 | 10.10.1.97      |
| PC3    | 10.10.1.18   | 255.255.255.240 | 10.10.1.17      |


**2.a.** 10.10.1.97

**2.c.** 10.10.1.17

**2.f.** 10.10.1.6

**2.g.** 10.10.1.4/30 si 10.10.1.6/32

**2.h.**
   - 10.10.1.10
   - 10.10.1.8/30 si 10.10.1.10/32

**3.a.** interfata serial 0/0/0 din R2 are IP gresit

**3.b** schimbam IP-ul din interfata serial 0/0/0 la 10.10.1.5/32

**1.**

| Device | IPv6 Address/Prefix    | Default Gateway |
|--------|------------------------|-----------------|
| PC2    | 2001:db8:1:1::2/64     | fe80::1         |
| PC4    | 2001:db8:1:4::2/64     | fe80::2         |


**2.a.** 2001:db8:1:3::2

**2.c.** nu a afisat niciun host

**2.f.** default gateway-ului de la PC4 e gresit

**3.a.** default gateway-ului de la PC4 e gresit

**3.b.** il schimbam

### 13.3

**PART 1:**

**1.** destination host unreachable

**2.b.** 10.0.0.254

**2.c.** 10.100.100.6

**3.** RouterB si RouterC

**3.a.** sunt up

**3.b.** la interfata serial 0/0/0 IP-ul nu este unul corect conform topologiei

**3.c.** schimbam IP-ul la 10.100.100.9

**4.b.** da

**PART 2:**

**b.** da

**c.** numarul de IP-uri difera, router-ul are cu unul mai putin

### 13.4

**PART 1:**

**3.**
- Sol1: DNS-ul are IP-ul gresit pentru DualStackServer.pka
- Sol2: PC1 are DNS server-ul gresit

**4.** Sol1 nu este problema, dar Sol2 este

**5.a.** da

**6.** problema a fost ca PC1 avea adresa IP gresita la DNS server

**PART 2:**

**3.** 
- Sol1: server-ul are default gateway-ul gresit
- Sol2: interfata de la router sa fie down 

**4.** Sol1 este problema 

**5.a.** da

**6.** problema era ca default gateway-ul de la server era gresit, dupa schimbarea lui a mers

**PART 3:**

**3.**
- Sol1: PC3 nu are IPv4 setat
- Sol2: PC2 nu are default gateway pentru IPv4

**4.** Sol2 este problema

**5.a.** da

**6.** PC2 nu avea default gateway setat, am setat la 192.168.0.1

### 13.5

**1.b.** au functionat toate ping-urile mai putin cele catre PC-A si PC-B care au dat host unreachable

**1.c.** da poate prin ambele metode 

**1.d.** avea doar IP-ul gresit PC-01

**2.b.** au functionat toate mai putin cele catre PC-A si PC-B

**2.c.** da, ambele

**2.d.** avea default gateway-ul gresit

**3.b.** 
- default gateway - nu
- web server - nu
- PC-A - da
- PC-01 - nu
- PC-02 - nu

**3.c.** nu la ambele

**3.d.** R1 avea IP-ul gresit la interfata gigabitEthernet 0/1

### 13.6

- PC-A default gateway nu e setat
- S1 IP default gateway gresit 
- R1 G0/0/1 avea halfway duplex si speed auto 

**Reflection Question:** Am putea sa verificam fiecare dispozitiv si sa il testam, iar dupa se ne mutam la celalalt.

### 13.10

**REFLECTION QUESTIONS:**

1. show ip route, show interfaces, show protocols

2. show ip interface brief

3. show interfaces, show ip interface brief, show protocols

4. show version

5. show arp, show interfaces, show ip route, show ip interface brief, show protocols

6. show version, show flash

7. show users

8. show interfaces 

9. show ip route

10. gigabitethernet 0/0 si serial 0/0/1