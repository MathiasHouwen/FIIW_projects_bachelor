/* ==============================================
	Practicum 1 BESC:

	Team 12
		- Ebbe Wertz
		- Mathias Houwen

   ============================================== */

#include <stdio.h>
#include <stdlib.h>	//voor random functies
#include <stdbool.h>

#define ARRAYLEN 25	//lengte initele data array (aantal positions)
#define ETD 4 //Aanral elemtenten tussen diplucaten (zie maakWillekeurigeLijst)

   /* ==============================================
	   Position defenitie
	  ============================================== */

struct position {
	float x;
	float y;
	float z;
};
typedef struct position Position; //position struct type kan nu genoemd worden door alleen "Position"

/* ==============================================
	functie signatures(implementatie onderaan)
   ============================================== */

   //..._PA = versie met pointer arithmetic

   //random:
void initaliseerRandom();	//zet rand seed
float randomDouble0Tot100();
Position randomPosition();

void maakWillekeurigeLijst(Position result[ARRAYLEN]);
void maakWillekeurigeLijst_PA(Position* resulte);

//indices, data arrays:
void optimaliseer(Position initieleData[], int indices[], Position data[]);
void optimaliseer_PA(Position* initieleData, int* indices, Position* data);

bool arrayBevatPos(Position pos, Position array[]);
bool arrayBevatPos_PA(Position pos, Position* arr);
bool posZijnGelijk(Position pos1, Position pos2);

int getIndex(Position pos, Position array[]);
int getIndex_PA(Position pos, Position* arr);

Position legePos();	//pos: x=0, y=0, z=0

//printers:
void printUitkomsten(Position dataInitieel[], int indices[], Position data[]);
void printUitkomsten_PA(Position* dataInitieel, int* indices, Position* data);

void printPosition(Position position);


/* ==============================================
	main
   ============================================== */

int main() {

	Position initieleData[ARRAYLEN];

	int indices[ARRAYLEN];
	Position verkleindeData[ARRAYLEN];

	initaliseerRandom();

	printf("\n\n\"Gewone\" versie:\n\n");

	// "Gewoone" functies
	maakWillekeurigeLijst(initieleData);
	optimaliseer(initieleData, indices, verkleindeData);
	printUitkomsten(initieleData, indices, verkleindeData);

	printf("\n\nVersie met pointer arithmetic:\n\n");

	// Functies met pointer aritmitiek
	maakWillekeurigeLijst_PA(initieleData);
	optimaliseer_PA(initieleData, indices, verkleindeData);
	printUitkomsten_PA(initieleData, indices, verkleindeData);

	return 0;
}

/* ==============================================
	functies: random
   ============================================== */

void initaliseerRandom() {
	int seed = time(NULL);	//huidig exact tijdstip = (redelijk) onvoorspelbaar
	srand(seed);			//vooral om niet elke run dezelde sequence te krijgen
}

float randomDouble0Tot100() {
	float tussen0en1 = (float)rand() / (float)RAND_MAX;	//randmax: intern gedefinieerd in stdlib
	return tussen0en1 * 100;
}

Position randomPosition() {
	Position pos;
	pos.x = randomDouble0Tot100();
	pos.y = randomDouble0Tot100();
	pos.z = randomDouble0Tot100();
	return pos;
}

void maakWillekeurigeLijst(Position result[ARRAYLEN]) {
	for (int i = 0; i < ARRAYLEN; i++) {
		if ((i % ETD != 0) || (i == 0)) {
			result[i] = randomPosition(); // Als het niet het vijde elment is generate randome waarden
		}
		else {
			int j = i / ETD; // Om het 5de element pak een duplicant
			result[i] = result[j];
		}
	}
}

void maakWillekeurigeLijst_PA(Position* result) {
	//comments: zie niet-PA verise
	for (int i = 0; i < ARRAYLEN; i++) {
		if ((i % ETD != 0) || (i == 0)) {
			*(result + i) = randomPosition();
		}
		else {
			int j = i / ETD;
			*(result + i) = *(result + j);
		}
	}
}


/* ==============================================
	functies: indices, data arrays
   ============================================== */

