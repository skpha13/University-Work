# Exceptii. Fluxuri I/O

# Exceptii

Exceptie = eveniment ce se produce in timpul executiei unui program si ce
perturba functionarea corecta a acestuia.

##### Crearea exceptiilor
- Exceptiile sunt obiecte => pentru a instantia o exceptie se foloseste cuvantul cheie **new**

##### Aruncarea exceptiilor
- Pentru a arunca o exceptie => se foloseste cuvantul cheie **throw**

##### Tratarea exceptiilor
Exceptiile pot fi tratate in doua moduri:
- adaugand **throws** in antetul functiei
- folosind un bloc **try-catch**

##### Try - catch - finally
```java
try {
    // try block
} catch (Exception1 e) { // catch este optional daca exista finally
    // exception handler
} finally { // finally se executa intotdeauna, indiferent daca se produce sau nu exceptia
    // finally block
}
```
- Nu putem avea doar **try** bloc. Trebuie adaugat **catch** sau **finally** bloc. Sau ambele blocuri, **catch si finally**.
- Putem avea mai multe blocuri **catch** inlantuite (ordinea exceptiilor trebuie sa fie de la particular (subclasa) la general)
```java  
try {
    // try block
} catch (NumberFormatException e) { // NumberFormatException este subclasa a exceptiei IllegalArgumentException
  // exception handler
} catch (IllegalArgumentException e) {
    // exception handler
}
 ```
- Codul din catch se executa in cazul in care se arunca exceptia respectiva
- **finally** - poate fi adaugat dupa catch; codul din acest bloc se executa **intotdeauna**,
  si daca a fost aruncata exceptia, si daca nu.

##### Multi-catch block
```java
  try {
    // try block
  } catch (Exception1 | Exception2 e) {
    // exception handler
  }
```
- Se foloseste atunci cand se doreste acelasi rezultat indiferent de exceptia mentionata in catch
- Exceptiile nu trebuei sa fie intr-o relatie (`catch (FileNotFoundException | IOException p)` nu se compileaza)

##### Try-with-Resources
- Doar clasele care implementeaza interfata _AutoCloseable_ pot fi folosite in try-with-resources
```java
try (AutoCloseableClass autoCloseable = new AutoCloseableClass()) {
    // try block
} catch (Exception e) {
    // exception handler
}
```
##### Clasificarea exceptiilor
Nu toate exceptiile trebuie prinse.

- **Checked exceptions** (compile time): trebuie prinse si tratate
- **Unchecked exceptions** (run time): nu trebuie prinse

###### Checked exceptions
* Sunt exceptii care trebuie declarate (folosind **_throws_** in signatura metodei) sau tratate (folosind bloc **_try-catch_**) de codul aplicatiei unde sunt aruncate
* Exemplu: daca se citeste numele unui fisier de la tastatura, aplicatia urmand a-l deschide si parsa, in cazul in care acest
fisier nu exista, ar trebui sa aruncam o eroare; aceasta poate fi tratata ulterior, astfel
incat utilizatorul sa-si dea seama ca a intervenit o eroare (ex: sa ii afisam un mesaj de eroare)
* Exemple: _FileNotFoundException, IOException, SQLException, ParseException_

###### Errors
- Definesc situaţii excepţionale declanşate de factori externi aplicaţiei,
  ce nu pot fi de obicei anticipate sau tratate
- Exemple: 
  - alocarea unui obiect foarte mare =>  _OutOfMemoryError_
  - apelarea unei metode de catre ea insasi de multe ori => _StackOverflowError_

###### Runtime Exceptions
- Reprezinta situatii excepţionale, declanşate de factori interni aplicaţiei.
  Aplicaţia nu poate anticipa şi nu îşi poate reveni dacă acestea sunt aruncate.
- Aceste exceptii de obicei semnaleaza prezenta unui bug in cod, deci in loc sa le prindem, ar trebui sa gasim sursa
  problemei si sa o tratam.
- Exemple: _NullPointerException, NumberFormatException, ArithmeticException_

##### Good practices:
- nu folositi return intr-un bloc finally
- nu folositi throws intr-un bloc finally
- nu ignorati exceptiile (eg: doar sa le printam si sa continuam executia)

# Fluxuri I/O

- used to process input & to produce output
- package: **java.io**

Un **stream** reprezinta un flux de date

Tipuri de stream-uri:
- InputStream: folosit pentru a citi date
- OutputStream: folosit pentru a scrie date

#### Byte Streams

- 8 bit (octet)
- clase: FileInputStream/FileOutputStream
- utile daca vrem sa procesam date in format binar (ex: imagini)

#### Character Streams

- 16 bit (character)
- clase: FileReader/FileWriter
- in spate, foloseste tot FileInputStream/FileOutputStream
- utile daca vrem sa procesam caractere Unicode

#### File

- permite operații specifice fișierelor și directoarelor, precum creare, ștergere, mutare etc., mai puțin operații de citire/scriere.

Metode uzuale ale clasei File:
- String getAbsolutePath() – returnează calea absolută a unui fișier;
- String getName() – returnează numele unui fișier;
- boolean createNewFile() – creează un nou fișier, iar dacă fișierul există deja metoda returnează false;
- File[] listFiles() – listeaza fisierele dintr-un director

#### DataInputStream & DataOutputStream

- permit citirea și scrierea datelor la nivel de tipuri de date primitive sau siruri de caractere
- clase: DataInputStream/DataOutputStream


#### Fluxuri I/O folosind buffer

- numar mare de accesari => probleme de performanta
  Clase:
-  BufferedReader, BufferedWriter – fluxuri de procesare la nivel de buffer de caractere
-  BufferedInputStream, BufferedOutputStream – fluxuri de procesare la nivel de buffer de octeți