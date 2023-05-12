#include <iostream>
#include <cstring>

using namespace std;

class seminar{
    string materie;
    int grupa[4], serie;
public:
    friend istream& operator>>(istream&, seminar&);
    friend ostream& operator<<(ostream&, const seminar&);
    int operator[](int);
    seminar& operator-();
    ///seminar& operator++();
    seminar& operator++(int);
    operator int();
    friend seminar& operator++(seminar&);

    seminar& operator=(seminar& other)
    {
        if(this != &other)
        {
            materie = other.materie;
            for (int i = 0; i < 4; ++i)
                grupa[i] = other.grupa[i];
            serie = other.serie;
        }
        return *this;
    }

    seminar& operator-(seminar& other)
    {
        seminar local(*this);
        local.serie -= other.serie;
        return local;
    }

    bool operator!=(const seminar& other)
    {
        for(int i = 0; i < 4; ++i)
            if (grupa[i] != other.grupa[i])
                return true;
        if (serie != other.serie)
            return true;
        if (materie != other.materie)
            return true;
        return false;
    }

    seminar& operator+(seminar& other)
    {
        seminar local(*this);
        local.serie += other.serie;
        return local;
    }

    seminar& operator+=(seminar& other)
    {
        *this = *this + other;
        return *this;
    }

    bool operator!()
    {
        if (materie == "POO")
            return false;
        return true;
    }
};
int main()
{
    seminar s1;
    cin>>s1;
    cout<<s1;
    cout<<s1[2];
    cout<<endl<<-s1;
    ++s1;
    s1++;
    cout<<endl<<s1;
    int y=s1;

    seminar v[3], s2, s3;
    v[0] = s1;
    cin >> s2 >> s3;
    v[1] = v[2] = s2 - s3;
    if (v[0] != v[2])
        v[0] += v[2];
    else if (!v[1]) cout << "v[1] nu e zero";

    return 0;
}
istream& operator>>(istream& in, seminar& s)
{
    in>>s.materie>>s.serie;
    for(int i=0; i<4;i++)
        in>>s.grupa[i];
    return in;
}
ostream& operator<<(ostream& out, const seminar& s)
{
    out<<s.materie<<" "<< s.serie<<" ";
    for(int i=0; i<4;i++)
        out<<s.grupa[i]<<" ";
    return out;
}
int seminar::operator[](int x)
{
    return this->grupa[x];
}
seminar& seminar::operator-()
    {
        this->serie=this->serie*(-1);
        return *this;
    }
/*seminar& seminar::operator++()
    {
        serie++;
        return *this;
    }*/
seminar& seminar::operator++(int)
    {
        serie++;
        return *this;
    }
seminar::operator int(){return this->serie;}
seminar& operator++(seminar& s)
    {
        s.serie++;
        return s;
    }
