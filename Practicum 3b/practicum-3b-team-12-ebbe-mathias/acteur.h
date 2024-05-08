#ifndef ACTEUR_H
#define ACTEUR_H

typedef struct ActorData ActorData;

struct ActorData {
    const char* name;
};

ActorData newActor(const char* name);
int compareActors(void* actor1, void* actor2);

#endif