void optimaliseer(Position initieleData[], int indices[], Position data[]) {
	int dataIteratieIndex = 0;	//data word langzamer gevuld dan initieleData word gelezen, kan dus i niet hergebruiken als index
	for (int i = 0; i < ARRAYLEN; i++) {
		Position pos = initieleData[i];
		//Als pos=uniek? -> pos in data
		if (!arrayBevatPos(pos, data)) {
			data[dataIteratieIndex] = pos;
			dataIteratieIndex++;
		}
		//steek data-index van pos (altijd) in de indices array
		int indexInData = getIndex(pos, data);
		indices[i] = indexInData;
	}
	//maak overige plaatsen in data leeg voor duidelijke leesbaarhied
	//! enkel voor onze leesbaarheid in een print, als efficient programma mag dit weggelaten
	for (int i = dataIteratieIndex; i < ARRAYLEN; i++) {
		Position niks = legePos();
		data[i] = niks;
	}
}

void optimaliseer_PA(Position* initieleData, int* indices, Position* data) {
	//comments: zie niet-PA verise
	int dataIteratieIndex = 0;
	for (int i = 0; i < ARRAYLEN; i++) {
		Position pos = *(initieleData + i);
		if (!arrayBevatPos_PA(pos, data)) {
			*(data + dataIteratieIndex) = pos;
			dataIteratieIndex++;
		}
		int indexInData = getIndex_PA(pos, data);
		*(indices + i) = indexInData;
	}
	for (int i = dataIteratieIndex; i < ARRAYLEN; i++) {
		Position niks = legePos();
		*(data + i) = niks;
	}
}

Position legePos() {
	Position leeg;
	leeg.x = 0;
	leeg.y = 0;
	leeg.z = 0;
	return leeg;
}

bool arrayBevatPos(Position pos, Position array[]) {
	//De getIndex zal -1 returnen wanneer pos niet in array
	int index = getIndex(pos, array);
	return index >= 0;
}

bool arrayBevatPos_PA(Position pos, Position* arr) {
	//comments: zie niet-PA verise
	int index = getIndex_PA(pos, arr);
	return index >= 0;
}

int getIndex(Position pos, Position array[]) {
	for (int i = 0; i < ARRAYLEN; i++) {
		Position posInArray = array[i];
		if (posZijnGelijk(pos, posInArray)) {
			return i; //eteen return, niet bewaren in var. -> sneller want hoef niet altijd te wachten op hele for loop
		}
	}
	return -1;	//return i zal functie vroeg stoppen, dus deze lijn word alleen gezien als pos niet in array
}

int getIndex_PA(Position pos, Position* arr) {
	//comments: zie niet-PA verise
	for (int i = 0; i < ARRAYLEN; i++) {
		Position posInArray = *(arr + i);
		if (posZijnGelijk(pos, posInArray)) {
			return i;
		}
	}
	return -1;
}

bool posZijnGelijk(Position pos1, Position pos2) {
	bool xgelijk = pos1.x == pos2.x;
	bool ygelijk = pos1.y == pos2.y;
	bool zgelijk = pos1.z == pos2.z;
	return xgelijk && ygelijk && zgelijk;
}

/* ==============================================
	functies: printers
   ============================================== */

void printUitkomsten(Position dataInitieel[], int indices[], Position data[]) {
	printf("======DATA_ORIGINEEL======  ->  || IND + ============DATA_NIEUW=========||\n");
	for (int i = 0; i < ARRAYLEN; i++) {
		printPosition(dataInitieel[i]);
		//.3 = 3 cijfers (kleine getallen worden bijgevuld met 0-en) -> maakt kolommen even breed -> mooie print
		printf("      || %.3d   %.3d: ", indices[i], i);
		printPosition(data[i]);
		printf("||\n");
	}

}

void printUitkomsten_PA(Position* dataIntitieel, int* indices, Position* data) {
	//comments: zie niet-PA verise
	printf("======DATA_ORIGINEEL======  ->  || IND + ============DATA_NIEUW=========||\n");
	for (int i = 0; i < ARRAYLEN; i++) {
		printPosition(*(dataIntitieel + i));
		printf("      || %.3d   %.3d: ", *(indices + i), i);
		printPosition(*(data + i));
		printf("||\n");
	}
}

void printPosition(Position position) {
	//gekozen om geen "posIsLeeg" functie te maken omdat we de x, y, en z vars kunnen hergebruiken in de else
	float x = position.x;
	float y = position.y;
	float z = position.z;
	if (x == 0 && y == 0 && z == 0) {
		printf("_________( nul )__________");	//duidelijke leesbaarheid
	}
	else {
		//6.2: 2=2decimalen, 6=6characters inc. punt -> 3 getallen voor punt
		printf("x:%06.2f y:%06.2f z:%06.2f", x, y, z);
	}

}

