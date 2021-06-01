// Implementacija postupka za rješavanje kvadratnih kongruencija. Program je interesantan
// s obzirom na činjenicu da se u njemu kao potprogrami javlja veliki broj algoritama koji
// se rade u okviru elementarne teorije brojeva.

// (C) 2017 by Željko Jurić, ETF Sarajevo

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>

// "Int" je ovdje definiran kao sinonim za tip "long long int", a po potrebi ga je
// moguće definirati kao klasu koja podržava rad s brojevima proizvoljne veličine.
// Jedini uvjet je da "Int" podržava sintaksu i semantiku koju podržava i tip "int".

typedef long long int Int;

// "Mod" vraća ostatak pri dijeljenju (modulus) svojih argumenata koji radi koretktno
// (s aspekta teorije brojeva) i za negativne operande. Ovu funkciju treba koristiti
// umjesto operatora "%" kad god postoji mogućnost da neki od operanada nije nenegativan.
// Drugi operand ne smije biti nula.

Int Mod(Int a, Int b) {
  if(a >= 0) return a % b;
  else if(b > 0) return b + a % b;
  else return -b + a % b;
}

// "IntDiv" vraća cjelobrojni količnik svojih argumenata, koji se uvijek zaokružuje
// naniže, što je konvencija koja se koristi u teoriji brojeva. Drugi operand ne smije
// biti nula.

Int IntDiv(Int a, Int b) {
  Int q = a / b;
  if(q >= 0) return q;
  else return q - 1;
}

// "GCD" vraća NZD svoja dva argumenta računat Euklidovim algoritmom. Radi korektno i za
// argumente koji su negativni ili 0.

Int GCD(Int a, Int b) {
  if(b == 0) return a;
  while(true) {
    Int c = Mod(a, b);
    if(c == 0) return b;
    a = b; b = c;
  }
}

// "ExtendedGCD" slično kao i "GCD" vraća NZD svoja dva argumenta računat Euklidovim
// algoritmom, ali se usput računaju i Bézoutovi koeficijenti "p" i "q", tj. koeficijenti
// u rastavi "NZD(a, b) = p * a + q * b" (prošireni Euklidov algoritam). Radi korektno
// i za argumente koji su negativni ili 0. S programerskog aspekta, interesantno je
// analizirati kako je inteligentnim "presipanjem" sadržaja promjenljivih izbjegnuto da
// se za realizaciju algoritma koriste nizovi...

Int ExtendedGCD(Int a, Int b, Int &p, Int &q) {
  p = 1; q = 0;
  if(b == 0) return a;
  p = 0; q = 1;
  Int r = 1, s = 0;
  while(true) {
    Int d = IntDiv(a, b);
    Int c = a - d * b, u = r - d * p, v = s - d * q;
    if(c == 0) return b;
    a = b; b = c; r = p; p = u; s = q; q = v;
  }
}

// "InverseMod" vraća inverzni element za element "a" po modulu "m". Funkcija baca izuzetak
// ukoliko element nije invertibilan.

Int InverseMod(Int a, Int m) {
  Int p, q;
  Int d = ExtendedGCD(a, m, p, q);
  if(d != 1) throw std::domain_error("Noninvertible");
  return Mod(p, m);
}

// "ProductMod" vraća rezultat množenja "a" i "b" po modulu "m". U suštini, implementacija
// ove funkcije mogla bi biti prosto "return Mod(a * b, m)" da nije jednog problema. Naime,
// vrlo se lako može desiti da računanje produkta "a * b" prekorači dozvoljeni opseg tipa
// "Int" (overflow), pa da se dobije pogrešan rezultat, bez obzira što bi krajnji rezultat
// (kad se uzme ostatak dijeljenja s "m") sasvim lijepo mogao stati u tip "Int". Štaviše,
// opseg "a" i "b" za koje bi rezultat bio ispravan jako je sužen, jer je dovoljno da recimo
// "a" i "b" budu veći od "sqrt(MAX)" pa da rezultat bude netačan, gdje je "MAX" najveća
// vrijednost koja može stati u tip "Int". Stoga je za računanje ove funkcije iskorišten
// algoritam poznat imenom "double-and-add", koji nije najefikasniji algoritam za ovu svrhu,
// ali je shvatljiv i jednostavan za implementaciju. Upotrebom ovog algoritma, prekoračenje
// se izbjegava sve dok "a" i "b" ne dostignu iznos oko "MAX/2". Ideja je da je proizvod
// "a * b" jednak dvostrukom proizvodu "a * b/2" ako je "b" paran, a na sve ovo još treba
// dodati "a" ako je "b" neparan (pri čemu je "/" cjelobrojno dijeljenje). Ova ideja se može
// ponovo primijeniti na računanje proizvoda "a * b/2" itd. sve dok drugi operand ne postane
// sasvim mali. Slijedi realizacija ove ideje. U slučaju da se kao tip "Int" koristi neka klasa
// kod koje ne postoji ograničenje na veličinu brojeva koji se mogu koristiti, implementaciju
// ove funkcije treba izvesti prosto kao "return Mod(a * b, m)".

