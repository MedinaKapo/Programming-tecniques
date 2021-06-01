//TP 2018/2019: Tutorijal 8, Zadatak 6
#include <iostream>
using namespace std;
template<typename Tip>
struct Cvor {
    Tip element;
    Cvor *veza;
};
template<typename TipElemenata>
Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni)
{
    Cvor<TipElemenata> *pocetak=nullptr,*prethodni;
    for(;;) {
        TipElemenata broj;
        cin>>broj; 
        if(broj==zavrsni)break;
        Cvor <TipElemenata>*novi(new Cvor<TipElemenata>);
        novi->element=broj;
        novi->veza=nullptr;
        if(!pocetak)pocetak=novi;
        else prethodni->veza=novi;
        prethodni=novi;
    }
    return pocetak;
}
template<typename TipElemenata>
int BrojElemenata(Cvor<TipElemenata> *pocetak)
{
    int vracam=0;
    if(pocetak==nullptr)return vracam;
    for(auto x=pocetak; x!=nullptr; x=x->veza) {
        vracam++;
    }
    return vracam;
}
template<typename TipElemenata>
TipElemenata SumaElemenata(Cvor<TipElemenata>*pocetak)
{
    TipElemenata suma{};
    if(pocetak==nullptr)return suma;
    for(auto x=pocetak; x!=nullptr; x=x->veza) {
        suma+=x->element;
    }
    return suma;
}
template<typename TipElemenata>
int BrojVecihOd(Cvor<TipElemenata>*pocetak,TipElemenata prag)
{
    int vracam=0;
    if(pocetak==nullptr)return vracam;
    for(auto x=pocetak; x!=nullptr; x=x->veza) {
        if(x->element>prag)vracam++;
    }
    return vracam;
}
template<typename TipElemenata>
void UnistiListu(Cvor<TipElemenata> *pocetak)
{
    Cvor<TipElemenata>*poc;
    while(pocetak!=nullptr) {
        poc=pocetak;
        pocetak=pocetak->veza;
        delete poc;
    }
}
int main ()
{
    cout<<"Unesite slijed brojeva (0 za kraj): ";
    auto lista=KreirajPovezanuListu<double>(0);
    auto prag=SumaElemenata(lista)/BrojElemenata(lista);
    cout<<"U slijedu ima "<<BrojVecihOd(lista,prag)<<" brojeva vecih od njihove aritmeticke sredine"<<endl;
    UnistiListu(lista);
    return 0;
}
