#include <stdio.h>
#include "actorList.h"

//maakt een nieuwe node van een actor
ActorNode* newActorNode(ActorData* actorData) {
    //Geheugen alloceren op heap
    ActorNode* actorNode = malloc(sizeof(ActorNode));
    if (!actorNode) {
        printMallocErr("Actor", actorData->name);
        exit(EXIT_FAILURE);
    }
    //data
    actorNode->actor = actorData;
    actorNode->next = NULL;
    actorNode->previous = NULL;
    return actorNode;
}

//voegt een actor toe aan een bestaande linked list
void insertActor(ActorNode** head, ActorNode* actorNode) {
    ActorNode* current = *head;
    ActorNode* prev = NULL;

    // Ga door de lijst tot bij de plaats waar die moet ge-insert worden
    while (current) {
        int compare = compareActors(actorNode->actor, current->actor);
        if (compare < 0) break;
        //om een duplicate insert te negeren
        if (compare == 0) return;
        prev = current;
        current = current->next;
    }

    if (!prev) {
        // HEAD
        actorNode->next = *head;
        (*head)->previous = actorNode;
        *head = actorNode;
    }
    else if (!current) {
        // TAIL
        prev->next = actorNode;
        actorNode->previous = prev;
    }
    else {
        prev->next = actorNode;
        actorNode->previous = prev;
        actorNode->next = current;
        current->previous = actorNode;
    }
}


//voegt een actor toe een linked list, of initialiseert de list als ze nog niet bestaat
void createOrInsertActor(ActorNode** head, ActorNode* actorNode) {
    if (*head) {
        insertActor(head, actorNode);
    }
    else {
        *head = actorNode;
    }
}

//verwijderd een actor van een actors list
void deleteActorFromActorList(ActorNode** head, ActorData* actorData) {
    ActorNode* current = *head;
    ActorNode* prev = NULL;

    while (current != NULL && compareActors(actorData, current->actor) > 0) {
        prev = current;
        current = current->next;
    }

    if (!current) return; //actor zit niet in lijst
    if (!prev) {
        //Head
        *head = current->next;
        ActorNode* next = current->next;
        //Een lijst van 1 lang kan head en tail zijn
        if (next) {
            next->previous = NULL;
        }
    }
    else {
        //Mid
        ActorNode* next = current->next;
        prev->next = next;
        if (next) {
            next->previous = prev;
        }
    }

    free(current);
}
//verwijderd actors van list en ook uit alle movies
void deleteActor(MovieNode** movieHead, ActorNode** actorHead, ActorData* actorData) {
    MovieNode* currentMovie = *movieHead;
    while (currentMovie) {
        //deleteActorFromActorList in deleteActorFromMovie negeert al actors die niet aanwezig zijn
        deleteActorFromMovie(currentMovie->movie, actorData);
        currentMovie = currentMovie->next;
    }
    deleteActorFromActorList(actorHead, actorData);
}