Int ProductMod(Int a, Int b, Int m) {
  Int p = 0;
  a = Mod(a, m); b = Mod(b, m);
  while (b > 0) {
    if (b % 2 == 1) p = Mod(p + a, m);
    a = Mod(a * 2, m); b /= 2;
  }
  return Mod(p, m);
}

// "PowerMod" vraća vrijednost "a" dignutu na "n"-ti stepen po modulu "m" računatu pomoću
// algoritma "kvadriraj-i-množi". Eksponent "n" mora biti nenegativan, u suprotnom rezultat
// nije definiran.

Int PowerMod(Int a, Int n, Int m) {
  Int p = 1;
  while(n != 0) {
    if(n % 2 != 0) p = ProductMod(p, a, m);
    a = ProductMod(a, a, m); n /= 2;
  }
  return p;
}

// "PowerInt" vraća vrijednost "a" dignutu na "n"-ti stepen računatu pomoću algoritma
// "kvadriraj-i-množi". Ova funkcija je brža i pouzdanija od funkcije "pow", a također
// i znatno brža od stepenovanja računatog na naivni način, ponovljenim množenjem.

Int PowerInt(Int a, Int n) {
  Int p = 1;
  while(n != 0) {
    if(n % 2 != 0) p *= a;
    a *= a; n /= 2;
  }
  return p;
}

// "LinearCongruenceAux" je pomoćna funkcija koja vraća najmanje tipično rješenje
// linearne kongruencije "a * x == b (mod m)". Pri tome kongruencija mora biti rješiva,
// u suprotnom je rezultat nedefiniran.

Int LinearCongruenceAux(Int a, Int b, Int m) {
  Int p, q;
  ExtendedGCD(a, m, p, q);
  return ProductMod(p, b, m);
}

// "LinearCongruence" vraća vektor koji sadrži sva tipičnih rješenja linearne
// kongruencije kongruencije "a * x == b (mod m)", odnosno prazan vektor ako kongruencija
// nije rješiva. Funkcija je napisana čisto radi potpunosti, jer se ne koristi nigdje
// u ostatku programa.

std::vector<Int> LinearCongruence(Int a, Int b, Int m) {
  Int d = GCD(a, m);
  if(b % d != 0) return {};
  Int t = LinearCongruenceAux(a / d, b / d, m / d);
  std::vector<Int> x(d);
  for(Int i = 0; i < d; i++) x[i] = t + m * i / d;
  return x;
}

// "ChineseRemainder" vraća tipično rješenje sistema linearnih kongruencija oblika
// "x == c[i] (mod m[i])", uz pretpostavku da su svi moduli iz vektora "m" uzajamno
// prosti, tako da se može koristiti kineska teorema o ostacima. U suprotnom, ponašanje
// funkcije je nedefinirano. Također, vektori "c" i "m" moraju imati isti broj
// elemenata, inače je ponašanje funkcije nedefinirano.

Int ChineseRemainder(std::vector<Int> c, std::vector<Int> m) {
  Int p = 1;
  for(int i = 0; i < m.size(); i++) p *= m[i];
  Int s = 0;
  for(int i = 0; i < m.size(); i++) {
    Int k = p / m[i];
    s += k * LinearCongruenceAux(k, c[i], m[i]);
  }
  return Mod(s, p);
}

// "LegendreJacobiSymbol" vraća vrijednost Legendre-Jacobijevog simbola "(a | m)"
// računatu isključivo koristeći osnovne osobine Legendre-Jacobijevih simbola
// (Jacobijev algoritam). U skladu s definicijom Legendre-Jacobijevih simbola, "m"
// mora biti nenegativan paran broj, inače je rezultat nedefiniran.

int LegendreJacobiSymbol(Int a, Int m) {
  int t = 1;
  if(a < 0) {
    a = -a;
    if(m % 4 == 1) t = -t;
  }
  while(a != 0) {
    while(a % 2 == 0) {
      a /= 2;
      if(m % 8 == 3 || m % 8 == 5) t = -t;
    }
    std::swap(a, m);
    if(a % 4 == 3 && m % 4 == 3) t = -t;
    a = a % m;
  }
  if(m != 1) t = 0;
  return t;
}

