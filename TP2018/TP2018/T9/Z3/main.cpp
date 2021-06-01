/* 
    TP 16/17 (Tutorijal 9, Zadatak 3)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include<cmath>
using namespace std;
class Vektor3d{
	double koordinate[3]; 
	mutable int brojac{};
	public:
	void Postavi(double x,double y,double z){
		Vektor3d::koordinate[0]=x;
		Vektor3d::koordinate[1]=y;
		Vektor3d::koordinate[2]=z;
	}
	void Ocitaj(double &x,double &y,double &z)const{
		x=Vektor3d::koordinate[0];
		y=Vektor3d::koordinate[1];
		z=Vektor3d::koordinate[2];
	}
	void Ispisi()const{
		cout<<"{"<<koordinate[0]<<","<<koordinate[1]<<","<<koordinate[2]<<"}";
		brojac++;
	}  
	double DajX()const{return koordinate[0];}
	double DajY()const{return koordinate[1];}
	double DajZ()const{return  koordinate[2];}
	void PostaviX(double x){koordinate[0]=x;}
	void PostaviY(double y){koordinate[1]=y;}
	void PostaviZ(double z){koordinate[2]=z;}
	int DajBrojIspisa()const{return brojac;}
	double DajDuzinu()const{return sqrt(koordinate[0]*koordinate[0]+koordinate[1]*koordinate[1]+koordinate[2]*koordinate[2]);}
	Vektor3d &PomnoziSaSkalarom(double s){
		koordinate[0]*=s;koordinate[1]*=s;koordinate[2]*=s;
		return *this;
	}
	Vektor3d &SaberiSa(const Vektor3d &v){
		koordinate[0]+=v.koordinate[0];
		koordinate[1]+=v.koordinate[1];
		koordinate[2]+=v.koordinate[2];
		return *this;
	}
	friend Vektor3d ZbriVektora(const Vektor3d &v1,const Vektor3d &v2);
};
Vektor3d ZbriVektora(const Vektor3d &v1,const Vektor3d &v2){
	Vektor3d v3;
	v3.Postavi(v1.DajX()+v1.DajX(),v1.DajY()+v2.DajY(),v1.DajZ()+v2.DajZ());
	return v3;
}
int main ()
{
	Vektor3d v1,v2,v3;
	v1.Postavi(4,3,2);
	v2.Postavi(2,1,3);
	ZbriVektora(v1,v2).Ispisi();
	cout<<endl;
	v1.PomnoziSaSkalarom(5).Ispisi();
	cout<<endl;
	v1.SaberiSa(v2).Ispisi();
	cout<<endl;
	v3.PostaviX(5);
	v3.PostaviY(6);
	v3.PostaviZ(7);
	v3.PomnoziSaSkalarom(5).Ispisi();
	cout<<endl;
	cout<<v3.DajX()<<" "<<v3.DajY()<<" "<<v3.DajZ()<<endl;
	cout<<v3.DajDuzinu();
	double x,y,z;
	cout<<endl;
	v2.Ocitaj(x,y,z);
	cout<<x<<" "<<y<<" "<<z;
	v1.Ispisi();v2.Ispisi();v1.Ispisi();
	cout<<"Objekat v1 je ispisan "<<v1.DajBrojIspisa()<<" puta, a objekat v2 "<<v2.DajBrojIspisa()<<"puta"<<endl;
	return 0;
}