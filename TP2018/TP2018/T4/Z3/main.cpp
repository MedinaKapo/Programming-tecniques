//TP 2018/2019: Tutorijal 4, Zadatak 3
#include <iostream>
#include<vector>
#include<string>
using namespace std;
string slova(string &s)
{
    string slova;  
    char slovo;
    for(int i=0; i<s.size(); i++) {
        slovo=s.at(i);
        if(slovo>='a' && slovo<='z')slova.push_back(toupper(slovo));
        else slova.push_back(slovo);
    }
    return slova;
}
void IzdvojiKrajnjeRijeci(const vector<string> &v,string &prva,string &zadnja)
{
    string rijec,rijec1,vektorska;
    if(v.size()>0) {
        rijec=v.at(0);
        rijec1=v.at(0);
        for(int i=0; i<v.size(); i++) {
            vektorska=v.at(i);
            if(slova(vektorska)<=slova(rijec)) {
                rijec=v.at(i);
                prva=v.at(i);
            }
            if(slova(vektorska)>=slova(rijec1)) {
                rijec1=v.at(i);
                zadnja=v.at(i);
            }
        }
        prva=rijec;
        zadnja=rijec1;
    }
} 
void ZadrziDuplikate(vector<string> &v)
{
    bool duplo=false;
    vector<string>pom;
    string rijecii,rijecij;
    //trazi duplikate,ako se nadje ista rijec,a prije nalazenja prve kopije nije se nikad nasla prije kopija,
    //onda trpaj u pomocni a ako jeste zanemari
    for(int i=0; i<v.size(); i++) {
        for(int j=i+1; j<v.size(); j++) {
            rijecii=v.at(i);
            rijecij=v.at(j);
            duplo=false;
            for(int k=0; k<pom.size(); k++)
                if(rijecij==pom.at(k))duplo=true;

            if(rijecii==rijecij && duplo==false) {
                pom.push_back(v.at(i));
            }
        }
    }
    v=pom;
}
int main ()
{
    string rijeci;
    cout<<"Koliko zelite unijeti rijeci: ";
    int n;
    cin>>n;
    cout<<"Unesite rijeci:";
    vector<string> v;
    cin.clear();
    cin.ignore(10000,'\n');
    for(int i=0; i<n; i++) {
        cin>>rijeci;
        v.push_back(rijeci);
    }
    cout<<endl;
    string prva,zadnja;
    IzdvojiKrajnjeRijeci(v,prva,zadnja);
    ZadrziDuplikate(v);
    cout<<"Prva rijec po abecednom poretku je: "<<prva<<endl;
    cout<<"Posljednja rijec po abecednom poretku je: "<<zadnja<<endl;
    cout<<"Rijeci koje se ponavljaju su: ";
    for(int i=0; i<v.size(); i++) {
        cout<<v.at(i)<<" ";
    }
    return 0;
}
