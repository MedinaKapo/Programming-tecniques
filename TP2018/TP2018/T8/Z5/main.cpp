//TP 2018/2019: Tutorijal 8, Zadatak 5
#include <iostream>
#include<tuple>
using namespace std;
typedef tuple<double,double,double> Vektor3d;
void UnesiVektor(Vektor3d &a)
{
    double x,y,z;
    cout<<"X = ";
    cin>>x;
    cout<<"Y = ";
    cin>>y; 
    cout<<"Z = ";
    cin>>z;
    a=tie(x,y,z);

}
Vektor3d ZbirVektora(Vektor3d &a,Vektor3d &b)
{
    return{make_tuple(get<0>(a)+get<0>(b),get<1>(a)+get<1>(b),get<2>(a)+get<2>(b))};
}
Vektor3d VektorskiProizvod(Vektor3d &a,Vektor3d &b)
{
    return{make_tuple(get<1>(a)*get<2>(b)-get<2>(a)*get<1>(b),-(get<0>(a)*get<2>(b))+get<2>(a)*get<0>(b),get<0>(a)*get<1>(b)-get<1>(a)*get<0>(b))};
}
void IspisiVektor(const Vektor3d &v)
{
    cout<<"{"<<get<0>(v)<<","<<get<1>(v)<<","<<get<2>(v)<<"}";
}
int main ()
{
    Vektor3d a,b;
    cout<<"Unesi prvi vektor:"<<endl;
    UnesiVektor(a);
    cout<<"Unesi drugi vektor:"<<endl;
    UnesiVektor(b);
    cout<<"Suma ova dva vektora je: ";
    IspisiVektor(ZbirVektora(a,b));
    cout<<endl;
    cout<<"Njihov vektorski prozivod je: ";
    IspisiVektor(VektorskiProizvod(a,b));
    return 0;
}
