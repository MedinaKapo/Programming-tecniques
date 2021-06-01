/*
    TP 2018/2019: Tutorijal 5, Zadatak 7

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
#include<algorithm>
#include<stdexcept> 
#include<deque>
#include<type_traits> 
using namespace std;
template<typename tip>
auto SumaBloka(tip p1,tip p2)/*->decltype(*p1+*p2)*/->typename remove_reference<decltype(*p1)>::type
{
	if(p1==p2)throw range_error("Blok je prazan");
	auto suma=*p1;
	p1++;
	while(p1!=p2) {
		suma+=*p1;
		p1++;
	}
	return suma; 
}
int main ()
{
	try{
	int n;
	deque<double>d;
	cout<<"Unesi koliko zelis da bude elemenata u deku: ";
	cin>>n;
	cout<<"Unesi elemente: ";
	d.resize(n);
	double br;
	for_each(d.begin(),d.end(),[](double &br) {
		cin>>br;
	});
	
		cout<<"Suma bloka: "<<SumaBloka(d.begin(),d.end());
	} catch(range_error izuzetak) {
		cout<<izuzetak.what()<<endl;
	}
	return 0;
}
