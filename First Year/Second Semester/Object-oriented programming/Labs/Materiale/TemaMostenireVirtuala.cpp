//Mihai Andrei-Cristian, grupa 212
#include <iostream>
#include <string>
using namespace std;

class CitireAfisare
{
public:
	virtual istream& citire(istream&) = 0;
	virtual ostream& afisare(ostream&) const = 0;
};

class Persoana
{
protected:
	string nume;
	string cnp;
public:
	string getNume()const
	{
		return this->nume;
	}
	string getCnp()const
	{
		return this->cnp;
	}
	Persoana()
	{
		this->nume = "necunoscut";
		this->cnp = "necunoscut";
	}
	Persoana(string nume, string cnp)
	{
		this->nume = nume;
		this->cnp = cnp;
	}
	Persoana(const Persoana& p)
	{
		this->nume = p.nume;
		this->cnp = p.cnp;
	}
	virtual Persoana& operator=(const Persoana& p)
	{
		if (this != &p)
		{
			this->nume = p.nume;
			this->cnp = p.cnp;
		}
		return *this;
	}
	~Persoana()
	{

	}
	virtual istream& citire(istream& in)
	{
		cout << "Introduceti numele: ";
		getline(in, this->nume);

		cout << "Introduceti CNP-ul: ";
		getline(in, this->cnp);

		return in;
	}
	virtual ostream& afisare(ostream& o) const
	{
		o << "Nume: " << this->nume << endl;
		o << "CNP: " << this->cnp << endl;
		return o;
	}
	friend istream& operator>>(istream& in, Persoana& p)
	{
		return p.citire(in);
	}
	friend ostream& operator<<(ostream& o, const Persoana& p)
	{
		return p.afisare(o);
	}
};

class Student : virtual public Persoana
{
protected:
	string facultate;
public:
	Student() :Persoana()
	{
		this->facultate = "necunoscuta";
	}
	Student(string nume, string cnp, string facultate) :Persoana(nume, cnp)
	{
		this->facultate = facultate;
	}
	Student(const Student& s) :Persoana(s)
	{
		this->facultate = s.facultate;
	}
	Persoana& operator=(const Persoana& p)
	{
		if (this != &p)
		{
			Persoana::operator=(p);
			if (dynamic_cast<Student*>(const_cast<Persoana*>(&p)))
				this->facultate = dynamic_cast<Student*>(const_cast<Persoana*>(&p))->facultate;
		}
		return *this;
	}
	virtual Student& operator=(const Student& s)
	{
		if (this != &s)
		{
			Persoana::operator=(s);
			this->facultate = s.facultate;
		}
		return *this;
	}
	~Student()
	{

	}
	virtual istream& citire(istream& in)
	{
		Persoana::citire(in);
		cout << "Introduceti facultatea: ";
		getline(in, this->facultate);
		return in;
	}
	virtual ostream& afisare(ostream& o) const
	{
		Persoana::afisare(o);
		o << "Facultate: " << this->facultate << endl;
		return o;
	}
};

class Angajat : virtual public Persoana
{
protected:
	string functie;
public:
	Angajat() :Persoana()
	{
		this->functie = "necunoscuta";
	}
	Angajat(string nume, string cnp, string functie) :Persoana(nume, cnp)
	{
		this->functie = functie;
	}
	Angajat(const Angajat& a) :Persoana(a)
	{
		this->functie = a.functie;
	}
	Persoana& operator=(const Persoana& p)
	{
		if (this != &p)
		{
			Persoana::operator=(p);
			if (dynamic_cast<Angajat*>(const_cast<Persoana*>(&p)))
				this->functie = dynamic_cast<Angajat*>(const_cast<Persoana*>(&p))->functie;
		}
		return *this;
	}
	virtual Angajat& operator=(const Angajat& a)
	{
		if (this != &a)
		{
			Persoana::operator=(a);
			this->functie = a.functie;
		}
		return *this;
	}
	~Angajat()
	{

	}
	virtual istream& citire(istream& in)
	{
		Persoana::citire(in);
		cout << "Introduceti functia: ";
		getline(in, this->functie);
		return in;
	}
	virtual ostream& afisare(ostream& o) const
	{
		Persoana::afisare(o);
		o << "Functie: " << this->functie << endl;
		return o;
	}
};

