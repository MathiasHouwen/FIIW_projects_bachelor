//
// Created by ebbew on 29-3-2024.
//

#define CONSUMER_MAX_PROD_AANTAL 10 //maximaal # prod die een consumer in 1 keer kan kopen
#define CONSUMER_TIJD 1

/* ==============================================
	functie signatures(implementatie onderaan)
   ============================================== */
//main
void* consumer_main(void* consumerNr);
//doe order
_Noreturn void consumer_maakRandomOrders(int consumerNr);
Order consumer_randomOrder(int consumerNr);

/* ==============================================
	functies: Main
   ============================================== */
void* consumer_main(void* consumerNr){
    int* consumerPointer = (int*) consumerNr;
    int consumer = *consumerPointer;
    consumer_maakRandomOrders(consumer);
}
/* ==============================================
	functies: doe order
   ============================================== */
_Noreturn void consumer_maakRandomOrders(int consumerNr){
    while(1){
        pthread_mutex_lock(&mutex);
        Order order = consumer_randomOrder(consumerNr);
        queue_voegOrderToe(order);
        pthread_mutex_unlock(&mutex);
        sleep(CONSUMER_TIJD);
    }
}
Order consumer_randomOrder(int consumerNr){
    int productID = randomInteger(0, server_StockGrootte);
    int count = randomInteger(1, CONSUMER_MAX_PROD_AANTAL);
    Order order = compacteConstructor(productID, count, consumerNr);
    return order;
}


