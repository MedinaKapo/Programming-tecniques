/*
    TP 16/17 (Tutorijal 10, Zadatak 2)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<cmath>
#include<stdexcept>
#include<iomanip>
using namespace std;
class Krug
{
	double poluprecnik;
public:
	explicit Krug(double x)
	{
		if(x<=0)throw domain_error("Neispravan poluprecnik");
		poluprecnik=x;
	}
	void Postavi(double x);
	double DajPoluprecnik() const
	{
		return poluprecnik;
	}
	double DajObim()const
	{
		return 2*poluprecnik*atan(1)*4;
	}
	double DajPovrsinu()const
	{
		return poluprecnik*poluprecnik*4*atan(1);
	}
	void Skaliraj(double x);
	void Ispisi()const;

};
void Krug::Postavi(double x)
{
	if(x<=0)throw domain_error("Neispravan poluprecnik");
	else poluprecnik=x;
}
void Krug::Ispisi()const
{
	cout<<"R="<<fixed<<setprecision(5)<<DajPoluprecnik()<<" O="<<DajObim()<<" P="<<DajPovrsinu()<<endl;
}
void Krug::Skaliraj(double x)
{
	if(x<=0)throw domain_error("Neispravan faktor skaliranja");
	poluprecnik*=x;
}
class Valjak
{
	Krug baza;
	double visina;
public:
	explicit Valjak(double x,double y):baza(x)
	{
		if(x<=0)throw domain_error("Neispravan poluprecnik");
		if(y<=0)throw domain_error("Neispravna visina");
		baza=Krug(x);
		visina=y;
	}
	void Postavi(double x,double y);
	Krug DajBazu()const
	{
		return baza;
	}
	double DajPoluprecnikBaze()const
	{
		return baza.DajPoluprecnik();
	}
	double DajVisinu()const
	{
		return visina;
	}
	double DajPovrsinu()const
	{
		return 2*baza.DajPovrsinu()+baza.DajObim()*visina;
	}
	double DajZapreminu()const
	{
		return baza.DajPovrsinu()*visina;
	}
	double Skaliraj(double x);
	void Ispisi()const;
};
void Valjak::Postavi(double x,double y)
{
	if(x<=0)throw domain_error("Neispravan poluprecnik");
	if(y<=0)throw domain_error("Neispravna visina");
	baza=Krug(x);
	visina=y;
}
double Valjak::Skaliraj(double x)
{
	if(x<=0)throw domain_error("Neispravan faktor skaliranja");
	baza.Postavi(baza.DajPoluprecnik()*x);
	visina*=x;
}
void Valjak::Ispisi()const
{
	cout<<"R="<<fixed<<setprecision(5)<<baza.DajPoluprecnik()<<" H="<<DajVisinu()<<" P="<<DajPovrsinu()<<" V="<<DajZapreminu()<<endl;
}
int main ()
{
	try {
		Krug k(5);
		Valjak v(2,5);
		k.Postavi(2);
		cout<<k.DajPoluprecnik()<<" "<<k.DajObim()<<" "<<k.DajPovrsinu()<<endl;
		k.Ispisi();
		cout<<endl;
		v.Postavi(2,2);
		cout<<v.DajPovrsinu()<<" "<<v.DajVisinu()<<" "<<v.DajZapreminu()<<" "<<v.DajPoluprecnikBaze()<<endl;
		v.Ispisi();
		cout<<endl;
		const Krug k1(10);
		const Valjak v1(11,12);
		k1.Ispisi();
		cout<<endl;
		cout<<k1.DajPoluprecnik()<<" "<<k1.DajObim()<<" "<<k1.DajPovrsinu()<<endl;
		cout<<v1.DajPovrsinu()<<" "<<v1.DajVisinu()<<" "<<v1.DajZapreminu()<<" "<<v1.DajPoluprecnikBaze()<<endl;
		k.Skaliraj(5);
		cout<<k.DajPoluprecnik()<<endl;
		v.Skaliraj(10);
		cout<<v.DajPoluprecnikBaze()<<endl;
		k.Postavi(-1); 
	} catch(domain_error izuzetak) {
		cout<<izuzetak.what()<<endl;
	}
	return 0;
}
