//TP 2017/2018: Tutorijal 3, Zadatak 5
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
deque<int>IzdvojiElemente(deque<int>d,bool vrijednost)
{
    deque<int> vracam;
    if(vrijednost==true) {
        for(int i=d.size()-1; i>=0; i--) {
            if(Suma(d.at(i))%2==0)vracam.push_front(d.at(i));
        }
    } else {
        for(int i=d.size()-1; i>=0; i--) {
            if(Suma(d.at(i))%2!=0)vracam.push_front(d.at(i));
        }
    }
    return vracam;
}
int main ()
{
    int br,n;
    cout<<"Koliko zelite unijeti elemenata: ";
    cin>>n;
    if(n<=0) {
        cout<<"Broj elemenata mora biti veci od 0!"<<endl;
        return 0;
    }
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
