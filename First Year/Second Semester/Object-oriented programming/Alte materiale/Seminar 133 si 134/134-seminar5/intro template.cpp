#include <iostream>
#include <vector>

using namespace std;

class Persoana {
protected:
    string nume;
public:
    virtual void citire()
    {
        cin >> nume;
    }
    virtual void afisare ()
    {
        cout << nume;
    }
};

class Copil : public Persoana {
    int varsta;
public:
    void citire()
    {
        cin >> nume >> varsta;
    }
    void afisare ()
    {
        cout << nume << ' ' << varsta;
    }
};

class Student : public Persoana {
protected:
    int grupa;
public:
    void citire() override
    {
        cin >> nume >> grupa;
    }
    void afisare () override
    {
        cout << nume << ' ' << grupa;
    }
};

class Student134 : public Student {
    float notaPOO;
public:

    Student134()
    {
        grupa = 134;
    }

    void citire() override
    {
        cin >> nume >> notaPOO;
    }
    void afisare () override
    {
        cout << nume << ' ' << notaPOO;
    }
};

template <class T>
class Gestiune {
    vector<T> v;
    int n;
public:
    void citire();
    void afisare();
};

template <class T>
void Gestiune<T>::citire()
{
    cin >> n;
}

template <class T>
void Gestiune<T>::afisare()
{
    cout << n;
}

// template<>
// class Gestiune<Student134>

int main()
{
    Gestiune<Persoana> A;
    Gestiune<Copil> B;
    Gestiune<Student> C;
    Gestiune<Student134> D;

    A.citire();
    B.citire();
    C.citire();
    D.citire();
    A.afisare();
    B.afisare();
    C.afisare();
    D.afisare();

    return 0;
}