// "TonelliAux" je pomoćna funkcija koja vraća jedno (od ukupno dva) tipična rješenja
// kvadratne kongruencije "x^2 == a (mod p)" računatu Tonellijevim algoritmom, pod
// uvjetom da je "p" prost broj različit od 2, da je kongruencija uopće rješiva,
// i da su "a" i "p" uzajamno prosti (tj. da "a" nije djeljiv s "p"). U suprotnom,
// rezultat funkcije je nedefiniran.

Int TonelliAux(Int a, Int p) {
  Int g = 2;
  while(LegendreJacobiSymbol(g, p) != -1) g = std::rand() % p;
  Int t = (p - 1) / 2, v = 1, w = a, h = InverseMod(g, p);
  while(t % 2 == 0) {
    t /= 2; h = ProductMod(h, h, p);
    if(PowerMod(w, t, p) != 1) {
      v = ProductMod(v, g, p); w = ProductMod(w, h, p);
    }
    g = ProductMod(g, g, p);
  }
  return ProductMod(v, PowerMod(w, (t + 1) / 2, p), p);
}

// "QuadraticCongruencePrimeAux" je pomoćna funkcija koja vraća jedno (od ukupno dva)
// tipična rješenja kvadratne kongruencije "x^2 == a (mod p)" pod uvjetom da je "p"
// prost broj različit od 2, da je kongruencija uopće rješiva, i da su "a" i "p" uzajamno
// prosti. U suprotnom, rezultat funkcije je nedefiniran. Ovisno od toga kakav je "p"
// koristi se Lagrangeova formula, Legendreova formula, ili Tonellijev algoritam, ukoliko
// nema drugog izbora. U načelu, ova funkcija nije neophodna, jer Tonellijev algoritam
// radii u slučajevima kada se može koristiti Lagrangeova ili Legendreova formula, samo
// je ovako brže i efikasnije.

Int QuadraticCongruencePrimeAux(Int a, Int p) {
  if(p % 4 == 3) return PowerMod(a, (p + 1) / 4, p);
  else if(p % 8 == 5) {
    Int x = PowerMod(a, (p + 3) / 8, p);
    if(ProductMod(x, x, p) == Mod(a, p)) return x;
    return ProductMod(PowerMod(a, (p + 3) / 8, p), PowerMod(2, (p - 1) / 4, p), p);
  }
  else return TonelliAux(a, p);
}

// "QuadraticCongruencePrime" vraća vektor tipičnih rješenja kvadratne kongruencije
// "x^2 == a (mod p)" kod koje je "p" prost broj, pri čemu su "a" i "p" uzajamno prosti.
// Vraćeni vektor može sadržavati dva elementa (rješenja), jedan element (samo ako je "p"
// jednak 2), ili biti prazan, ukoliko kongruencija nije rješiva. Ukoliko "p" nije prost
// broj, ili "a" i "p" nisu uzajamno prosti, rezultat funkcije je nedefiniran. Funkcija
// će raditi korektno i ako se poziv funkcije "QuadraticCongruencePrimeAux" zamijeni
// pozivom funkcije "TonelliAux".

std::vector<Int> QuadraticCongruencePrime(Int a, Int p) {
  if(LegendreJacobiSymbol(a, p) == -1) return {};
  if(p == 2) return {1};
  Int x = QuadraticCongruencePrimeAux(a, p);
  return {x, p - x};
}

// "QuadraticCongruencePrimePowerAux" je pomoćna funkcija koja vraća jedno (od ukupno
// dva) tipična rješenja kvadratne kongruencije "x^2 == a (mod p^k)" pod uvjetom da je "p"
// prost broj različit od 2, da je kongruencija uopće rješiva, da su "a" i "p" uzajamno
// prosti, i da je "k" pozitivan broj. U suprotnom, rezultat funkcije je nedefiniran. Za
// računanje koristi se Henselova lema. Umjesto formule "x = Mod(x - h * (x * x - a), m)",
// Henselova lema je implementirana zamjenom množenja s pozivom funkcije "ProductMod",
// da se izbjegne opasnost od prekoračenja pri računanju izraza poput "x * x", itd. Naime,
// na taj način se svi međurezultati odmah reduciraju po modulu "m".

Int QuadraticCongruencePrimePowerAux(Int a, Int p, Int k) {
  Int x = QuadraticCongruencePrimeAux(a, p);
  Int h = InverseMod(2 * x, p), m = p;
  for(Int i = 2; i <= k; i++) {
    m *= p;
    x = Mod(x - ProductMod(h, ProductMod(x, x, m) - a, m), m);
  }
  return x;
}

