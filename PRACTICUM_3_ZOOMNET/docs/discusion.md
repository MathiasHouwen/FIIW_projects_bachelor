# Algoritmes
## 1. Designing the initial network

* MST minum spanning tree
  - Kruskal's Algorithm
  - Prim's Algorithm
  - Borůvka’s Algorithm

| **Aspect**               | **Kruskal's Algorithm**                          | **Prim's Algorithm**                           | **Borůvka’s Algorithm**                         |
|--------------------------|------------------------------------------------|-----------------------------------------------|------------------------------------------------|
| **Purpose**              | Finds a Minimum Spanning Tree (MST).            | Finds an MST.                                  | Finds an MST.                                   |
| **Approach**             | Greedy.                                         | Greedy.                                        | Greedy and iterative.                           |
| **Process**              | Sorts edges by weight and adds the smallest edge that doesn’t form a cycle. | Starts from a vertex and grows the MST by adding the smallest edge connecting to an unvisited vertex. | Adds the cheapest edge for each component in parallel; merges components iteratively. |
| **Data Structure Used**  | Union-Find (Disjoint Set).                      | Priority Queue (Heap).                        | Union-Find for component merging.              |
| **Edge Handling**        | Processes edges globally.                       | Processes edges locally (around the current tree). | Processes edges in parallel for all components.|
| **Time Complexity**      | \(O(E \log E + E \alpha(V))\) (sorting edges + Union-Find). | \(O(E + V \log V)\) (with Fibonacci Heap).     | \(O(E \log V)\) (depends on edge contraction). |
| **Space Complexity**     | \(O(E + V)\).                                   | \(O(E + V)\).                                  | \(O(E + V)\).                                   |
| **Graph Representation** | Works well with edge lists.                     | Works best with adjacency lists/matrices.     | Works with edge lists or adjacency structures. |
| **Parallelization**      | Difficult to parallelize.                       | Less suited for parallelization.              | Highly parallelizable due to independent component processing. |
| **Best Use Case**        | Sparse graphs or when edges are already sorted. | Dense graphs or adjacency list available.     | Highly distributed systems or very large graphs. |
| **Drawbacks**            | Sorting can be costly for large edge lists.     | Requires a good data structure for efficiency.| Requires more iterations and is less intuitive. |

## 2. Adapting to constraints

* MST via Kruskal's wordt opgebouwd vanuit een edge list
  - die edge list kan op voorhand worden ingevuld als "include list"
  - iteraties / recursie calls voor connecties in de "exclude list" kunnen genegeerd worden

## 3. Optimizing upgrades
### huidige oplossing:
1. voor de toe te voegen connectie, bepaal de totale weight van het pad daar tussen
2. vergelijk met de weight van de nieuwe connectie
### initieel idee:
1. voeg nieuwe connectie toe
2. zoek de gevormde lus
3. verwijder het deel van de lus dat de grootste weight heeft
* lus zoeken met de connectie is in principe hetzelfde dan pad zoeken zonder de connectie. Pad zoeken is meer intuitief te implementeren
* complexiteit van de lus zoeken is bepalen waar de lus start en eindigd (om van alle visited nodes te weten welke nodes in de lus zijn en welke vertakkingen zijn)

## 4. Maintaining after roll-out

### realistisch net
 - DFS (aka 'normale') traversal met een boolean parameter en gewoon in elke recursie call de parameter inverten
   - elke 'depth' krijg dan een alternerende waarde -> die kan dan channel1 of channel2 zijn
   - er zijn maar 2 channels omdat de graph een MST is

### Channels voor all possible connecties
 - Graph coloring algoritme

# Datastructuren

# Edge list vs adjacency matrix?
 - sparse structuur. Cities hebben vooral connecties met aangrenzende cities. Dus zeker niet met alle andere nodes
   - Matrix zou dus te veel memory gebruiken
   - Keuze: edge list
 ### structur edge list:
  - Edge list = (sorted) set van connecties: {city1*, city2*, weight, real}
    - city1+city2 = citynode pointers. Real=possible connectie / echt verbonden connectie
    - gesorteerd op weight, want helpt bij Kruskal's Algorithm
  - CityNode struct:
    - city naam + channel
    - (unordered) map van connecties die die city heeft
      - Key = andere cityNode pointer
      - Value = connectie pointer
      - Gegeven 2 city node pointers kan je O(1) de connectie pointer vinden
      - Gegeven een city kan je meteen zijn naburige connecties vinden
  - CityNode opslag: LookupTable (CityNodeLUT)
    - alloceer citynode pointer via city naam string
    - vraag pointer via naam string
    - delete city via naam string
    - Kan dus O(1) een city vinden via naam. Dan hoef de public interface van graph geen pointers te vragen -> low coupling

# Edge Cases
1. Eilanden als input. Alle eilanden moeten behandeld worden
    - Kruskal's werkt via de edge list op alle connecties, en niet via traversal van connecties van nodes
    - Eilanden kunnen dus niet gemist worden
2. meerder gelijke gewichten
3. 2 possible paths tussen dezeflde twee nodes. ALs ene een 'verleidende' lage weight heeft direct langs een van de twee nodes, maar een extreem grote weight in het midden, dan moet het andere path gekozen worden, dat er aan de eindbestemmingen duurder uitziet maar in totaal goedkoper is
    - Kruskal's neemt de kleinste connecties van de edge list.
    - Is dus niet greedy per node in een traversal manier
    - Te greedy via de edge list als er een extreem lage connectie is? -> edge case 3
4. weer 2 possible paden, maar waarbij ene een connectie met een extreem lage weight (bvb laagste van de hele graph) heeft

# Ebbe's OneNote notities: <img src="Robin_kwam_aan_mijn_code.jpg" width="48"/>
![](Graph_diagrammen.png)