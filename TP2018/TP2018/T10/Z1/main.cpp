/*
    TP 16/17 (Tutorijal 10, Zadatak 1)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<stdexcept>
using namespace std;
class StedniRacun
{
	double x;
public:
	StedniRacun()
	{
		x=0;
	}
	StedniRacun(double a)
	{
		if(a<0)throw logic_error("Nedozvoljeno pocetno stanje");
		x=a;
	}
	double Ulozi(double iznos);
	double Podigni(double iznos);
	double DajStanje()const;
	double ObracunajKamatu(double iznos);
};
double StedniRacun::DajStanje()const
{
	return x;
}
double StedniRacun::Ulozi(double iznos)
{
	x+=iznos;
	if(x<0)throw logic_error("Transakcija odbijena");
}
double StedniRacun::Podigni(double iznos)
{
	if(iznos>DajStanje())throw logic_error("Transakcija odbijena");
	x-=iznos;
}
double StedniRacun::ObracunajKamatu(double iznos)
{
	if(iznos<0)throw logic_error("Nedozvoljena kamatna stopa");
	iznos/=100;
	double stanje=DajStanje()*iznos;
	x+=stanje;
	return x;

}
int main ()
{
	StedniRacun p;
	cout<<p.DajStanje();
	cout<<endl;
	StedniRacun a(50);
	cout<<a.DajStanje();
	cout<<endl;
	a.Ulozi(5);
	cout<<a.DajStanje();
	cout<<endl;
	a.Podigni(5);
	cout<<a.DajStanje();
	cout<<endl;
	a.ObracunajKamatu(5);
	cout<<a.DajStanje();
	a.Ulozi(10);
	cout<<a.DajStanje();
	cout<<endl;
	const StedniRacun b(8);
	cout<<b.DajStanje();
	return 0;
}
