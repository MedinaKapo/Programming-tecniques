/* TP, 2018/2019
*/
#include <iostream>
#include<algorithm>
#include<type_traits>
#include<string>
#include<deque>
#include<cmath>
using namespace std;
template<typename tip>
bool ZaSve(tip p1,tip p2,bool f(typename remove_reference<decltype(*p1)>::type))
{
    while(p1!=p2) {
        if(f(*p1)==false)return false;
        p1++;
    }
    return true;
}
template<typename tip2>
bool MakarJedan(tip2 p1,tip2 p2,bool f(typename remove_reference<decltype(*p1)>::type))
{
    while(p1!=p2) {
        if(f(*p1)==true)return true;
        p1++;
    }
    return false;
}
template<typename tip3>
auto Akumuliraj(tip3 p1,tip3 p2,typename remove_reference<decltype(*p1)>::type f
                (typename remove_reference<decltype(*p1)>::type,typename remove_reference<decltype(*p1)>::type),
                typename remove_reference<decltype(*p1)>::type a0=0)-> typename remove_reference<decltype(*p1)>::type
{
    if(p1==p2)return a0;
    typename remove_reference<decltype(*p1)>::type s=f(a0,*p1);
    p1++;
    if(p1==p2) return s;
    while(p1!=p2) {
        s=f(s,*p1);
        p1++; 
    }
    return s;
}
int main ()
{
    string s;
    cout<<"Unesite string: ";
    getline(cin,s);
    //cin>>s;
    bool svi;
    svi=ZaSve(s.begin(),s.end(),[](char s) {
        if(s>='a' || s<='z' || s>='A' || s<='Z' || s>=48 || s<=57)return true;
        return false;
    });
    if(svi==true)cout<<"Uneseni string sadrzi samo slova i cifre"<<endl;
    else cout<<"Uneseni string sadrzi i druge znakove osim slova i cifara"<<endl;
    cout<<"Unesite niz od 10 brojeva: ";
    int niz[10];
    for_each(niz,niz+10,[](int &n) {  
        cin>>n;
    });
    bool djeljivi=MakarJedan(niz,niz+10,[](int n) {
        int suma=0;
        while(n!=0){
            suma+=n%10;  
            n/=10;
        }  
        if(n%suma==0)return true;
        return false;
    });
    if(djeljivi==true)cout<<"U nizu ima brojeva djeljivih sa sumom svojih cifara"<<endl;
    else cout<<"U nizu nema brojeva djeljivih sa sumom svojih cifara"<<endl;
    deque<double> d(10);
    cout<<"Unesite dek od 10 elemenata: "<<endl;
    for_each(d.begin(),d.end(),[](double &n) {
        cin>>n;
    });
    double a0=0,a1=1;
    double suma=Akumuliraj(d.begin(),d.end(),[](double x,double y) {
        return x+y;
    },a0);
    double produkt=Akumuliraj(d.begin(),d.end(),[](double x,double y) {
        return x*y;
    },a1);
    a0=*d.begin();
    double najmanji=Akumuliraj(d.begin(),d.end(),[](double x,double y) {
        if(x<y)return x;
        return y;
    },a0);
    double najveci=Akumuliraj(d.begin(),d.end(),[](double x,double y) {
        if(x>y)return x;
        return y;
    },a0);
    cout<<"Suma deka: "<<suma<<endl;
    cout<<"Produkt deka: "<<produkt<<endl;
    cout<<"Najveci elemenat deka: "<<najveci<<endl;
    cout<<"Najmanji elemenat deka: "<<najmanji<<endl;
    return 0;
}
