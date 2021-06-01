/*
    TP 2018/2019: Tutorijal 5, Zadatak 5

	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.

	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.

			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;
double TrapeznoPravilo(double f(double),double a,double b,int n)
{
	double dio1=(1./2)*f(a);
	double dio2=(1./2)*f(b);
	double dio3=(b-a)/n;
	double dio4=0;
	for(int i=1; i<=n-1; i++)
		dio4+=f(a+dio3*i);
	double dio5=dio1+dio2+dio4;
	double dio6=dio3*dio5;  
	return fabs(dio6);
}
int main ()
{
	cout<<"Unesite broj podintervala: ";
	int n;
	cin>>n;
	cout<<"Za taj broj podintervala priblizne vrijednosti integrala iznose:"<<endl;
	cout<<"- Za funkciju sin x na intervalu (0,pi): "<<fixed<<setprecision(5)<<TrapeznoPravilo(sin,0,4*atan(1),n)<<endl;
	cout<<"- Za funkciju x^3 na intervalu (0,10): "<<fixed<<setprecision(2)<<TrapeznoPravilo([](double x) {
		return x*x*x;
	},0,10,n)<<endl;
	cout<<"- Za funkciju 1/x na intervalu (1,2): "<<fixed<<setprecision(5)<<TrapeznoPravilo([](double x) {
		return (1./x);
	},1,2,n)<<endl;

	return 0;
}
