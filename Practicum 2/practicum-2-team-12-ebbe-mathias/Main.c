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
#include <stdbool.h>


#define STOCK_PROD 20    //aantal unieke producten in stock
#define STOCK_INIT_CNT 30 // initele product count voor alles in stock
#define MAX_CONS_CNT 5 //maximaal # prod die een consumer in 1 keer kan kopen
#define MAX_PROD_CNT 5  //maximaal # prod die een producer in 1 keer kan maken

#define CONSUMERS 5 //aantal comsumers
#define PRODUCERS 2 //aantal producers

#define QUE_LENGHT 256

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

typedef struct {
    Product *product;
    int aantal;
    int consumer;
} Order;

typedef struct {
    Product *product;
    Product *stock[STOCK_PROD];
    Order *queue[QUE_LENGHT];
} Server;

/* ==============================================
	globale variabelen
   ============================================== */

Product stock[STOCK_PROD];

Order queue[QUE_LENGHT];
int kop = 0;
int next = 0;
int queueSize = 0;

pthread_mutex_t mutex;

/* ==============================================
	functie signatures(implementatie onderaan)
   ============================================== */

//SERVER/stock:
bool koop(int id, int aantal, int consumer);
void produceer(int id, int aantal, int producer);

bool addQueue(Order order);
void requestKoop(int id, int aantal, int consumer);

//HELPERS:
Product* getProductViaID(int id);
void initStock();
void initRandom();
int randomInteger(int minInclusief, int maxExclusief);
void maakThreads(pthread_t consumerThreads[CONSUMERS], pthread_t producerThreads[PRODUCERS]);
void joinThreads(pthread_t consumerThreads[CONSUMERS], pthread_t producerThreads[PRODUCERS]);
//consumers/producers:
void* koopRandomProducten(void* consumerNr);
void* produceerRanomProducten(void* producerNr);
//printers:
void printAankoop(int consumer, int aantal, int id);
void printProductie(int producer, int aantalGeproduceerd, int nieuwAantalInStock, int id);
void printTeWeinigStock(int gewenstAantal, int aantalInStock, int id);

/* ==============================================
	main
   ============================================== */

int main() {


    initRandom();
    initStock();
    printf("Stock geinitialiseerd met %d producten met count: %d\n", STOCK_PROD, STOCK_INIT_CNT);

    pthread_t consumerThreads[CONSUMERS];   //alle consumer threads
    pthread_t producerThreads[PRODUCERS];   //alle producer threads

    maakThreads(consumerThreads, producerThreads);
    joinThreads(consumerThreads, producerThreads);
}

/* ==============================================
	functies: producer/consumer
   ============================================== */
bool koop(int id, int aantal, int consumer) {
    Product* product = getProductViaID(id);
    //poiner want anders krijgen we een kopie die niet automatisch update in de stock array
    if(product->productCount < aantal){
        printTeWeinigStock(aantal, product->productCount, id);
        return false; //guard clause: Door de return in de bad case kan de rest van de functie volledig gebruikt worden voor de good case
    }
    pthread_mutex_lock(&mutex);
    product->productCount -= aantal;
    printAankoop(consumer, aantal, id);
    pthread_mutex_unlock(&mutex);
    return true;
}

void produceer(int id, int aantal, int producer) {
    Product* product = getProductViaID(id);

    pthread_mutex_lock(&mutex);

    product->productCount += aantal;
    printProductie(producer, aantal, product->productCount, id);

    pthread_mutex_unlock(&mutex);
}

void* koopRandomProducten(void* consumerNr){    //_Noreturn = een suggestie door de IDE
    while(1){
        int productID = randomInteger(0, STOCK_PROD);
        int count = randomInteger(1, MAX_CONS_CNT);
        int* consumer = (int*) consumerNr;
        requestKoop(productID, count, *consumer);
        sleep(1);
    }
}

void* produceerRanomProducten(void* producerNr){    //_Noreturn = een suggestie door de IDE
    while(1){
        int productID = randomInteger(0, STOCK_PROD);
        int count = randomInteger(1, MAX_PROD_CNT);
        int* producer = (int*) producerNr;
        produceer(productID, count, *producer);
        sleep(1);

    }
}

/* ==============================================
	functies: Queue
   ============================================== */
bool addQueue(Order order){
    if(queueSize == QUE_LENGHT){return false;}
    queue[next] = order;
    queueSize++;
    next = (next+1)%QUE_LENGHT;
    return true;
}

void requestKoop(int id, int aantal, int consumer){
    Product *product = getProductViaID(id);
    Order order;
    order.product = product;
    order.aantal = aantal;
    order.consumer = consumer;
    addQueue(order);
}
void verwijderVanQue(Order order){
    //
}

void handelQueAf(){ // JA KUT NAAM IDK
    for (int i=0; i<queueSize; ++i){
        Order order = queue[i];
        if(koop(order.product->productID, order.aantal, order.consumer)){
            // REMOVE FROM LIST
        }
    }
}
/* ==============================================
	functies: helpers
   ============================================== */

void initStock() {
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

void maakThreads(pthread_t consumerThreads[CONSUMERS], pthread_t producerThreads[PRODUCERS]){
    int consumerNrs[CONSUMERS];
    int producerNrs[PRODUCERS]; //onthoud alle nummers van 0 tot CONSUMERS
    //want i veranderd telkens dus een pointer naar i zal uiteindelijk altijd de laatste iteratie zien
    //moeten allemaal hier buiten de for zitten, anders worden ze van de stack gegooid na de for
    for(int i=0; i<CONSUMERS; i++){
        consumerNrs[i] = i;
        pthread_t* thread = &consumerThreads[i];
        int* consumerNr = &consumerNrs[i];
        pthread_create(thread, NULL, koopRandomProducten, (void*) consumerNr);
    }
    for(int i=0; i < PRODUCERS; i++){
        producerNrs[i] = i;
        pthread_t* thread = &producerThreads[i];
        int* producerNr = &consumerNrs[i];
        pthread_create(thread, NULL, produceerRanomProducten, (void*) producerNr);
    }
}
void joinThreads(pthread_t consumerThreads[CONSUMERS], pthread_t producerThreads[PRODUCERS]){
    for(int i=0; i < CONSUMERS; i++){
        pthread_t thread = consumerThreads[i];
        pthread_join(thread, NULL);

    }
    for(int i=0; i < PRODUCERS; i++){
        pthread_t thread = producerThreads[i];
        pthread_join(thread, NULL);
    }
}

/* ==============================================
	functies: printers
   ============================================== */

//consumer int komt van thread nummer
void printAankoop(int consumer, int aantal, int id) {
	printf("Consumer %d has acquired %d of product %d.\n", consumer, aantal, id);
}
void printProductie(int producer, int aantalGeproduceerd, int nieuwAantalInStock, int id){
    printf("producer %d replenised product %d by %d (now %d)\n",
           producer, id, aantalGeproduceerd, nieuwAantalInStock);
}
void printTeWeinigStock(int gewenstAantal, int aantalInStock, int id){
    printf("product %d is out of stock. (requested: %d, stock: %d)\n", id, gewenstAantal, aantalInStock);
}

