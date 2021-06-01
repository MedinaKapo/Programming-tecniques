/* 
    TP 2018/2019: Tutorijal 5, Zadatak 2
	
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
#include<string>
using namespace std;
template<typename tip1,typename tip2>
tip2 RazmijeniBlokove(tip1 p1,tip1 p2,tip2 p3){
	while(p1!=p2){
		auto pok=*p3; 
		*p3=*p1; 
		*p1=pok;
		p1++;p3++;
	}
	return p3;
} 
int main ()
{
	int niz1[2]={2,6};
	int niz2[2]={1,3};
	int *p=RazmijeniBlokove(begin(niz1),end(niz1),begin(niz2));
	int *q=begin(niz2);
	for(int i=0;i<2;i++)cout<<*q++<<" ";
	string s1="tehnike programiranja";
	string s2="inzenjerska matematik";
	auto s3=RazmijeniBlokove(s1.begin(),s1.end(),s2.begin());
	cout<<s2<<endl;
	return 0;
} 