// "QuadraticCongruencePower2" vraća vektor tipičnih rješenja kvadratne kongruencije
// "x == a (mod 2^k)", uz pretpostavku da je "a" uzajamno prost s "2^k" (što zapravo
// znači da je "a" neparan). Ovisno od "a" i "k", vraćeni vektor može sadržavati 0
// (za slučaj kad kongruencija nije rješiva), 1, 2 ili 4 rješenja. "k" mora biti
// pozitivan inače je rezultat funkcije nedefiniran. Isto se dešava u slučaju da "a"
// nije neparan broj.

std::vector<Int> QuadraticCongruencePower2(Int a, Int k) {
  if(k == 1) return {1};
  else if(k == 2)
    if(Mod(a, 4) != 1) return {};
    else return {1, 3};
  if(Mod(a, 8) != 1) return {};
  std::vector<Int> x{1, 3, 5, 7};
  if(k == 3) return x;
  Int p = 16;
  for(Int i = 4; i <= k; i++) {
    Int t = x[0];
    if(ProductMod(t, t, p) != Mod(a, p)) t = x[1];
    x = {t, p - t, p / 2 + t, p / 2 - t}; p *= 2;
    std::sort(x.begin(), x.end());
  }
  return x;
}

// "QuadraticCongruencePrimePower" vraća vektor tipičnih rješenja kvadratne
// kongruencije "x == a (mod p^k)", uz pretpostavku da je "p" prost broj (koji
// može biti i 2), i da je "a" uzajamno prost s "p^k" (što zapravo znači da "a"
// nije djeljiv s "p"). Ovisno od "a", "p" i "k", vraćeni vektor može sadržavati
// 0 (za slučaj kad kongruencija nije rješiva), 1, 2 ili 4 rješenja. "k" mora
// biti pozitivan, inače je rezultat funkcije nedefiniran. Isto se dešava u
// slučaju da je "a" djeljiv s "p".

std::vector<Int> QuadraticCongruencePrimePower(Int a, Int p, Int k) {
  if(p == 2) return QuadraticCongruencePower2(a, k);
  if(LegendreJacobiSymbol(a, p) == -1) return {};
  Int x = QuadraticCongruencePrimePowerAux(a, p, k);
  return {x, PowerInt(p, k) - x};
}

// "FactorInteger" nalazi kanonsku rastavu broja "n" na proste faktore oblika
// "n = p1^e1 * p2^e2 * ...  * pk^ek" i vraća kao rezultat vektor uređenih parova
// "(p1, e1)", "(p2, e2)", itd. Za broj 1 (koji nije ni prost ni složen) se smatra
// da mu je kanonska rastava na proste faktore prazna, tako da se kad je "n" jednak
// 1 vraća kao rezultat prazna lista. "n" mora biti pozitivan, inače je rezultat
// funkcije nedefiniran. Funkcija radi na principu traženja prostih faktora "grubom
// silom", s obzirom da bilo koji inteligentniji metod traženja prostih faktora
// zahtijeva daleko dublje poznavanje teorije brojeva.

std::vector<std::pair<Int, Int>> FactorInteger(Int n) {
  std::vector<std::pair<Int, Int>> f;
  for(Int i = 2; i <= n / i; i++)
    if(n % i == 0) {
      Int e = 0;
      while(n % i == 0) {
        n /= i; e++;
      }
      f.push_back({i, e});
    }
  if(n != 1) f.push_back({n, 1});
  return f;
}

// "QuadraticCongruenceComposite" vraća vektor tipičnih rješenja kvadratne
// kongruencije "x == a (mod m)", uz jedinu pretpostavku da su "a" i "m"
// uzajamno prosti (tj. "m" ne mora biti prost broj) i da je "m" pozitivan.
// Ukoliko "a" i "m" nisu uzajamno prosti, ili "m" nije pozitivan, rezultat
// funkcije je nedefiniran. S programerske tačke gledišta, interesantno je
// analizirati kako se formiraju sistemi linearnih kongruencija kombinirajući
// individualna rješenja pomoćnih kongruencija na koje se polazna kongruencija
// raspada u slučaju kada je "m" složen broj (za tu svrhu služe igrarije s
// vektorom "w").

