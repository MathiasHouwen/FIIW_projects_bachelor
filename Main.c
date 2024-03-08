#include <stdio.h>
#include <stdlib.h>

#define N 5
//Ebbe Wertz
//Mathias Houwen

/*
* =======================
*     OPGAVE
* =======================

	geheugen:
		1 array met data (elk data element is een instantie van de position struct
		1 array met indices die refereren naar data elementen in de data array

	voorbeeld uitvoer:
	"
		Position Data
			1 : x : 0.1 y : 0.8 z : 1.5
			2 : x : 0.2 y : 0.7 z : 0.1
			3 ...
	"
	Deze punten worden gelezen vanaf de indices array.
	(die kan bvb 2 punten hebben met dezelfde coordinaten.
	In de data array is dan eig maar 1 van dat punt opgeslagen
	er zijn dan 2 indices die naar datzelfde punt wijzen)

*/


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
//printers:
void printUitkomsten(int indices[], Position data[]);
void printPosition(Position position);
//random:
void initaliseerRandom();
double randomDouble0Tot100();
Position randomPosition();
//indices, data arrays
void optimaliseer(Position initieleData[N], int indices[], Position data[]);
/* ==============================================
	main
   ============================================== */

int main() {
	initaliseerRandom();
	Position p1 = randomPosition();
	Position p2 = randomPosition();
	Position p3 = randomPosition();
	
	Position initieleData[N] = { p1, p3, p1, p2, p3 };
	int indices[N];
	Position verkleindeData[N];

	optimaliseer(initieleData, indices, verkleindeData);


	return 0;
}

/* ==============================================
	functies
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

void optimaliseer(Position initieleData[], int indices[], Position data[]) {
	int dataIndex = 0;	//omdat data geen dupl. bevat en initeledata wel kan data geen zelfde index van een for in initieledata gebruiken
	for (int i = 0; i < N; i++) {
		Position pos = initieleData[i];
		printPosition(pos);
	}
}


void printUitkomsten(int indices[], Position data[]) {
	//
}
void printPosition(Position position) {
	printf("x:%f y:%f z:%f\n", position.x, position.y, position.z);
}