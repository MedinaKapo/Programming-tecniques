//TP 2018/2019: Zadaća 3, Zadatak 2
#include <iostream>
#include<map>
#include<set>
#include<string>
#include<vector>
#include<stdexcept>  
using namespace std;   
vector<int> Pozicije(string s,string rijec)  
{ 
    vector<int>vracam; 
    int k;
    string test;
    for(int i=0; i<s.length(); i++) {
        if(s[i]!=' ' && s[i]!='\0' && s[i]!='.' && s[i]!=',' && s[i]!='!') {
            for(k=i; i<s.length(); k++) {
                if(s[k]=='\t' || s[k]==' ' || s[k]=='\0' || s[k]=='.' || s[k]==',' || s[k]=='!' || s[k]=='?' || s[k]=='+' || s[k]=='/' || s[k]=='-' || s[k]=='_')break;
                if(s[k]>='A' && s[k]<='Z')s[k]+='a'-'A';
            }
            test=s.substr(i,k-i);
            if(rijec==test)
                vracam.push_back(i);
            i=k-1;
        }
    }
    return vracam;
}
map<string,set<int>>KreirajIndeksPojmova(string s)
{
    map<string,set<int>> vracam{};
    // set<int> brojevi;
    string rijec;
    int k;
    for(int i=0; i<s.length(); i++) {
        if(s[i]!=' ' && s[i]!='\0' && s[i]!='.' && s[i]!=',' && s[i]!='!') {
            for(k=i; k<s.length(); k++) {
if(s[k]=='\t' || s[k]==' ' || s[k]=='\0' || s[k]=='.' || s[k]==',' || s[k]=='!' || s[k]=='?' || s[k]=='+' || s[k]=='/' || s[k]=='-' || s[k]=='_')break;
                if(s[k]>='A' && s[k]<='Z')s[k]+='a'-'A';
            }
            rijec=s.substr(i,k-i);

            vector<int>poz=Pozicije(s,rijec);
            set<int>brojevi;
            for(int z=0; z<poz.size(); z++) {

                brojevi.insert(poz.at(z));
            }
            vracam[rijec]=brojevi;
            i=k-1;
        }
    }
    return vracam;
}
set<int>PretraziIndeksPojmova(string s,map<string,set<int>> mapa)
{
    set<int> vracam;
    bool ima=false;
    for(auto it=mapa.begin(); it!=mapa.end(); it++) {
        if(it->first==s) {
            vracam=it->second;
            ima=true;
        }
    }
    if(ima==true)
        return vracam;
    else throw logic_error("Pojam nije nadjen");
}
void IspisiIndeksPojmova(map<string,set<int>> mapa)
{
    for(auto it=mapa.begin(); it!=mapa.end(); it++) {
        cout<<it->first<<": ";
        //for(auto x:it->second)cout<<x;
        set<int> skup=it->second;
        for(auto x=skup.begin(); x!=skup.end(); x++) {
            cout<<*x;
            x++;
            if(x!=skup.end())cout<<",";
            x--;
        };
        cout<<endl;
    }
}
int main ()
{
    string s;
    cout<<"Unesite tekst: ";
    getline(cin,s);
    map<string,set<int>> mapa=KreirajIndeksPojmova(s);
    IspisiIndeksPojmova(mapa);
    for(;;) {
        string rijec;
        cout<<"Unesite rijec: ";
        cin>>rijec;
        if(rijec==".")break;
        try {
            //for(auto x:PretraziIndeksPojmova(rijec,mapa))cout<<x<<" ";
            set<int> s=(PretraziIndeksPojmova(rijec,mapa));
            for(auto x=s.begin(); x!=s.end(); x++) {
                cout<<*x<<" ";
                /* x++;
                 if(x!=s.end())cout<<" ";
                 x--;*/
            }
            cout<<endl;
        } catch(logic_error izuzetak) {
            cout<<"Unesena rijec nije nadjena!"<<endl;
        }

    }
    return 0;
}
