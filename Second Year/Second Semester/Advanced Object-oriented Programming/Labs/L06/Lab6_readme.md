# Interfete marker. Controlul mostenirii. Enums

#### Interfete marker
- Sunt interfete care nu contin nicio constanta si nicio metoda (Eg. java.lang.Cloneable; java.io.Serializable)
- Semnaleaza JVM ca se doreste asigurarea unei anumite functionalitati la run-time

#### Controlul mostenirii (sealed, permits)
- O clasa '_sealed_' trebuie sa aiba subclase, subclase care o extind si care vor fi listate de keyword-ul '_permits_'
  - [specificator] **_sealed_** **class** Clasa **_permits_** Subclasa1, Subclasa2 {...}
- O **subclasa** care extinde o clasa sealed trebuie sa fie _sealed_, _non-sealed_ sau _final_
- O interfata 'sealed' trebuie sa aiba interfata care sa o extinda si/sau subclasa/record care sa o implementeze
  - [public] **_sealed_** **interface** Interfata **_permits_** Subinterfata, Subclasa {...}

#### Enumerari
- Sunt tipuri speciale de clase java, declarate cu keyword-ul 'enum', folosite pt a contine o multime finita de valori (Eg. zilele saptamanii, anotimpurile, lunile anului, etc.)
- Nu pot fi extinse. Sunt de tip final si extind clasa java.lang.Enum
- Metode mostenite: public final String name(); public final int ordinal()
- Eg. sintaxa: `public enum Anotimp {PRIMAVARA, VARA, TOAMNA, IARNA;}` - enum simplu
- Metode generate de compilator (pentru exemplul de mai sus):
  - `public static enums.Anotimp[] values();` - intoarce un array al valorilor enumerarii
  - `public static enums.Anotimp valueOf(java.lang.String);`
- Accesare: `Anotimp a = Anotimp.VARA;`
- Pot fi comparate folosind equals() sau '==' deoarece fiecare valoare a enumerarii este initializata o singura data in JVM
- Enumerarile pot contine:
  - variabile de instanta
  - constructori
  - metode de instanta
  - metode statice
  - metode abstracte
