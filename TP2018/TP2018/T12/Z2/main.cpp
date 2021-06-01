/* 
    TP 16/17 (Tutorijal 12, Zadatak 2)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include<set> 
#include<algorithm>  
#include<utility> 
using namespace std; 
template<typename Tip>
set<Tip>operator+(const set<Tip>&s1,const set<Tip>&s2){
	set<Tip>unija;
	for(auto it=s1.begin();it!=s1.end();it++)
	unija.insert(*it);
	for(auto it=s2.begin();it!=s2.end();it++)
	unija.insert(*it);
	return unija;
}
template<typename Tip>
set<Tip>operator*(const set<Tip>&s1,const set<Tip>s2){
	set<Tip>presjek;
	for(auto x:s1){
		for(auto y:s2){
			if(x==y)presjek.insert(x);
		}
	}
	return presjek;
}
template<typename Tip>
set<Tip>&operator+=(set<Tip>&s1,const set<Tip>&s2){
	for(auto x:s2)s1.insert(x);
	return s1;
}
template<typename Tip>
set<Tip>&operator*=(set<Tip>&s1,const set<Tip>&s2){
	set<Tip>presjek;
	for(auto x:s1){
		for(auto y:s2)
		if(x==y)presjek.insert(x);
	}
	s1=presjek;
	return s1;
}
template<typename Tip1,typename Tip2>
set<pair<Tip1,Tip2>>operator%(const set<Tip1>&s1,const set<Tip2>&s2){
	set<pair<Tip1,Tip2>>proizvod;
	for(auto x:s1){
		for(auto y:s2){
			proizvod.insert(make_pair(x,y));
		}
	}
	return proizvod;
}
template<typename Tip1,typename Tip2>
ostream &operator<<(ostream &tok,const set<pair<Tip1,Tip2>> &s){
	tok<<"{";
	for(auto it=s.begin();it!=s.end();it++){
		tok<<"("<<it->first<<","<<it->second<<")";
		if(it!=--s.end()){
			tok<<",";
			//it--;
			}
	}
	tok<<"}";
	return tok;
}
template<typename Tip>
ostream &operator<<(ostream &tok,const set<Tip> &s){
	tok<<"{";
	for(auto it=s.begin();it!=s.end();it++){
		tok<<*it;
		if(it!=--s.end()){
			tok<<",";
			//it--;
		}
	}
		tok<<"}"; 
		return tok;
	
} 
int main ()
{
	set<int>s1{2,4,6,8},s2{1,2,3,4};
	set<int>presjek;
	cout<<s1+s2<<endl;
	cout<<s1*s2<<endl;
	cout<<s1%s2<<endl;
	set<char>s3{'M','K'};
	cout<<s1%s3<<endl;
	s1+=set<int>{1,2,3};
	cout<<s1<<endl;
	s1*=set<int>{7,8,9};
	cout<<s1<<endl;
	return 0;
}