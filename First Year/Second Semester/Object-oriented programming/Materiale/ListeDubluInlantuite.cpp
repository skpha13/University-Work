// Mihai Andrei-Cristian, grupa 212
// Implementarea unei liste dublu inlantuite folosind clase
#include <iostream>
using namespace std;

class Element
{
	int val;
	Element* urmator;
	Element* anterior;
public:
	int getVal() const;
	void setVal(int val);
	Element* getUrmator() const;
	void setUrmator(Element* urmator);
	Element* getAnterior() const;
	void setAnterior(Element* anterior);

	Element();
	Element(int val, Element* anterior, Element* urmator);
	Element(const Element& e);
	Element& operator=(const Element& e);
	~Element();
	friend ostream& operator<<(ostream& o, const Element& e);
};
int Element::getVal() const
{
	return this->val;
}
void Element::setVal(int val)
{
	this->val = val;
}
Element* Element::getUrmator() const
{
	return this->urmator;
}
void Element::setUrmator(Element* urmator)
{
	this->urmator = urmator;
}
Element* Element::getAnterior() const
{
	return this->anterior;
}
void Element::setAnterior(Element* anterior)
{
	this->anterior = anterior;
}

Element::Element()
{
	this->val = 0;
	this->urmator = NULL;
	this->anterior = NULL;
}
Element::Element(int val, Element* anterior, Element* urmator)
{
	this->val = val;
	this->urmator = urmator;
	this->anterior = anterior;
}
Element::Element(const Element& e)
{
	val = e.val;
	this->urmator = NULL;
	this->anterior = NULL;
}
Element& Element::operator=(const Element& e)
{
	if (this != &e)
	{
		val = e.val;
	}
	return *this;
}
Element::~Element()
{

}
ostream& operator<<(ostream& o, const Element& e)
{
	o << e.val << " ";
	return o;
}

class ListaDI
{
	Element* cap;
public:
	ListaDI();
	~ListaDI();

	friend ostream& operator<<(ostream& o, const ListaDI& l);
	bool insert(int poz, int val);
	void push_front(int val);
	void push_back(int val);

	ListaDI(Element* cap);
	ListaDI(const ListaDI& l);
	ListaDI& operator=(const ListaDI& l);

