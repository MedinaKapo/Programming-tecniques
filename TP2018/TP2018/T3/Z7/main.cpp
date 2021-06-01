//TP 2017/2018: Tutorijal 3, Zadatak 7
#include <iostream>
#include<vector>
#include<stdexcept>
#include<iomanip>
using namespace std;
int BrojCifara(int n)
{
    int brojac=0;
    if(n<0) {
        n*=-1;
        brojac=1;
    }
    while(n!=0) {
        brojac++;
        n/=10;
    }
    return brojac; 
}
int NajvecaSirina(vector<vector<int>> m)
{
    int max=0;
    //klasicna petlja
    /*for(int i=0;i<m.size();i++){
        for(int j=0;j<m.at(i).size();j++){
            if(BrojCifara(m.at(i).at(j))>max)max=BrojCifara(m.at(i).at(j));
        }
    }*/
    //foreach pelja
    for(vector<int> red:m) {
        for(int i:red) {
            if(BrojCifara(i)>max)max=BrojCifara(i);
        }
    }
    return max;
}
vector<vector<int>> PascalovTrougao(int n)
{
 
    if(n<0) {
        throw domain_error ("Broj redova ne smije biti negativan");
    }
    vector<vector<int>> trougao(n);
    for(int i=0; i<n; i++) {
        trougao.at(i).resize(i+1);
    }
    for(int i=0; i<n; i++) {
        trougao.at(i).at(0)=1;
       trougao.at(i).at(i)=1;
    }
    for(int i=2; i<n; i++) {
        for(int j=1; j<i; j++) {
            trougao.at(i).at(j)=trougao.at(i-1).at(j-1)+trougao.at(i-1).at(j);
        }
    }

    return trougao;
}

int main ()
{
    try {
        int n;
        cout<<"Unesite broj redova: "<<endl;
        cin>>n;
        vector<vector<int>>paskalov;
        paskalov=PascalovTrougao(n);
        int max=NajvecaSirina(paskalov);
        //klasicni ispis
        /*for(int i=0;i<n;i++){
            for(int j=0;j<paskalov.at(i).size();j++){
                cout<<right<<setw(max+1)<<paskalov.at(i).at(j);
            }
            cout<<endl;
        }*/
        //foreach petlja ispis
        for(vector<int>red:paskalov) {
            for(int i:red)cout<<right<<setw(max+1)<<i;
            cout<<endl;
        }
    } catch(domain_error izuzetak) {
        cout<<izuzetak.what()<<endl;
        return 0;
    }
    return 0;
}