std::vector<Int> QuadraticCongruenceComposite(Int a, Int m) {
  std::vector<std::pair<Int, Int>> f = FactorInteger(m);
  int k = f.size();
  if(k == 0) return {0};
  std::vector<std::vector<Int>> s(k);
  for(int i = 0; i < k; i++) {
    s[i] = QuadraticCongruencePrimePower(a, f[i].first, f[i].second);
    if(s[i].size() == 0) return {};
  }
  std::vector<Int> x, n(k), c(k);
  for(int i = 0; i < k; i++) n[i] = PowerInt(f[i].first, f[i].second);
  std::vector<int> w(k);
  while(true) {
    for(int i = 0; i < k; i++) c[i] = s[i][w[i]];
    x.push_back(ChineseRemainder(c, n));
    int i = 0;
    while(i < w.size() && w[i] == s[i].size() - 1) w[i++] = 0;
    if(i == w.size()) return x;
    w[i]++;
  }
}

// "ExtractSquare" vraća vrijednost "q" iz rastave broja "n" oblika "n = p * q^2"
// gdje je "p" broj slobodan od kvadrata. Naravno, "p" se može dobiti kao "n / q^2".
// "n" mora biti pozitivan, inače je rezultat funkcije nedefiniran.

Int ExtractSquare(Int n) {
  std::vector<std::pair<Int, Int>> f = FactorInteger(n);
  Int q = 1;
  for(int i = 0; i < f.size(); i++)
    q = PowerInt(f[i].first, f[i].second / 2);
  return q;
}

// "QuadraticCongruence" je konačna funkcija za rješavanje kvadratnih kongruencija
// "x^2 == a (mod m)", bez ikakvih ograničenja na "m", osim da "m" ne smije biti
// jednak nuli (0 kao modul je besmislen). Funkcija vraća vektor svih tipičnih
// rješenja kongruencije (koji može biti prazan, ako kongruencija nije rješiva), pri
// čemu su rješenja sortirana u rastući poredak.

std::vector<Int> QuadraticCongruence(Int a, Int m) {
  if(m < 0) m = -m;
  std::vector<Int> x;
  Int d = GCD(a, m);
  if(d == 1) x = QuadraticCongruenceComposite(a, m);
  else {
    Int q = ExtractSquare(d), p = d / (q * q);
    if(GCD(p, m / d) != 1) return {};
    Int z = LinearCongruenceAux(p, a / d, m / d);
    std::vector<Int> y = QuadraticCongruenceComposite(z, m / d);
    for(int j = 0; j < y.size(); j++)
      for(int i = 0; i < q; i++)
        x.push_back(p * q * y[j] + (m / q) * i);
  }
  std::sort(x.begin(), x.end());
  return x;
}

// Poređenja radi, napisana je i funkcija "QuadraticCongruenceBruteForce" koja
// rješava kvadratne kongruencije "grubom silom". Neko bi mogao pomisliti da li
// je vrijedilo pisati sav ovaj gore kod radi nečega što se "grubom silom" može
// izvesti u 5 linija koda. Isplativost svega najbolje se vidi ukoliko probate
// testirati obje funkcije sa argumentima "a" i "m" koji imaju 7 i više cifara
// (za brojeve s više od 10 cifara rješenje "grubom silom" nije moguće dobiti
// ni u kakvom razumnom vremenu).

std::vector<Int> QuadraticCongruenceBruteForce(Int a, Int m) {
  std::vector<Int> x;
  a = Mod(a, m);
  for(Int i = 0; i < m; i++)
    if(ProductMod(i, i, m) == a) x.push_back(i);
  return x;
}

// I na kraju, mali testni program...

int main() {
  std::cout << "Rjesavanje kvadratnih kongruencija oblika x^2 == a (mod m)\n";
  std::cout << "----------------------------------------------------------\n\n";
  Int a, m;
  std::cout << "a = "; std::cin >> a;
  std::cout << "m = "; std::cin >> m;
  std::cout << std::endl;
  std::vector<Int> x = QuadraticCongruence(a, m);
  if(x.size() == 0) std::cout << "Nema rjesenja!";
  else std::cout << "Rjesenja su: ";
  for(int i = 0; i < x.size(); i++) std::cout << x[i] << " ";
  std::cout << std::endl << std::endl;
  std::cout << "Poredjenja radi, slijedi rjesavanje grubom silom\n";
  std::cout << "(testirajte razliku na brojevima s 7 ili vise cifara)...\n\n";
  x = QuadraticCongruenceBruteForce(a, m);
  if(x.size() == 0) std::cout << "Nema rjesenja!";
  else std::cout << "Rjesenja su: ";
  for(int i = 0; i < x.size(); i++) std::cout << x[i] << " ";
  std::cout << std::endl;
}
