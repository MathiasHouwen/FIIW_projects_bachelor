#include <stdio.h>
#define STOCK_PROD 20    //aantal unieke producten in stock
#define STOCK_INIT_CNT 50 // initele product count voor alles in stock


typedef struct {
	int productID;  // == index in stock[]
	int productCount;
} Product;
/*
 * Server:get order van consumer (aantal , id)
 *  1) kijk of productcount >= aantal
 *  2.a) ja -> productcount--; geef product aan consumer
 *  2.b) nee -> message (en niks anders doen) -> efficient via guard clause
 */

/*
 * Que maken.
 * eig gewoon een stack maken maar dan FIFO ipv LIFO
 *
 *     -> array (size = ? moet als groot genoege buffer dienen)
 *     ofwel: array volledig hervullen om items de verschuiven
 *     ofwel: geen vast begin/eindpunt in array, maar een stack pointer
 *              probleem: het is niet LIFO dus wss 2 stackpointers
 *
 */

//SERVER/stock:
void koop(int id, int aantal);
void produceer(int index, int aantal);
//HELPERS:
Product getProductViaID(Product stock[STOCK_PROD], int id);
void initialiseerStock();
//consumers/producers:
void koopRanomProducten();
void produceerRanomProducten();
//printers:
void printAankoop(int consumer, int aantal, int id);

int main() {
    initialiseerStock();
    printf("Stock geinitialiseerd met %d producten met count: %d", STOCK_PROD, STOCK_INIT_CNT);
	return 0;
}

void initialiseerStock() {
    //maakt van elk product een stock aan van 50
    Product stock[STOCK_PROD];
    for(int productID = 0; productID<STOCK_PROD; productID++){
        Product product;
        product.productID = productID;
        product.productCount = STOCK_INIT_CNT;
        stock[productID] = product;
    }
}


/*
 * SERVER/stock:
 */

void koop(int id, int aantal) {
	//1) Product = getProductViaID
    //2) product.count -= aantal;
}
void produceer(int id, int aantal) {
	//
}

/*
 * PRODUCER/CONSUMER:
 */

void koopRanomProducten(){
    //1 willekeurig product kiezen
    //willekeurig aantal kopen

    //2x random int -> koop(int1, int2);
}

void produceerRanomProducten(){
    //
}

/*
 * HELPERS:
 */

Product getProductViaID(Product stock[STOCK_PROD], int id){
    Product product;
    //
    return product;
}

/*
 * PRINTERS:
 */

//consumer int komt van thread nummer
void printAankoop(int consumer, int aantal, int id) {
	printf("Consumer %d has acquired %d of product %d.", consumer, aantal, id);
}

