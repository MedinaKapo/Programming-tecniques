/*
    TP 2018/2019: Tutorijal 5, Zadatak 1

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
using namespace std;
int main ()
{
	char niz[1000];
	cout<<"Unesite recenicu: ";
	cin.getline(niz,1000); 
	char *pok;   
	pok=niz; 
	if(*pok!='\0' && *pok==' ')
		while(*pok!='\0' && *pok==' ')pok++;
	if(*pok!='\0' && *pok!=' ')
		while(*pok!='\0' && *pok!=' ')pok++;
	if(*pok!='\0' && *pok==' ')
		while(*pok!='\0' && *pok==' ')pok++;
	cout<<"Recenica bez prve rijeci glasi: "<<pok<<endl;
	return 0;
}
