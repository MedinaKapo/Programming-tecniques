/* 
    TP 16/17 (Tutorijal 7, Zadatak 6)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include<list>
#include<new>
#include<stdexcept> 
using namespace std;
template<typename tip>
typename std::list<tip> SortirajListu(typename std::list<tip> &lista){
	typename std::list<tip> &vracam=lista;
	for(auto it=vracam.begin();it!=vracam.end();it++){
		auto min=it;
		it++;
		for(auto it2=it;it2!=vracam.end();it2++){
			if(*it2<*min){
		auto pom=*min;
		*min=*it2; 
		*it2=pom;
			}  
		}
		it--; 
	}
	return vracam;
	
}
int main ()
{ 
	int n;
	cout<<"Koliko ima elemenata: ";
	cin>>n;
	cin.ignore(1000,'\n'); 
	cout<<"Unesite elemente: ";
	int br;
	list<int>lista;
	list<int>::iterator it=lista.begin();
	for(int i=0;i<n;i++){
		cin>>br;
		lista.insert(it,br);
		it++;
	}
	cout<<"Sortirana lista: ";
	list<int>lista1;
	lista1=(SortirajListu(lista));
	for(auto x:lista1)cout<<x<<" ";
	return 0;
}