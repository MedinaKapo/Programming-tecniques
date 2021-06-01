/*
    TP 16/17 (Tutorijal 10, Zadatak 3)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<cmath>
using namespace std;
class Vektor3d
{
	double koordinate[3];
	mutable int brojac{};
public:
	Vektor3d()
	{
		koordinate[0]=0;
		koordinate[1]=0;
		koordinate[2]=0;
	}
	Vektor3d(double x,double y,double z)
	{
		koordinate[0]=x;
		koordinate[1]=y;
		koordinate[2]=z;
	}
	void Postavi(double x,double y,double z)
	{
		Vektor3d::koordinate[0]=x;
		Vektor3d::koordinate[1]=y;
		Vektor3d::koordinate[2]=z;
	}
	Vektor3d(const Vektor3d &v):brojac(0)
	{
		koordinate[0]=v.koordinate[0];
		koordinate[1]=v.koordinate[1];
		koordinate[2]=v.koordinate[2];
	}
	void Ocitaj(double &x,double &y,double &z)const
	{
		x=Vektor3d::koordinate[0];
		y=Vektor3d::koordinate[1];
		z=Vektor3d::koordinate[2];
	}
	void Ispisi()const
	{
		cout<<"{"<<koordinate[0]<<","<<koordinate[1]<<","<<koordinate[2]<<"}";
		brojac++;
	}
	double DajX()const
	{
		return koordinate[0];
	}
	double DajY()const
	{
		return koordinate[1];
	}
	double DajZ()const
	{
		return koordinate[2];
	}
	void PostaviX(double x)
	{
		koordinate[0]=x;
	}
	void PostaviY(double y)
	{
		koordinate[1]=y;
	}
	void PostaviZ(double z)
	{
		koordinate[2]=z;
	}
	int DajBrojIspisa()const
	{
		return brojac;
	}
	double DajDuzinu()const
	{
		return sqrt(koordinate[0]*koordinate[0]+koordinate[1]*koordinate[1]+koordinate[2]*koordinate[2]);
	}
	Vektor3d &PomnoziSaSkalarom(double s)
	{
		koordinate[0]*=s;
		koordinate[1]*=s;
		koordinate[2]*=s;
		return *this;
	}
	Vektor3d &SaberiSa(const Vektor3d &v)
	{
		koordinate[0]+=v.koordinate[0];
		koordinate[1]+=v.koordinate[1];
		koordinate[2]+=v.koordinate[2];
		return *this;
	}
	friend Vektor3d ZbirVektora(const Vektor3d &v1,const Vektor3d &v2);
};
Vektor3d ZbirVektora(const Vektor3d &v1,const Vektor3d &v2)
{
	Vektor3d v3;
	v3.Postavi(v1.DajX()+v2.DajX(),v1.DajY()+v2.DajY(),v1.DajZ()+v2.DajZ());
	return v3;
}
int main ()
{
	Vektor3d v;
	v.Postavi(1,1,1);
	v.Postavi(2,2,2);
	v.PostaviX(5);
	v.PostaviY(5);
	v.PostaviZ(5);
	cout<<v.DajX()<<" "<<v.DajY()<<" "<<v.DajZ()<<endl;
	v.PomnoziSaSkalarom(5);
	v.Ispisi();
	cout<<endl;
	Vektor3d u(1,1,1);
	v.SaberiSa(u);
	v.Ispisi();
	cout<<endl;
	Vektor3d p(2,3,4);
	Vektor3d z=ZbirVektora(p,v);
	z.Ispisi();
	cout<<v.DajBrojIspisa()<<endl;
	cout<<v.DajDuzinu();
	cout<<endl;
	v=u;
	v.Ispisi();
	double x,y,t;
	v.Ocitaj(x,y,t);
	cout<<x<<y<<t;
	return 0;
}