/************************* seminar 2 - 133 ************************/
/*
class Student{
    char* nume;
    int serie;
public:
    Student(){
        nume = new char[7];
        strcpy(nume, "anonim");
        serie = 0;
    }
    ~Student(){
        delete [] nume;
        }
    friend istream& operator>>(istream& is, Student& s);
    friend ostream& operator<<(ostream& os, const Student& s);
    Student& operator=(Student&);
    friend bool operator!=(Student &lhs,Student &rhs)
    {
        return !(strcmp(lhs.nume,rhs.nume)==0 && lhs.serie==rhs.serie);
    }
};

class Curs{
    char* nume;
    Student* studenti;
    int nr;
public:
    Curs(){
        nume = new char[7];
        strcpy(nume, "anonim");
        studenti = NULL;
        nr = 0;
    }
    ~Curs(){
        delete [] nume;
        delete [] studenti;
    }
    friend istream& operator>>(istream&, Curs&);
    friend ostream& operator<<(ostream&, const Curs&);
    Curs& operator+(Student& s);
    Curs& operator=(Curs& c);
    Curs& operator+(Curs& c);
     friend bool operator==(Curs &lhs,Curs &rhs)
    {
        if(lhs.nr!=rhs.nr)
        return false;
        for(int i=0;i<lhs.nr;i++)
            if(lhs.studenti[i]!=rhs.studenti[i])
                return false;
        if(strcmp(lhs.nume,rhs.nume)!=0)
        return false;
        return true;

    }
    Curs& operator++();
};

istream& operator>>(istream& is, Student& s){
    //is.get();
    cout<<"Dati numele: ";
    delete [] s.nume;
    s.nume = new char[255];
    is.getline(s.nume, 255);
    //is.get();
    cout<<"Dati seria: ";
    is>>s.serie;
    is.get();
    return is;
}

ostream& operator<<(ostream& os, const Student& s){
    os<<"Numele: "<<s.nume<<"\nSeria: "<<s.serie<<"\n";
    return os;
}

istream& operator>>(istream& is, Curs& c){
    delete [] c.nume;
    c.nume = new char[255];
    cout << "Dati numele cursului: ";
    is.getline(c.nume, 255);
    cout << "Dati numarul de studenti: ";
    is >> c.nr;
    is.get();
    if(c.studenti != NULL)
        delete [] c.studenti;
    c.studenti = new Student[c.nr];
    for(int i = 0; i < c.nr; i++){
        cout << "Dati informatiile pentru studentul " << i+1 <<"\n";
        is >> c.studenti[i];
    }
    return is;
}

ostream& operator<<(ostream& os, const Curs& c){
    os << "Cursul " << c.nume <<" are studentii: \n";
    for(int i = 0; i < c.nr; i++)
        os << c.studenti[i];
    return os;
}
Curs& Curs :: operator+(Student& s){
    Student* aux = new Student[this->nr];
    for(int i =0;i<this->nr;i++){
        aux[i] = this->studenti[i];
    }
    delete[] this->studenti;
    this->studenti = new Student[this->nr+1];
    for(int i =0;i<this->nr;i++){
         this->studenti[i] = aux[i];
    }
    delete[] aux;
    this->studenti[this->nr] = s;
    this->nr++;
    return *this;
}
Curs& Curs::operator+(Curs& c){
    if(strcmp(this->nume,c.nume)==0)
    {
        Student* aux = new Student[this->nr];
    for(int i =0;i<this->nr;i++){
        aux[i] = this->studenti[i];
    }
    delete[] this->studenti;
    this->studenti = new Student[this->nr+c.nr];
    for(int i =0;i<this->nr;i++){
         this->studenti[i] = aux[i];
    }
    for(int i=this->nr;i<c.nr+this->nr;i++)
        this->studenti[i]=c.studenti[i-this->nr];
    delete[] aux;

    this->nr+=c.nr;
    }
    return *this;
}
 Curs& Curs::operator++(){
     this->nr+=1;
     ///de adaugat studenti
     return *this;
 }
Curs& Curs::operator=(Curs&c){
    if (this != &c){
    this->nr =c.nr;
    delete[] this->nume;
    this->nume = new char[strlen(c.nume)+1];
    strcpy(this->nume,c.nume);
    delete[] this->studenti;
    this-> studenti = new Student[c.nr];
    for(int i =0;i<c.nr;i++){
        this->studenti[i] = c.studenti[i];
    }

    }
    return *this;
}
Student& Student::operator=(Student&s){
    if(this != &s){
        this->serie = s.serie;
        delete[] this->nume;
        this->nume = new char[strlen(s.nume)+1];
        strcpy(this->nume,s.nume);
    }
    return *this;
}
int main()
{
    Curs c1, c2, c3;
    cin >> c1;
    cout << c1;

    Student s;
    cin>>s;
    cout<<s;
    c1 = c1+s;
    cout <<c1;
    cin>>c2;
    c3=c1+c2;
    cout<<c3;

    if(c1==c2)
        cout<<"identic";
    else {++c1;
    cout<<"NU SUNT IDENTICE";}
    return 0;
}
*/
