/* 
    TP 16/17 (Tutorijal 12, Zadatak 3)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
using namespace std;
enum Dani{Ponedjeljak,Utorak,Srijeda,Cetvrtak,Petak,Subota,Nedjelja};
/*Dani &operator++(Dani &d){
	if(int(d)+1!=8)return d=Dani(int(d)+1);
	else return d=Dani(int(d)+1-7);
}*/
Dani &operator++(Dani &d){
	return d=Dani((int(d)+1)%7);
}
Dani operator++(Dani &d,int){
	Dani pom=d;
	++d; 
	return pom;
}   
/*Dani operator+(Dani d,int n){ 
	if(int(d)+n<8)return Dani(int(d)+n);
	else return Dani(int(d)+n-7);
}*/  
Dani operator+(Dani d,int n){
	return Dani((int(d)+n)%7); 
}
ostream &operator<<(ostream &tok,const Dani d){
	string dan[]={"Ponedjeljak","Utorak","Srijeda","Cetvrtak","Petak","Subota","Nedjelja"};
	tok<<dan[static_cast<int>(d)];
	return tok;
}
int main ()
{
	for(Dani d=Ponedjeljak;d<=Petak;d++)cout<<d<<endl;
	for(Dani d=Ponedjeljak;d<=Nedjelja;d++){
		if(d==Nedjelja){cout<<d<<endl;break;}
		else cout<<d<<endl;}
	return 0;
}