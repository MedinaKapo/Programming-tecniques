//TP 2018/2019: Tutorijal 4, Zadatak 4
#include <iostream>
#include<cmath>
using namespace std;
template<typename NekiTip>
void UnosBroja(string unos,string greska,NekiTip &broj)
{
    for(;;) {
        cout<<unos<<endl;
        cin>>broj;
        if(cin.peek()!='\n') {
            cout<<greska<<endl; 
            cin.clear();
            cin.ignore(10000,'\n');
        } else break;
    }  
}
double stepen(double baza,int eksponent)
{
    double vracam=1;
    for(int i=0; i<abs(eksponent); i++) {
        vracam*=baza;
    }
    if(eksponent<0)vracam=1/vracam;
    return vracam;
}
int main ()
{
    double baza;
    int eksponent;
    UnosBroja("Unesite bazu: ","Neispravan unos, pokusajte ponovo...",baza);
    UnosBroja("Unesite cjelobrojni eksponent: ","Neispravan unos, pokusajte ponovo...",eksponent);
    cout<<baza<<" na "<<eksponent<<" iznosi "<<stepen(baza,eksponent)<<endl;
    return 0;
}
