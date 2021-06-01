/*//TP 2018/2019: Zadaća 4, Zadatak 2
#include <iostream>


// C++ program for Shannon Fano Algorithm 
  
// include header files 

using namespace std; 
  
// declare structure node 
struct node { 
  
    // for storing symbol 
    string sym; 
  
    // for storing probability or frquency 
    float pro; 
    int arr[20]; 
    int top; 
} p[20]; 
  
typedef struct node node; 
  
// function to find shannon code 
void shannon(int l, int h, node p[]) 
{ 
    float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0; 
    int i, d, k, j; 
    if ((l + 1) == h || l == h || l > h) { 
        if (l == h || l > h) 
            return; 
        p[h].arr[++(p[h].top)] = 0; 
        p[l].arr[++(p[l].top)] = 1; 
        return; 
    } 
    else { 
        for (i = l; i <= h - 1; i++) 
            pack1 = pack1 + p[i].pro; 
        pack2 = pack2 + p[h].pro; 
        diff1 = pack1 - pack2; 
        if (diff1 < 0) 
            diff1 = diff1 * -1; 
        j = 2; 
        while (j != h - l + 1) { 
            k = h - j; 
            pack1 = pack2 = 0; 
            for (i = l; i <= k; i++) 
                pack1 = pack1 + p[i].pro; 
            for (i = h; i > k; i--) 
                pack2 = pack2 + p[i].pro; 
            diff2 = pack1 - pack2; 
            if (diff2 < 0) 
                diff2 = diff2 * -1; 
            if (diff2 >= diff1) 
                break; 
            diff1 = diff2; 
            j++; 
        } 
        k++; 
        for (i = l; i <= k; i++) 
            p[i].arr[++(p[i].top)] = 1; 
        for (i = k + 1; i <= h; i++) 
            p[i].arr[++(p[i].top)] = 0; 
  
        // Invoke shannon function 
        shannon(l, k, p); 
        shannon(k + 1, h, p); 
    } 
} 
  
// Function to sort the symbols 
// based on their probability or frequency 
void sortByProbability(int n, node p[]) 
{ 
    int i, j; 
    node temp; 
    for (j = 1; j <= n - 1; j++) { 
        for (i = 0; i < n - 1; i++) { 
            if ((p[i].pro) > (p[i + 1].pro)) { 
                temp.pro = p[i].pro; 
                temp.sym = p[i].sym; 
  
                p[i].pro = p[i + 1].pro; 
                p[i].sym = p[i + 1].sym; 
  
                p[i + 1].pro = temp.pro; 
                p[i + 1].sym = temp.sym; 
            } 
        } 
    } 
} 
  
// function to display shannon codes 
void display(int n, node p[]) 
{ 
    int i, j; 
    cout << "\n\n\n\tSymbol\tProbability\tCode"; 
    for (i = n - 1; i >= 0; i--) { 
        cout << "\n\t" << p[i].sym << "\t\t" << p[i].pro << "\t"; 
        for (j = 0; j <= p[i].top; j++) 
            cout << p[i].arr[j]; 
    } 
} 
  
// Driver code 
int main() 
{ 
    int n, i, j; 
    float total = 0; 
    string ch; 
    node temp; 
  
    // Input number of symbols 
    cout << "Enter number of symbols\t: "; 
   cin>>n;
    // Input symbols 
    for (i = 0; i < n; i++) { 
        cout << "Enter symbol " << i + 1 << " : "; 
        ch = (char)(65 + i); 
        cout << ch << endl; 
  
        // Insert the symbol to node 
        p[i].sym += ch; 
    } 
  
    // Input probability of symbols 
    float x[10];
    for (i = 0; i < n; i++) { 
        cout << "\nEnter probability of " << p[i].sym << " : "; 
       cin>>x[i];
  
        // Insert the value to node 
        p[i].pro = x[i]; 
        total = total + p[i].pro; 
  
        // checking max probability 
        if (total > 1) { 
            cout << "Invalid. Enter new values"; 
            total = total - p[i].pro; 
            i--; 
        } 
    } 
  
    p[i].pro = 1 - total; 
  
    // Sorting the symbols based on 
    // their probability or frequency 
    sortByProbability(n, p); 
  
    for (i = 0; i < n; i++) 
        p[i].top = -1; 
  
    // Find the shannon code 
    shannon(0, n - 1, p); 
  
    // Display the codes 
    display(n, p); 
    return 0; 
}

// C++ program for Huffman Coding 
/*#include <iostream> 
#include <cstdlib> 
using namespace std; 
  
// This constant can be avoided by explicitly 
// calculating height of Huffman Tree 
#define MAX_TREE_HT 100 
  
// A Huffman tree node 
struct MinHeapNode { 
  
    // One of the input characters 
    char data; 
  
    // Frequency of the character 
    unsigned freq; 
  
    // Left and right child of this node 
    struct MinHeapNode *left, *right; 
}; 
  
// A Min Heap: Collection of 
// min-heap (or Huffman tree) nodes 
struct MinHeap { 
  
    // Current size of min heap 
    unsigned size; 
  
    // capacity of min heap 
    unsigned capacity; 
  
    // Attay of minheap node pointers 
    struct MinHeapNode** array; 
}; 
  
// A utility function allocate a new 
// min heap node with given character 
// and frequency of the character 
struct MinHeapNode* newNode(char data, unsigned freq) 
{ 
    struct MinHeapNode* temp 
        = (struct MinHeapNode*)malloc
(sizeof(struct MinHeapNode)); 
  
    temp->left = temp->right = NULL; 
    temp->data = data; 
    temp->freq = freq; 
  
    return temp; 
} 
  
// A utility function to create 
// a min heap of given capacity 
struct MinHeap* createMinHeap(unsigned capacity) 
  
{ 
  
    struct MinHeap* minHeap 
        = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 
  
    // current size is 0 
    minHeap->size = 0; 
  
    minHeap->capacity = capacity; 
  
    minHeap->array 
        = (struct MinHeapNode**)malloc(minHeap-> 
capacity * sizeof(struct MinHeapNode*)); 
    return minHeap; 
} 
  
// A utility function to 
// swap two min heap nodes 
void swapMinHeapNode(struct MinHeapNode** a, 
                    struct MinHeapNode** b) 
  
{ 
  
    struct MinHeapNode* t = *a; 
    *a = *b; 
    *b = t; 
} 
  
// The standard minHeapify function. 
void minHeapify(struct MinHeap* minHeap, int idx) 
  
{ 
  
    int smallest = idx; 
    int left = 2 * idx + 1; 
    int right = 2 * idx + 2; 
  
    if (left < minHeap->size && minHeap->array[left]-> 
freq < minHeap->array[smallest]->freq) 
        smallest = left; 
  
    if (right < minHeap->size && minHeap->array[right]-> 
freq < minHeap->array[smallest]->freq) 
        smallest = right; 
  
    if (smallest != idx) { 
        swapMinHeapNode(&minHeap->array[smallest], 
                        &minHeap->array[idx]); 
        minHeapify(minHeap, smallest); 
    } 
} 
  
// A utility function to check 
// if size of heap is 1 or not 
int isSizeOne(struct MinHeap* minHeap) 
{ 
  
    return (minHeap->size == 1); 
} 
  
// A standard function to extract 
// minimum value node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
  
{ 
  
    struct MinHeapNode* temp = minHeap->array[0]; 
    minHeap->array[0] 
        = minHeap->array[minHeap->size - 1]; 
  
    --minHeap->size; 
    minHeapify(minHeap, 0); 
  
    return temp; 
} 
  
// A utility function to insert 
// a new node to Min Heap 
void insertMinHeap(struct MinHeap* minHeap, 
                struct MinHeapNode* minHeapNode) 
  
{ 
  
    ++minHeap->size; 
    int i = minHeap->size - 1; 
  
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 
  
        minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
        i = (i - 1) / 2; 
    } 
  
    minHeap->array[i] = minHeapNode; 
} 
  
// A standard function to build min heap 
void buildMinHeap(struct MinHeap* minHeap) 
  
{ 
  
    int n = minHeap->size - 1; 
    int i; 
  
    for (i = (n - 1) / 2; i >= 0; --i) 
        minHeapify(minHeap, i); 
} 
  
// A utility function to print an array of size n 
void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        cout<< arr[i]; 
  
    cout<<"\n"; 
} 
  
// Utility function to check if this node is leaf 
int isLeaf(struct MinHeapNode* root) 
  
{ 
  
    return !(root->left) && !(root->right); 
} 
  
// Creates a min heap of capacity 
// equal to size and inserts all character of 
// data[] in min heap. Initially size of 
// min heap is equal to capacity 
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 
  
{ 
  
    struct MinHeap* minHeap = createMinHeap(size); 
  
    for (int i = 0; i < size; ++i) 
        minHeap->array[i] = newNode(data[i], freq[i]); 
  
    minHeap->size = size; 
    buildMinHeap(minHeap); 
  
    return minHeap; 
} 
  
// The main function that builds Huffman tree 
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) 
  
{ 
    struct MinHeapNode *left, *right, *top; 
  
    // Step 1: Create a min heap of capacity 
    // equal to size. Initially, there are 
    // modes equal to size. 
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 
  
    // Iterate while size of heap doesn't become 1 
    while (!isSizeOne(minHeap)) { 
  
        // Step 2: Extract the two minimum 
        // freq items from min heap 
        left = extractMin(minHeap); 
        right = extractMin(minHeap); 
  
        // Step 3: Create a new internal 
        // node with frequency equal to the 
        // sum of the two nodes frequencies. 
        // Make the two extracted node as 
        // left and right children of this new node. 
        // Add this node to the min heap 
        // '$' is a special value for internal nodes, not used 
        top = newNode('$', left->freq + right->freq); 
  
        top->left = left; 
        top->right = right; 
  
        insertMinHeap(minHeap, top); 
    } 
  
    // Step 4: The remaining node is the 
    // root node and the tree is complete. 
    return extractMin(minHeap); 
} 
  
// Prints huffman codes from the root of Huffman Tree. 
// It uses arr[] to store codes 
void printCodes(struct MinHeapNode* root, int arr[], int top) 
  
{ 
  
    // Assign 0 to left edge and recur 
    if (root->left) { 
  
        arr[top] = 0; 
        printCodes(root->left, arr, top + 1); 
    } 
  
    // Assign 1 to right edge and recur 
    if (root->right) { 
  
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1); 
    } 
  
    // If this is a leaf node, then 
    // it contains one of the input 
    // characters, print the character 
    // and its code from arr[] 
    if (isLeaf(root)) { 
  
        cout<< root->data <<": "; 
        printArr(arr, top); 
    } 
} 
  
// The main function that builds a 
// Huffman Tree and print codes by traversing 
// the built Huffman Tree 
void HuffmanCodes(char data[], int freq[], int size) 
  
{ 
    // Construct Huffman Tree 
    struct MinHeapNode* root 
        = buildHuffmanTree(data, freq, size); 
  
    // Print Huffman codes using 
    // the Huffman tree built above 
    int arr[MAX_TREE_HT], top = 0; 
  
    printCodes(root, arr, top); 
} 
  
// Driver program to test above functions 
int main() 
{ 
  
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f','g','h','i','j','k','l','m','n','o','p' }; 
    int freq[] = {  90,75,75,75,75,62,62,62,62,60,60,50,50,50,50,40}; 
  
    int size = sizeof(arr) / sizeof(arr[0]); 
  
    HuffmanCodes(arr, freq, size); 
  
    return 0; 
} */
/*// Implementacija postupaka za analizu Markovljevih izvora informacija.
// (C) 2019 by Željko Jurić, ETF Sarajevo

// Eventualne bagove možete prijavljivati na email zjuric@etf.unsa.ba

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

// Neki korisni aliasi...

typedef std::vector<int> IntVector;
typedef std::vector<double> RealVector;
typedef std::vector<std::pair<int, double>> PairVector;
typedef std::vector<std::vector<int>> IntMatrix;
typedef std::vector<std::vector<double>> RealMatrix;
typedef std::vector<std::vector<std::pair<int, double>>> PairMatrix;

// Klasa "GeneralMarkovSource" je klasa koja modelira proizvoljan Markovljev
// izvor informacija. Jedino ograničenje je da izvor mora biti unifilaran i
// nerastavljiv. Interfejs klase sastoji se od sljedećih elemenata:
//
// GeneralMarkovSource(const PairMatrix &T);
// int GetNoOfStates() const;
// int GetNoOfMessages() const;
// const IntMatrix &GetTransitions() const;
// const RealMatrix &GetTransitionProbabilities() const;
// const RealVector &GetStateProbabilities() const;
// const RealVector &GetStateEntropies() const;
// double GetEntropy() const;
// int GetOrder() const;
//
// Značenja pojedinih funkcija biće opisana prilikom njihove implementacije.

class GeneralMarkovSource {
  mutable RealVector H_states;            // Entropije stanja
  mutable double H_src;                   // Entropija izvora
protected:
  IntMatrix transitions;                  // Matrica strukture prelaza
  RealMatrix p_trans;                     // Matrica vjerovatnoća prelaza
  mutable RealVector p_states;            // Vektor vjerovatnoća stanja
  mutable int order;                      // Red izvora
  GeneralMarkovSource() { H_src = - 1; }
public:
  GeneralMarkovSource(const PairMatrix &T);
  virtual ~GeneralMarkovSource() {}
  int GetNoOfStates() const;
  int GetNoOfMessages() const;
  const IntMatrix &GetTransitions() const;
  const RealMatrix &GetTransitionProbabilities() const;
  const RealVector &GetStateProbabilities() const;
  const RealVector &GetStateEntropies() const;
  double GetEntropy() const;
  int GetOrder() const;
};

// Konstruktor klase "GeneralMarkovSource" kreira Markovljev izvor informacija
// koji mora biti unifilaran i nerastavljiv. Parametar "T" je matrica prelaza
// koja opisuje ponašanje izvora. Ova matrica je matrica uređenih parova
// formata "n x m" gdje je "n" broj stanja automata, a "m" broj različitih
// poruka koje izvor emitira. Stanja su numerirana od "1" do "n" a poruke od
// "1" do "m". Element ove matrice u "i"-tom redu i "j"-toj koloni je uređeni
// par čija je prva komponenta cijeli broj koji predstavlja broj stanja (od
// "1" do "n") u koje izvor prelazi ukoliko se nalazi u stanju "i" a emitira
// "j"-tu poruku, dok je druga komponenta realni broj koji predstavlja
// vjerovatnoću s kojom se taj prelaz odvija (s obzirom na činjenicu da C++
// indeksira redove i kolone od nule, a ne od jedinice, to je zapravo element
// matrice s indeksima "i-1" i "j-1"). Ukoliko u stanju "i" nije moguće
// emitiranje "j"-te poruke, odgovrajući element patrice treba postaviti na
// "{0,0}". Ukoliko parametar "T" ne sadrži ispravnu formu matrice, ili
// ukoliko je neki od elemenata matrice neispravan baca se izuzetak. Element
// matrice je neispravan ukoliko mu prva komponenta (novo stanje) nije u
// opsegu od "0" do "n" ("0" predstavlja nemoguć prelaz), ili ukoliko mu druga
// komponenta (vjerovatnoća prelaza) nije realan broj u opsegu od "0" do "1"
// uključivo. Također, suma svih vjerovatnoća u ma kojem redu matrice mora
// biti tačno jednaka jedinici, u suprotnom se baca izuzetak.

GeneralMarkovSource::GeneralMarkovSource(const PairMatrix &T) {
  if(T.size() == 0)
    throw std::domain_error("Invalid format of transition matrix");
  H_src = -1; order = -1;
  int n = T.size(), m = T[0].size();
  transitions.resize(n, IntVector(m));
  p_trans.resize(n, RealVector(m));
  for(int i = 0; i < n; i++) {
    if(T[i].size() != m)
      throw std::domain_error("Invalid format of transition matrix");
    double p_tot = 0;
    for(int j = 0; j < m; j++) {
      int t = T[i][j].first;
      if(t < 0 || t > n)
        throw std::domain_error("Invalid next state of transition");
      transitions[i][j] = t;
      double p = T[i][j].second;
      if(p < 0 || p > 1)
        throw std::domain_error("Invalid transition probability");
      p_trans[i][j] = p;
      p_tot += p;
    }
    if(std::fabs(p_tot - 1) > 1e-5)
      throw std::domain_error("Inconsistent transition probabilities");
  }
}

// Funkcija "GetNoOfStates" vraća broj stanja koje posjeduje izvor.

int GeneralMarkovSource::GetNoOfStates() const {
  return p_trans.size();
}

// Funkcija "GetNoOfMessages" vraća broj stanja koje posjeduje izvor.

int GeneralMarkovSource::GetNoOfMessages() const {
  return p_trans[0].size();
}

// Funkcija "GetTransitions" vraća matricu strukture prelaza izvora, tj.
// matricu formata "n x m" gdje je "n" broj stanja automata, a "m" broj
// različitih poruka koje izvor emitira, u kojoj element u "i"-tom redu i
// "j"-toj koloni predstavlja broj stanja (od "1" do "n") u koji izvor prelazi
// ukoliko se nalazi u stanju "i" a emitira "j"-tu poruku (s obzirom na
// činjenicu da C++ indeksira redove i kolone od nule, a ne od jedinice, to je
// zapravo element matrice s indeksima "i-1" i "j-1"). Ukoliko u stanju "i"
// nije moguće emitiranje "j"-te poruke, odgovarajući element matrice imaće
// vrijednost "0".

const IntMatrix &GeneralMarkovSource::GetTransitions() const {
  return transitions;
}

// Funkcija "GetTransitionProbabilities" vraća matricu vjerovatnoća prelaza
// izvora, tj. matricu formata "n x m" gdje je "n" broj stanja automata, a "m"
// broj različitih poruka koje izvor emitira, u kojoj element u "i"-tom redu i
// "j"-toj koloni predstavlja vjerovatnoću da izvor u stanju "i" emitira
// "j"-tu poruku (s obzirom na činjenicu da C++ indeksira redove i kolone od
// nule, a ne od jedinice, to je zapravo element matrice s indeksima "i-1" i
// "j-1"). Ukoliko je u stanju "i" nemoguće emitiranje "j"-te poruke,
// odgovarajuća vjerovatnoća biće jendaka nuli.

const RealMatrix &GeneralMarkovSource::GetTransitionProbabilities() const {
  return p_trans;
}

// Funkcija "GetStateProbabilities" računa i vraća kao rezultat vektor čiji su
// elementi redom vjerovatnoće svih stanja izvora od "1" do "n" (s obzirom na
// činjenicu da C++ indeksira elemente od nule, a ne od jedinice, vjerovatnoća
// stanja "i" nalazi se u elementu vektora s indeksom "i-1"). Funkcija radi na
// principu da se na osnovu opisa izvoda formira odgovarajući skup linearnih
// jednačina za određivanje vjerovatnoće stanja, koje se nakon toga rješavaju
// poznatim Gaussovim algoritmom eliminacije s djelomičnom pivotizacijom i
// supstitucijom unazad. Izračunate vjerovatnoće se keširaju u privatnom
// atributu klase, tako da funkcija odmah vraća izračunate vrijednosti iz keša
// ukoliko se ustanovi da su one raspoložive. Ukoliko izvor nije nerastavljiv,
// tako da računanje vjerovatnoća stanja nije moguće izvršiti jednoznačno bez
// dopunskih informacija, baca se izuzetak.

const RealVector &GeneralMarkovSource::GetStateProbabilities() const {
  if(p_states.size() != 0) return p_states;
  int n = GetNoOfStates(), m = GetNoOfMessages();
  RealMatrix A(n, RealVector(n));
  p_states.resize(n);
  for(int i = 0; i < n; i++) A[i][i] = 1;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++) {
      int t = transitions[i][j];
      if(t != 0) A[t - 1][i] -= p_trans[i][j];
    }
  for(int j = 0; j < n; j++) A[n - 1][j] = 1;
  p_states[n - 1] = 1;
  for(int k = 0; k < n; k++) {
    int p = k;
    for(int i = k + 1; i < n; i++)
      if(std::fabs(A[i][k]) > std::fabs(A[p][k])) p = i;
    if(std::fabs(A[p][k]) < 1e-10)
      throw std::domain_error("The source is not unseparable");
    if(p != k) {
      A[k].swap(A[p]); std::swap(p_states[k], p_states[p]);
    }
    for(int i = k + 1; i < n; i++) {
      double mu = A[i][k] / A[k][k];
      A[i][k] = mu;
      for(int j = k + 1; j < n; j++) A[i][j] -= mu * A[k][j];
      p_states[i] -= mu * p_states[k];
    }
  }
  for(int i = n - 1; i >= 0; i--) {
    double s = p_states[i];
    for(int j = i + 1; j < n; j++) s -= A[i][j] * p_states[j];
    p_states[i] = s / A[i][i];
  }
  return p_states;
}

// Funkcija "GetStateEntropies" računa i vraća kao rezultat vektor čiji su
// elementi redom entropije svih stanja izvora od "1" do "n" (s obzirom na
// činjenicu da C++ indeksira elemente od nule, a ne od jedinice, vjerovatnoća
// stanja "i" nalazi se u elementu vektora s indeksom "i-1"). Za računanje
// entropije stanja "i" koriste se vjerovatnoće emitiranja poruka u tom
// stanju, a one su raspoložive u "i"-tom redu matrice vjerovatnoća prelaza
// izvora. Izračunate entropije se keširaju u privatnom atributu klase, tako
// da funkcija odmah vraća izračunate vrijednosti iz keša ukoliko se ustanovi
// da su one raspoložive.

const RealVector &GeneralMarkovSource::GetStateEntropies() const {
  if(H_states.size() != 0) return H_states;
  for(const RealVector &row : p_trans) {
    double sum = 0;
    for(double e : row) sum -= (e == 0) ? 0 : e * log(e);
    H_states.push_back(sum / log(2));
  }
  return H_states;
}

// Funkcija "GetEntropy" računa i vraća kao reuzutat entropiju izvora. Ova
// funkcija prvo obezbjeđuje da su sigurno izračunate vjerovatnoće i entropije
// svih stanja, a nakon toga računa entropiju izvora kao skalarni proizvod
// vektora vjerovatnoća i vektora entropija stanja. Izračunate entropije se
// kešira u privatnom atributu klase, tako da funkcija odmah vraća izračunatu
// vrijednost iz keša ukoliko se ustanovi da je ona raspoloživa. Ukoliko izvor
// nije nerastavljiv, tako da računanje vjerovatnoća stanja nije moguće
// izvršiti jednoznačno bez dopunskih informacija, baca se izuzetak.

double GeneralMarkovSource::GetEntropy() const {
  if(H_src != -1) return H_src;
  GetStateProbabilities();
  GetStateEntropies();
  H_src = 0;
  for(int i = 0; i < p_states.size(); i++) H_src += p_states[i] * H_states[i];
  return H_src;
}

// Funkcija "GetOrder" nalazi i vraća kao rezultat red izvora. Algoritam se
// zasniva na brute-force simulaciji ponašanja izvora za sve sekvence poruka
// dužine "k" iz svih mogućih početnih stanja za sve vrijednosti "k" od 0
// nadalje, dok se ne pronađe takvo "k" da sve sekvence vode u isto stanje
// bez obzira na stanje iz kojeg smo krenuli. Takvo "k" je red izvora. Kako
// red izvora može biti najviše jednak "n(n-1)/2", gdje je "n" broj stanja,
// testiranje se prekida ukoliko se ova vrijednost premaši. Tada izvor uopće
// nije konačnog reda i kao rezultat se vraća -1. Algoritam je kompleksan za
// pratiti, zbog četverostruko ugniježdenih petlji. Treba voditi računa da u
// najgorem slučaju, kad je red izvora upravo "n(n-1)/2", treba testirati i
// svih "m^(n(n-1)/2)" sekvenci dužine "n(n-1)/2", gdje je "m" broj različitih
// poruka koje emitira izvor, što može trajati neprihvatljivo dugo za iole
// veće vrijednosti "n". Stoga se ne može očekivati da ova funkcija uvijek
// nađe red izvora u razumnom vremenu. Nađeni red se kešira u privatnom
// atributu klase, tako da funkcija odmah vraća nađenu vrijednosti iz keša
// ukoliko se ustanovi da je ona raspoloživa.

int GeneralMarkovSource::GetOrder() const {
  if(order != -1) return order;
  int n = GetNoOfStates(), m = GetNoOfMessages(), mk = 1;
  for(int k = 0; k <= n * (n - 1) / 2; k++) {
    bool f = true;
    for(int j = 0; f && (j < mk); j++) {
      int old = -1;
      for(int i = 0; f && (i < n); i++) {
        int state = i, seq = j, t = 1;
        for(int j = 1; (t != 0) && (j <= k); j++) {
          t = transitions[state][seq % m];
          if(t == 0) state = old;
          else state = t - 1;
          seq /= m;
        }
        if(old != -1 && state != old) f = false;
        old = state;
      }
    }
    if(f) return k;
    mk *= m;
  }
  return -1;
}

// Klasa "FiniteOrderSource" je klasa koja modelira proizvoljan izvor
// informacija konačnog reda. Kako su ovakvi izvori specijalan slučaj općih
// Markovljevih izvora (razlikuje se samo način zadavanja), ova klasa je
// naslijeđena iz klase "GeneralMarkovSource". Jedino ograničenje je da izvor
// mora biti unifilaran i nerastavljiv. Preciznije, izvor konačnog reda "k"
// emitira "m" različitih poruka ovdje se modelira kao Markovljev izvor sa
// "m^k" stanja, pri čemu stanja odgovaraju sekvencama od posljednjih "m"
// emitiranih poruka.
//
// Interfejs klase sastoji se od sljedećih elemenata, od kojih su većina
// naslijeđeni iz bazne klase "GeneralMarkovSource" (praktički, razlikuju se
// samo konstruktori):
//
// FiniteOrderSource(const RealMatrix &p_trans);
// FiniteOrderSource(int m, const RealVector &p_seq);
// int GetNoOfStates() const;
// int GetNoOfMessages() const;
// const IntMatrix &GetTransitions() const;
// const RealMatrix &GetTransitionProbabilities() const;
// const RealVector &GetStateProbabilities() const;
// const RealVector &GetStateEntropies() const;
// double GetEntropy() const;
// int GetOrder() const;

class FiniteOrderSource : public GeneralMarkovSource {
public:
  FiniteOrderSource(const RealMatrix &p_trans);
  FiniteOrderSource(int m, const RealVector &p_seq);
};

// Klasa "FiniteOrderSource" posjeduje dva konstruktora, koji se razlikuju po
// tome šta su ulazni podaci koji opisuju izvor. U oba slučaja, kako se izvor
// modelira kao Markovljev izvor čija su stanja određena sa "k" posljednjih
// emitiranih poruka, gdje je "k" red izvora, sljedeće stanje nakon emitiranja
// poruke određuje se automatski, tako da nema potrebe da se ručno zadaje
// struktura prelaza. Prvi konstruktor prima kao ulaz matricu vjerovatnoća
// prelaza "p_trans". Ova matrica ima "m^k" redova i "m" kolona, pri čemu je
// "k" red izvora, a "m" broj različitih poruka koje emitira izvor. Redovi
// matrice odgovaraju redom sekvencama poruka dužine "k" sortiranim u
// leksikografski poredak, tj. sekvencama "x1x1x1...x1x1", "x1x1x1...x1x2",
// ..., "x1x1x1...x1xm", "x1x1x1...x2x1", ..., "x1x1x1...x2xm", ...,
// "x1x1x2...x1x1", ..., "xmx1x1...x1x1", ..., "xmxmxm...xmxm". Elementi reda
// matrice "p_trans" koji odgovara nekoj sekvenci poruka predstavljaju redom
// vjerovatnoće da će se nakon te sekvence emitirati prva, druga, ..., "m"-ta
// poruka. Svi elementi ove matrice moraju biti realni brojevi u opsegu od "0"
// do "1" uključivo i suma elemenata u svakom redu ove matrice mora biti tačno
// jednaka jedinici. U suprotnom se baca izuzetak. Izuzetak se također baca i
// u slučaju da parametar "p_trans" nema ispravnu strukturu matrice, ili
// ukoliko predstavlja matricu neadekvatnih dimenzija. Red izvora određuje se
// automatski, na osnovu formata matrice "p_trans".

FiniteOrderSource::FiniteOrderSource(const RealMatrix &p_trans) {
  if(p_trans.size() == 0)
    throw std::domain_error("Invalid format of transition matrix");
  GeneralMarkovSource::p_trans = p_trans;
  int n = GetNoOfStates(), m = GetNoOfMessages();
  order = 0;
  for(int i = n; i > 1; i /= m) {
    if(i % m != 0)
      throw std::domain_error("Invalid format of transition matrix");
    order++;
  }
  transitions.resize(n, IntVector(m));
  for(int i = 0; i < n; i++) {
    if(p_trans[i].size() != m)
      throw std::domain_error("Invalid format of transition matrix");
    double p_tot = 0;
    for(int j = 0; j < m; j++) {
      transitions[i][j] = (n > 1) ? (m * i) % n + j + 1 : 0;
      double p = p_trans[i][j];
      if(p < 0 || p > 1)
        throw std::domain_error("Invalid transition probability");
      p_tot += p;
    }
    if(std::fabs(p_tot - 1) > 1e-5)
      throw std::domain_error("Inconsistent transition probabilities");
  }
}

// U drugom konstruktoru klase "FiniteOrderSource", izvor "k" tog reda koji
// emitira "m" različitih poruka zadaje se putem vektora "p_seq" čiji su
// elementi vjerovatnoće emitiranja svih mogućih sekvenci poruka dužine "k+1",
// s obzirom da ove vjerovatnoće u potpunosti opisuju izvor. Pored ovog
// vektora, konstruktoru je potrebno zadati i broj poruka "m", s obzirom da se
// ta informacija ne može odrediti iz samog vektora "p_seq". Elementi ovog
// vektora odgovaraju redom sekvencama poruka dužine "k+1" sortiranim u
// leksikografski poredak. Kako takvih sekvenci ima ukupno "m^(k+1)" tolika
// mora biti i dužina vektora, u suprotnom se baca izuzetak. Prilikom ovakvog
// zadavanja izvora, interesantno je da se vjerovatnoće stanja određuju veoma
// lako koristeći zakone teorije vjerovatnoće, bez potrebe za rješavanjem
// sistema linearnih jednaćina. Nakon određivanja vjerotatnoća stanja, lako se
// određuju i uvjetne vjerovatnoće koje tvore matricu vjerovatnoća prelaza.
// Svi elementi vektora "p_seq" moraju biti realni brojevi u opsegu od "0" do
// "1" i suma im mora biti jednaka jedinici, inače se baca izuzetak. Međutim,
// elementi vektora "p_seq" moraju ispunjavati i još strožije uvjete da bi sve
// bilo konzistentno. Naime, iz zakona teorije vjerovatnoće slijedi da ukoliko
// je "S" ma kakva sekvenca poruka dužine "k", tada suma vjerovatnoća svih
// sekvenci oblika "Sxi" za sve "i" od "1" do "m" mora biti jednaka sumi
// vjerovatnoća oblika "xiS" za sve "i" od "1" do "m". Ukoliko ovo nije
// ispunjeno, matrica vjerovatnoća prelaza neće biti konzistentna, što također
// dovodi do bacanja izuzetka.

FiniteOrderSource::FiniteOrderSource(int m, const RealVector &p_seq) {
  if(p_seq.size() % m != 0)
    throw std::domain_error("Invalid format of transition matrix");
  int n = p_seq.size() / m;
  order = 0;
  for(int i = n; i > 1; i /= m) {
    if(i % m != 0)
      throw std::domain_error("Invalid format of transition matrix");
    order++;
  }
  p_states.resize(n);
  double p_sum = 0;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++) {
      double p = p_seq[n * j + i];
      if(p < 0 || p > 1)
        throw std::domain_error("Invalid sequence probability");
      p_states[i] += p; p_sum += p;
    }
  if(std::fabs(p_sum - 1) > 1e-5)
    throw std::domain_error("Inconsistent sequence probabilities");
  p_trans.resize(n, RealVector(m));
  transitions.resize(n, IntVector(m));
  for(int i = 0; i < n; i++) {
    double p_cs = p_states[i], p_tot = 0;
    for(int j = 0; j < m; j++) {
      transitions[i][j] = (n > 1) ? (m * i) % n + j + 1 : 0;
      double p = p_seq[m * i + j] / p_cs;
      p_trans[i][j] = p;
      p_tot += p;
    }
    if(std::fabs(p_tot - 1) > 1e-5)
      throw std::domain_error("Inconsistent sequence probabilities");
  }
}

// "IntPow" je pomoćna globalna funkcija ra računanje "n^k", gdje su "n" i "k"
// cijeli brojevi i "k>=0". Koristi ponovljeno množenje, tako da je efikasna
// samo za ne prevelike vrijednosti "k", ali je u svakom slučaju mnogo
// efikasnija od bibliotečke funkcije "pow" iz bibioteke "cmath", koja je
// namijenjena za realne argumente.

int IntPower(int n, int k) {
  int p = 1;
  for(int i = 1; i <= k; i++) p *= n;
  return p;
}

// "GetInt" je pomoćna globalna funkcija namijenjena za unos cijelih brojeva
// sa tastature, uz kontrolu grešaka pri unosu. Uneseni broj se smješta u
// parametar "x", a sama funkcija vraća kao rezultat "true" ili "false",
// ovisno da li je unos bio uspješan ili ne.

bool GetInt(int &x) {
  std::cin >> x;
  if(std::cin && std::cin.peek() == '\n') return true;
  std::cin.clear(); std::cin.ignore(10000, '\n');
  return false;
}

// "GetReal" je pomoćna globalna funkcija namijenjena za unos realnih brojeva
// sa tastature, uz kontrolu grešaka pri unosu. Također, podržano je i da se
// brojevi mogu unositi u formi razlomaka, kao "p/q". Uneseni broj se smješta
// u parametar "x", a sama funkcija vraća kao rezultat "true" ili "false",
// ovisno da li je unos bio uspješan ili ne.

bool GetReal(double &x) {
  std::cin >> x;
  if(std::cin.peek() == '/') {
    double y;
    std::cin.get();
    std::cin >> y;
    x /= y;
  }
  if(std::cin && std::cin.peek() == '\n') return true;
  std::cin.clear(); std::cin.ignore(10000, '\n');
  return false;
}

// "DisplaySequence" je pomoćna globalna funkcija za ispis sekvenci poruka.
// Parametar "k" predstavlja dužinu poruke, "m" je broj različitih poruka
// koje se koriste za formiranje sekvenci, dok je "i" indeks (redni broj)
// sekvence u leksikografskom poretku, numeriran od nule nadalje. Tako
// sekvenca "x1x1x1...x1x1" ima indeks "0", sekvenca "x1x1x1...x1x2"
// indeks "1", sekvenca "x1x1x1...x1xm" indeks "m-1", sekvenca "x1x1x1...x2x1"
// indeks "m", itd. Rad funkcije zasniva se na činjenici da ukoliko indeks "i"
// rastavimo na cifre u bazi "m", individualne cifre predstavljaju redne
// brojeve individualnih poruka, numeriranih od "0" nadalje.


void DisplaySequence(int i, int m, int k) {
  int r = 0;
  for(int j = 1; j <= k; j++) {
    r = m * r + i % m; i /= m;
  }
  for(int j = 1; j <= k; j++) {
    std::cout << "x" << r % m + 1;
    r /= m;
  }
}

// Funkcija "AnalyzeSource" je globalni potprogram koji prima model izvora
// informacija kao parametar, a zatim računa i ispisuje na ekran vjerovatnoće
// i entropije svih njegovih stanja, te entropiju izvora.

void AnalyzeSource(const GeneralMarkovSource &src) {
  int n = src.GetNoOfStates();
  const RealVector &p_states = src.GetStateProbabilities();
  const RealVector &H_states = src.GetStateEntropies();
  std::cout << "Vjerovatnoce stanja: " << std::endl;
  for(int i = 0; i < n; i++)
    std::cout << "p(S" << i + 1 << ")=" << p_states[i] << std::endl;
  std::cout << std::endl << "Entropije stanja: " << std::endl;
  for(int i = 0; i < n; i++)
    std::cout << "H(S" << i + 1 << ")=" << H_states[i] << std::endl;
  std::cout << std::endl << "Entropija izvora: "
    << src.GetEntropy() << std::endl;
}

// "GeneralMarkovSourceDemo" je demonstracijski potprogram koji obavlja
// analizu općeg Markovljevog izvora informacija na osnovu podataka koji se
// unose putem tastature. Unosi se opis prelaza izvora iz stanje u stanje,
// kao i vjerovatnoće tih prelaza.

void GeneralMarkovSourceDemo() {
  int n, m;
  std::cout << "Broj stanja: ";
  GetInt(n);
  std::cout << "Broj poruka: ";
  GetInt(m);
  std::cout << std::endl;
  std::cout << "Ukoliko je neki od prelaza nemoguć, unesite 0 za novo "
    << "stanje i odgovarajuću vjerovatnoću" << std::endl;
  PairMatrix T(n, PairVector(m));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      std::cout << "Iz stanja S" << i + 1 << " nakon emitiranja poruke x"
        << j + 1 << " izvor prelazi u stanje S";
      GetInt(T[i][j].first);
      std::cout << "Vjerovatnoca tog prelaza iznosi p(S" << i + 1
        << "/x" << j + 1 << ")=";
      GetReal(T[i][j].second);
    }
    std::cout << std::endl;
  }
  GeneralMarkovSource src(T);
  int order = src.GetOrder();
  if(order != -1) std::cout << "Red izvora: " << order << std::endl;
  else
    std::cout << "Izvor nije konacnog reda" << std::endl;
  std::cout << std::endl;
  AnalyzeSource(src);
}

// "FiniteOrderSourceDemo" je demonstracijski potprogram koji obavlja analizu
// izvora informacija konačnog reda na osnovu podataka koji se unose putem
// tastature, pri čemu se izvor "k"-tog reda opisuje skupom uvjetnih
// vjerovatnoća da će biti emitirana određena poruka ukoliko je poznato
// prethodnih "k" poruka.

void FiniteOrderSourceDemo() {
  int k, m;
  std::cout << "Red izvora: ";
  GetInt(k);
  std::cout << "Broj poruka: ";
  GetInt(m);
  std::cout << std::endl;
  int ns = IntPower(m, k);
  RealMatrix p_trans(ns, RealVector(m));
  for(int i = 0; i < ns; i++) {
    for(int j = 0; j < m; j++) {
      std::cout << "p(x" << j + 1;
      if(k != 0) std::cout << "/";
      DisplaySequence(i, m, k);
      std::cout << ")=";
      GetReal(p_trans[i][j]);
    }
  }
  std::cout << std::endl;
  AnalyzeSource(FiniteOrderSource(p_trans));
}

// "FiniteOrderSourceType2Demo" je demonstracijski potprogram koji obavlja
// analizu izvora informacija konačnog reda na osnovu podataka koji se unose
// putem tastature, pri čemu se izvor "k"-tog reda opisuje vjerovatnoćama
// emitiranja svih mogućih sekvenci dužine "k+1".

void FiniteOrderSourceType2Demo() {
  int k, m;
  std::cout << "Red izvora: ";
  GetInt(k);
  std::cout << "Broj poruka: ";
  GetInt(m);
  std::cout << std::endl;
  int ns = IntPower(m, k), nsq = ns * m;;
  RealVector Pseq(nsq);
  for(int i = 0; i < nsq; i++) {
    std::cout << "p(";
    DisplaySequence(i, m, k + 1);
    std::cout << ")=";
    GetReal(Pseq[i]);
  }
  std::cout << std::endl;
  FiniteOrderSource src(m, Pseq);
  const RealMatrix &p_trans = src.GetTransitionProbabilities();
  std::cout << "Vjerovatnoce prelaza: " << std::endl;
  for(int i = 0; i < ns; i++) {
    for(int j = 0; j < m; j++) {
      std::cout << "p(x" << j + 1;
      if(k != 0) std::cout << "/";
      DisplaySequence(i, m, k);
      std::cout << ")=" << p_trans[i][j] << std::endl;
    }
  }
  std::cout << std::endl;
  AnalyzeSource(src);
}

// Na kraju, glavni program traži od korisnika na koji način želi unositi izvor,

int main() {
  int opt;
  std::cout << "PRORACUN STATISTICKIH POKAZATELJA MARKOVLJEVIH IZVORA\n\n"
    << "1. Izvor je zadan uvjetnim vjerovatnocama emitiranja poruka\n"
    << "2. Izvor je zadan vjerovatnocama sekvenci porkuka\n"
    << "3. Izvor je zadan grafom prelaza kao opci Markovljev izvor\n\n"
    << "Odaberite opciju: ";
  GetInt(opt);
  std::cout << std::endl;
  std::cout << "Sve vjerovatnoce koje se traze, mogu se zadavati i kao razlomci, "
    << "u formatu p/q" << std::endl << std::endl;
  try {
    if(opt == 1) FiniteOrderSourceDemo();
    else if(opt == 2) FiniteOrderSourceType2Demo();
    else if(opt == 3) GeneralMarkovSourceDemo();
  }
  catch(const std::domain_error &e) {
    std::cout << "Doslo je do sljedece greske: \"" << e.what() << "\""
      << std::endl;
  }
  return 0;
}
*/

