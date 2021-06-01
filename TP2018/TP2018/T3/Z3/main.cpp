//TP 2017/2018: Tutorijal 3, Zadatak 3
#include <iostream>
#include<deque>
using namespace std;
int Suma(int n)
{
    int sum=0;
    while(n!=0) {
        sum+=n%10;
        n/=10;
    }
    return sum;
}
deque<int> IzdvojiElemente(deque<int> d,bool vrijednost)
{
    deque<int> vracam;
    if(vrijednost==true) { 
        for(int i:d) {
            if(Suma(i)%2==0)vracam.push_back(i);
        }
    } else { 
        for(int i:d) {
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
    cout<<"Unesite elemente: ";
    deque<int>a;
    for(int i=0; i<n; i++) {
        cin>>br;
        a.push_back(br);
    }
    deque<int>b;
    deque<int>c;
    b=IzdvojiElemente(a,true);
    c=IzdvojiElemente(a,false);
    for(int i=0; i<b.size(); i++) {
        if(i>0 && i<b.size())cout<<",";
        cout<<b.at(i);
    }
    cout<<endl;
    for(int i=0; i<c.size(); i++) {
        if(i>0 && i<c.size())cout<<",";
        cout<<c.at(i);
    }
    return 0;
}
