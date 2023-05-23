#pragma once
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


template <typename T>
class Locuinta {
public:
    virtual T CalculChirie(int X, int Y) = 0;
};

class MyLocuinta : public Locuinta<int> {
protected:    
    string numeClient;
    int suprafataUtila;
    float discount;
    int specificitate;
public:
    MyLocuinta(string numeClient, int suprafataUtila, float discount, int specificitate) : numeClient(numeClient), suprafataUtila(suprafataUtila), discount(discount), specificitate(specificitate) {
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

    friend ostream& operator<<(ostream& out, MyLocuinta& locuinta) {
        out << "Nume client: " << locuinta.numeClient << endl
            << "Suprafata utila: " << locuinta.suprafataUtila << endl
            << "Discount: " << locuinta.discount << endl;
        return out;
    }
    virtual ~MyLocuinta() {}
};

class Apartament : public MyLocuinta {
private:
    int etaj;
public:
    Apartament(string numeClient, int suprafataUtila, float discount, int etaj) : MyLocuinta(numeClient, suprafataUtila, discount, etaj)  {}

    int CalculChirie(int X, int Y) override {
        return X * suprafataUtila * (1 - Y * discount / 100.0);
    }

    friend ostream& operator<<(ostream& out, Apartament& apartament) {
        out << "Tip locuinta: Apartament" << endl
            << "Etaj: " << apartament.etaj << endl
            << static_cast<MyLocuinta&>(apartament);
        return out;
    }
    ~Apartament() {}
};

class Casa : public MyLocuinta {
private:
    int suprafataCurte;
public:
    Casa(string numeClient, int suprafataUtila, float discount, int suprafataCurte) : MyLocuinta(numeClient, suprafataUtila, discount, suprafataCurte) {}

    int CalculChirie(int X, int Y) override {
        return X * (suprafataUtila + 0.2 * suprafataCurte) * (1 - Y * discount / 100.0);
    }
    friend ostream& operator<<(ostream& out, Casa& casa) {
        out << "Tip locuinta: Casa" << endl
            << "Suprafata curte: " << casa.suprafataCurte << endl
            << static_cast<MyLocuinta&>(casa);
        return out;
    }
    ~Casa() {}
};

class AgentieImobiliara {
private:
    vector<unique_ptr<MyLocuinta>> v;
public:
    AgentieImobiliara() {}

    void adaugaLocuinta(unique_ptr<MyLocuinta> locuinta) {
        v.push_back(move(locuinta));
    }

    MyLocuinta* getLocuinta(int index) {
        return v[index].get();
    }

    int getNumarLocuinte() {
        return v.size();
    }

    // Metoda pentru a accesa vectorul v
    vector<unique_ptr<MyLocuinta>>& getVectorLocuinte() {
        return v;
    }

    // Metoda pentru a modifica vectorul v
    void setVectorLocuinte(vector<unique_ptr<MyLocuinta>> newV) {
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
                unique_ptr<MyLocuinta> apartament = make_unique<Apartament>(numeClient, suprafataUtila, discount, etaj);
                agentie.adaugaLocuinta(move(apartament));
            }
            else if (tip == "Casa") {
                string numeClient;
                int suprafataUtila, suprafataCurte;
                float discount;
                in >> numeClient >> suprafataUtila >> discount >> suprafataCurte;
                unique_ptr<MyLocuinta> casa = make_unique<Casa>(numeClient, suprafataUtila, discount, suprafataCurte);
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
    ~AgentieImobiliara() {}
};

class LocuintaFactory {
public:
    static unique_ptr<Apartament> createApartament(string numeClient, int suprafataUtila, float discount, int etaj) {
        return make_unique<Apartament>(numeClient, suprafataUtila, discount, etaj);
    }
    static unique_ptr<Casa> createCasa(string numeClient, int suprafataUtila, float discount, int suprafataCurte) {
        return make_unique<Casa>(numeClient, suprafataUtila, discount, suprafataCurte);
    }
};


class LocuintaBuilder {
    string numeClient;
    int suprafataUtila;
    float discount;
    int specificitate;
public:
    LocuintaBuilder& setNumeClient(const string& numeClient) {
        this->numeClient = numeClient;
        return *this;
    }

    LocuintaBuilder& setSuprafataUtila(int suprafataUtila) {
        if (suprafataUtila < 0) {
            throw SuprafataUtilaNegativaException();
        }
        this->suprafataUtila = suprafataUtila;
        return *this;
    }

    LocuintaBuilder& setDiscount(float discount) {
        if (discount < 0 || discount > 100) {
            throw DiscountInvalidException();
        }
        this->discount = discount;
        return *this;
    }

    LocuintaBuilder& setSpecificitate(int specificitate) {
        this->specificitate = specificitate;
        return *this;
    }

    unique_ptr<Apartament> buildApartament() const {
        return make_unique<Apartament>(numeClient, suprafataUtila, discount, specificitate);
    }

    unique_ptr<Casa> buildCasa() const {
        return make_unique<Casa>(numeClient, suprafataUtila, discount, specificitate);
    }
};
