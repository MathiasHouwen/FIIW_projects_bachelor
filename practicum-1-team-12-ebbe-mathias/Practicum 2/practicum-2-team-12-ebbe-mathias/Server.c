/* ==============================================
	Practicum 2 BESC:
	Team 12
		- Ebbe Wertz
		- Mathias Houwen
   ============================================== */

#define SERVER_INIT_STOCKGROOTTE 3 //initeel aantal unieke producten in stock
#define SERVER_STOCK_INIT_PRODUCTCOUNT 30 // initele product count voor alles in stock
#define SERVER_TIJD 1

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
Product *stock;
int server_StockGrootte = SERVER_INIT_STOCKGROOTTE;    //aantal producten in stock

/* ==============================================
	functie signatures(implementatie onderaan)
   ============================================== */
//main
_Noreturn void* server_main();
//stock management
void server_mallocDynamischeStock();
void server_initStock();
void server_verhoogStockGrootte();
//produce/consume
void server_koopOrderVanQueue();
bool server_koopProduct(int id, int aantal, int consumer);
void server_produceerProduct(int id, int aantal, int producer);
void server_vulProductBij(int id, int aantal, int producer);
void server_maakNiewProduct(int aantal, int producer);
//printers
void server_printAankoop(int consumer, int aantal, int id);
void server_printProductBijgevuld(int producer, int aantalGeproduceerd, int nieuwAantalInStock, int id);
void server_printNieuwProduct(int producer, int aantal, int id);

void server_printStockInitInfo(int stockGrootte, int productCount);
void server_printFailOrderOpniewInQueueInfo();

void server_printTeWeinigStockWarning(int gewenstAantal, int aantalInStock, int id);
void server_printStockMallocError();
void server_printStockReallocError();

/* ==============================================
	functies: Main
   ============================================== */
_Noreturn void* server_main(){
    server_mallocDynamischeStock();
    server_initStock();
    server_printStockInitInfo(server_StockGrootte, SERVER_STOCK_INIT_PRODUCTCOUNT);
    while (1){
        sleep(SERVER_TIJD);
        pthread_mutex_lock(&mutex);
        server_koopOrderVanQueue();
        pthread_mutex_unlock(&mutex);
    }
}
/* ==============================================
	functies: Stock
   ============================================== */
//zet initele stock op heap
void server_mallocDynamischeStock() {
    stock = malloc( server_StockGrootte * sizeof(Product));
    if (stock == NULL){
        server_printStockMallocError();
        exit(-1);
    }
}
//vult de stock met initele producten
void server_initStock() {
    server_mallocDynamischeStock();
    //maakt van elk product een stock aan van count=SERVER_STOCK_INIT_PRODUCTCOUNT
    for(int productID = 0; productID<server_StockGrootte; productID++){
        Product product;
        product.productID = productID;
        product.productCount = SERVER_STOCK_INIT_PRODUCTCOUNT;
        stock[productID] = product;
    }
}
//maakt de stock 1 element groter
void server_verhoogStockGrootte(){
    server_StockGrootte++;
    Product* nieuwStock = realloc(stock, server_StockGrootte * sizeof(Product));
    if (nieuwStock == NULL){
        server_printStockReallocError();
        exit(-1);
    }
    stock = nieuwStock;
    nieuwStock = NULL;
}
/* ==============================================
	functies: Consume/Produceer
   ============================================== */
//leest een order van queue en koopt die uit stock
void server_koopOrderVanQueue(){
    Order order;
    bool queSucces = queue_haalOrderErUit(&order);
    if(queSucces){
        bool koopSucces = server_koopProduct(order.productID, order.aantal, order.consumer);
        if(!koopSucces){
            queue_voegOrderToe(order);
            server_printFailOrderOpniewInQueueInfo();
        }
    }
}
//koop een product uit stock
bool server_koopProduct(int id, int aantal, int consumer) {
    Product* product = &(stock[id]);
    //poiner want anders krijgen we een kopie die niet automatisch update in de stock array
    if(product->productCount < aantal){
        server_printTeWeinigStockWarning(aantal, product->productCount, id);
        return false; //guard clause: Door de return in de bad case kan de rest van de functie volledig gebruikt worden voor de good case
    }
    product->productCount -= aantal;
    server_printAankoop(consumer, aantal, id);
    return true;
}
//produceer een product naar stock
void server_produceerProduct(int id, int aantal, int producer){
    if(id < server_StockGrootte) {
        server_vulProductBij(id, aantal, producer);
    } else {
        server_maakNiewProduct(aantal, producer);
    }
}
//produceer, specifiek: vul de count van een bestaand product bij
void server_vulProductBij(int id, int aantal, int producer) {
    Product* product = &(stock[id]);
    product->productCount += aantal;
    server_printProductBijgevuld(producer, aantal, product->productCount, id);
}
//produceer, specifiek: voeg een volledig nieuw product aan stock toe
void server_maakNiewProduct(int aantal, int producer){
    server_verhoogStockGrootte();
    int id = server_StockGrootte-1;
    Product product;
    product.productCount = aantal;
    product.productID = id;
    stock[id] = product;
    server_printNieuwProduct(producer, aantal, id);
}
/* ==============================================
	functies: Printers
   ============================================== */
void server_printAankoop(int consumer, int aantal, int id) {
    printf("[Server] Consumer %d has acquired %d of product %d.\n", consumer, aantal, id);
}
void server_printProductBijgevuld(int producer, int aantalGeproduceerd, int nieuwAantalInStock, int id){
    printf("[Server] producer %d replenised product %d by %d (now %d)\n",
           producer, id, aantalGeproduceerd, nieuwAantalInStock);
}
void server_printNieuwProduct(int producer, int aantal, int id){
    printf("[Server] producer %d created a new product: %d and made %d of it.\n", producer, id, aantal);
}
void server_printTeWeinigStockWarning(int gewenstAantal, int aantalInStock, int id){
    printf("\033[31m[SERVER: WARNING]: product %d is out of stock. (requested: %d, stock: %d)\033[0m\n", id, gewenstAantal, aantalInStock);
}
void server_printStockInitInfo(int stockGrootte, int productCount){
    printf("\033[34m[SERVER: INFO]: Stock geinitialiseerd met %d producten met count: %d\033[0m\n", stockGrootte, productCount);
}
void server_printFailOrderOpniewInQueueInfo(){
    printf("\033[34m[SERVER: INFO]: Mislukte order is terug achteraan de queue gezet.\033[0m\n");
}
void server_printStockMallocError(){
    printf("\033[31m[SERVER: ERROR]Malloc error: kan stock niet op heap zetten.\033[0m\n");
}
void server_printStockReallocError(){
    printf("\033[31m[SERVER: ERROR] Realloc error: kan stock size niet vergroten.\033[0m\n");
}