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

#define AANTAL_CONSUMERS 5 //aantal comsumers
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
	functie signatures(implementatie onderaan) OVERAL BESCHIKBAAR
   ============================================== */

//Queue:
bool queue_voegOrderToe(Order order);
bool queue_haalOrderErUit(Order* order);
//HELPERS:
int randomInteger(int minInclusief, int maxExclusief);
Order compacteConstructor(int id, int aantal, int consumer);

#include "Server.c"
#include "Consumer.c"
#include "Producer.c"

/* ==============================================
	functie signatures(implementatie onderaan) ALLEEN DEZE FILE
   ============================================== */

//treads
void maakThreads(pthread_t consumerThreads[AANTAL_CONSUMERS], pthread_t producerThreads[AANTAL_PRODUCERS]);
void joinThreads(const pthread_t consumerThreads[AANTAL_CONSUMERS], const pthread_t producerThreads[AANTAL_PRODUCERS]);
//helpers
void initRandom();
int verhoogIndexMetRotate(int index, int grens);
//printers:
void queue_printQueVolWarning();
void queue_printQueLeegInfo();

/* ==============================================
	main
   ============================================== */
int main() {
    initRandom();   //zet random seed
    pthread_t serverThread; //server thread
    pthread_t consumerThreads[AANTAL_CONSUMERS];   //alle consumer threads
    pthread_t producerThreads[AANTAL_PRODUCERS];   //alle producer threads

    pthread_create(&serverThread, NULL, server_main, NULL);
    sleep(1);
    maakThreads(consumerThreads, producerThreads);  //create producer en consumer threads

    pthread_join(serverThread, NULL);
    joinThreads(consumerThreads, producerThreads);//join producer en consumer threads
    free(stock);
}


/* ==============================================
	functies: Queue
   ============================================== */
//voegt een order toe achteraan de queue
//returnt false als de queue helemaal vol zit
bool queue_voegOrderToe(Order order){
    if(abs(queLeesIndex - queSchrijfIndex) >= QUE_GROOTTE){
        queue_printQueVolWarning();
        return false;
    }
    queue[queSchrijfIndex] = order;
    queSchrijfIndex = verhoogIndexMetRotate(queSchrijfIndex, QUE_GROOTTE);
    return true;
}
//haalt een order uit vooraan de queue, via OUT-parameter
//returnt fasle als er niks in de que zit
bool queue_haalOrderErUit(Order* order){
    if(abs(queLeesIndex - queSchrijfIndex) == 0){
        queue_printQueLeegInfo();
        return false;
    }
    *order = queue[queLeesIndex];
    queLeesIndex = verhoogIndexMetRotate(queLeesIndex, QUE_GROOTTE);
    return true;
}
//om als oneliner een order te maken
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
//zet random seed
void initRandom(){
    long long seed = time(NULL);
    srand(seed);
}
//maakt random integer tussen min en max (min inclusief)
int randomInteger(int minInclusief, int maxExclusief){
    //maximum is exclusief: nummers van 0 tot (niet t.e.m.) max
    float tussen0en1 = (float)rand() / (float)(RAND_MAX-1);	//randmax: intern gedefinieerd in stdlib
    return minInclusief + (int) (tussen0en1 * (float)(maxExclusief - minInclusief));
}
//maakt de threads can cons en prod
void maakThreads(pthread_t consumerThreads[AANTAL_CONSUMERS], pthread_t producerThreads[AANTAL_PRODUCERS]){
    int consumerNrs[AANTAL_CONSUMERS];
    int producerNrs[AANTAL_PRODUCERS]; //onthoud alle nummers van 0 tot AANTAL_CONSUMERS
    //want i veranderd telkens dus een pointer naar i zal uiteindelijk altijd de laatste iteratie zien
    //moeten allemaal hier buiten de for zitten, anders worden ze van de stack gegooid na de for

    for(int i=0; i < AANTAL_PRODUCERS; i++){
        producerNrs[i] = i;
        pthread_t* thread = &producerThreads[i];
        int* producerNr = &producerNrs[i];
        pthread_create(thread, NULL, producer_main, (void*) producerNr);
    }
    for(int i=0; i < AANTAL_CONSUMERS; i++){
        consumerNrs[i] = i;
        pthread_t* thread = &consumerThreads[i];
        int* consumerNr = &consumerNrs[i];
        pthread_create(thread, NULL, consumer_main, (void *) consumerNr);
    }


}
//joint de threads van cons en prod
void joinThreads(const pthread_t consumerThreads[AANTAL_CONSUMERS], const pthread_t producerThreads[AANTAL_PRODUCERS]){
    for(int i=0; i < AANTAL_CONSUMERS; i++){
        pthread_t thread = consumerThreads[i];
        pthread_join(thread, NULL);

    }
    for(int i=0; i < AANTAL_PRODUCERS; i++){
        pthread_t thread = producerThreads[i];
        pthread_join(thread, NULL);
    }
}
//Om een index te verhogen, die terug naar 0 springt na een maximale waarde ("rotate")
int verhoogIndexMetRotate(int index, int grens){
    index++;
    if(index >= grens){
        index = 0;
    }
    return index;
}
/* ==============================================
	functies: printers
   ============================================== */
void queue_printQueVolWarning(){
    printf("\033[31m[QUEUE: WARNING] Je probeert iets in de queue te steken terwijl ze vol is; Order genegeert\033[0m\n");
}
void queue_printQueLeegInfo(){
    printf("\033[34m[QUEUE: INFO]: Je probeert te lezen uit queue terwijl ze leeg is; Actie genegeert\033[0m\n");
}