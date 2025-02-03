# Probleme Partea 2

## 1

Sa se arate ca bijectia lui Cantor:

```math
<x, y> = \frac{(x+y)(x+y+1)}{2} + y
```

este o functie primitiv recursiva

## 2

Sa se arate ca `2-COL` se poate reduce la `2-SAT`

## 3

Fie sistemul `2Q` un sistem de polinoame cu grad maxim `2` cu coeficientii numere intregi.

```math
p_i(x_1, x_2, ..., x_n) = 0
```

Daca `x` iau valori din multimea `{0, 1}`, este problema decidabila ?
 
## 4

Sa se arate ca `4-SAT` se reduce la `2Q`

## Rezolvari (nu neaparat corecte)

### 1

Fractia: 

```math
\frac{(x+y)(x+y+1)}{2}
```

Poate fi scrisa ca suma de primele `k` numere intregi (suma lui Gauss)

```math
T(0) = 0

\\

T(k+1) = T(k) + T(k+1)
```

Functia de mai sus e primitiv recursiva.
Deci bijectia lui Cantor se transforma in:

```math
f(x,y) = T(x + y) + y
```

T e primitiv recursiva, adunarea e o operatie primitiv recursiva => bijectia lui Cantor e primitiv recursiva

### 2

In 2-COL putem tranforma problema intr-una de `XOR-SAT`. Adica daca avem muchie intre A si B, relatia va fi transformata in urmatoarea clauza:

```math
(A \oplus B)
```

Facem asta pentru fiecare muchie, si la final verificam daca pentru graful nostru relatia da `0` sau `1`.

```math
XOR-SAT \leq_m 2-SAT 
```
> La cea de sus nu sunt asa sigur

```math
2-COL \leq_m XOR-SAT
```

Deci din cele 2 rezulta ca:

```math
2-COL \leq_m 2-SAT
```

### 3

Din cauza ca `x` iau valori `0` sau `1` o sa fie de fapt un sistme de polinoame de gradul `1`. Adica un fel de sistem de ecuatii liniare (cu mentiunea ca putem alege sau nu un element). 

Am zis ca este decidabil ca putem sa parcurgem o masca de biti de la `0` pana la `2^n` care si pentru fiecare masca in parte sa verificam toate polinoamele sa dea `0`. Daca gasim o masca inseamna ca am gasit o alegere de coeficienti care sa rezolve sistemul, altfel daca nu, inseamna ca nu are solutie. Deci este decidabil.

### 4

Aici am aratat ca `2Q` e un fel de `SAT`. Cel mai probabil gresit, dar am scris mai multe explicatii care nu au sens pe foaie.

Si cum stim ca:

```math
4-COL \leq_m SAT
```

```math
2Q = SAT
```

Rezulta ca:

```math
4-COL \leq_m 2Q
```


