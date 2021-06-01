//TP 2018/2019: Tutorijal 4, Zadatak 5
#include <iostream>
#include<vector>
#include<string>
using namespace std;
template<typename NekiTip>
vector<NekiTip> Presjek(const vector<NekiTip>&a,const vector<NekiTip>&b)
{
    vector<NekiTip> vracam,c,pom;
    //trazi iste i stavljaj ih u vektor c
    for(int i=0; i<a.size(); i++) { 
        for(int j=0; j<b.size(); j++) { 
            if(a.at(i)==b.at(j))c.push_back(a.at(i));
        } 
    }
    //analiziraj vektor c,tj.trazi da li u vektoru c ima duplih brojeva,ako ima duplikate trpaj u pomocni,a ako ne trpaj sve u vracam
    for(int i=0; i<c.size(); i++) {
        int istina=0;
        for(int k=0; k<pom.size(); k++)if(c.at(i)==pom.at(k))istina=1;
        if(istina==1)continue;

        for(int j=0; j<c.size(); j++) {
            if((c.at(i)==c.at(j)) && i!=j) {
                pom.push_back(c.at(i));
                break;
            }
        }

        vracam.push_back(c.at(i));

    }

    return vracam;
}
int main ()
{
    int n1,n2,br;
    cout<<"Test za realne brojeve..."<<endl;
    cout<<"Unesite broj elemenata prvog vektora: ";
    cin>>n1;
    vector<int>v1;
    cout<<"Unesite elemente prvog vektora: ";
    for(int i=0; i<n1; i++) {
        cin>>br;
        v1.push_back(br);
    }
    cout<<"Unesite broj elemenata drugog vektora: ";
    cin>>n2;
    vector<int>v2;
    cout<<"Unesite elemente drugog vektora: ";
    for(int i=0; i<n2; i++) {
        cin>>br;
        v2.push_back(br);
    }
    cout<<"Zajednicki elementi su: ";
    vector<int>v3=Presjek(v1,v2);

    for(int i=0; i<v3.size(); i++) {
        if(i>0 && i<v3.size())cout<<" ";
        cout<<v3.at(i);
    }
    cout<<endl;
    cout<<endl;
    cout<<"Test za stringove..."<<endl;
    cout<<"Unesite broj elemenata prvog vektora: ";
    int m1,m2;
    cin>>m1;
    cin.clear();
    cin.ignore(10000,'\n');
    cout<<"Unesite elemente prvog vektora (ENTER nakon svakog unosa): ";
    string s;
    vector<string>s1;
    for(int i=0; i<m1; i++) {
        getline(cin,s);
        s1.push_back(s);
    }
    cout<<"Unesite broj elemenata drugog vektora: ";
    cin>>m2;
    cin.clear();
    cin.ignore(10000,'\n');
    vector<string>s2;
    cout<<"Unesite elemente drugog vektora (ENTER nakon svakog unosa): ";
    for(int i=0; i<m2; i++) {
        getline(cin,s);
        s2.push_back(s);
    }
    vector<string>s3=Presjek(s1,s2);
    cout<<"Zajednicki elementi su:"<<endl;
    for(int i=0; i<s3.size(); i++) {
        cout<<s3.at(i)<<endl;
    }

    return 0;
}
