### 6.1 

**PART 1:**

**1.d.**  
   - nu  
   - 3 pentru ca e broadcast si trimite la toate device-urile  
   - 172.16.31.3

**1.e.**  
   - adresa mac sursa a fost pusa in adresa mac destinatie  
   - iar adresa mac destinatie care era 0000.0000.0000 a luat valoarea adresei mac de la pc ul 172.16.31.3 in mac sursa

**1.f.**    1

**2.a.**    da

**2.c.**  
   - 172.16.31.3  
   - cand nu stie care e adresa mac a destinatiei

**PART 2:**

**1.c.**   4 cu 4

**2.a.**   da

**2.b.**   pentru ca ambele se conecteaza la access point si este adresa mac a lui

**PART 3:**

**1.c.**   172.16.31.1

**1.e.**   2

**1.f.**   172.16.31.1

**1.g.**   pentru ca mai intai ca sa poata ajunge la 10.10.10.1 trebuie sa treaca prin default gateway care face conexiunea cu cealalata retea si are IP 172.16.31.1

**2.a.**   0

**2.c.**   da

### 6.2

**1.e.**

| Destination MAC Address | Source MAC Address   | Source IP Address | Destination IP Address | At Device  |
|--------------------------|----------------------|-------------------|------------------------|------------|
| 000C.85CC.1DA7           | 00D0.D311.C788       | 172.16.31.5       | 172.16.31.2            | Switch 1   |
| 000C.85CC.1DA7           | 00D0.D311.C788       | 172.16.31.5       | 172.16.31.2            | Hub        |
| 00D0.D311.C788           | 000C.85CC.1DA7       | 172.16.31.2       | 172.16.31.5            | 172.16.31.2|

**2.**

**PING 172.16.31.2 from 172.16.31.3**
| Destination MAC Address | Source MAC Address   | Source IP Address | Destination IP Address | At Device  |
|--------------------------|----------------------|-------------------|------------------------|------------|
| N/A                      | N/A                  | 172.16.31.3       | 172.16.31.2            | 172.16.31.3|
| 000C.85CC.1DA7           | 0060.7036.2849       | 172.16.31.3       | 172.16.31.2            | 172.16.31.3|
| 000C.85CC.1DA7           | 0060.7036.2849       | 172.16.31.3       | 172.16.31.2            | Hub        |
| 000C.85CC.1DA7           | 0060.7036.2849       | 172.16.31.3       | 172.16.31.2            | Switch 1   |
| 0060.7036.2849           | 000C.85CC.1DA7       | 172.16.31.2       | 172.16.31.3            | 172.16.31.2|

\
**PING 172.16.31.4 from 172.16.31.5**
| Destination MAC Address | Source MAC Address   | Source IP Address | Destination IP Address | At Device  |
|--------------------------|----------------------|-------------------|------------------------|------------|
| N/A                      | N/A                  | 172.16.31.5       | 172.16.31.4            | 172.16.31.5|
| 000C.CF0B.BC80           | 00D0.D311.C788       | 172.16.31.5       | 172.16.31.4            | 172.16.31.5|
| 00D0.D311.C788           | 000C.CF0B.BC80       | 172.16.31.4       | 172.16.31.5            | 172.16.31.4|

**PART 2:**

**1.**

| Destination MAC Address | Source MAC Address   | Source IP Address | Destination IP Address | At Device    |
|--------------------------|----------------------|-------------------|------------------------|--------------|
| 00D0.BA8E.741A           | 00D0.D311.C788       | 172.16.31.5       | 10.10.10.2             | 172.16.31.5  |
| 00D0.BA8E.741A           | 00D0.D311.C788       | 172.16.31.5       | 10.10.10.2             | Switch 1     |
| 0060.2F84.4AB6           | 00D0.588C.2401       | 172.16.31.5       | 10.10.10.2             | Router       |
| 0060.2F84.4AB6           | 00D0.588C.2401       | 172.16.31.5       | 10.10.10.2             | Switch 0     |
| 0050.0FAB.6C82           | 0060.2F84.4AB6       | 172.16.31.5       | 10.10.10.2             | Access Point |
| 0060.2F84.4AB6           | 0050.0FAB.6C82       | 10.10.10.2        | 172.16.31.5            | 10.10.10.2   |


\
**Reflection Questions**
1. da
2. nu
3. nimic
4. destinatia
5. pentru ca este mai importanta destinatia decat sursa
6. no
7. la ruter
8. ruterul
9. de la device-urile care au trimis si primit informatie
10. nu
11. da
12. ~
13. ca sa le poate conecta intre ele
14. in loc de IPv4 am fi folosit adrese IPv6

### 6.3

**PART 1:**

**2.e.**   pentru ca PCA1 nu stie adresa MAC a PCA2 si intreaba toti vecinii ca sa o afle

**2.f.**   128

**2.g.**  
   -  135  
   - 0001.427E.E8ED SI 3333.FF00.000B

**2.h.**   nu

**2.i.**  
   - Ethernet II DEST ADDR: 3333.FF00.000B  
   - Ethernet II SRC ADDR:  0040.0BD2.243E  
   - IPv6 SRC IP: 2001:DB8:ACAD:1::B  
   - IPv6 DST IP: FF02::1:FF00:B

**2.j.**   pentru ca adresa ruterului nu e cea corespunzatoare si nici nu ne poate ajuta sa ajungem la adresa cautata

**2.l.**   da

**2.m.**   128

**2.o.**   pentru ca acum stie cum sa ajunga la PCA2 (adresa MAC) si nu trebuie sa mai intrebe vecinii

**PART 2:**

**1.f.**   FE80::201:42FF:FE73:E8ED

**1.g.**   0001.961D.6301

**1.i.**   adresa MAC destinatie

**1.m.**   pentru ping nu au fost, dar dupa da

**1.n.**  
   - cu cea a router-ului  
   - pentru ca trebuie sa se conecteze la alta retea

**2.b.**   
   - 4  
   - PCA1 si PCB1  
   - nu, pentru ca inca nu am avut nevoie sa ajungem la PCA2

**2.d.**   da

\
**Reflection Questions:**

**1.**   cand nu stie deja adresa MAC a device-ul destination

**2.**   cache-uieste adresele MAC 

**3.**   ~

**4.**   ~
