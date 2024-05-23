# Lambda. Interfete functionale. Referinte catre metode. Streams

Incepand cu Java 8 => suport pentru programare functionala

## Expresii lambda

* _Lambda_ este un concept din programarea functionala si reprezinta o functie anonima.
* Expresiile lambda au parametrii si body ca o metoda clasica dar nu au nume. 
* Sintaxa: `(lista parametrilor) -> {expresie sau instrucțiuni}`
* Exemple:

Valid lambda ce intoarce un boolean:

| Lambda                                       | Numar de parametrii   |
|----------------------------------------------|-----------------------|
| () -> true                                   | 0                     |
| x -> x.startsWith("test")                    | 1                     |
| (String x) -> x.startsWith("test")           | 1                     |
| (x, y) -> { return x.startsWith("test"); }   | 2                     |
| (String x, String y) -> x.startsWith("test") | 2                     |


## Interfete functionale

**Interfata functionala** => interfeta ce contine o singura metoda abstracta.
Acestea pot fi implementate folosind expresii lambda.
Ele au fost introduse pentru a reduce numarul de linii de cod scrise, si pentru a permite
pasarea functiilor ca si parametru altor metode.

- package: _java.util.function_ - interfete functionale uzuale, predefinite

#### Function

- primeste un parametru si intoarce un rezultat
- metoda abstracta: apply(Object)

#### BiFunction

- primeste 2 parametrii si intoarce un rezultat
- metoda abstracta: apply(Object, Object);

- IntFunction, DoubleFunction, IntToDoubleFunction, IntToLongFunction,
  DoubleToIntFunction,
  DoubleToLongFunction, LongToDoubleFunction, and LongToIntFunction.

#### Predicate

- primeste un parametru si returneaza Boolean
- metoda abstracta: test(Object)
- BiPredicate: primeste 2 parametrii

#### Supplier:

- nu primeste nici un parametru si returneaza un rezultat
- metoda abstracta: get()
- IntSupplier, DoubleSupplier, BooleanSupplier, LongSupplier

#### Consumer:

- primeste un parametru si nu returneaza nimic (void)
- metoda abstracta: accept(Object)
- IntConsumer, LongConsumer, DoubleConsumer, BiConsumer, ObjIntConsumer,
  ObjLongConsumer, ObjDoubleConsumer

#### UnaryOperator

- primeste un parametru si returneaza un rezultat de acelasi tip
- metoda abstracta: apply(Object)
- IntUnaryOperator, DoubleUnaryOperator, LongUnaryOperator

#### BinaryOperator

- primeste 2 parametrii si returneaza un rezultat de acelasi tip
- metoda abstracta: apply(Object, Object)
- IntBinaryOperator, LongBinaryOperator, DoubleBinaryOperator

#### Interfete functionale custom

- @FunctionalInterface
- compilatorul va arunca o eroare in cazul in care avem mai mult de o metoda abstracta

## Referinte catre metode (method references)
* Sunt un alt mod de simplificare al codului
* Pot fi utilizate in locul expresiilor lambda
* Exemplu:
  ```java
  Consumer<String> c = s -> System.out.println(s);
  Consumer<String> c = System.out::println;
  ```

## Streams

- stream = flux de elemente
- java.util.stream
- clasa: Stream<T>

#### Instantierea unui stream

- un stream poate fi creat dintr-o colectie / array
- metode: Collection/Array.stream() ; Stream.of()
- Stream.empty() : empty stream

#### Operatii pe stream-uri

Operatiile ce pot fi aplicate stream-urilor se impart in 2 categorii:

- operatii terminale (returneaza un alt rezultat)
- operatii intermediare (returneaza un stream)

Operatiile intermediare pot fi inlantuite.

Exemple de operatii intermediare:
- **map()** : converteste fiecare element din stream
- **filter()** : primeste un Predicate ca si parametru si filtreaza elementele stream-ului in functie de acesta
- **sorted()** : sorteaza un stream
- **distinct()** : returneaza elementele distincte din stream
- **flatMap()** : Stream<Collection<T>> -> Stream<T>

Exemple de operatii terminale:
- **foreach()** : aplica anumite operatii supra fiecarui element din stream
- **collect()** : stocheaza elementele din stream intr-o colectie
- **match()** : verifica un Predicate; returenaza boolean
- **count()** : returneaza numarul de elemente din stream
- **reduce()** : reduce elementele unui stream, folosind o functie; returneaza Optional
- **min(), max(), average()**

#### Stream.generate()

- primeste ca si parametru un Supplier pentru a genera elemente
- limit - numar elemente