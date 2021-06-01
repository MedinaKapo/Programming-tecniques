//TP 2017/2018: Tutorijal 2, Zadatak 1
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
/*using std::cout;
using std::cin;
using std::vector;
using std::endl; */
 
bool DaLiJeProst(int n)
{
    bool prost=true;
    if(n<=1)prost=false;
    else {
        for(int i=2; i<=sqrt(n); i++) {
            if(n%i==0)prost=false;
        }
    }
    return prost;
};
vector<int> ProstiBrojeviUOpsegu(int a,int b)
{
    vector<int> brojevi;
    for(int i=a; i<=b; i++) {
        if(DaLiJeProst(i)==true)brojevi.push_back(i);
        if(i==b)break;
    }
    return brojevi;
}
int main() 
{
    int a,b;
    cout<<"Unesite pocetnu i krajnju vrijednost: ";
    cin>>a>>b;
    vector<int> prosti;
    prosti=ProstiBrojeviUOpsegu(a,b);
    if(prosti.size()>0) {
        cout<<"Prosti brojevi u rasponu od "<<a<<" do "<<b<<" su: ";
        for(int i=0; i<prosti.size(); i++) {
            if(i>0 && i<prosti.size())cout<<", ";
            cout<<prosti.at(i);
        }
        cout<<endl;
    } else {
        cout<<"Nema prostih brojeva u rasponu od "<<a<<" do "<<b<<"!"<<endl;
    }
}
