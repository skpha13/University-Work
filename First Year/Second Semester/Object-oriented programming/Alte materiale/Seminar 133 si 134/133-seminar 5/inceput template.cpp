#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Persoana{
protected:
    string nume;
public:
    virtual void citire(){
        cin>>nume;
    }
    virtual ~Persoana(){}
};
class Elev: protected Persoana{
private:
    string scoala;
public:
    void citire(){
    cin>>nume>>scoala;
    }
    void afisare(){
    cout<<nume<<" "<<scoala<<endl;
    }
};
class Grupa133: protected Persoana{
private:
    const int nota_poo;
public:
    Grupa133():nota_poo(10){}
    void citire(){
    cin>>nume;
    }
    void afisare(){
    cout<<nume<<" "<<nota_poo<<"\n";
    }
};
template <class T> class Gestiune{
vector<T> v;
int n;
public:
    void citire();
    void afisare();
};
template <> class Gestiune<Grupa133>{
vector<Grupa133> v;
int n;
public:
    void citire();
    void afisare();
};
template <class T> void Gestiune<T>::citire(){
    cin>>n;
    for(int i=0;i<n;i++)
    {
        T obj;
        obj.citire();
        v.push_back(obj);
    }
}
template <class T> void Gestiune<T>::afisare(){
    for(auto &x:v){
        x.afisare();
    }
}

void Gestiune<Grupa133>::citire(){
    cin>>n;
    for(int i=0;i<n;i++)
    {
        Grupa133 obj;
        obj.citire();
        v.push_back(obj);
    }
}
void Gestiune<Grupa133>::afisare(){
    sort(v.begin(),v.end());
    for(auto &x:v){
        x.afisare();
    }
}
int main()
{
    Gestiune<Elev> el;
    el.citire();
    el.afisare();
    Gestiune<Grupa133> gr;
    gr.citire();
    gr.afisare();
    return 0;
}
