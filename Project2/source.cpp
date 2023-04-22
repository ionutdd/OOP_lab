#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <typeinfo>
using namespace std;

//Exceptii
class LocuintaException : public exception {
public:
    LocuintaException() noexcept {}
    virtual ~LocuintaException() noexcept {}
    virtual const char* what() const noexcept { return "Locuinta exception"; }
};

class SuprafataUtilaNegativaException : public LocuintaException {
public:
    SuprafataUtilaNegativaException() noexcept {}
    virtual ~SuprafataUtilaNegativaException() noexcept {}
    virtual const char* what() const noexcept { return "Suprafata utila negativa"; }
};

class DiscountInvalidException : public LocuintaException {
public:
    DiscountInvalidException() noexcept {}
    virtual ~DiscountInvalidException() noexcept {}
    virtual const char* what() const noexcept { return "Discount invalid"; }
};

class Locuinta {
protected:
    string numeClient;
    int suprafataUtila;
    float discount;
public:
    Locuinta(string numeClient, int suprafataUtila, float discount) : numeClient(numeClient), suprafataUtila(suprafataUtila), discount(discount) {
        if (suprafataUtila < 0) {
            throw SuprafataUtilaNegativaException();
        }
        if (discount < 0 || discount > 100) {
            throw DiscountInvalidException();
        }
    }

    virtual int CalculChirie(int X, int Y) = 0;

    static int numarLocuinte;
    static int GetNumarLocuinte() {
        return numarLocuinte;
    }
    float getDiscount()
    {
        return discount;
    }

    friend ostream& operator<<(ostream& out, Locuinta& locuinta) {
        out << "Nume client: " << locuinta.numeClient << endl
            << "Suprafata utila: " << locuinta.suprafataUtila << endl
            << "Discount: " << locuinta.discount << endl;
        return out;
    }
};

class Apartament : public Locuinta {
private:
    int etaj;
public:
    Apartament(string numeClient, int suprafataUtila, float discount, int etaj) : Locuinta(numeClient, suprafataUtila, discount), etaj(etaj) {}

    int CalculChirie(int X, int Y) override {
        return X * suprafataUtila * (1 - Y * discount / 100.0);
    }

    friend ostream& operator<<(ostream& out, Apartament& apartament) {
        out << "Tip locuinta: Apartament" << endl
            << "Etaj: " << apartament.etaj << endl
            << static_cast<Locuinta&>(apartament);
        return out;
    }
};

class Casa : public Locuinta {
private:
    int suprafataCurte;
public:
    Casa(string numeClient, int suprafataUtila, float discount, int suprafataCurte) : Locuinta(numeClient, suprafataUtila, discount), suprafataCurte(suprafataCurte) {}

    int CalculChirie(int X, int Y) override {
        return X * (suprafataUtila + 0.2 * suprafataCurte) * (1 - Y * discount / 100.0);
    }
    friend ostream& operator<<(ostream& out, Casa& casa) {
        out << "Tip locuinta: Casa" << endl
            << "Suprafata curte: " << casa.suprafataCurte << endl
            << static_cast<Locuinta&>(casa);
        return out;
    }
};

class AgentieImobiliara {
private:
    vector<unique_ptr<Locuinta>> v;
public:
    AgentieImobiliara() {}

    void adaugaLocuinta(unique_ptr<Locuinta> locuinta) {
        v.push_back(move(locuinta));
    }

    Locuinta* getLocuinta(int index) {
        return v[index].get();
    }

    int getNumarLocuinte() {
        return v.size();
    }

    // Metoda pentru a accesa vectorul v
    vector<unique_ptr<Locuinta>>& getVectorLocuinte() {
        return v;
    }

    // Metoda pentru a modifica vectorul v
    void setVectorLocuinte(vector<unique_ptr<Locuinta>> newV) {
        v = move(newV);
    }

