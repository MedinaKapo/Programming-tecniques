//TP 2018/2019: Zadaća 3, Zadatak 5
#include <iostream>
#include<stdexcept>
#include<set>
#include<vector>
#include<string>
#include<cmath>
#include<new>
using namespace std;
struct Dijete{
    string ime;
    Dijete *sljedeci;
};
int duzina_stringa(string s){
    int brojac=0;
    for(int i=0;i<s.size();i++){
        if((s[i]>=48 && s[i]<=58) || (s[i]>=65 && s[i]<=90) || (s[i]>=97 && s[i]<=122))brojac++;
    }
    return brojac;
}
void UnistiListu(Dijete *pocetak){
    Dijete *pom;
    Dijete *kraj=pocetak;
    while(pocetak!=kraj){
        pom=pocetak;
        pocetak=pocetak->sljedeci;
        delete pom;
    }
}
void Napravi(Dijete **prvi,string s){
    Dijete *pocetni=new Dijete();
    pocetni->ime=s;
    pocetni->sljedeci=pocetni;
    if(*prvi!=nullptr){
        Dijete *tmp=*prvi;
        while(tmp->sljedeci!=*prvi){
            tmp=tmp->sljedeci;}
            tmp->sljedeci=pocetni;
        }
        else{
            pocetni->sljedeci=pocetni;
            *prvi=pocetni;
        }
}
void Ocisti(Dijete *pocetak,string s){
    if(pocetak==nullptr)return;
    Dijete *trenutno=pocetak,*prethodni;
    while(trenutno->ime!=s){
        if(trenutno->sljedeci==pocetak)break;
        prethodni=trenutno;
        trenutno=trenutno->sljedeci;
    }
    if(trenutno->sljedeci==pocetak){
        pocetak=nullptr;
        delete(trenutno);
        return;
    }
    if(trenutno==pocetak){
        prethodni=pocetak;
        while(prethodni->sljedeci!=pocetak){
            prethodni=prethodni->sljedeci;
            pocetak=trenutno->sljedeci;
            prethodni->sljedeci=pocetak;
            delete(trenutno);
            
        }
    }
    else if(trenutno->sljedeci==pocetak){
        prethodni->sljedeci=pocetak;
        delete(trenutno);
    }
    else{
        prethodni->sljedeci=trenutno->sljedeci;
        delete(trenutno);
    }
}
vector<set<string>> Razvrstavanje(vector<string>imena,int broj_timova){
    if(broj_timova<1 || broj_timova>imena.size())throw logic_error("Razvrstavanje nemoguce");
    vector<set<string>> vracam;
    set<string>tim;
    set<string>prazan;
    int kontrola=1;
    int cijeli=imena.size()%broj_timova;
    int veliki,polovnicnih;
    if(cijeli!=0){
        veliki=((imena.size()/broj_timova)+1);
        polovnicnih=imena.size()/broj_timova;
    }
    else{
        veliki=imena.size()/broj_timova;
        cijeli=broj_timova;
        polovnicnih=0;
    }
    int brojac=0;
    Dijete *pocetak(nullptr),*prethodni;
    for(int i=0;i<imena.size();i++){
    Napravi(&pocetak,imena.at(i));
    pocetak=pocetak->sljedeci;
    }
    int duzina=duzina_stringa(pocetak->ime);
    bool uslov=false;
    int interni=0;
    Dijete *p=pocetak;
    string rijec=p->ime;
    tim.insert(rijec);
    Dijete *tmp=pocetak;
    for(;;){
        if(interni==broj_timova)break;
        if(kontrola==1){
            Ocisti(p,rijec);
            kontrola=2;
            if(tim.size()==veliki && uslov==false){
                vracam.push_back(tim);
                tim=prazan;
                brojac=0;
                interni++;
                if(interni==cijeli)uslov=true;
            }
        }
        else if(brojac==duzina){
            string ime_trenutnog=p->ime;
            duzina=duzina_stringa(ime_trenutnog);
            tim.insert(ime_trenutnog);
            Ocisti(p,ime_trenutnog);
            if(tim.size()==veliki && uslov==false){
                vracam.push_back(tim);
                tim=prazan;
                brojac=0;
                interni++;
                if(interni==cijeli)uslov=true;
            }
            else if(tim.size()==polovnicnih && uslov==true){
                vracam.push_back(tim);
                tim=prazan;
            }
            brojac=0;
        }
         else p=p->sljedeci;
        brojac++;
    }
    UnistiListu(pocetak);
    return vracam;
}

int main ()
{
    try{
        int n;
        cout<<"Unesite broj djece: ";
        cin>>n;
        cin.clear();
        cin.ignore(10000,'\n');
        string ime;
        vector<string>imena;
        cout<<"Unesite imena djece: "<<endl;
        for(int i=0;i<n;i++){
            getline(cin,ime);
            imena.push_back(ime);
        }
        cout<<"Unesite broj timova: ";
        int broj_timova;
        cin>>broj_timova;
        vector<set<string>> timovi=Razvrstavanje(imena,broj_timova);
        for(int i=0;i<timovi.size();i++){
            cout<<"Tim "<<i+1<<": ";
            for(auto x=timovi.at(i).begin();x!=timovi.at(i).end();x++){
                cout<<*x;
                x++;
                if(x!=timovi.at(i).end())cout<<", ";
                x--;
            }
            cout<<endl;
        }
    }
    catch(logic_error izuzetak){
        cout<<izuzetak.what()<<endl;
        return 0;
    }
	return 0;
}