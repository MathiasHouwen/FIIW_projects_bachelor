#include <stdio.h>
#define STOCK_CNT 20    //stock count (aantal unieke prods in stock)


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
Product getProductViaID(Product stock[STOCK_CNT], int id);
//consumers/producers:
void koopRanomProducten();
void produceerRanomProducten();
//printers:
void printAankoop(int consumer, int aantal, int id);

int main() {
    printf("hello world");
	return 0;
}

void initialiseerStock() {
    Product stock[STOCK_CNT];
    Product iPhone = { 0, 50 }; //EBBE PAS DIT AUB AAN DAT DAT IN EEN FORLOOP WORDT GEDIFEND
    Product lenovoLaptop = { 1, 50 }; // IDK HOW
    Product samsungPhone = { 2, 50 };
    Product windowsPhone = { 3, 50 };
    Product hpLaptop = { 4, 50 };
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

Product getProductViaID(Product stock[STOCK_CNT], int id){
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

