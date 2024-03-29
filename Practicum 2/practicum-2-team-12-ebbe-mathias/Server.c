//
// Created by ebbew on 29-3-2024.
//

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
void server_printTeWeinigStock(int gewenstAantal, int aantalInStock, int id);
void server_printNieuwProduct(int producer, int aantal, int id);
void server_printStockInit(int stockGrootte, int productCount);

/* ==============================================
	functies: Main
   ============================================== */
_Noreturn void* server_main(){
    server_mallocDynamischeStock();
    server_initStock();
    server_printStockInit(server_StockGrootte, SERVER_STOCK_INIT_PRODUCTCOUNT);
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
void server_mallocDynamischeStock() {
    stock = malloc( server_StockGrootte * sizeof(Product));
    if (stock == NULL){
        printf("\033[31mMalloc error: kan stock niet op heap zetten.\033[0m\n");
        exit(-1);
    }
}
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
void server_verhoogStockGrootte(){
    server_StockGrootte++;
    Product* nieuwStock = realloc(stock, server_StockGrootte * sizeof(Product));
    if (nieuwStock == NULL){
        printf("\033[31mRealloc error: kan stock size niet vergroten.\033[0m\n");
        exit(-1);
    }
    stock = nieuwStock;
    nieuwStock = NULL;
}
/* ==============================================
	functies: Consume/Produceer
   ============================================== */
void server_koopOrderVanQueue(){
    Order order;
    bool queSucces = queue_haalOrderErUit(&order);
    if(queSucces){
        bool koopSucces = server_koopProduct(order.productID, order.aantal, order.consumer);
        if(!koopSucces){
            printf("\033[31mWarning: out of stock error. Deze order is terug achteraan de que toegevoegd\033[0m\n");
            queue_voegOrderToe(order);
        }
    }
}
bool server_koopProduct(int id, int aantal, int consumer) {
    Product* product = &(stock[id]);
    //poiner want anders krijgen we een kopie die niet automatisch update in de stock array
    if(product->productCount < aantal){
        server_printTeWeinigStock(aantal, product->productCount, id);
        return false; //guard clause: Door de return in de bad case kan de rest van de functie volledig gebruikt worden voor de good case
    }
    product->productCount -= aantal;
    server_printAankoop(consumer, aantal, id);
    return true;
}
void server_produceerProduct(int id, int aantal, int producer){
    if(id < server_StockGrootte) {
        server_vulProductBij(id, aantal, producer);
    } else {
        server_maakNiewProduct(aantal, producer);
    }
}
void server_vulProductBij(int id, int aantal, int producer) {
    Product* product = &(stock[id]);
    product->productCount += aantal;
    server_printProductBijgevuld(producer, aantal, product->productCount, id);
}
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
void server_printTeWeinigStock(int gewenstAantal, int aantalInStock, int id){
    printf("[Server] product %d is out of stock. (requested: %d, stock: %d)\n", id, gewenstAantal, aantalInStock);
}
void server_printStockInit(int stockGrootte, int productCount){
    printf("Stock geinitialiseerd met %d producten met count: %d\n", server_StockGrootte, SERVER_STOCK_INIT_PRODUCTCOUNT);
}