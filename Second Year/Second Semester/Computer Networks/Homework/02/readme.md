### **2.1:**

**PART 1:**

**2.** 
   - **b.** 9600
   - **c.** S1

**3.**
   - **a.** connect
   - **b.** 
      - telnet terminal traceroute
      - telnet terminal

**PART 2:**

**1.** 
   - **a.** Turn on privileged commands
   - **b.** enable, nu se intampla nimic pentru ca nu stie ce comanda sa aleaga, telnet sau terminal
   - **c.** se schimba in S1#
   - **d.** 5

**2.**
   - **a.** Configuring from terminal, memory, or network? [terminal]?
   - **b.** se schimba in S1(config)#

**PART 3:**

**1.** 
   - **a.** 
      - *7:13:38.759 UTC Mon Mar 1 1993
      - 1993
   - **b.** incomplete command
   - **c.** set, Set the time and date
   - **d.** hh:mm:ss Current Time, ni se cere sa introducem orele, minutele si secundele. Daca nu introduceam si ?, ar fi afisat % Incomplete command

**2.**
   - **b.** 
      - cl + tab = nimic
      - clock = % Incomplete command
      - clock set 25:00:00 = % Invalid input detected at '^' marker
      - clock set 15:00:00 32 = % Invalid input detected at '^' marker

### **2.2:**

**PART 1:**

**3.** Putem verifica iesind din privileged EXEC mode si sa intram iar, introducand astfel parola. Sau putem folosi comanda show run si sa verificam daca parolele corespund.

**5.** copy running-config startup-config

**PART 2:**

**2.** 
   - **b.** Nu am reusit pentru ca nu am configurat IP-urile la switch-uri.

**PART 3:**

**1.** Configuram switch-ul cu un IP ca sa ne putem conecta de la distanta la el.
         no shutdown = ne face interfata activa

**4.** copy running-config startup-config

### **2.3:**

**F0/1:** 
   - S1 Status: up
   - S1 Protocol: up
   - S2 Status: up
   - S2 Protocol: up

**F0/6:**
   - S1 Status: up
   - S1 Protocol: up
   - S2 Status: down
   - S2 Protocol: down

**F0/18:**
   - S1 Status: down
   - S1 Protocol: down
   - S2 Status: up
   - S2 Protocol: up

**VLAN 1:**
   - S1 Status: up
   - S1 Protocol: up
   - S2 Status: up
   - S2 Protocol: up

**1.** Cele care sunt up sunt conectate cu alte device-uri, iar cele down nu

**2.** Adrese IP gresite, sau cablul de conectare gresit

### **2.4:**

**PART 1:**

**2.** 
   - **b.**
     - 24
     - 2
     - [0,4] si [5,15]
     - show startup-configuration
     - pentru ca inca nu am salvat configuratia in NVRAM

**PART 2:**

**7.** 
   - **b.** $1$mERr$ILwq/b7kc.7X/ejA4osn0
   - **c.** pentru ca ea este criptata

**8.** vor fi criptate, pentru ca am activat criptarea tuturor parolelor

**PART 3:**

**1.** mereu cand intram in CLI la switch

**2.** ca sa informeze persoana care se conecteaza despre anumite informatii precum faptul ca sistemul este down

**PART 4:**

**2.** copy run start

**3.** 
  - show startup-config
  - da