    friend istream& operator>>(istream& in, AgentieImobiliara& agentie) {
        int numLocuinte;
        in >> numLocuinte;
        for (int i = 0; i < numLocuinte; i++) {
            string tip;
            in >> tip;
            if (tip == "Apartament") {
                string numeClient;
                int suprafataUtila, etaj;
                float discount;
                in >> numeClient >> suprafataUtila >> discount >> etaj;
                unique_ptr<Locuinta> apartament = make_unique<Apartament>(numeClient, suprafataUtila, discount, etaj);
                agentie.adaugaLocuinta(move(apartament));
            }
            else if (tip == "Casa") {
                string numeClient;
                int suprafataUtila, suprafataCurte;
                float discount;
                in >> numeClient >> suprafataUtila >> discount >> suprafataCurte;
                unique_ptr<Locuinta> casa = make_unique<Casa>(numeClient, suprafataUtila, discount, suprafataCurte);
                agentie.adaugaLocuinta(move(casa));
            }
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, AgentieImobiliara& agentie) {
        for (int i = 0; i < agentie.getNumarLocuinte(); i++) {
            out << "Chiria pentru locuinta cand avem discount " << i + 1 << " este: " << agentie.getLocuinta(i)->CalculChirie(10, 1) << endl;
            out << "Chiria pentru locuinta cand nu avem discount " << i + 1 << " este: " << agentie.getLocuinta(i)->CalculChirie(10, 0) << endl;
            out << *(agentie.getLocuinta(i)) << endl;
        }
        return out;
    }
};


int main() {

    AgentieImobiliara agentie;
    int optiune;
    while (true) {
        cout << "Meniu:" << endl;
        cout << "1. Adauga o locuinta noua" << endl;
        cout << "2. Afiseaza toate locuintele" << endl;
        cout << "3. Calculeaza chiria pentru o locuinta" << endl;
        cout << "4. Iesire din program" << endl;
        cout << "Introduceti optiunea dorita: ";
        cin >> optiune;
        switch (optiune) {
        case 1: {
            string tip;
            cout << "Introduceti tipul locuintei (Apartament/Casa): ";
            cin >> tip;
            if (tip == "Apartament") {
                string numeClient;
                int suprafataUtila, etaj;
                float discount;
                cout << "Introduceti numele clientului: ";
                cin >> numeClient;
                cout << "Introduceti suprafata utila: ";
                cin >> suprafataUtila;
                cout << "Introduceti discount-ul: ";
                cin >> discount;
                cout << "Introduceti etajul: ";
                cin >> etaj;
                unique_ptr<Locuinta> apartament = make_unique<Apartament>(numeClient, suprafataUtila, discount, etaj);
                agentie.adaugaLocuinta(move(apartament));
                cout << "Apartament adaugat cu succes!" << endl;
            }
            else if (tip == "Casa") {
                string numeClient;
                int suprafataUtila, suprafataCurte;
                float discount;
                cout << "Introduceti numele clientului: ";
                cin >> numeClient;
                cout << "Introduceti suprafata utila: ";
                cin >> suprafataUtila;
                cout << "Introduceti discount-ul: ";
                cin >> discount;
                cout << "Introduceti suprafata curtii: ";
                cin >> suprafataCurte;
                unique_ptr<Locuinta> casa = make_unique<Casa>(numeClient, suprafataUtila, discount, suprafataCurte);
                agentie.adaugaLocuinta(move(casa));
                cout << "Casa adaugata cu succes!" << endl;
            }
            else {
                cout << "Tip de locuinta invalid! Introduceti 'Apartament' sau 'Casa'." << endl;
            }
            break;
        }
        case 2: {
            int numarLocuinte = agentie.getNumarLocuinte();
            if (numarLocuinte == 0) {
                cout << "Nu exista locuinte in baza dedate!" << endl;
            }
            else {
                cout << "Lista de locuinte:" << endl;
                cout << agentie;
            }
            break;
        }
        case 3: {
            int index;
            cout << "Introduceti indexul locuintei: ";
            cin >> index;
            if (index < 1 || index > agentie.getNumarLocuinte()) {
                cout << "Index invalid!" << endl;
            }
            else {
                float chiria = agentie.getLocuinta(index - 1)->CalculChirie(10,1);
                cout << "Chiria pentru locuinta cand avem discount" << index << " este " << chiria << endl;
                chiria = agentie.getLocuinta(index - 1)->CalculChirie(10, 0);
                cout << "Chiria pentru locuinta cand nu avem discount" << index << " este " << chiria << endl;
            }
            break;
        }
        case 4: {
            cout << "La revedere!" << endl;
            return 0;
        }
        default: {
            cout << "Optiune invalida!" << endl;
        }
        }
    }
 
    return 0;
}
