# Clase si metode abstracte. String, StringBuilder, StringBuffer. Imutabilitate. Singleton

#### Metode abstracte
- Sunt declarate folosind modificatorul '**abstract**' inaintea tipului returnat
- Nu au body (nu au implementare). Se termina in ';'
- Exemplu: `public abstract int myMethod();`
- O metoda abstracta poate fi declarata doar intr-o clasa abstracta
- O metoda abstracta trebuie suprascrisa in prima subclasa concreta (clasa non-abstracta)

#### Clase abstracte
- Sunt declarate folosind modificatorul '**abstract**' inaintea cuvantului cheie 'class'
- Nu pot fi instantiate direct (~~new AbstractClass()~~)
- Pot contine metode abstracte (dar nu este obligatoriu)
- Exemplu: `public abstract class MyClass {}`

#### String
- Obiect pentru manevrarea sirurilor de caractere. Se bazeaza intern pe un char array.
- Este immutabil. Orice modificare asupra obiectului String necesita construirea altui obiect String.
- Tipuri de instantiere:
  1. `String name = "Fluffy";` // zona de memorie: Constant pool (string literal)
  2. `String name = new String("Fluffy");` // zona de memorie: Heap
- https://docs.oracle.com/en/java/javase/15/docs/api/java.base/java/lang/String.html

#### StringBuilder
- Reprezinta o secventa de caractere mutabila. Un StringBuilder poate fi modificat fara a se crea un alt obiect StringBuilder
- Nu este thread-safe (doua sau mai multe thread-uri pot modifica simultan acelasi obiect)
- https://docs.oracle.com/en/java/javase/15/docs/api/java.base/java/lang/StringBuilder.html

#### StringBuffer
- Reprezinta o secventa de caractere mutabila. Un StringBuilder poate fi modificat fara a se crea un alt obiect StringBuilder
- Este thread-safe
- https://docs.oracle.com/en/java/javase/15/docs/api/java.base/java/lang/StringBuffer.html

#### Array
- Este o zona de memorie in Heap avand spatiu alocat pentru un numar stabilit de elemente.
- Trebuie initializate (Exemplu: `int[] a = {1, 2, 3, 4, 5}`) sau alocate dinamic inainte de utilizare (Exemplu: `int a[] = new int[5]`).
- Poate fi de orice Java type (char[], String[], Object[])

#### Imutabilitate
- Dupa creare, continutul unui obiect nu mai poate fi modificat
- Clase imutabile predefinite in Java: String, Boolean, Float, Integer, Short, ...
- Reguli pentru crearea unei clase imutabile:
  1. clasa se declara 'final', ca sa nu poate fi extinsa de alte clase
  2. campurile se declara 'final' (li se atribuie valori o singura data printr-un constructor cu parametrii) si 'private' (nu pot fi modificate direct valorile)
  3. clasa are un constructor parametrizat
  4. clasa nu contine metode de tip 'set' sau altele care pot modifica valorile campurilor
  5. clasa contine metode 'get' pentru toate campurile ei
  6. daca clasa contine un obiect mutabil
   - in constructor, se foloseste o copie clona a acestui obiect, altfel ulterior, prin modificarea externa a obiectului transmis se schimba starea obiectului principal (container)
   - nu se va returna niciodata referinta catre obiectul mutabil, ci referinta spre o copie clona a lui

  #### Singleton
- Clasa care are va avea un singur obiect instantiat


