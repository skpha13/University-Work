# Extinderea claselor. Polimorfism. Clasa Object

#### Extinderea claselor (derivare, mostenire):
- Este un mecanism de refolosire a codului. 
- Prin mostenire, o clasa de baza (parinte) este extinsa, adaugand functionalitate mai specializata
- Keyword: extends
- Nu putem mosteni mai multe clase simultan
- In Java, orice clasa extinde by default clasa Object.

#### Polimorfism
 - Capacitatea unui obiect de a lua forme diferite (A a = new B();)
 - Supraincarcare (overloading) - pot exista doua sau mai multe metode cu acelasi nume, dar având listele parametrilor diferite.
 - Suprascriere (overriding) - o subclasa rescrie o metoda a superclasei


#### Final keyword

- pe atribut/variabila: nu poate fi modificata (devine constanta)
- pe metoda: nu poate fi suprascrisa
- pe clasa: nu poate fi extinsa

### Ordinea de executare a constructorilor
- intai superclasa apoi subclasa (la instantierea unei subclase: new Subclass())
- super: apelul constructorului superclasei, daca exista, trebuie sa fie prima instructiune din constructorul subclasei
- daca nu se introduce în subclasa apelul explicit al unui constructor al superclasei, atunci compilatorul va
  incerca sa apeleze constructorul fara argumente al superclasei. Aceasta poate cauza o eroare în cazul în care
  superclasa nu are definit un constructor fara argumente, dar are definit unul cu argumente!

#### Clasa Object

- Este mostenita de orice clasa Java. Prin urmare, orice clasa Java mosteneste metodele clasei Object.
- Metode ale clasei Object: getClass(), toString(), equals(), hashCode()

#### Equals vs '== ''
- '==': obiectele sunt egale din punct de vedere al referintelor (au aceeasi referinta)
- equals:  obiectele sunt echivalente din punct de vedere al continutului