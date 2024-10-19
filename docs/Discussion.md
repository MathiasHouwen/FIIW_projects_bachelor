
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
 - ## (natuurlijk vecots en arrays, maar gesorteerd ge-insert)
   - Use case: alles waar je kan searchen of sorteren
   - (+): simpele verzamelingen zijn compatible met log(n) zoekalgoritmes. Gerbuikt ook minder pointers(geheugen) dan trees
   - (-): atomair: zal waarschijnlijk voor kleine sub verzamelingen gebruikt worden.
          merging algoritmes zijn dan nodig voor multi-user resultaten
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
   - (-): hoge insert tijd: hoe zoek je de nodes waartussen je moet inserten (zonder O(N))?
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
- ### Geclusterede gesorteerde hashmap/linkedlist voor "2d" mapping
  - Meer uitleg: stel feature 1 = time en feature 2 = user. Er is 1 map die alle tijden van alle users bijhoudt. Dmv de linked list hashmap zijn e tijden gesorteerd, maar in clusters per persoon. Doordat een andere map naar de start node van zijn cluster kan wijzen bekom je direct alle times van die persoon op volgorde.
  - (+) identieke functionaliteit aan geneste hashmap
  - (-) meer storage voor geconcatenteerde key strings (map versie), of log(n) om specifieke time te zoeken (list versie)
    - Die space overhead komt van het feit dat de prefix string (bvb username) een duplicaat is voor elke tijd van die persoon, terwijl de genseste map enkel tijd keys opslaat, die gezamelijk onder maar 1 username key liggen
---

---

# SPECIFIEK Opdrachten

---

---

## SPECIFIEK SIMPLISTIC

### datastrcutuur
- Events ongestructureerd op de heap
    - Houdt kopie/pointer naar username of starttime,
      zodat ondanks de gebruikte map, wel alle event fields direct beschikbaar zijn
- Username mapt naar een event via hashmap
- Starttime mapt naar event via hashmap
### algoritmes
- zowel naam als time kan direct ingevuld worden O(1)
### overwegingen
- Enkel space complexity maar dit is zeker niet extreem
---

## SPECIFIEK ADVANCED

### datastrcutuur
- Zelfde hashmap als Simplistic om van username naar event te gaan
    - Enige vershil is dat key = lijst[event*] ipv event*
    - Event lijst kan eventueel gesorteerd zijn
- Hashmap ook voor event name
- Interval tree voor datetimes?
### algoritmes
### overwegingen

---

## SPECIFIEK SCHEADULER

### datastrcutuur
 - Een van de 2d mapping approaches om user en date te mappen naar een "dagplanning" voor die user
    - Geneste map user[date] zodat je meteen alle dates van een user hebt. Bij elke structuur moeten dates gefiltert worden op basis van peroson
 - Dag planning heeft een gesorteerde linkedlist van events en avialability cache
 - Avialability cache is bitmap op half-uur-resolutie
 - Date map kan de linked list hybride hashmap gebruiken voor de gesorteerde print functie
 - Events per dag
### algoritmes
 - Functie 1: is enkel map keys of indices invullen om de bitmaps te verkrijgen. O(1)
 - Dan kunnen alle bitmaps ge-merged worden met elkaar alsook een bitmask van de gekozen timespan
 - Functie 2: Sorteren kan door de datums te iteraten via de hybride ge-integreerde linked list
 - Kan daarbij ook sorteren door de events (die ook op volgorde staan)
 - Bij meerdere users, via recursie, of loops die op elkaar wachten de events en data voor elke user zogezegd "gelijktijdig" iteraten
### overwegingen
 - De bitmaps nemen minder space dan 1 pointer in beslag, terwijl ze een extreem verschil maken in query tijd. -> zeer voordelige optimalisatie. Mogelijk gebruikt dit niet eens meer space dan een tree/graph appra=oach vanwege extra pointers
 - Bitmaps kunnen als integer ipv array vergelijkingen doen via bitwise operaions. Dat is in principe een instant en volledig parrallele compare voor alle timeslots
 - Waarom geneste hashmap en niet 2 apart waarbij 1 alle dates heeft, linked gesorteerd in groepen per person, waarbij map 2 een person mapt naar de start node voor zijn groep?
   - Om nog steeds direct een person-date combinatie te querien moeten de keys van de grote map een concatentatie zijn
   - In vgl tot nested maps bestaan er evenveel combinaties. Alleen worden nu person name strings gedupliceerd voor elke entry van 1 persoon, terwijl de geneste enkel dates storen en er is maar 1 persoon key
 - Waarom chache per dag en niet 1 cache voor heel jaar of zelf alle tijd?
   - Heel jaar is minder storage als de meeste dagen bezet zijn
   - Maar naast bezet zijn checken moet event ook effectief ingepland.
     De insert positie voor een event moet met n of log n gezocht worden (omdat event lijsten gesorteerd zijn).
     Dat is natuurlijk korter als dat voor 1 dag moet ipv voor alle events van die persoon.

---

---

# INITIELE (OUDE) DISCUSSIE

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
