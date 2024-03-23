#define hoeveelheidStock 5 // VERANDER NAAR 20

typedef struct {
	int productID;
	int productCount;
} product;

product stock[hoeveelheidStock];

int main() {
	return 0;
}

void initialiseerStock() {
	product iPhone = { 0, 50 }; //EBBE PAS DIT AUB AAN DAT DAT IN EEN FORLOOP WORDT GEDIFEND
	product lenovoLaptop = { 1, 50 }; // IDK HOW
	product samsungPhone = { 2, 50 };
	product windowsPhone = { 3, 50 };
	product hpLaptop = { 4, 50 };
}

void koop(int index, int aantal) {
	//
}

void produceer(int index, int aantal) {
	//
}

void printKoop(int consumer, int aantal, int index) {
	printf("Consumer %d has acquired %d of product %d.", consumer, aantal, index);
}

