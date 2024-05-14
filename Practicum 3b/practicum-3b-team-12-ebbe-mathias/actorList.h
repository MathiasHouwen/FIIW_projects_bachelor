#ifndef actorList_H
#define actorList_H

#include "data.h"

typedef struct ActorNode ActorNode;

struct ActorNode {
    ActorData* actor;
    ActorNode* next;
    ActorNode* previous;
};

ActorNode* newActorNode(ActorData* actorData);
void insertActor(ActorNode** head, ActorNode* actorNode);
void createOrInsertActor(ActorNode** head, ActorNode* actorNode);
void deleteActor(MovieNode** movieHead, ActorNode** actorHead, ActorData* actorData);
void deleteActorFromActorList(ActorNode** head, ActorData* actorData);

#endif