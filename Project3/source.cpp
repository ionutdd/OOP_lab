#include "Header.h"


int main() {

    AgentieImobiliara agentie;
    int optiune;
    while (true) {
        cout << "Meniu:" << endl;
        cout << "1. Adauga o locuinta noua" << endl;
        cout << "2. Afiseaza toate locuintele" << endl;
        cout << "3. Calculeaza chiria pentru o locuinta" << endl;
        cout << "4. Iesire din program" << endl;
        cout << "5. Introduceti o locuinta cu ajutorul clasei de tip Factory" << endl;
        cout << "6. Introduceti o locuinta cu ajutorul clasei de tip Builder" << endl;
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
                unique_ptr<Apartament> apartament = make_unique<Apartament>(numeClient, suprafataUtila, discount, etaj);
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
                unique_ptr<Casa> casa = make_unique<Casa>(numeClient, suprafataUtila, discount, suprafataCurte);
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
        case 5: {
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
                unique_ptr<Apartament> apartament = LocuintaFactory::createApartament(numeClient, suprafataUtila, discount, etaj);
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
                unique_ptr<Casa> casa = LocuintaFactory::createCasa(numeClient, suprafataUtila, discount, suprafataCurte);
                agentie.adaugaLocuinta(move(casa));
                cout << "Casa adaugata cu succes!" << endl;
            }
            else {
                cout << "Tip de locuinta invalid! Introduceti 'Apartament' sau 'Casa'." << endl;
            }
            break;
        }
        case 6: {
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
                LocuintaBuilder builder;
                builder.setNumeClient(numeClient).setSuprafataUtila(suprafataUtila).setDiscount(discount).setSpecificitate(etaj);
                unique_ptr<Apartament> apartament = builder.buildApartament();
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
                LocuintaBuilder builder;
                builder.setNumeClient(numeClient).setSuprafataUtila(suprafataUtila).setDiscount(discount).setSpecificitate(suprafataCurte);
                unique_ptr<Casa> casa = builder.buildCasa();
                agentie.adaugaLocuinta(move(casa));
                cout << "Casa adaugata cu succes!" << endl;
            }
            else {
                cout << "Tip de locuinta invalid! Introduceti 'Apartament' sau 'Casa'." << endl;
            }
            break;
        }
        default: {
            cout << "Optiune invalida!" << endl;
            return 0; 
        }
        }
    }
 
    return 0;
}
