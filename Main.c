#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Ebbe Wertz
//Mathias Houwen

#define ARRAYLEN 25
#define ETD 4 //Elemtents tussen diplucates 

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

//random:
void initaliseerRandom();
double randomDouble0Tot100();
Position randomPosition();
void maakWillekeurigeLijst(Position result[ARRAYLEN]);
void maakWillekeurigeLijst_PA(Position *resulte);

//indices, data arrays
void optimaliseer(Position initieleData[], int indices[], Position data[]);
void optimaliseer_PA(Position *initieleData, int *indices, Position *data);
bool arrayBevatPos(Position pos, Position array[]);
bool arrayBevatPos_PA(Position pos, Position* arr);
int getIndex(Position pos, Position array[]);
int getIndex_PA(Position pos, Position *arr);
bool posZijnGelijk(Position pos1, Position pos2);
Position legePos();

//printers:
void printUitkomsten(Position dataInitieel[], int indices[], Position data[]);
void printUitkomsten_PA(Position *dataInitieel, int *indices, Position *data);
void printPosition(Position position);


/* ==============================================
	main
   ============================================== */

int main() {
	Position initieleData[ARRAYLEN];
	int indices[ARRAYLEN];
	Position verkleindeData[ARRAYLEN];

	initaliseerRandom();

	// "Gewoone" functies
	maakWillekeurigeLijst(initieleData);
	optimaliseer(initieleData, indices, verkleindeData);
	printUitkomsten(initieleData, indices, verkleindeData);

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
	int seed = time(NULL);	//huidig exact tijdstip = onvoorspelbaar
	srand(seed);
}

double randomDouble0Tot100() {
	double tussen0en1 = (double)rand() / (double)RAND_MAX;	//randmax = internal uit stdlib
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

void maakWillekeurigeLijst_PA(Position *result) {
	for (int i = 0; i < ARRAYLEN; i++) {
		if ((i % ETD != 0) || (i == 0)) {
			*(result + i) = randomPosition(); //Als het niet het vijde elment is generate randome waarden
		}
		else {
			int j = i / ETD; //Om het 5de element pak een duplicant
			*(result + i) = *(result + j);
		}
	}
}


/* ==============================================
	functies: indices, data arrays
   ============================================== */

void optimaliseer(Position initieleData[], int indices[], Position data[]) {
	int dataIteratieIndex = 0;	//omdat data geen dupl. bevat en initeledata wel kan data geen zelfde index van een for in initieledata gebruiken
	for (int i = 0; i < ARRAYLEN; i++) {
		Position pos = initieleData[i];
		//Als pos=uniek? -> pos in data
		if (!arrayBevatPos(pos, data)) {
			data[dataIteratieIndex] = pos;
			dataIteratieIndex++;
		}
		//steek data-index van pos in de indices array
		int indexInData = getIndex(pos, data);
		indices[i] = indexInData;
	}
	//maak overige plaats in data leeg voor duidelijke leesbaarhied
	for (int i = dataIteratieIndex; i < ARRAYLEN; i++) {
		Position niks = legePos();
		data[i] = niks;
	}
}

void optimaliseer_PA(Position *initieleData, int *indices, Position *data) {
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
	Position niks;
	niks.x = 0;
	niks.y = 0;
	niks.z = 0;
	return niks;
}

bool arrayBevatPos(Position pos, Position array[]) {
	int index = getIndex(pos, array);
	return index >= 0;
}

bool arrayBevatPos_PA(Position pos, Position *arr) {
	int index = getIndex_PA(pos, arr);
	return index >= 0;
}

int getIndex(Position pos, Position array[]) {
	for (int i = 0; i < ARRAYLEN; i++) {
		Position posInArray = array[i];
		if (posZijnGelijk(pos, posInArray)) {
			return i;	//hier al meteen return en niet bewaren in variable -> sneller want niet altijd wacht op hele for loop
		}
	}
	return -1;
}

int getIndex_PA(Position pos, Position *arr) {
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
		printf("      || %.3d   %.3d: ", indices[i],i);
		printPosition(data[i]);
		printf("||\n");
	}

}

void printUitkomsten_PA(Position *dataIntitieel, int *indices, Position *data) {
	printf("======DATA_ORIGINEEL======  ->  || IND + ============DATA_NIEUW=========||\n");
	for (int i = 0; i < ARRAYLEN; i++) {
		printPosition(*(dataIntitieel + i));
		printf("      || %.3d   %.3d: ", *(indices + i), i);
		printPosition(*(data + i));
		printf("||\n");
	}
}

void printPosition(Position position) {
	double x = position.x;
	double y = position.y;
	double z = position.z;
	if (x == 0 && y == 0 && z == 0) {
		printf("_________( nul )__________");
	}
	else {
		printf("x:%06.2f y:%06.2f z:%06.2f", x, y, z);
	}
	
}

