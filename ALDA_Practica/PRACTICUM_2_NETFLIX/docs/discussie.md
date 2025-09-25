# Opgave requirements

#### ZOEK:
- Type: altijd
- Title ( + genre)
- Release year (exact == )
#### SORT:
- IMDb

# Approach

## Zoeken op type (aka alle zoekfucnties)
 - Types worden nooit gemixt
   - -> movies en series kunnen in een aparte instantie staan van de datastructuur

## Zoeken op title
 - Hoofd-structuur = Trie
 - ga door alle branches volgens title, en voeg alle branches toe aan een result set. return result set
 - De children field in een Trie Node is een map (BST) gesorteerd op IMDb

## Zoeken op genre
 - Trie node heeft ook genre(pointer)
 - Genres in datastructuur houden of garbage collection toevoegen
 - Zoek met genre: doe hetzelfde als zoeken op title maar voeg niet toe aan result set als genre != zoekgenre

## Zoeken op jaar
 - Max heap gaat niet
 - Alles apart opslaan, buiten de main Trie
 - Outer datastructuur: map of array om jaar te mappen naar inner datastructuur
 - Inner datastructuur: BST met movies, gesorteerd via IMDb rating

# concrete implementatie

```cpp
struct MovieOfSerieStruct{
    string name; // name is er voor de release year map later eventueel een end-of-word TrieNode pointer
    string genre; // ebbe fixt hier wel garbage collection voor
    int IMDbRating;
};
```
```cpp
struct TrieNode {
    char letter;
    MovieStruct* movie; // om genre te kunnen getten
    map<char, TrieNode*, sort=IMDb> children; // key = IMDb
    // leafnode = children.size == 0
    // niet-kruispunt = children.size == 1
    // kruispunt = children.size > 1
    // end-of-word = letter == '*' (of mss beter '\0')
};
```
```cpp
class Trie {
private:
    TrieNode* root;
    // recursieve helper insert via char
public:
    void insert(MovieStruct movie);
    void remove(MovieStruct movie);
    set<string> search(string prefix, string genre);
}
```
```cpp
class Netflix {
public:
    enum class Type{MOVIE, SERIES}
private:
    Trie moviesTitleTrie, seriesTitleTrie;
    int minYear; 
    vector<set<MovieStruct, sort=IMDb>> releaseYearSets;
public:
    //netflix
    insert(Type type, string title, string genre, int releaseYear, float rating);
    remove(Type type, string title, string genre); // genre omdat er duplicate titels zijn
    //user
    searchByTitle(Type type, string title, string genre = "");
    searchByReleaseYear(Type type, int releaseYear);
}
```
```cpp
// een commandlijn class die eindelijk goeie kwaliteit heeft,
// die we nog kunnen herbruiken voor practicum 3
class CLI{
    struct Command{
        string commandName; // eerste woord van command
        set<pair<char, string>> params; // "-naam waarde"
        set<string> flags;  // "--naam"
    };
    Command getInput();
    //eventueel een validate functie, waar je zelf een Command meegeeft als parameter,
    // om te checken dat de getInput die command name heeft, en om enkel specifieke flags/params toe te laten
};
```
