/*
    TP 2018/2019: Tutorijal 5, Zadatak 6

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
#include<vector>
#include<algorithm>
using namespace std;
int SumaCifara(int n)
{
	if(n==0)return 0;
	return abs(n%10)+SumaCifara(n/10);
}
bool Poredak(int n,int z)
{
	int suma1=SumaCifara(n);
	int suma2=SumaCifara(z);
	if(suma1<suma2)return true;
	if(suma1==suma2 && n<z)return true;
	return false;
}
int main ()
{
	int n;
	cout<<"Unesite broj elemenata: ";
	cin>>n;
	cout<<"Unesite elemente: ";
	vector<int> v;
	v.resize(n);
	int br; 
	for_each(v.begin(),v.end(),[](int &br) {
		cin>>br;
	});
	cout<<"Niz sortiran po sumi cifara glasi: ";
	sort(v.begin(),v.end(),Poredak);
	for_each(v.begin(),v.end(),[](int &br) {
		cout<<br<<" ";
	});
	cout<<endl;
	cout<<"Unesite broj koji trazite: ";
	cin>>br;
	if(binary_search(v.begin(),v.end(),br,Poredak))
		cout<<"Trazeni broj nalazi se na poziciji "<<find(v.begin(),v.end(),br)-v.begin()<<endl;
	else cout<<"Trazeni broj ne nalazi se u nizu!"<<endl;

	return 0;
}
