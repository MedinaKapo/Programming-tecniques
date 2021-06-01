/* 
    TP 16/17 (Tutorijal 7, Zadatak 7)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include<string>
#include<set>  
using namespace std;
template<typename tip>
typename std::set<tip> Unija(typename std::set<tip> set1,typename std::set<tip> set2){
	typename std::set<tip> vracam;
	for(auto x:set1)vracam.insert(x);
	for(auto x:set2)vracam.insert(x);
	return vracam;
} 
template<typename tip>
typename std::set<tip> Presjek(typename std::set<tip> set1,typename std::set<tip> set2){
	typename std::set<tip> vracam;
	for(auto x:set1){
		for(auto y:set2){
			if(x==y)vracam.insert(x); 
		}
	}
	return vracam; 
}  
int main ()
{
set<string>s1={"abc","bcd","mnk"};
set<string>s2={"abc","mnk","pqr"};
set<string>unija=Unija(s1,s2);
set<string>presjek=Presjek(s1,s2);
for(auto x:unija)cout<<x<<" ";
cout<<endl;
for(auto x:presjek)cout<<x<<" ";
cout<<endl;
	return 0;
}