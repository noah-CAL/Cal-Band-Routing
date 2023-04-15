# Cal-Band-Routing

## Problem Statement
In the University of California Marching Band, we use our custom-built and maintained program CalChart to place marchers on a 42x80 grid-like field for our field shows. One of the tasks of the STUNT marching committee is to not only create the designs for the field shows, but to also manually place and route each of the ~200 marchers between "stuntsheet" A to stuntsheet B such that there are no collisions between marchers at any point in time on the football field. Our marching style is primarily traveling East/West to North/South allowing only a single direction change, with *very rarely* allowing diagonal marching for difficult-to-solve transitions. 

"Solving transitions" difficult transitions can take 6+ hours which detracts from the overall show creation process, and there is currently no algorithm within CalChart to automate this process. Solving simple transitions, however, such as moving two seperate blocks of marchers, are simple to "solve" yet still take time to manually route every dot. Thus, this simplified problem can be broken down as optimizing a **Manhattan Routing Algorithm with Constraints**, with a marcher's path length from A to B (Manhattan Distance) as the cost function.

### Example

![image](https://user-images.githubusercontent.com/90151434/232248937-0402bdba-4c24-409f-8dda-470dbe11b39e.png)

The open / filled white dots represent the current stuntsheet while purple dots represent a view of the next stuntsheet's design. Currently, members on the STUNT committee must manually assign each marcher on the current sheet to one of the purple dots on the next sheet to create the next field design, all while minimizing marching distance and ensuring there are no collisions between marchers which often takes many hours.

## Algorithm Design

### Constraints
* Only a single marcher per grid-square at a given time.
* Marchers may only move either East/West or North/South during their movement, or may pivot in place which takes a single tick.
** **Simplification**: No diagonals are allowed.
* Marchers may start moving either in the East/West or North/South direction, and are only allowed **a single pivot** during their movement.
  * ex: **Move West 4 dots - pivot North - Move North 6 dots** is allowed, but **Move West 4 dots - pivot North - Move North 6 dots - Pivot East - Move East 2 dots** is not allowed because we pivot twice in a single path to reach the next dot.
* Nearby points *idealy* have similar paths (makes it easier to march and looks cleaner).
* Approximates, but does not need to perfectly minimize the distance cost-function.
* Amortized runtime is reasonably close to O(n^2).

## Research

This problem is similar to single-layer PCB routing, [a known NP-Complete problem](https://www.researchgate.net/publication/260584776_NP-Completeness_and_an_Approximation_Algorithm_for_Rectangle_Escape_Problem_With_Application_to_PCB_Routing), with the additional constraint that we must use Manhattan routing. 

Initially, I looked into implementations of the [Hungarian Algorithm with Forbidden Assignments](https://en.wikipedia.org/wiki/Hungarian_algorithm) by modeling the scenario as a variant of the [assignment problem](https://en.wikipedia.org/wiki/Assignment_problem). It works best when the cost matrix is sufficiently sparce which it is, as only 200/(42x80) * 100 ~= 6% of our grid is occupied at any instance in time. However, the upper bound is **O(n^4)** which is inoperable with our 200+ marchers.


## Implementation

Instead of the Hungarian Algorithm, I opted for finding a *close-enough* solution (the Hungarian Algorithm finds *the* optimal solution). The current algorithm is a variant of Dijkstra's Algorithm which finds the shortest paths between 200 points in two grids while also ensuring that the points do not overlap and they move in a limited way (i.e., they can only change directions once).

Additionally, as similar points will likely take similar paths, we use of a priority queue to provide a more efficient way to retrieve the next point to process based on its distance from the starting point. Without a PQ, we would need to perform a linear search through all the points to find the next closest point to process which would take O(n) time. PQ operations take *O(log n)* time, retrieving the next point is O(log n) time, and for n^2 pairs of points this leaves us with an overall runtime of O(n^2 log n).

As I work on the current implementation in C for performance, I'll update the README with my progress.
