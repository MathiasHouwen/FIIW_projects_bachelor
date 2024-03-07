#include <stdio.h>

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


//struct defenitie
struct position {
	float x;
	float y;
	float z;
};
typedef struct position Position; //position struct type kan nu genoemd worden door alleen "Position"

//functie signatures (implementatie onderaan)
void printUitkomsten(int indices[], Position data[]);
void printPosition(Position position);


int main() {
	Position testPos;
	testPos.x = 10.123;
	testPos.y = 11.321;
	testPos.z = 12.456;
	printPosition(testPos);
	return 0;
}


void printUitkomsten(int indices[], Position data[]) {
	//
}
void printPosition(Position position) {
	printf("x:%f y:%f z:%f", position.x, position.y, position.z);
}