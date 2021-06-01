//TP 2018/2019: Tutorijal 14, Zadatak 2
#include <iostream>
#include<fstream>
#include<algorithm>
#include<stdexcept>
#include<cstring>
using namespace std;
class Spremnik{
    protected:
    double tezina;
    char naziv[50];
    double predmeti;
    public:
    Spremnik(double tezina,const char naziv1[],double predmeti):tezina(tezina),predmeti(predmeti){
    strcpy(Spremnik::naziv,naziv1);
    }
    virtual double DajTezinu()const=0;
    virtual double DajUkupnuTezinu()const=0;
    virtual void Ispisi()const=0;
    virtual char *DajNaziv()const{return naziv;}
};
class Sanduk:public Spremnik{
    int broj;
    public:
    Sanduk(double tezina,char naziv[],double predmeti,int broj):Spremnik(tezina,naziv,predmeti),broj(broj){}
    double DajTezinu()const override{return tezina;}
    double DajUkupnuTezinu()const override{return predmeti*broj+tezina;}
    void Ispisi()const override{
        cout<<"Vrsta spremnika: Bure"<<endl;
        cout<<"Sadrzaj: "<<DajNaziv()<<end;
        cout<<"Vlastita tezina: "<<DajTezinu()<<endl;
        cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<endl;
    }
    
};
class Bure:public Spremnik{
    public:
    Bure(double tezina,char naziv[],double predmeti):Spremnik(tezina,naziv,predmeti){}
    
};
int main ()
{
	return 0;
}