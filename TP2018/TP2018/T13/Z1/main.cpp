/*
    TP 16/17 (Tutorijal 13, Zadatak 1)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<stdexcept>
#include<cmath>
#include<vector>
#include<memory>  
using namespace std;
class Lik
{
public:
	virtual void IspisiSpecificnosti()const=0;
	virtual double DajObim()const=0;
	virtual double DajPovrsinu()const=0;
	virtual ~Lik() {};
	void Ispisi()
	{
		IspisiSpecificnosti();
		cout<<"Obim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<endl;
	}
};
class Krug:public Lik
{
	double r;
public:
	Krug(double p):r(p)
	{
		if(p<=0)throw domain_error("Neispravni parametri");
	}
	void IspisiSpecificnosti()const override
	{
		cout<<"Krug poluprecnika "<<r<<endl;
	}
	double DajObim()const override
	{
		return 2*r*4*atan(1);
	}
	double DajPovrsinu()const override
	{
		return r*r*4*atan(1);
	}
};
class Pravougaonik:public Lik
{
	double a,b;
public:
	Pravougaonik(double c,double d):a(c),b(d)
	{
		if(c<=0 || d<=0)throw domain_error("Neispravni parametri");
	}
	void IspisiSpecificnosti()const override
	{
		cout<<"Pravougaonik sa stranicama duzine "<<a<<" i "<<b<<endl;
	}
	double DajObim()const override
	{
		return 2*(a+b);
	}
	double DajPovrsinu()const override
	{
		return a*b;
	}
};
class Trougao:public Lik
{
	double a,b,c;
public:
	Trougao(double d,double e,double f):a(d),b(e),c(f)
	{
		if(a+b<=c || b+c<=a || a+c<=b)throw domain_error("Neispravni parametri");
	}
	void IspisiSpecificnosti()const override
	{
		cout<<"Trougao sa stranicama duzine "<<a<<", "<<b<<" i "<<c<<endl;
	}
	double DajObim()const override
	{
		return a+b+c;
	}
	double DajPovrsinu()const override
	{
		double s=DajObim()/2.;
		return sqrt(s*(s-a)*(s-b)*(s-c));
	}
};
int main ()
{ 
	int n;
	cout<<"Koliko zelite likova: ";
	cin>>n;
	if(!cin)return 0;
	vector<shared_ptr<Lik>> likovi;
	int i=1;
//while(1){
	for(int i=0; i<n; i++) {
		try {
			cout<<"Lik "<<i+1<<": ";
			char znak;
			cin>>znak;
			if(znak=='K') {
				double r;
				cin>>r;
				if(!cin || cin.peek()!='\n') {
					cin.clear();
					cin.ignore(1000,'\n');
					cout<<"Pogresni podaci, ponovite unos!"<<endl;
					i--;
					continue;
				}
				likovi.push_back(shared_ptr<Lik>(new Krug(r)));
			} else if(znak=='P') {
				double a,b;
				char znak;
				cin>>a>>znak>>b;
				if(!cin || cin.peek()!='\n') {
					cin.clear();
					cin.ignore(1000,'\n');
					cout<<"Pogresni podaci, ponovite unos!"<<endl;
					i--;
					continue;
				}
				likovi.push_back(shared_ptr<Lik>(new Pravougaonik(a,b)));
			} else if(znak=='T') {
				double a,b,c;
				char znak;
				cin>>a>>znak>>b>>znak>>c;
				if(!cin || cin.peek()!='\n') {
					cin.clear();
					cin.ignore(1000,'\n');
					cout<<"Pogresni podaci, ponovite unos!"<<endl;
					i--;
					continue;
				}
				likovi.push_back(shared_ptr<Lik>(new Trougao(a,b,c)));
			} else {
				cin.clear();
				cin.ignore(1000,'\n');
				cout<<"Pogresni podaci, ponovite unos!"<<endl;
				i--;
				continue;

			}
			/*	if(i==n)break;  
				i++;*/ 
		} catch(...) {
			cout<<"Pogresni podaci, ponovite unos!"<<endl;
			i--; 
		} 
	}
	cout<<endl;
	for(int i=0; i<n; i++) {
		likovi.at(i)->Ispisi();
	}

	return 0;
}
