/* 
    TP 16/17 (Tutorijal 7, Zadatak 9)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include<functional>  
using namespace std;  
function<double(double)> plus2(double x){
	return [x](double y){return x+y;};
}
function<function<double(double)>(double)> plus3(double x){
	return [x](double y){return[x,y] (double z){return x+z+y;};};
}
int main ()
{ 
	cout<<plus2(5)(6)<<endl;
	cout<<plus3(1)(2)(3)<<endl;
	int x,y,z;
	cout<<"Unesi x,y,z";
	cin>>x>>y>>z;
	cout<<plus2(x)(y)<<endl;
	cout<<plus3(x)(y)(z)<<endl;
	return 0;
}