//TP 2017/2018: Tutorijal 3, Zadatak 6
#include <iostream>
#include<vector>
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
vector<vector<int>> KroneckerovProizvod(vector<int>a,vector<int> b)
{
    vector<vector<int>> matrica(a.size(),vector<int>(b.size()));
    for(int i=0; i<a.size(); i++) {
        for(int j=0; j<b.size(); j++) {
            matrica.at(i).at(j)=a.at(i)*b.at(j);
        }
    }
    return matrica;
}
int NajvecaSirina(vector<vector<int>> m)
{
    int brojac,max=0;
    /*
    for(int i=0;i<m.size();i++){
        for(int j=0;j<m.at(i).size();j++){
            if(BrojCifara(m.at(i).at(j))>max)max=BrojCifara(m.at(i).at(j));
        }
    }*/
    //foreach
    for(vector<int> red:m) {
        for(int i:red) {
            if(BrojCifara(i)>max)max=BrojCifara(i);
        }
    }
    return max;
}
int main ()
{
    int m1,m2,br;
    cout<<"Unesite broj elemenata prvog vektora: ";
    cin>>m1;
    cout<<"Unesite elemente prvog vektora: ";
    vector<int>a;
    for(int i=0; i<m1; i++) {
        cin>>br;
        a.push_back(br);
    }
    cout<<"Unesite broj elemenata drugog vektora: ";
    cin>>m2;
    cout<<"Unesite elemente drugog vektora: "<<endl;
    vector<int>b;
    for(int i=0; i<m2; i++) {
        cin>>br;
        b.push_back(br);
    }
    vector<vector<int>>proizvod=KroneckerovProizvod(a,b);
    int max=NajvecaSirina(proizvod);
    //klasicni ispis
    /*
    for(int i=0;i<proizvod.size();i++){
        for(int j=0;j<proizvod.at(0).size();j++){
            cout<<right<<setw(max+1)<<proizvod.at(i).at(j);
        }
        cout<<endl;
    }*/
    //foreach petlja ispis
    for(vector<int> red:proizvod) {
        for(int i:red)cout<<right<<setw(max+1)<<i;
        cout<<endl;
    }
    return 0;
}
