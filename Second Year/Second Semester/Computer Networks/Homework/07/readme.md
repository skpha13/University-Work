### 7.1

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

### 7.2

**PART 1:**

**2.b.**  
   - hostname = Router  
   - numar de interfete fast ethernet = 4  
   - numar de interfete fast ethernet = 2
   - numar de interfete serial = 2  
   - range vty lines = 0 4

**2.c.**   pentru ca inca n-am salvat configuratia in NVRAM

**PART 2:**

**2.a.**   show running-config

**2.c.**  
   - toate router-ele ar trebui sa aiba un mesaj al zilei pentru a ii avertiza pe cei ce se conecteaza ca accesul este interzis  
   - login

**2.d.**  
   - enable secret suprascrie enable password si daca ambele sunt setate pe router atunci trebuie introdusa enable secret  
   - o sa fie encrypted pentru ca service-ul de password-encryption cripteaza toate parolele curente si cele viitoare

**PART 3:**

**1.a.**  
   - copy running-config startup-config  
   - copy run start

**2.**  
   - 3  
   - c1900-universalk9-mz.SPA.151-4.M4.bin  
   - pentru ca se termina in .bin si restul in .xml

### 7.3

**PART 1:**

**1.a.**   show interfaces

**1.b.**   show interface serial 0/0/0

**1.c.**  
   - 209.165.200.225/30  
   - 1158 kilobits/sec

**1.d.**  
   - nu are adresa ip  
   - 000d.bd6c.7d01  
   - 1000000 Kbit

**2.a.**   show ip interface brief

**2.b.**  

   R1:  
   - serial interfaces = 2  
   - ethernet = 6  
   - nu, unele sunt gigabitethernet iar celelalte fastethernet

   R2:  
   - serial interfaces = 2  
   - ethernet = 2  
   - da

**3.a.**   show ip route

**3.b.**   
   - **1.** 1
   - **2.** 209.165.200.224/30
   - **3.** daca nu este listat il ignora

**PART 2:**

**3.**   copy running-config startup-config

**PART 3:**

**1.a.**  
   - 3 la fiecare  
   - ~
   - ~

**1.b.**   
   - **1.** 3
   - **2.** 2
   - **3.** 5
   - **4.** da

### 7.4

**PART 1**

**1.a.**
   - S1  -  192.168.10.1
   - S2  -  192.168.11.1
   - PC1 -  192.168.10.1
   - PC2 -  192.168.10.1
   - PC3 -  192.168.11.1
   - PC4 -  192.168.11.1

**1.b**

| TEST      | Successful? | Issues                                | Solution                              |
|-----------|-------------|---------------------------------------|---------------------------------------|
| PC1 to S1 | NU          | IP gresit la PC1                       | Am schimbat IP la 192.168.10.10       |
| PC1 to R1 | DA          | Aceeasi problema ca mai sus           | Am schimbat IP-ul                     |
| PC3 to S2 | NU          | S2 nu are adresa IP pentru Vlan1       | Am configurat Vlan1 cu ip 192.168.11.2|
| PC4 to R1 | DA          | Nu are probleme                        | Nu are solutie                        |


**PART 2**

| TEST        | Successful? | Issues                                        | Solution                                    |
|-------------|-------------|-----------------------------------------------|---------------------------------------------|
| PC4 to PC1  | NU          | Switch-urile nu au default gateway setat      | Am setat la S1 192.168.10.1 si S2 192.168.11.1|
| PC4 to PC1  | NU          | Default-gateway gresit                        | L-am setat la 192.168.11.1                  |

### 7.6

**PART 2:**

**1.c.**   nu 

**2.n.**   da, deoarce am configurat router-ul

**PART 3:**

**1.a.**  
   - c  
   - 2  
   - GigabitEthernet

**2.a.**  
   - up  
   - 0060.4731.8102  
   - 192.168.1.1/24

\
**Reflection Questions:**

**1.**  
   - interface gigabitethernet 0/0/1  
   - no shutdown

**2.**   nu ar mai exista comunicare intre PC-A si PC-B
