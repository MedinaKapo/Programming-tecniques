//TP 2018/2019: Tutorijal 8, Zadatak 2
#include <iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<algorithm>
#include<memory>
using namespace std;
const int BrojPredmeta (8); 
struct Datum {
    int dan,mjesec,godina;
};
struct Ucenik {
    string ime,prezime;
    Datum datum_rodjenja;
    int ocjene[BrojPredmeta];
    double prosjek;
    bool prolaz;
};

int main ()
{
    void UnesiUcenike(vector<shared_ptr<Ucenik>> &ucenici);
    void ObradiUCenike(vector<shared_ptr<Ucenik>> &ucenici);
    void IspisiIzvjestaj(const vector<shared_ptr<Ucenik>> &ucenici);
    int broj_ucenika;
    cout<<"Koliko ima ucenika: ";
    cin>>broj_ucenika;
    try {
        vector<shared_ptr<Ucenik>>ucenici(broj_ucenika);
        UnesiUcenike(ucenici);
        ObradiUCenike(ucenici);
        IspisiIzvjestaj(ucenici);
    } catch(...) {
        cout<<"Problemi sa memorijom...\n";
    }
    return 0;
}
void UnesiUcenike(vector<shared_ptr<Ucenik>> &ucenici)
{
    void UnesiJednogUcenika(shared_ptr<Ucenik> ucenik);
    for(int i=0; i<ucenici.size(); i++) {
        cout<<"Unesite podatke za "<<i+1<<". ucenika:\n";
        ucenici[i]=make_shared<Ucenik>();
        UnesiJednogUcenika(ucenici[i]);
    }
}
void UnesiJednogUcenika(shared_ptr<Ucenik> ucenik)
{
    void UnesiDatum(Datum &datum);
    void UnesiOcjene(int ocjene[],int broj_predmeta);
    cout<<"  Ime: ";
    cin>>ucenik->ime;
    cout<<"  Prezime: ";
    cin>>ucenik->prezime;
    cout<<"  Datum rodjenja (D/M/G): ";
    UnesiDatum(ucenik->datum_rodjenja);
    UnesiOcjene(ucenik->ocjene,BrojPredmeta);
}
void UnesiDatum(Datum &datum)
{
    char znak;
    cin>>datum.dan>>znak>>datum.mjesec>>znak>>datum.godina;
}
void UnesiOcjene(int ocjene[],int broj_predmeta)
{
    for(int i=0; i<broj_predmeta; i++) {
        cout<<"  Ocjena iz "<<i+1<<". predmeta: ";
        cin>>ocjene[i];
    }
}
void ObradiUCenike(vector<shared_ptr<Ucenik>> &ucenici)
{
    void ObradiJednogUcenika(shared_ptr<Ucenik> ucenik);
    for(shared_ptr<Ucenik> &ucenik:ucenici)ObradiJednogUcenika(ucenik);
    sort(ucenici.begin(),ucenici.end(),[](const shared_ptr<Ucenik> u1,const shared_ptr<Ucenik> u2) {
        return u1->prosjek>u2->prosjek;
    });
}
void ObradiJednogUcenika(shared_ptr<Ucenik> ucenik)
{
    double suma_ocjena=0;
    ucenik->prosjek=1;
    ucenik->prolaz=false;
    for(int ocjena:ucenik->ocjene) {
        if(ocjena==1)return;
        suma_ocjena+=ocjena;
    }
    ucenik->prolaz=true;
    ucenik->prosjek=suma_ocjena/BrojPredmeta;
}
void IspisiIzvjestaj(const vector<shared_ptr<Ucenik>> &ucenici)
{
    void IspisiJednogUcenika(const shared_ptr<Ucenik> ucenik);
    cout<<endl;
    for(const shared_ptr<Ucenik> ucenik:ucenici)IspisiJednogUcenika(ucenik);
}
void IspisiJednogUcenika(const shared_ptr<Ucenik> ucenik)
{
    void IspisiDatum(const Datum &datum);
    cout<<"Ucenik "<<ucenik->ime<<" "<<ucenik->prezime<<" rodjen ";
    IspisiDatum(ucenik->datum_rodjenja);
    if(ucenik->prolaz)cout<<" ima prosjek "<<setprecision(3)<<ucenik->prosjek;
    else cout<<" mora ponavljati razred";
    cout<<endl;
}
void IspisiDatum(const Datum &datum)
{
    cout<<datum.dan<<"/"<<datum.mjesec<<"/"<<datum.godina;
}
