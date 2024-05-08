#include <stdio.h>
#include "acteur.h"

// Functie om een nieuwe acteur struct te maken
ActorData newActor(const char* name) {
    ActorData actorData;
    actorData.name = name;
    return actorData;
}

int compareActors(void* actor1, void* actor2) {
    ActorData* actorData1 = (ActorData*)actor1;
    ActorData* actorData2 = (ActorData*)actor2;
    return strcmp(actorData1->name, actorData2->name);
}