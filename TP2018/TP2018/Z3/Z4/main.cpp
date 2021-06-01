//TP 2018/2019: Zadaća 3, Zadatak 4
#include <iostream>
#include<set>
#include<vector>
#include<stdexcept>
#include<string>  
#include<list>
#include<cmath>
using namespace std;
int duzina_stringa(string s)
{
    int brojac=0;
    int duzina=s.size();
    for(int i=0; i<duzina; i++) {
        if((s[i]>=48 && s[i]<=58) || (s[i]>=65 && s[i]<=90) || (s[i]>=97 && s[i]<=122))brojac++;
    }
    return brojac;
}
vector<set<string>> Razvrstavanje(vector<string> imena,int broj_timova)
{
    if(broj_timova<1 || broj_timova>imena.size())throw logic_error("Razvrstavanje nemoguce");
    vector<set<string>> vracam;
    list<string>lista;
    set<string>tim;
    set<string>prazan;
    int kontrola=1;
    int cijeli=(imena.size()%broj_timova);
    //if(cijeli==0)cijeli=imena.size()/broj_timova;
    int veliki,polovicni,malih;
    if(cijeli!=0) {
        veliki=((imena.size()/broj_timova)+1);
        polovicni=imena.size()/broj_timova;
        malih=imena.size()-veliki;
    } else {
        veliki=imena.size()/broj_timova;
        cijeli=broj_timova;
        polovicni=0;
        malih=0;
    }
    int brojac=0;

    for(int i=0; i!=imena.size(); i++) {
        lista.push_back(imena.at(i));
    }

    list<string>::iterator it(lista.begin());
    list<string>::iterator it2(lista.end());
    string rijec=*it;
    int duzina=duzina_stringa(rijec);
    int interni=0;
    bool uslov=false;
    tim.insert(*it);
    //it=lista.erase(it);
    for(;;) {
        if(interni==broj_timova)break;
        if(it==lista.end())it=lista.begin();
        if(kontrola==1) {
            it=lista.erase(it);
            kontrola=2;
            if(tim.size()==veliki && uslov==false) {
                vracam.push_back(tim);
                tim=prazan;
                brojac=0;
                interni++;
                if(interni==cijeli)uslov=true;
            }
        } else if(brojac==duzina) {
            string ime=*it;
            duzina=duzina_stringa(ime);
            tim.insert(ime);
            it=lista.erase(it);

            if(tim.size()==veliki && uslov==false) {
                vracam.push_back(tim);
                tim=prazan;
                brojac=0;
                interni++;
                if(interni==cijeli)uslov=true;
            }

            else if(tim.size()==polovicni &&uslov==true) {
                vracam.push_back(tim);
                tim=prazan;

            }
            brojac=0;

        } else if(lista.begin()==lista.end())break;
        else it++;
        brojac++;
        if(it==lista.end()) {
            for(; it!=lista.begin();)it--;
        }

    }

    return vracam;
}
int main ()
{
    try {
        int n;
        cout<<"Unesite broj djece: ";
        cin>>n;
        cin.clear();
        cin.ignore(1000,'\n');
        string ime;
        vector<string>imena;
        cout<<"Unesite imena djece: "<<endl;
        for(int i=0; i< n; i++) {
            getline(cin,ime);
            imena.push_back(ime);
        }
        cout<<"Unesite broj timova: "; 
        int broj_timova;
        cin>>broj_timova;
        vector<set<string>> timovi=Razvrstavanje(imena,broj_timova);
        for(int i= 0; i<timovi.size( ); i++) {
            cout<<"Tim "<<i+1<<": ";
            for(auto x=timovi.at(i).begin( ); x!=timovi.at(i).end( ); x++) {
                cout<<*x;
                x++;
                if(x!=timovi.at(i).end())cout<<", ";
                x--;
            }
            cout<<endl;      
  
        } 
    }   catch(logic_error izuzetak) {
        cout<<"Izuzetak: "<<izuzetak.what()<<endl;
        return 0;
    }
    return 0;

}
