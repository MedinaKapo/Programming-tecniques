//TP 2018/2019: Tutorijal 8, Zadatak 4
#include <iostream>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
string ZamijeniPremaRjecniku(string s,map<string,string>mapa)
{
    bool razmak=true;
    int i=0;
    while(i<s.size()) {
        if(s.at(i)==' ')razmak=true; 
        else if(razmak==true) {
            razmak=false;
            int j=i;
            while(j<s.size() && s.at(j)!=' ')j++;
            string rijec=s.substr(i,j-i);
            if(mapa.find(rijec)!=mapa.end())
                s.replace(i,j-i,mapa[rijec]);
        }
        i++;
    }
    return s;
}

int main ()
{
    string s="kako da ne";
    map<string,string> mapa{{"kako","how"},{"da","yes"},{"ne","no"}};
    s=ZamijeniPremaRjecniku(s,mapa);
    cout<<s<<endl;
    return 0;
}
