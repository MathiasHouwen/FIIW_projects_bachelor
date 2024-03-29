//
// Created by ebbew on 29-3-2024.
//

#define PRODUCER_MAX_PROD_AANTAL 2  //maximaal # prod die een producer in 1 keer kan maken
#define PRODUCER_TIJD 15

/* ==============================================
	functie signatures(implementatie onderaan)
   ============================================== */
//main
void* producer_main(void* producerNr);
//doe order
_Noreturn void producer_produceerRanomProducten(int producerNr);

/* ==============================================
	functies: Main
   ============================================== */
void* producer_main(void* producerNr){
    int* producerPointer = (int*) producerNr;
    int producer = *producerPointer;
    producer_produceerRanomProducten(producer);
}
/* ==============================================
	functies: produceer
   ============================================== */
_Noreturn void producer_produceerRanomProducten(int producerNr){    //_Noreturn = een suggestie door de IDE
    while(1){
        pthread_mutex_lock(&mutex);
        int aantal = randomInteger(1, PRODUCER_MAX_PROD_AANTAL+1);
        int productID = randomInteger(0, server_StockGrootte+1);    //+1 geeft kans om nieuwe producten te maken
        server_produceerProduct(productID, aantal, producerNr);
        pthread_mutex_unlock(&mutex);
        sleep(PRODUCER_TIJD);
    }
}