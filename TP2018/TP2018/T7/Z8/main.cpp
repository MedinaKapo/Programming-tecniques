/* 
    TP 16/17 (Tutorijal 7, Zadatak 8)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include<string>
#include<algorithm>
using namespace std;
string IzvrniBezRazmaka(string s){
	string pomocni;
	remove_copy(s.rbegin(),s.rend(),back_inserter(pomocni),' ');
	return pomocni;
} 
int main () 
{      
	string s;
	cout<<"unesi string";
	getline(cin,s);
	s=IzvrniBezRazmaka(s);
	cout<<s<<endl;
	string t="tehnike programiranja";
	t=IzvrniBezRazmaka(t);
	cout<<t;
	return 0;
}