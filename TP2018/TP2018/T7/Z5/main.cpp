/* 
    TP 16/17 (Tutorijal 7, Zadatak 5)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include<algorithm>
#include<new>  
#include<memory>
#include<string> 
#include<stdexcept>
using namespace std;
typedef shared_ptr<string> recenice;
int main ()
{
	int n;
	cout<<"Koliko zelite recenica: ";
	cin>>n;
	cin.ignore(1000,'\n');
	
	try{
		cout<<"Unesite recenice:"<<endl;
		shared_ptr<recenice>pok(new recenice[n],[](recenice *pok){delete[] pok;});
		for(int i=0;i<n;i++){
			pok.get()[i]=make_shared<string>();
			getline(cin,*pok.get()[i]);
		}
		sort(pok.get(),pok.get()+n,[](recenice a,recenice b){
			if(*a<*b)return true; 
			return false;
		}); 
		cout<<"Sortirane recenice:"<<endl;
		for(int i=0;i<n;i++)
		cout<<*pok.get()[i]<<endl;
		pok=nullptr;
		delete[] pok.get();
	}
	catch(bad_alloc){
		cout<<"Problemi s memorijom!"<<endl;
		
	}
	return 0;
}