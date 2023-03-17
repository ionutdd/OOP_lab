#include <iostream>
#include <vector>

using namespace std;

// We begin with the first class which will be called 'Materie'
class Materie {
private:
	string denumire;
	bool optional;
public:
	Materie(const string altadenumire, const bool altoptional) //copy constructor for line 109
	{
		denumire = altadenumire;
		optional = altoptional;
		cout << "Constructor de copiere" << endl;
	}
	Materie() //default copy constructor for m3 on line 109
	{
		denumire = "";
		optional = false;
		cout << "Constructor de copiere default" << endl;
	}
	bool operator == (const Materie& altaMaterie) {  //overloading '==' operator for the condition inside the if from linie 110
		if (denumire == altaMaterie.denumire)
			return true;
		return false;
	}
	friend ostream& operator<<(ostream& out, Materie& materie) {  //overloading '<<' operator so that we can print out objects from class Materie
		out << "denumire: " << materie.denumire << endl << "optional: " << materie.optional << endl;
		return out;
	}
	~Materie()  //destructor for objects from class Materie
	{
		cout << endl << "Destructor materie" << endl;
	}
};

//We proceed with the 2nd class which will be called 'Student'
class Student {
private:
	int nrMatricol,grupa;
	string nume;
public:
	Student(const int altnrMatricol, const string altnume, const int altagrupa) //copy constructor for line 116
	{
		nrMatricol = altnrMatricol;
		grupa = altagrupa;
		nume = altnume;
		cout << "Constructor de copiere" << endl;
	}
	Student() //default copy constructor for s2 on line 115
	{
		cout << "Constructor de copiere default" << endl; 
		nrMatricol = 0;
		nume = "";
		grupa = 0;
	}
	friend istream& operator>>(istream& in, Student& student) {  // overloading ">>" operator so we can read objects from class Student
		in >> student.nrMatricol >> student.nume >> student.grupa;
		return in;
	}
	friend ostream& operator<<(ostream& out, const Student& student) { //overloading "<<" operator so we can print objects from class Student
		out << "Nr. Matricol: " << student.nrMatricol << endl << "nume: " << student.nume << endl << "grupa: " << student.grupa << endl;
		return out;
	}
	~Student() //destructor for objects from class Student
	{
		cout << endl << "Destructor student" << endl;
	}
};
//We now proceed to our 3rd clas which will be called Curs
class Curs{
	Materie mat;
	int nrStudenti;
	vector<Student> v;
public:
	Curs(const Materie materiadorita) //used on line 120 to get the required information
	{
		mat = materiadorita;
	}
	Curs operator+=(const Student& studentdorit) //overloading "+=" operator so that we can add a Student in our vector which will store information about our students (line 121)
	{
		this->v.push_back(studentdorit);
		return *this;
	}
	Curs operator+(const Student& studentintarziat) //this will do the same thing as "+=" operator (line 122)
	{
		this->v.push_back(studentintarziat);
		return *this;
	}
	friend ostream& operator<<(ostream& out, Curs& curs) { //overloading "<<" operator so we can print objects from class Curs
		out << "Materie: " << endl << curs.mat << endl << "nrStudenti: " << curs.v.size() << endl << "studenti:" << endl;
		for (const auto& i : curs.v)
			cout << i << " ";
		cout << endl;
		return out;
	}
	Materie materie() const { //helping us to get the information about 'materie' so we can put it into our mat value 
		return mat;
	}
	~Curs() //destructor for objects from class Curs
	{
		cout << endl << "Destructor curs" << endl;
	}
};
int main()
{
	Materie m1("POO", 0), m2("Pedagogie", 1), m3;
	if (m1 == m2)
		cout << "Cursuri identice";
	else
		cout << "Denumiri diferite";

	cout << endl <<endl << "Am trecut la clasa studenti" << endl << endl;
	Student s1(12, "Ionescu", 133), s2;
	cin >> s2;
	cout << s1 << s2;
	cout << endl << "Am trecut la clasa curs" << endl << endl;
	Curs c1(m1);
	c1 += s1;
	c1 = c1 + s2;
	Curs c2 = c1;
	cout << endl;
	cout << c2;
	m3 = c2.materie();
	cout << m3;
	return 0;
}
