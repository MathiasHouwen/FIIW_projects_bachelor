typedef struct {
	const char* name;
} ActorData;


typedef struct {
	ActorData* actor;
	ActorNode* next;
	ActorNode* previous;
} ActorNode;

typedef struct {
	const char* name;
	int year;
	struct ActorNode* actors;
} MovieData;

typedef struct {
	MovieData* movie;
	MovieNode* next;
} MovieNode;int main() {	return 1;}