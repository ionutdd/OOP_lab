/*
Grupa, nume: 134 Dobrin Ionut-Alexandru
compilator default C++ Microsoft Visual Studio 2022
Tutore laborator: Caliman Stefan Daniel
*/

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <typeinfo>

using namespace std;

class trs : public exception {
public:
	const char* what()
	{
		return " Nu ai introdus un nr de trons >=1";
	}
};

class nr_trs : public exception {
public:
	const char* what()
	{
		return " Nu ai introdus un nr de trons >=1 si mai mic sau egal cu nr de tronsoane al drumului";
	}
};

class benzi : public exception {
public:
	const char* what()
	{
		return " Nu ai introdus un nr de benzi >=2";
	}
};

class drumm : public exception {
public:
	const char* what()
	{
		return " Nu ai introdus un tip de drum corect";
	}
};

class drumuri {
protected:
	string denumire;
	float lungime;
	int nr_trons;
public:
	drumuri(string denumire, float lungime, int nr_trons) : denumire(denumire), lungime(lungime), nr_trons(nr_trons) {}
	drumuri(drumuri& altdrum)
	{
		denumire = altdrum.denumire;
		lungime = altdrum.lungime;
		nr_trons = altdrum.nr_trons;
	}
	drumuri() {};
	friend ostream& operator<<(ostream& out, drumuri& drum)
	{
		out << "Drumul: " << drum.denumire << "lungimea: " << drum.lungime << "nr_trons: " << drum.nr_trons;
		return out;
	}
	~drumuri() {};
};

class national : virtual public drumuri {
	int nr_jud;
public:
	national(string denumire, float lungime, int nr_trons, int nr_jud) {
		denumire = denumire;
		lungime = lungime;
		nr_trons = nr_trons;
		nr_jud = nr_jud;
	}
	national(national& altnational)
	{
		denumire = altnational.denumire;
		lungime = altnational.lungime;
		nr_trons = altnational.nr_trons;
		nr_jud = altnational.nr_jud;
	}
	friend ostream& operator<<(ostream& out, national& nat)
	{
		out << "Drumul: " << nat.denumire << "lungimea: " << nat.lungime << "nr_trons: " << nat.nr_trons << "nr_jud: " << nat.nr_jud;
		return out;
	}
	~national() {};
};

class european : virtual public drumuri {
protected:
	int nr_tari;
public:
	european(string denumire, float lungime, int nr_trons, int nr_tari) {
		denumire = denumire;
		lungime = lungime;
		nr_trons = nr_trons;
		nr_tari = nr_tari;
	}
	european(european& alteuropean)
	{
		denumire = alteuropean.denumire;
		lungime = alteuropean.lungime;
		nr_trons = alteuropean.nr_trons;
		nr_tari = alteuropean.nr_tari;
	}
	friend ostream& operator<<(ostream& out, european& euro)
	{
		out << "Drumul: " << euro.denumire << "lungimea: " << euro.lungime << "nr_trons: " << euro.nr_tari;
		return out;
	}
	european() {};
	~european() {};
};


class autostrada : virtual public drumuri {
protected:
	int nr_benzi;
public:
	autostrada(string denumire, float lungime, int nr_trons, int nr_benzi) {
		denumire = denumire;
		lungime = lungime;
		nr_trons = nr_trons;
		nr_benzi = nr_benzi;
	}
	autostrada(autostrada& altautostrada)
	{
		denumire = altautostrada.denumire;
		lungime = altautostrada.lungime;
		nr_trons = altautostrada.nr_trons;
		nr_benzi = altautostrada.nr_benzi;
	}
	friend ostream& operator<<(ostream& out, autostrada& autoo)
	{
		out << "Drumul: " << autoo.denumire << "lungimea: " << autoo.lungime << "nr_trons: " << autoo.nr_trons << "nr_benzi: " << autoo.nr_benzi;
		return out;
	}
	autostrada() {};
	~autostrada() {};
};

class autoeuro : public autostrada, public european {
public:
	autoeuro(string denumire, float lungime, int nr_trons, int nr_tari, int nr_benzi) {
		denumire = denumire;
		lungime = lungime;
		nr_trons = nr_trons;
		nr_tari = nr_tari;
		nr_benzi = nr_benzi;
	}
	autoeuro(autoeuro& altautoeuro)
	{
		denumire = altautoeuro.denumire;
		lungime = altautoeuro.lungime;
		nr_trons = altautoeuro.nr_trons;
		nr_tari = altautoeuro.nr_tari;
		nr_benzi = altautoeuro.nr_benzi;
	}
	friend ostream& operator<<(ostream& out, autoeuro& alt)
	{
		out << "Drumul: " << alt.denumire << "lungimea: " << alt.lungime << "nr_trons: " << alt.nr_trons << "nr_tari: " <<alt.nr_tari << "nr_benzi" << alt.nr_benzi;
		return out;
	}
	autoeuro() {};
	~autoeuro() {};
};

