/* ==============================================
	Practicum 2 BESC:
	Team 12
		- Ebbe Wertz
		- Mathias Houwen
   ============================================== */
#include <stdio.h>
#include <stdlib.h>	//voor random functies
#include <time.h>   //voor random seed
#include<unistd.h>  //voor sleep
#include <pthread.h>    //voor threading

#define STOCK_PROD 20    //aantal unieke producten in stock
#define STOCK_INIT_CNT 30 // initele product count voor alles in stock
#define MAX_CONS_CNT 5 //maximaal # prod die een consumer in 1 keer kan kopen
#define MAX_PROD_CNT 5  //maximaal # prod die een producer in 1 keer kan maken



/*
 * TODO:
 * Que maken.
 * eig gewoon een stack maken maar dan FIFO ipv LIFO
 *
 *     -> array (size = ? moet als groot genoege buffer dienen)
 *     ofwel: array volledig hervullen om items de verschuiven
 *     ofwel: geen vast begin/eindpunt in array, maar een stack pointer
 *              probleem: het is niet LIFO dus wss 2 stackpointers
 *
 */



/* ==============================================
	struct defenities
   ============================================== */

typedef struct {
    int productID;  // == index in stock[]
    int productCount;
} Product;

/* ==============================================
	globale variabelen
   ============================================== */

Product stock[STOCK_PROD];

/* ==============================================
	functie signatures(implementatie onderaan)
   ============================================== */

//SERVER/stock:
void koop(int id, int aantal);
void produceer(int id, int aantal);
//HELPERS:
Product* getProductViaID(int id);
void initialiseerStock();
void initRandom();
int randomInteger(int minInclusief, int maxExclusief);
//consumers/producers:
_Noreturn void koopRanomProducten();
_Noreturn void produceerRanomProducten();
//printers:
void printAankoop(int consumer, int aantal, int id);
void printProductie(int producer, int aantalGeproduceerd, int nieuwAantalInStock, int id);
void printTeWeinigStock(int gewenstAantal, int aantalInStock, int id);

/* ==============================================
	main
   ============================================== */

int main() {
    initRandom();
    initialiseerStock();
    printf("Stock geinitialiseerd met %d producten met count: %d\n", STOCK_PROD, STOCK_INIT_CNT);
    koopRanomProducten();
}

/* ==============================================
	functies: producer/consumer
   ============================================== */

void koop(int id, int aantal) {
    Product* product = getProductViaID(id);
    //poiner want anders krijgen we een kopie die niet automatisch update in de stock array
    if(product->productCount < aantal){
        printTeWeinigStock(aantal, product->productCount, id);
        return; //guard clause: Door de return in de bad case kan de rest van de functie volledig gebruikt worden voor de good case
    }
    product->productCount -= aantal;
    int consumer = 0; // TODO
    printAankoop(consumer, aantal, id);
}
void produceer(int id, int aantal) {
    Product* product = getProductViaID(id);
    product->productCount += aantal;
    int producer = 0; //TODO
    printProductie(producer, aantal, product->productCount, id);
}

_Noreturn void koopRanomProducten(){    //_Noreturn = een suggestie door de IDE
    while(1){
        int productID = randomInteger(0, STOCK_PROD);
        int count = randomInteger(1, MAX_CONS_CNT);
        koop(productID, count);
        sleep(1);
    }
}

_Noreturn void produceerRanomProducten(){    //_Noreturn = een suggestie door de IDE
    while(1){
        int productID = randomInteger(0, STOCK_PROD);
        int count = randomInteger(1, MAX_PROD_CNT);
        koop(productID, count);
        sleep(1);
    }
}

/* ==============================================
	functies: helpers
   ============================================== */

void initialiseerStock() {
    //maakt van elk product een stock aan van count=STOCK_INIT_CNT
    for(int productID = 0; productID<STOCK_PROD; productID++){
        Product product;
        product.productID = productID;
        product.productCount = STOCK_INIT_CNT;
        stock[productID] = product;
    }
}

void initRandom(){
    long long seed = time(NULL);
    srand(seed);
}

Product* getProductViaID(int id){
    return &(stock[id]);
}

int randomInteger(int minInclusief, int maxExclusief){
    //maximum is exclusief: nummers van 0 tot (niet t.e.m.) max
    float tussen0en1 = (float)rand() / (float)RAND_MAX;	//randmax: intern gedefinieerd in stdlib
    return minInclusief + (int) (tussen0en1 * (float)(maxExclusief - minInclusief));
}

/* ==============================================
	functies: printers
   ============================================== */

//consumer int komt van thread nummer
void printAankoop(int consumer, int aantal, int id) {
	printf("Consumer %d has acquired %d of product %d.\n", consumer, aantal, id);
}
void printProductie(int producer, int aantalGeproduceerd, int nieuwAantalInStock, int id){
    printf("stock of product %d is replenised to %d(= +%d) by producer %d\n",
           id, nieuwAantalInStock, aantalGeproduceerd, producer);
}
void printTeWeinigStock(int gewenstAantal, int aantalInStock, int id){
    printf("product %d is out of stock. (requested: %d, stock: %d)\n", id, gewenstAantal, aantalInStock);
}

