//TP 2018/2019: Zadaća 4, Zadatak 3
#include <iostream>
#include<tuple>
#include<utility>
#include<stdexcept>
#include<iomanip>
#include<string>
#include<vector>
#include<initializer_list>
#include<algorithm>
using namespace std;
class Datum{
    int d,m,g;
    void PostaviNormalizirano(int &d,int &m,int &g){
        if(m%2==0){
            if(d==31 && m!=2){
                d=0;
                m++;
            }
            if(m>=13){
                m=0;
                g++;
            }
            if(m==2 && g%400==0){
                if(d==29){
                    d=0;
                    m++;
                }
            }
            else if(m==2 && g%400!=0){
                if(d==30){
                    d=0;
                    m++;
                }
            }
        }
        
    }
    public:
    explicit Datum(int dan,int mjesec,int godina){
        d=dan;m=mjesec;g=godina;
    }
    void Postavi(int dan,int mjesec,int godina){
        if(dan<0 || mjesec<0 || godina<0)throw domain_error("Neispravan datum");
        if(mjesec%2==0 && mjesec!=2 && dan>=31)throw domain_error("Neispravan datum");
        if(mjesec%2!=0 && dan>31)throw domain_error("Neispravan datum");
        if(mjesec==2 && godina%400==0 && dan>=29)throw domain_error("Neispravan datum");
        if(mjesec==2 && godina%400!=0 && dan>=30)throw domain_error("Neispravan datum");
        PostaviNormalizirano(dan,mjesec,godina);
        d=dan;
        mjesec=m;
        godina=g;
    }
    tuple<int,int,int>Ocitaj()const{
        return{make_tuple(d,m,g)};
    }
    void Ispisi()const{
        cout<<d<<"/"<<m<<"/"<<g;
    }
};
class Vrijeme{
    int sat,minuta;
    public:
    explicit Vrijeme(int sati,int minute){
        sat=sati;minuta=minute;
    }
    void Postavi(int sati,int minute){
        if(sati<0 || sati>=24 || minute<0 || minute>=60)throw domain_error("Neispravno vrijeme");
        sat=sati;
        minuta=minute;
    }
    pair<int,int>Ocitaj()const{
        return{make_pair(sat,minuta)};
    }
    void Ispisi()const{
        cout<<setfill('0')<<setw(2)<<sat<<":"<<setw(2)<<minuta;
    }
    
};
class Pregled{
    string ime;
    Datum datumpregleda;
    Vrijeme vrijemepregleda;
    public:
    Pregled(const string &ime_pacijenta,const Datum &datum_pregleda,const Vrijeme &vrijeme_pregleda):datumpregleda(datum_pregleda),vrijemepregleda(vrijeme_pregleda)
    {
        ime=ime_pacijenta;
    }
    Pregled(const string &ime_pacijenta,int dan_pregleda,int mjesec_pregleda,int godina_pregleda,int sat_pregleda,int minute_pregleda):
    datumpregleda(dan_pregleda,mjesec_pregleda,godina_pregleda),vrijemepregleda(sat_pregleda,minute_pregleda){
        ime=ime_pacijenta;
    }
    void PromijeniPacijenta(const string &ime_pacijenta){
        ime=ime_pacijenta;
    }
    void PromijeniDatum(const Datum &novi_datum){
        datumpregleda=novi_datum;
    }
    void PromijeniVrijeme(const Vrijeme &novo_vrijeme){
        vrijemepregleda=novo_vrijeme;
    }
    void PomjeriDanUnaprijed(){
        tuple<int,int,int>m;
        m=datumpregleda.Ocitaj();
        int m1,m2,m3;
        m1=get<0>(m);
        m2=get<1>(m);
        m3=get<2>(m);
        m1++;
        datumpregleda.Postavi(m1,m2,m3);
    }
    string DajImePacijenta()const{return ime;}
    Datum DajDatumPregleda()const{return datumpregleda;}
    Vrijeme DajVrijemePregleda()const{return vrijemepregleda;}
    static bool DolaziPrije(const Pregled &p1,const Pregled &p2){
        Datum p11=p1.DajDatumPregleda(),p22=p2.DajDatumPregleda();
        tuple<int,int,int>m;
        m=p11.Ocitaj();
        int m1,m2,m3;
        m1=get<0>(m);
        m2=get<1>(m);
        m3=get<2>(m);
        tuple<int,int,int>n;
        n=p22.Ocitaj();
        int n1,n2,n3;
        n1=get<0>(n);
        n2=get<1>(n);
        n3=get<2>(n);
        if(m1<n1 && m2<n2)return true;
        return false;
    }
    void Ispisi()const{
        Datum daj=DajDatumPregleda();
        Vrijeme daj1=DajVrijemePregleda();
        cout<<left<<setw(30)<<DajImePacijenta();
        daj.Ispisi();
        cout<<" ";
        daj1.Ispisi();
        cout<<endl;
    }
    
};
class Pregledi{
    Pregled **niz;
    int broj;
    const int max_broj;
    public:
    explicit Pregledi(int max_broj_pregleda):max_broj(max_broj_pregleda),broj(0){
        niz=new Pregled*[max_broj_pregleda]{};
    }
    Pregledi(initializer_list<Pregled> spisak_pregleda):broj(spisak_pregleda.size()),max_broj(broj){
        niz=new Pregled*[max_broj];
        int i=0;
        for(Pregled p:spisak_pregleda){
            try{
                niz[i]=new Pregled(p);
            }
            catch(...){
                delete[]niz;
            }
            i++;
        }
    }
    ~Pregledi(){
        for(int i=0;i<broj;i++)delete niz[i];
        delete[]niz;
    }
    Pregledi(const Pregledi &pregledi):niz(nullptr),broj(pregledi.broj),max_broj(pregledi.max_broj){
        niz=new Pregled*[max_broj]{};
        for(int i=0;i<broj;i++)niz[i]=new Pregled(*pregledi.niz[i]);
    }
    Pregledi(Pregledi &&pregledi):niz(nullptr),broj(pregledi.broj),max_broj(pregledi.max_broj){
        niz=pregledi.niz;
        pregledi.niz=nullptr;
        pregledi.broj=0;
    }
    Pregledi &operator=(const Pregledi &pregledi){
        if(this==&pregledi)return *this;
        for(int i=0;i<broj;i++)delete niz[i];
        delete []niz;
        broj=pregledi.broj;
        niz=new Pregled*[max_broj]{};
        for(int i=0;i<broj;i++){
            niz[i]=new Pregled(*pregledi.niz[i]);
        }
        return *this;
    }
    Pregledi &operator=(Pregledi &&pregledi){
        if(this==&pregledi)return *this;
        for(int i=0;i<broj;i++)delete niz[i];
        delete[]niz;
        broj=pregledi.broj;
        niz=pregledi.niz;
        pregledi.niz=nullptr;
        pregledi.broj=0;
        return *this;
    }
    void RegistrirajPregled(const string &ime_pacijenta,const Datum &datum_pregleda,const Vrijeme &vrijeme_pregleda){
        if(broj==max_broj)throw range_error("Dostignut maksimalan broj pregleda");
        niz[broj]=new Pregled(ime_pacijenta,datum_pregleda,vrijeme_pregleda);
        broj++;
    }
    void RegistrirajPregled(const string &ime_pacijenta,int dan_pregleda,int mjesec_pregleda,int godina_pregleda,int sat_pregleda,int minute_pregleda){
        if(broj==max_broj)throw range_error("Dostrignut maksimalan broj pregleda");
        niz[broj]=new Pregled(ime_pacijenta,dan_pregleda,mjesec_pregleda,godina_pregleda,sat_pregleda,minute_pregleda);
        broj++;
    }
    void RegistrirajPregled(Pregled *pregled){
        if(broj==max_broj)throw range_error("Dostignut maksimalan broj pregleda");
        niz[broj]=pregled;
        broj++;
    }
    int DajBrojPregleda()const{
        return broj;
    }
    int DajBrojPregledaNaDatum(const Datum &datum)const{
        int brojac=0;
        brojac=count_if(niz,niz+broj,[datum](const Pregled *p){
            int dan,mjesec,godina;
            Datum d1=p->DajDatumPregleda();
            tuple<int,int,int>d;
            d=d1.Ocitaj();
            dan=get<0>(d);
            mjesec=get<1>(d);
            godina=get<2>(d);
            tuple<int,int,int>d2;
            d2=datum.Ocitaj();
            int dan2,mjesec2,godina2;
            dan2=get<0>(d2);
            mjesec2=get<1>(d2);
            godina2=get<2>(d2);
            if(dan==dan2 && mjesec==mjesec2 && godina==godina2)return true;
            return false;
        });
        return brojac;
    }
    Pregled &DajNajranijiPregled(){
        if(niz==niz+broj)throw domain_error("Nema registriranih pregleda");
        return **min_element(niz,niz+broj,[](Pregled *p1,Pregled *p2){
            Datum d1=p1->DajDatumPregleda();
            Datum d2=p2->DajDatumPregleda();
            tuple<int,int,int>d3,d4;
            d3=d1.Ocitaj();
            d4=d2.Ocitaj();
            int dan1,mj1,god1,dan2,mj2,god2;
            dan1=get<0>(d3);
            mj1=get<1>(d3);
            god1=get<2>(d3);
            dan2=get<0>(d4);
            mj2=get<1>(d4);
            god2=get<2>(d4);
            if(god1<=god2 && mj1<=mj2 && dan1<dan2)return true;
            return false;});
               
    }
    Pregled DajNajranijiPregled()const{
        if(niz==niz+broj)throw domain_error("Nema registriranih prelgeda");
        return **min_element(niz,niz+broj,[](const Pregled *p1,const Pregled *p2){
            Datum d1=p1->DajDatumPregleda();
            Datum d2=p2->DajDatumPregleda();
            tuple<int,int,int>d3,d4;
            d3=d1.Ocitaj();
            d4=d2.Ocitaj();
            int dan1,mj1,god1,dan2,mj2,god2;
            dan1=get<0>(d3);
            mj1=get<1>(d3);
            god1=get<2>(d3);
            dan2=get<0>(d4);
            mj2=get<1>(d4);
            god2=get<2>(d4);
            if(god1<=god2 && mj1<=mj2 && dan1<dan2)return true;
            return false;
        });
    }
    void IsprazniKolekciju(){
        for(int i=0;i<broj;i++)delete niz[i];
    }
   void ObrisiPregledePacijenta(const string &ime_pacijenta){
       for(int i=0;i<broj;i++){
           if(niz[i]->DajImePacijenta()==ime_pacijenta){
               delete niz[i];
               niz[i]=nullptr;
           }
       }
   }
   void IspisiPregledeNaDatum(const Datum &datum)const{
       for(int i=0;i<broj;i++){
           Datum dat=niz[i]->DajDatumPregleda();
           tuple<int,int,int>d1=dat.Ocitaj(),d2=datum.Ocitaj();
           int dan1,mj1,god1,dan2,mj2,god2;
           dan1=get<0>(d1);
           mj1=get<1>(d1);
           god1=get<2>(d1);
           dan2=get<0>(d2);
           mj2=get<1>(d2);
           god2=get<2>(d2);
           if(dan1==dan2 && mj1==mj2 && god1==god2){
               cout<<setw(30)<<niz[i]->DajImePacijenta();
               niz[i]->DajDatumPregleda().Ispisi();
               niz[i]->DajVrijemePregleda().Ispisi();
               cout<<endl;
           }
       }
   }
   
   
};
int main ()
{
   /* cout<<"Unesite maksimalan broj pregleda: ";
    int max; 
    cin>>max;
    char znak='"';
    Pregledi niz(max);
    initializer_list<Pregled>spisak;
    int i=0;
    while(1){
    cout<<"Unesite ime novog pacijenta ili "<<znak<<"kraj"<<znak<<" za zavrsetak unosa: ";
    string ime;
    getline(cin,ime);
    if(ime=="kraj")break;
    cout<<"Unesite dan, mjesec i godinu pregleda: ";
    int d,m,g;
    cin>>d>>m>>g;
    cout<<"Unesite sate i minute pregleda: ";
    int h,m1;
    cin>>h>>m1;
    Pregled element(ime,d,m,g,h,m1);
    spisak[i]=(element);
    i++;
    }
    niz(spisak);
    int opcija;
    while(opcija!=7){
        cout<<"Odaberite jednu od sljedecih opcija"<<endl;
        cout<<"1 - Broj pregleda na datum"<<endl;
        cout<<"2 - Najraniji pregled"<<endl;
        cout<<"3 - Obrisi pregled pacijenta"<<endl;
        cout<<"4 - Obrisi najraniji pregled"<<endl;
        cout<<"5 - Ispisi sve preglede na datum"<<endl;
        cout<<"6 - Ispisi sve preglede"<<endl;
        cout<<"7 - Kraj programa";
        if(opcija==1){
            cout<<"Unesite dan mjesec i godinu: ";
            int d1,m11,g1;
            cin>>d1>>m11>>g1;
            Datum d11(d1,m11,g1);
            cout<<niz->DajBrojPregledaNaDatum(d11);
        }
        
    }*/
	return 0;
}