/*// C++ program for Kruskal's algorithm to find Minimum Spanning Tree 
// of a given connected, undirected and weighted graph 
#include <bits/stdc++.h> 
using namespace std; 

// a structure to represent a weighted edge in graph 
class Edge 
{ 
	public: 
	int src, dest, weight; 
}; 

// a structure to represent a connected, undirected 
// and weighted graph 
class Graph 
{ 
	public: 
	// V-> Number of vertices, E-> Number of edges 
	int V, E; 

	// graph is represented as an array of edges. 
	// Since the graph is undirected, the edge 
	// from src to dest is also edge from dest 
	// to src. Both are counted as 1 edge here. 
	Edge* edge; 
}; 

// Creates a graph with V vertices and E edges 
Graph* createGraph(int V, int E) 
{ 
	Graph* graph = new Graph; 
	graph->V = V; 
	graph->E = E; 

	graph->edge = new Edge[E]; 

	return graph; 
} 

// A structure to represent a subset for union-find 
class subset 
{ 
	public: 
	int parent; 
	int rank; 
}; 

// A utility function to find set of an element i 
// (uses path compression technique) 
int find(subset subsets[], int i) 
{ 
	// find root and make root as parent of i 
	// (path compression) 
	if (subsets[i].parent != i) 
		subsets[i].parent = find(subsets, subsets[i].parent); 

	return subsets[i].parent; 
} 

// A function that does union of two sets of x and y 
// (uses union by rank) 
void Union(subset subsets[], int x, int y) 
{ 
	int xroot = find(subsets, x); 
	int yroot = find(subsets, y); 

	// Attach smaller rank tree under root of high 
	// rank tree (Union by Rank) 
	if (subsets[xroot].rank < subsets[yroot].rank) 
		subsets[xroot].parent = yroot; 
	else if (subsets[xroot].rank > subsets[yroot].rank) 
		subsets[yroot].parent = xroot; 

	// If ranks are same, then make one as root and 
	// increment its rank by one 
	else
	{ 
		subsets[yroot].parent = xroot; 
		subsets[xroot].rank++; 
	} 
} 

// Compare two edges according to their weights. 
// Used in qsort() for sorting an array of edges 
int myComp(const void* a, const void* b) 
{ 
	Edge* a1 = (Edge*)a; 
	Edge* b1 = (Edge*)b; 
	return a1->weight > b1->weight; 
} 

// The main function to construct MST using Kruskal's algorithm 
void KruskalMST(Graph* graph) 
{ 
	int V = graph->V; 
	Edge result[V]; // Tnis will store the resultant MST 
	int e = 0; // An index variable, used for result[] 
	int i = 0; // An index variable, used for sorted edges 

	// Step 1: Sort all the edges in non-decreasing 
	// order of their weight. If we are not allowed to 
	// change the given graph, we can create a copy of 
	// array of edges 
	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp); 

	// Allocate memory for creating V ssubsets 
	subset *subsets = new subset[( V * sizeof(subset) )]; 

	// Create V subsets with single elements 
	for (int v = 0; v < V; ++v) 
	{ 
		subsets[v].parent = v; 
		subsets[v].rank = 0; 
	} 

	// Number of edges to be taken is equal to V-1 
	while (e < V - 1 && i < graph->E) 
	{ 
		// Step 2: Pick the smallest edge. And increment 
		// the index for next iteration 
		Edge next_edge = graph->edge[i++]; 

		int x = find(subsets, next_edge.src); 
		int y = find(subsets, next_edge.dest); 

		// If including this edge does't cause cycle, 
		// include it in result and increment the index 
		// of result for next edge 
		if (x != y) 
		{ 
			result[e++] = next_edge; 
			Union(subsets, x, y); 
		} 
		// Else discard the next_edge 
	} 

	// print the contents of result[] to display the 
	// built MST 
	cout<<"Following are the edges in the constructed MST\n"; 
	for (i = 0; i < e; ++i) 
		cout<<result[i].src<<" -- "<<result[i].dest<<" == "<<result[i].weight<<endl; 
	return; 
} 

// Driver code 
int main() 
{ 
	/* Let us create following weighted graph 
			10 
		0--------1 
		| \ | 
	6| 5\ |15 
		| \ | 
		2--------3 
			4 
	int V = 4; // Number of vertices in graph 
	int E = 5; // Number of edges in graph 
	Graph* graph = createGraph(V, E); 


	// add edge 0-1 
	graph->edge[0].src = 1; 
	graph->edge[0].dest = 2; 
	graph->edge[0].weight =1290 ; 
	
		graph->edge[1].src = 1; 
	graph->edge[1].dest =4 ; 
	graph->edge[1].weight =760 ; 
	
		graph->edge[2].src =1 ; 
	graph->edge[2].dest = 6; 
	graph->edge[2].weight =680 ; 
	
		graph->edge[3].src = ; 
	graph->edge[3].dest = ; 
	graph->edge[3].weight = ; 

	// add edge 0-2 
	graph->edge[1].src = 0; 
	graph->edge[1].dest = 2; 
	graph->edge[1].weight = 6; 

	// add edge 0-3 
	graph->edge[2].src = 0; 
	graph->edge[2].dest = 3; 
	graph->edge[2].weight = 5; 

	// add edge 1-3 
	graph->edge[3].src = 1; 
	graph->edge[3].dest = 3; 
	graph->edge[3].weight = 15; 

	// add edge 2-3 
	graph->edge[4].src = 2; 
	graph->edge[4].dest = 3; 
	graph->edge[4].weight = 4; 

	KruskalMST(graph); 

	return 0; 
} 

// This code is contributed by rathbhupendra 

*/
    #include<stdio.h>
    #include<conio.h>
    #include<stdlib.h>
    int i,j,k,a,b,u,v,n,ne=1;
    int min,mincost=0,cost[9][9],parent[9];
    int find(int);
    int uni(int,int);
    int main()
    {
    	
    	printf("\n\tImplementation of Kruskal's algorithm\n");
    	printf("\nEnter the no. of vertices:");
    	scanf("%d",&n);
    	printf("\nEnter the cost adjacency matrix:\n");
    	for(i=1;i<=n;i++)
    	{
    		for(j=1;j<=n;j++)
    		{
    			scanf("%d",&cost[i][j]);
    			if(cost[i][j]==0)
    				cost[i][j]=999;
    		}
    	}
    	printf("The edges of Minimum Cost Spanning Tree are\n");
    	while(ne < n)
    	{
    		for(i=1,min=999;i<=n;i++)
    		{
    			for(j=1;j <= n;j++)
    			{
    				if(cost[i][j] < min)
    				{
    					min=cost[i][j];
    					a=u=i;
    					b=v=j;
    				}
    			}
    		}
    		u=find(u);
    		v=find(v);
    		if(uni(u,v))
    		{
    			printf("%d edge (%d,%d) =%d\n",ne++,a,b,min);
    			mincost +=min;
    		}
    		cost[a][b]=cost[b][a]=999;
    	}
    	printf("\n\tMinimum cost = %d\n",mincost);
    	getch();
    }
    int find(int i)
    {
    	while(parent[i])
    	i=parent[i];
    	return i;
    }
    int uni(int i,int j)
    {
    	if(i!=j)
    	{
    		parent[j]=i;
    		return 1;
    	}
    	return 0;
    }