class StudentAngajat : public Student, public Angajat
{
	bool practica;
public:
	StudentAngajat() :Persoana(), Student(), Angajat()
	{
		this->practica = false;
	}
	StudentAngajat(string nume, string cnp, string facultate, string functie, bool practica) :Persoana(nume, cnp), Student(nume, cnp, facultate), Angajat(nume, cnp, functie)
	{
		this->practica = practica;
	}
	StudentAngajat(const StudentAngajat& sa) :Persoana(sa), Student(sa), Angajat(sa)
	{
		this->practica = sa.practica;
	}
	Persoana& operator=(const Persoana& p)
	{
		if (this != &p)
		{
			if (dynamic_cast<StudentAngajat*>(const_cast<Persoana*>(&p)))
			{
				Student::operator=(p);
				this->functie = dynamic_cast<StudentAngajat*>(const_cast<Persoana*>(&p))->functie;
				this->practica = dynamic_cast<StudentAngajat*>(const_cast<Persoana*>(&p))->practica;
			}
			else
			{
				if (dynamic_cast<Angajat*>(const_cast<Persoana*>(&p)))
					Angajat::operator=(p);
				else
				{
					if (dynamic_cast<Student*>(const_cast<Persoana*>(&p)))
						Student::operator=(p);
					else
					{
						Persoana::operator=(p);
					}
				}
			}
		}
		return *this;
	}
	StudentAngajat& operator=(const StudentAngajat& sa)
	{
		if (this != &sa)
		{
			Student::operator=(sa);
			this->functie = sa.functie;
			this->practica = sa.practica;
		}
		return *this;
	}
	~StudentAngajat()
	{

	}
	virtual istream& citire(istream& in)
	{
		Student::citire(in);
		cout << "Introduceti functia: ";
		getline(in, this->functie);
		cout << "Introduceti daca face practica (0 - NU, 1 - DA): ";
		in >> this->practica;
		return in;
	}
	virtual ostream& afisare(ostream& o) const
	{
		Student::afisare(o);
		o << "Functie: " << this->functie << endl;
		o << (this->practica ? "Face practica" : "Nu face practica") << endl;
		return o;
	}
};


void Testari()
{
	cout << "=======================================================================================================================" << endl;
	cout << "Testari\n";
	cout << "=======================================================================================================================" << endl;
	cout << "Clasa Persoana\n";
	cout << "=======================================================================================================================" << endl;
	cout << "Constructor fara parametrii\n\n";

	Persoana p1;
	cout << p1 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Constructor cu toti parametrii\n\n";

	Persoana p2("Florina Bianca", "2980612434585");
	cout << p2 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Constructor copiere\n\n";

	Persoana p3(p2);
	cout << p3 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Operator =\n\n";

	Persoana p4;
	p4 = p2;
	cout << p4 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Citire si afisare\n\n";

	Persoana p5;
	cin >> p5;
	cout << p5 << endl;

	cout << "=======================================================================================================================" << endl;
	cout << "Clasa Student\n";
	cout << "=======================================================================================================================" << endl;
	cout << "Constructor fara parametrii\n\n";

	Student s1;
	cout << s1 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Constructor cu toti parametrii\n\n";

	Student s2("Georgescu Filip", "1990810428462", "Facultatea de Matematica si Informatica");
	cout << s2 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Constructor copiere\n\n";

	Student s3(s2);
	cout << s3 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Operator =\n\n";

	Student s4;
	s4 = s2;
	cout << s4 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Citire si afisare\n\n";

	Student s5;
	cin >> s5;
	cout << s5 << endl;

	cout << "=======================================================================================================================" << endl;
	cout << "Clasa Angajat\n";
	cout << "=======================================================================================================================" << endl;
	cout << "Constructor fara parametrii\n\n";

	Angajat a1;
	cout << a1 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Constructor cu toti parametrii\n\n";

	Angajat a2("Popescu Mihai", "1900207456897", "manager");
	cout << a2 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Constructor copiere\n\n";

	Angajat a3(a2);
	cout << a3 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Operator =\n\n";

	Angajat a4;
	a4 = a2;
	cout << a4 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Citire si afisare\n\n";

	Angajat a5;
	cin >> a5;
	cout << a5 << endl;

	cout << "=======================================================================================================================" << endl;
	cout << "Clasa StudentAngajat\n";
	cout << "=======================================================================================================================" << endl;
	cout << "Constructor fara parametrii\n\n";

	StudentAngajat sa1;
	cout << sa1 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Constructor cu toti parametrii\n\n";

	StudentAngajat sa2("Mazilu Adriana Elena", "5000302417691", "Facultatea de Matematica si Informatica", "programator", true);
	cout << sa2 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Constructor copiere\n\n";

	StudentAngajat sa3(sa2);
	cout << sa3 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Operator =\n\n";

	StudentAngajat sa4;
	sa4 = sa2;
	cout << sa4 << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Citire si afisare\n\n";

	StudentAngajat sa5;
	cin >> sa5;
	cout << sa5 << endl;

	cout << "=======================================================================================================================" << endl;
}

int main()
{
	Testari();
	return 0;
}