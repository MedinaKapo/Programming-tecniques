/* TP, 2018/2019
*/
#include <iostream>
#include<string>
#include<algorithm>
#include<new>
using namespace std;
template<typename tip>
tip *StvoriInicijaliziraniNiz(int n) 
{ 
    tip *pok; 
    try {
        pok=new tip[n];
        for(int i=0; i<n; i++)pok[i]=tip();
        return pok;
    } catch(...) {
        delete[] pok;
        throw;
    }
}
bool KriterijSortiranja(string s,string n)
{
    transform(&s[0],&s[s.length()],&s[0],(int(*)(int))toupper);
    transform(&n[0],&n[n.length()],&n[0],(int(*)(int))toupper);

    if(n.length()==s.length()) {
        if(s<n)return true;
    }
    if(s.length()<n.length())return true;
    return false; 
 
} 
void SortirajPoDuzini(string *niz,int vel)
{
    sort(niz,niz+vel,KriterijSortiranja);
 
}
bool PretraziBinarno(string *niz,int vel,string rijec)
{
    return binary_search(niz,niz+vel,rijec,KriterijSortiranja);

}
int main () 
{  
    int n;
    cout<<"Unesite broj rijeci: ";
    cin>>n;
    /*cin.ignore(10000,'\n');
    cin.clear();*/
    try {
        auto niz_stringova=StvoriInicijaliziraniNiz<string>(n);
        cout<<"Unesite rijeci: ";
        string rijec;
        for(int i=0; i<n; i++) {
            //getline(cin,rijec);
            cin>>rijec;
            niz_stringova[i]=rijec;
        }
        SortirajPoDuzini(niz_stringova,n);
        cout<<"Sortirane rijeci: ";
        for(int i=0; i<n; i++)cout<<niz_stringova[i]<<" ";
        cout<<endl;
        cout<<"Unesite rijec za pretragu: ";
        string pretraga;
        cin>>pretraga;
        bool prisutnost=PretraziBinarno(niz_stringova,n,pretraga);
        if(prisutnost)cout<<"Rijec '"<<pretraga<<"' se nalazi u nizu."<<endl;
        else cout<<"Rijec '"<<pretraga<<"' se ne nalazi u nizu."<<endl;
        delete[] niz_stringova;
    } catch(...) {
        cout<<"Nedovoljno memorije!"<<endl;
    }
    return 0;
}