class contracte {
	int unic;
	string nume;
	string cif;
	vector<drumuri> v;
	int tronson;
public:
	contracte(int unic, string nume, string cif, vector<drumuri>v, int tronson)
	{
		unic = unic;
		nume = nume;
		cif = cif;
		for (int i = 0; i < v.size(); i++)
		{
			v[i] = v[i];
		}
		tronson = tronson;
	}
	contracte(contracte& altcontract)
	{
		unic = unic;
		nume = nume;
		cif = cif;
		for (int i = 0; i < v.size(); i++)
		{
			v[i] = v[i];
		}
		tronson = tronson;
	}
	contracte() {};
	friend ostream& operator<<(ostream& out, contracte& contr)
	{
		for (int i = 0; i < contr.v.size(); i++)
		{
			out << "Contractul cu id-ul: " << contr.unic << "numele: " << contr.nume << "CIF: " << contr.cif << "tronson: " << contr.tronson;
			out << contr.v[i];
		}
		return out;
	}
	~contracte() {};
};
int main()
{
	//ar fi trebuit sa fac la linia 226 vector de contracte, nu de drumuri si de aceea am eroarea de no copy constructor in class 'drumuri'
	//daca as mai fi avut timp, as fi facut pentru punctele b si c sa mearga getter pentru cif si lungime 
	//si as fi modificat vectorul sa fi fost de tipul contracte ca sa stocheze informatii despre contracte
	/*while (true)
	{
		cout << "1.Introduceti contract nou" << endl;
		cout << "2.Iesire program" << endl;
		cout << "Introduceti optiune: ";
		int op;
		int unic = 0;
		float cost;
		cin >> op;
		cout << endl;
		vector<drumuri> v;
		switch (op)
		{
		case(1): 
			{
				unic += 1;
				string nume;
				cout << "Introduceti nume: ";
				cin >> nume;
				string cif;
				cout << "Introduceti cif: ";
				cin >> cif;
				int tronson;
				cout << "Introduceti tronson: ";
				cin >> tronson;

				cout << "Acum introdu informatii pentru drum: ";
				string tip;
				cout << "Intodu tip de drum (national, european, autostrada, autoeuro)";
				cin >> tip;
				string denumire;
				cout << "Intodu denumirea drumului";
				cin >> denumire;
				float lungime;
				cout << "Intodu lungimea drumului";
				cin >> lungime;
				int nr_trons;
				cout << "Intodu numarul de tronsoane al drumului";
				cin >> nr_trons;
				try {
					if (nr_trons < 1)
						throw nr_trs();
				}
				catch (nr_trs& obj)
				{
					cout << obj.what() << endl;
					break;
				}
				if (tip == "national")
				{
					int nr_jud;
					cout << "Introdu numarul de judete al drumului: ";
					cin >> nr_jud;
					national nat(denumire, lungime, nr_trons, nr_jud);
					v.push_back(nat);
					cost = 3000 / 1000 * lungime / nr_trons;
				}
				else if (tip == "european")
				{
					int nr_tari;
					cout << "Introdu numarul de tari al drumului: ";
					cin >> nr_tari;
					european eur(denumire, lungime, nr_trons, nr_tari);
					v.push_back(eur);
					cost = 3000 / 1000 * lungime / nr_trons + 500/1000 * nr_tari;
				}
				else if (tip == "autostrada")
				{
					int nr_benzi;
					cout << "Introdu numarul de benzi al drumului: ";
					cin >> nr_benzi;
					try {
						if (nr_benzi<2)
							throw benzi();
					}
					catch (benzi& obj)
					{
						cout << obj.what() << endl;
						break;
					}
					cost = 2500 / 1000 * nr_benzi * lungime / nr_trons;
					autostrada aut(denumire, lungime, nr_trons, nr_benzi);
					v.push_back(aut);
				}
				else if (tip == "autoeuro")
				{
					int nr_benzi;
					cout << "Introdu numarul de benzi al drumului: ";
					cin >> nr_benzi;
					try {
						if (nr_benzi < 2)
							throw benzi();
					}
					catch (benzi& obj)
					{
						cout << obj.what() << endl;
						break;
					}
					int nr_tari;
					cout << "Introdu numarul de tari al drumului: ";
					cin >> nr_tari;
					cost = 2500 / 1000 * nr_benzi * lungime / nr_trons + 500/1000 * nr_tari;
					autoeuro aueu(denumire, lungime, nr_trons, nr_tari, nr_benzi);
					v.push_back(aueu);
				}
				else {
					try {
							throw drumm();
					}
					catch (drumm& obj)
					{
						cout << obj.what() << endl;
						break;
					}
				}
				try {
					if (tronson<1 || tronson > nr_trons)
						throw trs();
				}
				catch (trs& obj)
				{
					cout << obj.what() << endl;
					break;
				}
				
					
				if (tip == "autostrada")
					cost = 3000 / 1000 * lungime / nr_trons;
			}
		case(2):
		{
			break;
			//c
			/*int cif;
			cout << "Introduceti cif-ul contractului caruia sa ii dam erase: ";
			cin >> cif;
				for (int i = 0; i < v.size(); i++)
				{
					if (typeid(v[i].cif) == cif)
						v.erase(i);
				}*/
			/*
			//d
				string denumire;
			cout << "Introduceti denumirea drumului caruia sa ii calculam costul total: ";
			cin >> denumire;
		}
		}
		for (int i = 0; i < v.size(); i++)
			cout << v[i];
		
		//b
		/*int suma = 0, sumauto = 0;
		for (int i = 0; i < v.size(); i++)
		{
			suma += v[i].lungime; //nu merge getter lung
		}
		for (int i = 0; i < v.size(); i++)
		{
			if(typeid(v[i]) == typeid(autostrada))
				sumauto += v[i].lungime; //nu merge getter lung
		}
		*/
	//}//
	return 0;
}