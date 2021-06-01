/* 
    TP 2018/2019: Tutorijal 5, Zadatak 3
	
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
#include<cmath>
using namespace std;
void unesi(int &n){
	cin>>n;
}
bool kvadrat(int n){
	if ((int)sqrt(n)==sqrt(n))return true;
	return false; 
	
	
} 
bool nisitrocifren(int n){
	if(n<0)n*=-1;
	if (n>=100 && n<=999)return false;
	return true;

}
void ispisi(int &n){
	cout<<n<<" ";
}
bool manji(const int &n,const int &z){
	int n1,z1;
	n1=n;z1=z;
	if(n1<0)n1*=-1;
	if(z1<0)z1*=-1;
	if ((int)(log10(n1))+1<(int)(log10(z1))+1)return true;
	return false;
	
}
int main ()
{  
	int niz[1000];
	int n;
	cout<<"Unesite broj elemenata (max. 1000): ";
	cin>>n;
	cout<<"Unesite elemente: ";
	int br;
	for_each(niz,niz+n,*unesi);
	cout<<"Najveci element niza je "<<*max_element(niz,niz+n)<<" "<<endl;
	cout<<"Najmanji element niza se pojavljuje "<<count(niz,niz+n,*min_element(niz,niz+n))<<" puta u nizu"<<endl;
	cout<<"U nizu ima "<<count_if(niz,niz+n,kvadrat)<<" brojeva koji su potpuni kvadrati"<<endl;
	cout<<"Prvi element sa najmanjim brojem cifara je "<<*min_element(niz,niz+n,manji)<<endl;
	cout<<"Elementi koji nisu trocifreni su: ";
	int niz2[1000];
	copy_if(niz,niz+n,niz2,nisitrocifren);
	int vel=count_if(niz,niz+n,nisitrocifren);
	for_each(niz2,niz2+vel,*ispisi);
	return 0;
}