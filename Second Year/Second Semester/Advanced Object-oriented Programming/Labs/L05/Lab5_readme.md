# Records. Interfete. Comparable. Comparator

#### Records
- Sunt tipuri speciale de clase java in care compilatorul insereaza boilerplate cod (constructor canonic, getters, equals, hashCode, toString)
- Sunt implicit final si extind clasa abstracta java.lang.Record
- Eg. sintaxa: `public record Student(String nume, int grupa, double medie) {}`
- Se pot adauga constructori:
  - _canonic_ (toate componentele recordului in ordinea definirii) cu prelucrari suplimentare ale componentelor record-ului
  - _compact_, fara lista de parametrii (Eg. `public Student {}`)
  - _custom_, cu lista partiala de parametrii (Eg. 
      `public Student(String nume) {
        this(nume, 0, 0);
      }`
  )
- Se pot adauga:
  - date, metode si blocuri de initializare **statice**
  - metode **nestatice**


#### Interfete
- keyword: **interface**
- modificator de acces: public sau default package

Pot contine:
- constante (implicit public, static si final)
- metode abstracte (fara implementare), implicit public si abstract
- metode implicite (default) cu implementare
- metode statice cu implementare
- metode private cu implementare

Utilizare:
- inainte de a utiliza o interfata, este nevoie de o clasa care sa o implementeze (o interfata nu poate fi instantiata direct) - keyword: **implements**
- o clasa poate implementa mai multe interfete
- o clasa care implementeaza o interfata trebuie sa ii implementeze toate metodele abstracte
- o interfata poate mosteni alte interfete - keyword: **extends**

**Comparable si Comparator**

Java pune la dispozitie doua interfete pentru a compara obiectele in vederea sortarii lor

**Comparable**

- Un obiect Comparable (care implementeaza interfata **java.lang.Comparable** ) este capabil sa se compare el insusi cu un alt obiect.
- Comparable asigură o sortare naturală a obiectelor după un anumit criteriu.
- Clasele de tip Number (Integer, Double,..) implementeaza interfata Comparable
- Interfata Comparable are o singura metoda:
    `public interface Comparable<T> {
        int compareTo(T o);
    }`

- **_public int compareTo(Object obj):_** este folosita pentru a compara obiectul curent cu un alt obiect specificat. Returneaza:
  - un intreg pozitiv, daca obiectul curent este mai mare decat obiectul specificat
  - un intreg negativ, daca obiectul curent este mai mic decat obiectul specificat
  - zero, daca obiectul curent este egal cu obiectul specificat

**Comparator**
- Spre deosebire de Comparable, un Comparator (care implementeaza interfata java.util.Comparator) este o clasa diferita, externa obiectelor pe care le compara. Este o clasa separata.
- Un Comparator este folosit atunci cand este nevoie de strategii de comparare mai complexe
- Pot fi transmisi unei metode de sortare (Eg. Collections.sort(List,Comparator) sau Arrays.sort(Object[],Comparator))

- **_public int compare(Object o1, Object o2):_** compara doua obiecte. Returneaza un intreg negativ, zero, sau un intreg pozitiv daca primul argument este mai mic, egal, sau mai mare decat al doilea.





