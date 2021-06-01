//TP 2018/2019: Tutorijal 4, Zadatak 2
#include <iostream>
#include<string>
#include<utility>
using namespace std;
void IzvrniString(string &s){
    for(int i=0;i<s.size()/2;i++){
        swap(s.at(i),s.at(s.size()-i-1));
    }
} 
int main () 
{ 
    string recenica; 
    cout<<"Unesi string: ";
    getline(cin,recenica);
    IzvrniString(recenica);
    cout<<"Izvrnuti string je: "<<recenica;
    
	return 0;
}