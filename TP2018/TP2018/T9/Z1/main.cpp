/*
    TP 16/17 (Tutorijal 9, Zadatak 1)

	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include<cmath>
using namespace std;
class Vektor3d
{
	double x,y,z;
public:
	void Postavi(double x,double y,double z)
	{
		Vektor3d::x=x;
		Vektor3d::y=y;
		Vektor3d::z=z;
	}
	void Ocitaj(double &x,double &y,double &z)const
	{
		x=Vektor3d::x;
		y=Vektor3d::y;
		z=Vektor3d::z;
	}
	void Ispisi()const
	{
		cout<<"{"<<x<<","<<y<<","<<z<<"}";
	}
	double DajX() const
	{
		return x;
	}
	double DajY()const
	{
		return y;
	}
	double DajZ()const
	{
		return z;
	}
	void PostaviX(double x)
	{
		Vektor3d::x=x;
	}
	void PostaviY(double y)
	{
		Vektor3d::y=y;
	}
	void PostaviZ(double z)
	{
		Vektor3d::z=z;
	}
	double DajDuzinu()const
	{
		return sqrt(x*x+y*y+z*z);
	}
	Vektor3d &PomnoziSaSkalarom(double s)
	{   
		x*=s;
		y*=s;
		z*=s; 
		return *this;
	}
	Vektor3d &SaberiSa(const Vektor3d &v)
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
		return *this;
	}
	friend Vektor3d ZbirVektora(const Vektor3d &v1,const Vektor3d &v2);
};
Vektor3d ZbirVektora(const Vektor3d &v1,const Vektor3d &v2)
{
	Vektor3d v3;
	v3.x=v1.x+v2.x;
	v3.y=v1.y+v2.y;
	v3.z=v1.z+v2.z;
	return v3;
}
 
int main ()
{
	Vektor3d v1,v2,v3;
	v1.Postavi(4,3,2);
	v2.Postavi(2,1,3);
	ZbirVektora(v1,v2).Ispisi();
	cout<<endl;
	v1.PomnoziSaSkalarom(5).Ispisi();
	cout<<endl;
	v1.SaberiSa(v2).Ispisi();
	cout<<endl;
	v3.PostaviX(5);
	v3.PostaviY(6);
	v3.PostaviZ(7);
	v3.PomnoziSaSkalarom(5).Ispisi();
	cout<<v3.DajX();
	cout<<" ";
	cout<<v3.DajY();
	cout<<" ";
	cout<<v3.DajZ();
	cout<<endl;
	cout<<v3.DajDuzinu();
	double x,y,z;
	v2.Ocitaj(x,y,z);
	cout<<endl;
	cout<<x<<" "<<y<<" "<<z;

	return 0;
}
