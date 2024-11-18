

# Approach

sort de trie child nodes set op basis van aantal verdere children
->  hierdoor zijn queries automatisch gesort

types worden nooit gemixt -> dus movies en series in compleet aparte datastructure opslaan

## requirements

### ZOEK:
 - Type: altijd
 - Title ( + genre)
 - Release year (exact == )

### SORT:
 - IMDb

# concrete implementatie

```cpp
struct TrieNode {
    char letter;
    std::unordered_set<TrieNode*> children;
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
public:
    void insert(string string);
    void remove(string string);
    set<string> search(string prefix);
}
```
```cpp
class linkedMap<DataT, IndexT, SortT> {
public:
    struct MapNode{
        MapNode* next;
        MapNode* prev;
        DataT data;         // Trie child node
        IndexT indexKey;    // IMDb rating
        SortT sortKey;      // char letter
    }
private:
    MapNode* head;
    unordered_map<MapNode*> quickIndexer;
public:
    void insert(DataT data, IndexT indexKey, SortT sortKey);
    void remove(IndexT indexKey);
    set<MapNode> getAll();
}
```
```cpp
class Netflix {
public:
    enum class Type{MOVIE, SERIES}
private:
    Trie movies, series;
public:
    add(Type type, string title, string genre, int releaseYear, float rating);
    remove(Type type, string title);
    searchByTitle(Type type, string title, string genre = "");
    searchByReleaseYear(Type type, int releaseYear);
}
```

