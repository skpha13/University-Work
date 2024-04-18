# Serializarea/Deserializarea obiectelor.

# Serializarea obiectelor
* Este procesul de conversie a unui obiect intr-un flux binar.
* Pentru a serializa un obiect (folosind I/O API), obiectul trebuie sa implementeze interfata marker _java.io.Serializable_
* Good practice: fiecare clasa serializabila declara variabila statica _serialVersionUID_, urmand ca ea sa fie updatata sau incrementata de fiecare data cand structura clasei se va schimba (ex1)
* Modificatorul **transient**: datele marcate cu acest modificator NU se serializeaza. Adica, la deserializare aceste date transient vor primi valorile Java default (Eg. 0.0 pentru Double sau null pt un obiect)
* Datele membre **statice** - NU se serializeaza
* Pentru ca o clasa sa fie serializabila, fiecare obiect folosit de aceasta clasa trebuie sa fie serializabil, tranzient sau sa aiba valoarea null la momentul serializarii (ex2)


# Deserializarea obiectelor
Este procesul de convertire a unui flux binar intr-un obiect.

