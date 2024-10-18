
# DATASTRUCTUREN & ALGORITMES ALGEMENE VERZAMELING

---

---


## Bestaande_structuren________________
 - ### Hashmap (std::unordered_map)
   - Use case: naam/tijd/datum mappen naar event of andere entry-node
   - (+): O(1)
   - (-): storage overhead
---
 - ### balanced binary search tree (std::map)
   - Use case: naam mappen naar gesorteerde events
   - (+): snelle gesorteerde search O(log(n))
   - (-): geen O(1) direct acces meer
---
 - ### Trie (radix trie maar op per elke char i.p.v. prefix)
   - Use case: namen opslaan met snelle opzoek
   - (+): log(n) om een naam te zoeken, met minder storage dan hashmap
   - (-): is hashmap storage een nadeel? + niet heel bruikbaar bij niet-strings
---
- ### Min-Heap
    - Use case: meerdere gesorteerde collecties snel mergen naar 1 gezamelijke gesorteerde collectie
    - (+): log(n) agendas van meer users mergen met behoud van sorteerorde
    - (-) hoe users mappen als alle tijden in 1 map zitten?
--- 
- ### Interval tree
    - Use case: zoeken van interval overlaps (kijken of tijdslot beschikbaar is)
    - (+): log(n) om bezette tijdslots te vinden
    - (-): zelfde nadeel als min heap
---
- ### Van Emde Boas tree
  - Use case: zelfde als interval tree + min heap
  - (+) kan voordelen can interval tree en min heap combineren zonder (time-)overhead
  - (-) Zelfde als interval en min-heap + extra implementatie complexiteit
---
- ### Bitmaps (eigen idee, maar wordt blijkbaar wel conventioneel gebruikt met bepaade use cases)
  - Use case: beschikbaarheden binair cachen
  - (+): extreme efficientie voor tijdslots bekijken
  - (-): space complexity kan ook extreem ver oplopen -> enkel te gebruiken bij strategisch gekozen resolutie
---
- ### Sparse Matrix linked list implementatie
  - Use case: beschikbaarheden binair cashen
  - (+): kan de extreme storage size van een 2d array over alle mogelijke tijdstippen verminderen tot enkel gebruikte tijdstippen
  - (-): verliest de directe indexing acces -> n of log(n)
---
- ### R-tree
  - Use case: "2d" mapping (standaard intentionele case = geometrie)
  - (+): kan 2 'entiteiten' bvb naam+datum naar 1 event mappen met log(n) opzoektijd
  - (-): niet helemaal perfect voor deze use case + map complexiteit wanneer map keys niet numeric zijn

## Eigen_Hybride_augmentaties__________
 - ### Hashmap met values als linked list nodes
   - (+): directe acces, maar ook iteratie op gesorteerde volgorde
 - ### Geneste hashmaps voor "2d" mapping
   - (+): O(1)
   - (-): space overhead en redundantie
- ### hashmap met unified keys (geconcat als strings) voor "2d" mapping
  - (+): O(1)
  - (-): space overhead en redundantie + kan niet bvb alle events van
         1 user krijgen, terwijl geneste map met user als outer map,
         kan je van de inner date map alle entries selecteren.
         aka: geen "full query" mogelijkheid voor 1 dimensie
- ### merged combinatie van 2 trees (tot soort graph met 2 entrypoints) voor "2d" mapping
  - (+): meer relationele vrijheid tussen nodes
  - (-): hogere complexiteit dan de hashmap approaches
---

---

# SPECIFIEK Opdrachten

---

---

# SPECIFIEK ADVANCED

---

---

# SPECIFIEK SCHEADULER

simplistic:
    - Hashmap
        -> graph die gelinked zijn door pointers
        -> hash functies om dingen op te zoeken met O(1)
    - trie
        -> strings ingebouwd
        -> opzoeken is 0(log(n)) omdat het heel de boom moet doorlopen

    => Hashmap is beter omdat het opzoeken efficienter is en het terughalen van een string is instant d.m.v. string pointer

advanced:
    - Hashmap
        -> opzoeken is 0(1) in elke richting (tussen events, names, DateTimes,...)
        Voor de UserName->Event map:
            Value = een lijst van events
            Bij eze lijst worden gesorteerd op startTime de event pointer ge-insert
            -> dat maakt zoek algoritmen log(n)

        opstelling heap:
            -> TimeSpans moeilijk te vergelijken in deze heapstructuur waar alleen events timespans bijhouden
                -> moeten door elke user iteraten en deze vergelijken
            -> lijst of tree van TimeSpans bijhouden
                -> ordenened zorgt voor snelle vergelijking en bepaling van vrije momenten
            -> matrix van TimeSpans bijhouden
                -> vergelijken van Timespans vergemakkelijken
            -> Date: het year-gedeelte kan in een lookup table waar elke index overeenkomt met year-min_year

    => Hashmap met in de heap een matrix van TimeSpans omdat zoeken en vergelijken hier heel veel voorkomt, toevoegen iets minder

schedular:
    - grotendeels hetzelfde als advanced
        -> vergelijken van TimeSpans enz is uitgewerkt in advanced

    Eventuele overweging:
        Naast enkel direct timespans, kan een person ook een agenda bitmap (array/matrix) oplsaan
        optie 1) bitmap per jaar, resolutie=datum -> kan dag indexeren, dan log(n) zoeken naar tijdslot
        optie 2) bitmap per dag, minuut=resolutie. (nadeel: 180 bytes per dag)



       Dagen: INTERVAL TREE -> log(N) voor alles (inclusief checken voor overlappende timespans)
          Alternatief (betere keuze): bitmaps (veronderstellend dat tijd resolutie 30min is)
