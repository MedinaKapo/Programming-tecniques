/* TP, 2018/2019
*/
#include <iostream>
#include<stdexcept>
#include<cmath>
using namespace std;
bool prost(int n)
{
    if(n==1)return false;
    //if(n==2)return true;
    for(int i=2; i<=sqrt(n); i++) {
        if(n%i==0)return false;
    }  
    return true;
}
void RastavaBroja(int n,int &p,int &q)
{
    if(n<=0 || (int)n!=n)throw domain_error("Broj koji se rastavlja mora biti prirodan");
    int broj=n,m=1,k=1;
    for(int i=2; i<=n; i++) {
        if(prost(i)==true && n%(i*i)==0) {
            while(n%(i*i)==0) {
                k*=i;
                n/=(i*i);
            }
        }
        if(prost(i)==true && n%i==0 && n%(i*i)!=0)m*=i;
        n=broj;
        if(m*k*k==broj)break;
    }
    p=m;
    q=k;
}
int main ()
{
    try {
        int n;
        cout<<"Unesite prirodan broj"<<endl;;
        cin>>n;
        int p,q;
        RastavaBroja(n,p,q);
        cout<<p<<" "<<q<<endl;


    } catch(domain_error izuzetak) {
        cout<<"Izuzetak: "<<izuzetak.what()<<"!"<<endl;
    }

    return 0;
}
