//TP 2018/2019: Tutorijal 8, Zadatak 3
#include <iostream>
#include<iomanip>
#include<string>
#include<algorithm>
using namespace std;
const int BrojPredmeta=8;
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
    void UnesiUcenike(Ucenik **p_ucenici,int broj_ucenika);
    void ObradiUcenike(Ucenik** p_ucenici,int broj_ucenika);
    void IspisiIzvjestaj(Ucenik **p_ucenici,int broj_ucenika);
    void OslobodiMemoriju(Ucenik **p_ucenici,int broj_ucenika);
    int broj_ucenika;
    cout<<"Koliko ima ucenika: ";
    cin>>broj_ucenika;
    try {
        Ucenik **p_ucenici=new Ucenik*[broj_ucenika];
        for(int i=0; i<broj_ucenika; i++)p_ucenici[i]=nullptr;
        try {
            UnesiUcenike(p_ucenici,broj_ucenika);
        } catch(...) {
            OslobodiMemoriju(p_ucenici,broj_ucenika);
            throw;
        }
        ObradiUcenike(p_ucenici,broj_ucenika);
        IspisiIzvjestaj(p_ucenici,broj_ucenika);
        OslobodiMemoriju(p_ucenici,broj_ucenika);
    } catch(...) {
        cout<<"Problemi sa memorijom...\n";
    }
    return 0;
}
void UnesiUcenike(Ucenik **p_ucenici,int broj_ucenika)
{
    void UnesiJednogUcenika(Ucenik *p_ucenik);
    for(int i=0; i<broj_ucenika; i++) {
        cout<<"Unesite podatke za "<<i+1<<". ucenika:\n";
        p_ucenici[i]=new Ucenik;
        UnesiJednogUcenika(p_ucenici[i]);
    }
}
void UnesiJednogUcenika(Ucenik *p_ucenik)
{
    void UnesiDatum(Datum &datum);
    void UnesiOcjene(int ocjene[],int broj_predmeta);
    cout<<"  Ime: ";
    cin>>p_ucenik->ime;
    cout<<"  Prezime: ";
    cin>>p_ucenik->prezime;
    cout<<"  Datum rodjenja (D/M/G): ";
    UnesiDatum(p_ucenik->datum_rodjenja);
    UnesiOcjene(p_ucenik->ocjene,BrojPredmeta);
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
void ObradiUcenike(Ucenik **p_ucenici,int broj_ucenika)
{
    void ObradiJednogUcenika(Ucenik *p_ucenik);
    for(int i=0; i<broj_ucenika; i++)ObradiJednogUcenika(p_ucenici[i]);
    sort(p_ucenici,p_ucenici+broj_ucenika,[](const Ucenik *p_u1,const Ucenik *p_u2) {
        return p_u1->prosjek>p_u2->prosjek;
    });
}
void ObradiJednogUcenika(Ucenik *p_ucenik)
{
    double suma_ocjena=0;
    p_ucenik->prosjek=1;
    p_ucenik->prolaz=false;
    for(int ocjena:p_ucenik->ocjene) {
        if(ocjena==1)return;
        suma_ocjena+=ocjena;
    }
    p_ucenik->prolaz=true;
    p_ucenik->prosjek=suma_ocjena/BrojPredmeta;
}
void IspisiIzvjestaj(Ucenik** p_ucenici,int broj_ucenika)
{
    void IspisiJednogUcenika(const Ucenik *p_ucenik);
    cout<<endl;
    for(int i=0; i<broj_ucenika; i++)IspisiJednogUcenika(p_ucenici[i]);
}
void IspisiJednogUcenika(const Ucenik *p_ucenik)
{
    void IspisiDatum(const Datum &datum);
    cout<<"Ucenik "<<p_ucenik->ime<<" "<<p_ucenik->prezime<<" rodjen ";
    IspisiDatum(p_ucenik->datum_rodjenja);
    if(p_ucenik->prolaz)
        cout<<" ima prosjek "<<setprecision(3)<<p_ucenik->prosjek;
    else cout<<" mora ponavljati razred";
    cout<<endl;
}
void IspisiDatum(const Datum &datum)
{
    cout<<datum.dan<<"/"<<datum.mjesec<<"/"<<datum.godina;
}
void OslobodiMemoriju(Ucenik **p_ucenici,int broj_ucenika)
{
    for(int i=0; i<broj_ucenika; i++)delete p_ucenici[i];
    delete []p_ucenici;
}
