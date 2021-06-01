/* 
    TP 16/17 (Tutorijal 7, Zadatak 10)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include<functional>
using namespace std;
function<int(int)> IteriranaFunkcija(function<int(int)>f,int n){
	return [f,n](int x){if(n<=0){x=n;return x;}for(int i=0;i<n;i++)x=f(x);return x;};
}
int main ()   
{  
	auto g=IteriranaFunkcija([](int x){return x+x;},5)(5); 
	cout<<g<<endl;
	auto r=IteriranaFunkcija([](int x){return x+x;},5)(0);
	cout<<r<<endl;
	return 0; 
}