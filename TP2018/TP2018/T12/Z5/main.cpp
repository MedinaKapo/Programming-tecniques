/* 
    TP 16/17 (Tutorijal 12, Zadatak 5)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<vector> 
#include<functional> 
#include<algorithm>  
using namespace std; 
int main () 
{
	int n;
	cout<<"Koliko zelite elemenata: ";
	cin>>n;
	cout<<"Unesite elemente: ";   
	int broj;
	vector<double>brojevi; 
	for(int i=0;i<n;i++){ 
		cin>>broj;
		brojevi.push_back(broj);
	}
	//transform(brojevi.begin(),brojevi.end(),brojevi.begin(),bind1st(divides<double>(),1));
	transform(brojevi.begin(),brojevi.end(),brojevi.begin(),bind(divides<double>(),1,placeholders::_1));
	cout<<"Transformirani elementi: ";
	for(int i=0;i<n;i++)cout<<brojevi.at(i)<<" ";
	return 0;
}