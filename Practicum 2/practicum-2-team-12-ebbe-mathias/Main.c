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

#define AANTALCONSUMERS 5 //aantal comsumers
#define AANTAL_PRODUCERS 5 //aantal producers
#define QUE_GROOTTE 50

/* ==============================================
	struct defenities
   ============================================== */
typedef struct {
    int productID;
    int aantal;
    int consumer;
} Order;

/* ==============================================
	globale variabelen
   ============================================== */
Order queue[QUE_GROOTTE];
int queSchrijfIndex = 0;
int queLeesIndex = 0;

pthread_mutex_t mutex;

/* ==============================================
	functie signatures(implementatie onderaan)
   ============================================== */


//SERVER/stock:

bool queue_voegOrderToe(Order order);
bool queue_haalOrderErUit(Order* order);
//HELPERS:

void initRandom();
int randomInteger(int minInclusief, int maxExclusief);
Order compacteConstructor(int id, int aantal, int consumer);

//consumers/producers:

//printers:


#include "Server.c"
#include "Consumer.c"
#include "Producer.c"

int verhoogIndexMetRotate(int index, int grens){
    index++;
    if(index >= grens){
        index = 0;
    }
    return index;
}

void maakThreads(pthread_t consumerThreads[AANTALCONSUMERS], pthread_t producerThreads[AANTAL_PRODUCERS]);
void joinThreads(pthread_t consumerThreads[AANTALCONSUMERS], pthread_t producerThreads[AANTAL_PRODUCERS]);

/* ==============================================
	main
   ============================================== */
int main() {



    initRandom();

    pthread_t consumerThreads[AANTALCONSUMERS];   //alle consumer threads
    pthread_t producerThreads[AANTAL_PRODUCERS];   //alle producer threads

    maakThreads(consumerThreads, producerThreads);
    pthread_t serverThread;
    pthread_create(&serverThread, NULL, server_main, NULL);

    pthread_join(serverThread, NULL);



    joinThreads(consumerThreads, producerThreads);
    free(stock);

}


/* ==============================================
	functies: Queue
   ============================================== */
bool queue_voegOrderToe(Order order){
    //returnt false als de queue helemaal vol zit
    if(abs(queLeesIndex - queSchrijfIndex) >= QUE_GROOTTE){
        printf("\033[31mWarning: Je probeert iets in de queue te steken terwijl ze vol is; Order genegeert\033[0m\n");
        return false;
    }
    queue[queSchrijfIndex] = order;
    queSchrijfIndex = verhoogIndexMetRotate(queSchrijfIndex, QUE_GROOTTE);
    return true;
}
bool queue_haalOrderErUit(Order* order){
    //returnt fasle bij consumer error (=out of stock)
    //of: als er niks in de que zit
    if(abs(queLeesIndex - queSchrijfIndex) == 0){
        printf("\033[31mWarning: Je probeert te lezen uit queue terwijl ze leeg is; Actie genegeert\033[0m\n");
        return false;
    }
    *order = queue[queLeesIndex];
    queLeesIndex = verhoogIndexMetRotate(queLeesIndex, QUE_GROOTTE);
    return true;
}

Order compacteConstructor(int id, int aantal, int consumer){
    Order order;
    order.productID = id;
    order.aantal = aantal;
    order.consumer = consumer;
    return order;
}

/* ==============================================
	functies: helpers
   ============================================== */




void initRandom(){
    long long seed = time(NULL);
    srand(seed);
}


int randomInteger(int minInclusief, int maxExclusief){
    //maximum is exclusief: nummers van 0 tot (niet t.e.m.) max
    float tussen0en1 = (float)rand() / (float)RAND_MAX;	//randmax: intern gedefinieerd in stdlib
    return minInclusief + (int) (tussen0en1 * (float)(maxExclusief - minInclusief));
}

void maakThreads(pthread_t consumerThreads[AANTALCONSUMERS], pthread_t producerThreads[AANTAL_PRODUCERS]){
    int consumerNrs[AANTALCONSUMERS];
    int producerNrs[AANTAL_PRODUCERS]; //onthoud alle nummers van 0 tot AANTALCONSUMERS
    //want i veranderd telkens dus een pointer naar i zal uiteindelijk altijd de laatste iteratie zien
    //moeten allemaal hier buiten de for zitten, anders worden ze van de stack gegooid na de for
    for(int i=0; i < AANTALCONSUMERS; i++){
        consumerNrs[i] = i;
        pthread_t* thread = &consumerThreads[i];
        int* consumerNr = &consumerNrs[i];
        pthread_create(thread, NULL, consumer_main, (void *) consumerNr);
    }
    for(int i=0; i < AANTAL_PRODUCERS; i++){
        producerNrs[i] = i;
        pthread_t* thread = &producerThreads[i];
        int* producerNr = &producerNrs[i];
        pthread_create(thread, NULL, producer_main, (void*) producerNr);
    }
}
void joinThreads(pthread_t consumerThreads[AANTALCONSUMERS], pthread_t producerThreads[AANTAL_PRODUCERS]){
    for(int i=0; i < AANTALCONSUMERS; i++){
        pthread_t thread = consumerThreads[i];
        pthread_join(thread, NULL);

    }
    for(int i=0; i < AANTAL_PRODUCERS; i++){
        pthread_t thread = producerThreads[i];
        pthread_join(thread, NULL);
    }
}
