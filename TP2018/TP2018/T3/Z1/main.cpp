//TP 2017/2018: Tutorijal 3, Zadatak 1
#include <iostream>
#include<vector>
using namespace std;
int Suma(int n)
{
   // if(n<0)n*=-1; 
    int sum=0;
    while(n!=0) {
        sum+=n%10;
        n/=10;
    }
    return sum;
}
vector<int> IzdvojiElemente(vector<int> v,bool vrijednost)
{
    vector<int> vracam; 
    if(vrijednost==true) {
        for(int i:v) {
            if(Suma(i)%2==0)vracam.push_back(i);
        }
    } else {
        for(int i:v) {
            if(Suma(i)%2!=0)vracam.push_back(i);
        }
    }
    return vracam;
}

int main ()
{
    int n,br;
    cout<<"Koliko zelite unijeti elemenata: ";
    cin>>n;
    if(n<=0) {
        cout<<"Broj elemenata mora biti veci od 0!"<<endl;
        return 0;
    }
    cout<<"Unesite elemente: ";
    vector<int>a;
    for(int i=0; i<n; i++) {
        cin>>br;
        a.push_back(br);
    }
    vector<int>b;
    vector<int>c;
    b=IzdvojiElemente(a,true);
    c=IzdvojiElemente(a,false);
    for(int x:b)cout<<x<<" ";
    cout<<endl;
    for(int x:c)cout<<x<<" ";
    return 0;
}
