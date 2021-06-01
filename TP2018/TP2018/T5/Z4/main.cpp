/*
    TP 2018/2019: Tutorijal 5, Zadatak 4

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
#include<deque>
#include<algorithm>
#include<cmath>
using namespace std;

int main ()
{
	int n;
	cout<<"Unesite broj elemenata: ";
	cin>>n;
	cout<<"Unesite elemente: ";
	deque<int>d;
	d.resize(n);
	for_each(d.begin(),d.end(),[](int &br) {
		cin>>br;
	});
	cout<<"Najveci element deka je "<<*max_element(d.begin(),d.end())<<endl;;
	cout<<"Najmanji element deka se pojavljuje "<<count(d.begin(),d.end(),*min_element(d.begin(),d.end()))<<" puta u deku"<<endl;
	cout<<"U deku ima "<<count_if(d.begin(),d.end(),[](int &br) {
		if((int)sqrt(br)==sqrt(br))return true;
		return false;
	});
	cout<<" brojeva koji su potpuni kvadrati"<<endl;
	cout<<"Prvi element sa najmanjim brojem cifara je "<<*min_element(d.begin(),d.end(),[](int &n,int &z) {
		int n1=n,z1=z;
		if(n1<0)n1*=-1;
		if(z1<0)z1*=-1;
		if((int)log10(n1)+1<(int)log10(z1)+1)return true;
		return false;
	})<<endl;
	cout<<"Elementi koji nisu trocifreni su: ";
	int vel=count_if(d.begin(),d.end(),[](int &br) {
		int n=br;
		if(n<0)n*=-1;
		if(n>=100 && n<=999)return  false;
		return true;
	});
	deque<int> b;
	b.resize(vel);
	copy_if(d.begin(),d.end(),b.begin(),[](int &br) {
		int n=br;
		if(n<0)n*=-1;
		if(n>=100 && n<=999)return false;
		return true;
	});
	for_each(b.begin(),b.end(),[](int &br) {
		cout<<br<<" ";
	});

	return 0;
}
