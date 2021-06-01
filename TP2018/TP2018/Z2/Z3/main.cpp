/* TP, 2018/2019
*/
#include <iostream>
#include<vector>
#include<deque>
using namespace std;
template<typename tip>
int duzina(tip p1,tip p2){
    int brojac=0;
    while(p1!=p2){
        brojac++; 
        p1++;  
    }
    return brojac;
}
template<typename Tip1,typename Tip2,typename Tip3>
Tip3 SimetricnaRazlikaBlokova(Tip1 p1,Tip1 p2,Tip2 p3,Tip2 p4,Tip3 p5){
    int velicina_vracam=0;
    int velicina_prvog=duzina(p1,p2);
    int velicina_drugog=duzina(p3,p4);
    int i=0,brojac_parametri=0,brojac_vracanje=0,k=0;
    while(i<velicina_prvog){
        for(int j=0;j<velicina_drugog;j++){
            if(p1[i]==p3[j])brojac_parametri++;
        }
        if(brojac_parametri==0){
            while(k<velicina_vracam){
                if(p1[i]==p5[k])brojac_vracanje++;
                k++;
            }
            if(brojac_vracanje==0){p5[velicina_vracam]=p1[i];
            ++velicina_vracam;}
        }
        i++;
        brojac_vracanje=0;
        brojac_parametri=0;
        k=0;
    }
    i=0;
    brojac_parametri=0;brojac_vracanje=0;k=0;
    while(i<velicina_drugog){
        for(int j=0;j<velicina_prvog;j++){
            if(p3[i]==p1[j])brojac_parametri++;
        }
        if(brojac_parametri==0){
            while(k<velicina_vracam){
                if(p5[k]==p3[i])brojac_vracanje++;
                k++;
            }
            if(brojac_vracanje==0){
                p5[velicina_vracam]=p3[i];
                ++velicina_vracam;
            }
        }
        i++;
        brojac_vracanje=0;
        brojac_parametri=0;
        k=0;
    }
    return (p5+velicina_vracam);
}

int main ()
{
    int niz[100];
    cout<<"Unesite broj elemenata niza"<<endl;;
    int n;
    cin>>n;
    cout<<"Unesite elemente niza"<<endl;
    for(int i=0;i<n;i++){
        int br;
        cin>>br;
        niz[i]=br;
    }
   
    cout<<"Unesite broj elemenata deka"<<endl;
    int n1;
    cin>>n1;
    deque<int>d(n1);
    cout<<"Unesite elemente deka"<<endl;
int br1;
    for(int i=0;i<n1;i++){ 
        cin>>br1;
        d[i]=br1; 
    }
    vector<int> rezultat;
    rezultat.resize(100);
    vector<int>::iterator r;
    r=rezultat.begin();
    vector<int>::iterator kraj=SimetricnaRazlikaBlokova(niz,niz+n,d.begin(),d.end(),rezultat.begin());
    if(r!=kraj){
    cout<<"Simetricna razlika blokova je: ";
    while(r!=kraj)cout<<*r++<<" ";
    }
    else cout<<"Blokovi nemaju simetricnu razliku";
	return 0;
}