# 🧭 Project Development Guidelines: Internet Service Optimization (C++)

This document provides a clear roadmap and set of instructions for developing the **Internet Service Optimization Project** in C++. Follow each phase carefully to ensure your program fulfills all requirements and is easy to maintain, test, and present.

---

## 📌 Objective

Develop a C++ program that assists an ISP company in solving various network optimization problems involving distances, data flows, and geographic coordinates. The program will:

1. Read and process graph data from input files.
2. Compute the **Minimum Spanning Tree (MST)** for optimal fiber wiring.
3. Solve the **Traveling Salesman Problem (TSP)** to find the shortest delivery route.
4. Compute **Maximum Flow** between two nodes.
5. Determine the **nearest exchange center** for a given location.

---

## 🧩 Project Structure

Organize your project files as follows:

```
📁 InternetServiceOptimization
├── main.cpp              # Entry point of the program
├── graph.h / graph.cpp   # Classes and functions for graph operations
├── tsp.h / tsp.cpp       # TSP (Traveling Salesman Problem) logic
├── maxflow.h / maxflow.cpp # Max Flow algorithm implementation
├── geometry.h / geometry.cpp # Exchange distance calculations
├── utils.h / utils.cpp   # Input/output handling and validation
└── input.txt             # Test input data
```

---

## 🧠 Step-by-Step Development Plan

### Step 1: Input Handling

**Goal:** Read and parse all input data correctly.

**Tasks:**

* Read integer `N` (number of neighborhoods).
* Read two `N x N` matrices:

  * Distance matrix (for MST and TSP)
  * Capacity matrix (for Max Flow)
* Read the coordinates list for each neighborhood.
* Store data in suitable structures (e.g., `vector<vector<int>>` or `vector<pair<int, int>>`).

**Tips:**

* Implement a `readInput()` function to handle all parsing.
* Validate matrix dimensions.

---

### Step 2: Minimum Spanning Tree (MST)

**Goal:** Determine the minimal set of edges that connect all nodes with the least total distance.

**Tasks:**

* Implement **Prim's** or **Kruskal's** algorithm.
* Use a structure to store edges `(nodeA, nodeB, weight)`.
* Output: list of selected edges and total distance.

**Example Output:**

```
Optimal wiring:
A - B (16 km)
B - C (18 km)
C - D (7 km)
Total: 41 km
```

---

### Step 3: Traveling Salesman Problem (TSP)

**Goal:** Find the shortest possible route that visits each neighborhood once and returns to the start.

**Tasks:**

* Implement a heuristic (e.g., **Nearest Neighbor** or **Cheapest Link** method).
* Use recursion or permutation methods for smaller graphs.
* Output the optimal visiting order and total distance.

**Example Output:**

```
Shortest Route:
A -> B -> D -> C -> A
Distance: 72 km
```

---

### Step 4: Maximum Flow

**Goal:** Compute the maximum possible information flow between two nodes.

**Tasks:**

* Implement **Ford–Fulkerson** or **Edmonds–Karp** algorithm.
* Input: capacity matrix.
* Output: total maximum flow value from source (node 0) to sink (node N-1).

**Example Output:**

```
Maximum Flow: 112 units
```

---

### Step 5: Closest Exchange Finder

**Goal:** Given a new location, determine which exchange center is geographically closest.

**Tasks:**

* Compute Euclidean distance between points.
* Identify the smallest distance.
* Optionally, generate Voronoi-like regions (conceptually or visually).

**Example Output:**

```
Closest Exchange to (320, 210) → Exchange 2 at (300,100)
```

---

## ⚙️ Implementation Recommendations

* Use **classes** to represent `Graph`, `Edge`, and `Node` for modularity.
* Apply **functions** for each task to separate logic cleanly.
* Use descriptive variable names (e.g., `distanceMatrix`, `capacityMatrix`).
* Comment each function briefly (purpose and parameters).

---

## 🧪 Testing

Create multiple input files to test edge cases:

* Fully connected vs. partially connected graphs.
* Large vs. small datasets.
* Asymmetric vs. symmetric distances.

Run using:

```bash
./internet_project input.txt
```

Validate outputs match expected results for MST, TSP, and Max Flow.

---

## 🧑‍💻 Suggested Roles (Team of 3)

| Role        | Responsibilities                                  |
| ----------- | ------------------------------------------------- |
| Developer 1 | Graph algorithms (MST, Max Flow)                  |
| Developer 2 | TSP implementation & optimization                 |
| Developer 3 | Input parsing, geometry calculations, integration |

---

## 🧾 Deliverables

* C++ source code (.cpp and .h files)
* Input and output test files
* README file (documentation)
* Report summarizing algorithms, results, and conclusions

---

## 📚 References

* Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. *Introduction to Algorithms*. MIT Press.
* Sedgewick, R. & Wayne, K. *Algorithms (4th Edition)*.
* Ford, L. R., & Fulkerson, D. R. (1956). *Maximal flow through a network*. Canadian Journal of Mathematics.

---

✅ **By following these steps, your team will be able to implement a robust, efficient, and well-documented solution for the Internet Service Optimization problem.**
