//TP 2017/2018: Tutorijal 3, Zadatak 8
#include <iostream>
#include<string>
#include<stdexcept>
using namespace std;
string IzdvojiRijec(string recenica,int n)
{
    string rijec;
    int razmak=1,broj_rijeci=0,pocetak=0,kraj=0;
    for(int i=0; i<recenica.length(); i++) {
        if(recenica.at(i)==' ')razmak=1;
        else if(razmak==1) {
            razmak=0;
            broj_rijeci++; 
            if(broj_rijeci==n) {
                pocetak=i;
                while(pocetak!=recenica.length() && recenica.at(pocetak)!=' ')pocetak++;
                kraj=pocetak-i;
                rijec=recenica.substr(i,kraj);
            }
        }
 
    }
    if((kraj==0 && pocetak==0) || n<0 || n>recenica.length() || n>broj_rijeci)throw range_error("IZUZETAK: Pogresan redni broj rijeci!");
    return rijec;

}
int main ()
{
    try {
        int n;
        cout<<"Unesite redni broj rijeci: ";
        cin>>n;
        cin.ignore(1000000,'\n');
        cout<<"Unesite recenicu: ";
        string recenica;
        getline(cin,recenica);
        string rijec=IzdvojiRijec(recenica,n);
        cout<<"Rijec na poziciji "<<n<<" je "<<rijec<<endl;
    } catch(range_error izuzetak) {
        cout<<izuzetak.what()<<endl;
    }
    return 0;
}