	bool deletePoz(int poz);
	bool pop_front();
	bool pop_back();
	int remove(int val);
	int size();
};
ListaDI::ListaDI()
{
	this->cap = NULL;
}
ListaDI::~ListaDI()
{
	Element* p = this->cap;
	while (p != NULL)
	{
		Element* deSters = p;
		p = p->getUrmator();
		delete deSters;
		deSters = NULL;
	}
}
ostream& operator<<(ostream& o, const ListaDI& l)
{
	Element* p = l.cap;
	while (p != NULL)
	{
		cout << *p;
		p = p->getUrmator();
	}
	return o;
}
bool ListaDI::insert(int poz, int val)
{
	if (poz < 0)
		return false;
	if (poz == 0)
	{
		if (cap != NULL)
		{
			Element* nou = new Element(cap->getVal(), cap, cap->getUrmator());
			cap->setVal(val);
			cap->setUrmator(nou);
		}
		else
		{
			cap = new Element(val, NULL, NULL);
		}
		return true;
	}

	Element* p = cap;
	int pozCurenta = 0;
	while (p != NULL)
	{
		if (pozCurenta == poz - 1)
		{
			if (p->getUrmator() == NULL)
			{
				Element* nou = new Element(val, p, NULL);
				p->setUrmator(nou);
			}
			else
			{
				Element* nou = new Element(val, p, p->getUrmator());
				(p->getUrmator())->setAnterior(nou);
				p->setUrmator(nou);

			}
			return true;
		}
		p = p->getUrmator();
		pozCurenta += 1;
	}
	return false;
}
void ListaDI::push_front(int val)
{
	insert(0, val);
}
void ListaDI::push_back(int val)
{
	Element* p = cap;
	int pozInserare = 0;
	while (p != NULL)
	{
		pozInserare += 1;
		p = p->getUrmator();
	}
	insert(pozInserare, val);
}
ListaDI::ListaDI(Element* cap)
{
	if (cap != NULL)
	{
		Element* p = cap;
		this->cap = new Element(*cap);
		p = p->getUrmator();
		while (p != NULL)
		{
			this->push_back(p->getVal());
			p = p->getUrmator();
		}
	}
	else
	{
		this->cap = NULL;
	}
}
ListaDI::ListaDI(const ListaDI& l)
{
	if (l.cap != NULL)
	{
		Element* parcurgeL = l.cap;
		this->cap = new Element(*l.cap);
		parcurgeL = parcurgeL->getUrmator();
		while (parcurgeL != NULL)
		{
			this->push_back(parcurgeL->getVal());
			parcurgeL = parcurgeL->getUrmator();
		}
	}
	else
	{
		this->cap = NULL;
	}
}
ListaDI& ListaDI::operator=(const ListaDI& l)
{
	if (this != &l)
	{
		if (l.cap != NULL)
		{
			Element* parcurgeL = l.cap;
			this->cap = new Element(*l.cap);
			parcurgeL = parcurgeL->getUrmator();
			while (parcurgeL != NULL)
			{
				this->push_back(parcurgeL->getVal());
				parcurgeL = parcurgeL->getUrmator();
			}
		}
		else
		{
			this->cap = NULL;
		}
	}
	return *this;
}
bool ListaDI::deletePoz(int poz)
{
	if (poz < 0)
		return false;
	Element* p = cap;
	if (poz == 0)
	{
		if (p != NULL)
		{
			if (p->getUrmator() != NULL)
			{
				Element* nextp = p->getUrmator();
				if (nextp->getUrmator() != NULL)
				{
					p->setVal(nextp->getVal());
					(nextp->getUrmator())->setAnterior(p);
					p->setUrmator(nextp->getUrmator());
					delete nextp;
					nextp = NULL;
				}
				else
				{
					p->setVal(nextp->getVal());
					p->setUrmator(NULL);
					delete nextp;
					nextp = NULL;
				}
			}
			else
			{
				delete cap;
				cap = NULL;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	int pozCurenta = 0;
	while (p != NULL)
	{
		if ((pozCurenta == poz - 1) && (p->getUrmator() != NULL))
		{
			Element* nextp = p->getUrmator();
			if (nextp->getUrmator() != NULL)
			{
				(nextp->getUrmator())->setAnterior(p);
				p->setUrmator(nextp->getUrmator());
				delete nextp;
				nextp = NULL;
			}
			else
			{
				p->setUrmator(NULL);
				delete nextp;
				nextp = NULL;
			}
			return true;
		}
		p = p->getUrmator();
		pozCurenta += 1;
	}
	return false;
}
bool ListaDI::pop_front()
{
	if (deletePoz(0))
		return true;
	return false;
}
bool ListaDI::pop_back()
{
	Element* p = cap;
	int pozCurenta = -1;
	while (p != NULL)
	{
		pozCurenta += 1;
		p = p->getUrmator();
	}
	if (deletePoz(pozCurenta))
		return true;
	return false;
}
int ListaDI::remove(int val)
{
	int gasit = 0;
	while (cap != NULL)
	{
		if (cap->getVal() == val)
		{
			this->deletePoz(0);
			gasit += 1;
		}
		else
		{
			break;
		}
	}

	Element* p = cap;
	int pozCurenta = 0;
	while (p != NULL)
	{
		pozCurenta += 1;
		if (p->getUrmator() != NULL)
		{
			if ((p->getUrmator())->getVal() == val)
			{
				deletePoz(pozCurenta);
				pozCurenta -= 1;
				gasit += 1;
			}
			else
			{
				p = p->getUrmator();
			}
		}
		else
		{
			p = p->getUrmator();
		}
	}
	return gasit;
}
int ListaDI::size()
{
	Element* p = cap;
	int pozCurenta = 0;
	while (p != NULL)
	{
		p = p->getUrmator();
		pozCurenta += 1;
	}
	return pozCurenta;
}

void Testari()
{
	cout << "=======================================================================================================================" << endl;
	cout << "Testari" << endl;
	cout << "=======================================================================================================================" << endl;
	cout << "push_front()\n\n";

	ListaDI l1;
	cout << "l1 = " << l1 << endl;
	l1.push_front(20);
	cout << "l1 = " << l1 << endl;
	l1.push_front(10);
	cout << "l1 = " << l1 << endl << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "push_back()\n\n";

	ListaDI l2;
	cout << "l2 = " << l2 << endl;
	l2.push_back(10);
	cout << "l2 = " << l2 << endl;
	l2.push_back(40);
	cout << "l2 = " << l2 << endl << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "insert(int poz, int val)\n\n";

	cout << "l2 = " << l2 << endl;
	l2.insert(1, 20);
	cout << "l2 = " << l2 << endl;
	l2.insert(2, 30);
	cout << "l2 = " << l2 << endl << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "pop_front()\n\n";

	cout << "l1 = " << l1 << endl;
	l1.pop_front();
	cout << "l1 = " << l1 << endl;
	l1.pop_front();
	cout << "l1 = " << l1 << endl << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "pop_back()\n\n";

	l1.push_back(10);
	l1.push_back(20);
	cout << "l1 = " << l1 << endl;
	l1.pop_back();
	cout << "l1 = " << l1 << endl;
	l1.pop_back();
	cout << "l1 = " << l1 << endl << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "deletePoz(int poz)\n\n";

	l1.push_back(10);
	l1.push_back(20);
	l1.push_back(30);
	l1.push_back(40);
	cout << "l1 = " << l1 << endl;
	l1.deletePoz(2);
	cout << "l1 = " << l1 << endl;
	l1.deletePoz(1);
	cout << "l1 = " << l1 << endl << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "remove(int val)\n\n";

	ListaDI l3;
	l3.push_back(10);
	l3.push_back(10);
	l3.push_back(30);
	l3.push_back(40);
	l3.push_back(10);
	l3.push_back(10);
	l3.push_back(50);
	l3.push_back(10);
	l3.push_back(60);
	cout << "l3 = " << l3 << endl;
	l3.remove(10);
	cout << "l3 = " << l3 << endl;
	l3.push_back(10);
	cout << "l3 = " << l3 << endl;
	l3.remove(10);
	cout << "l3 = " << l3 << endl << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "size()\n\n";

	cout << "l3 = " << l3 << endl;
	cout << "Dimensiune l3 = " << l3.size() << endl;
	l3.push_back(10);
	cout << "l3 = " << l3 << endl;
	cout << "Dimensiune l3 = " << l3.size() << endl << endl;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
}

int main()
{
	Testari();

	return 0;
}