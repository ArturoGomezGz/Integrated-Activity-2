# Input File Design Documentation

This document explains the design and purpose of each input file created to stress-test the network optimization algorithms implemented in this project.

## Input File Format

Each input file follows this structure:

1. **N**: An integer representing the number of neighborhoods
2. **Distance Matrix**: N×N matrix with distances in kilometers between neighborhoods
3. **Capacity Matrix**: N×N matrix with maximum data flow capacities between neighborhoods
4. **Coordinates**: List of N ordered pairs (A,B) representing locations on a coordinate plane

## Input Files Overview

### input1.txt - Baseline Test (4 nodes)
**Purpose**: Original test case for basic functionality validation

**Characteristics**:
- 4 neighborhoods forming a small, manageable network
- Fully connected graph with varying distances
- Moderate capacity values
- Well-distributed coordinates

**Tests**:
- Basic MST construction
- Simple TSP with 4 cities
- Standard max flow calculation
- Voronoi region generation with 4 points

---

### input2.txt - Dense Graph (5 nodes)
**Purpose**: Stress test for algorithms handling fully-connected dense graphs

**Characteristics**:
- 5 neighborhoods with **complete connectivity** (every node connects to every other)
- All edges have positive weights (no zeros except diagonal)
- Uniform distribution of relatively similar edge weights (10-35 km)
- High capacity values throughout the network (20-55 units)
- Coordinates form a square pattern with center point

**Stress Tests**:
- **MST Algorithm**: Must choose optimal edges from many available options (10 possible edges for 4 needed)
- **TSP Algorithm**: Tests permutation generation with 24 different possible routes (4! = 24)
- **Max Flow**: Multiple parallel paths available between source and sink
- **Voronoi**: Regular geometric pattern tests boundary calculations

**Expected Behavior**:
- MST should find 4 edges with minimum total weight
- TSP has many valid routes to compare
- Max flow should be relatively high due to multiple paths

---

### input3.txt - Sparse Linear Chain (6 nodes)
**Purpose**: Stress test for bottleneck scenarios and sparse connectivity

**Characteristics**:
- 6 neighborhoods in a **linear chain topology** (A→B→C→D→E→F)
- Highly sparse: Only 5 edges in the entire graph (minimum for connectivity)
- Each edge is the only connection between its endpoints
- Decreasing capacity along the chain (100→50→40→30→20)
- Linear coordinate placement on a horizontal line

**Stress Tests**:
- **MST Algorithm**: Trivial case - must include all existing edges (no choice)
- **TSP Algorithm**: Only one valid Hamiltonian path (if any), tests handling of sparse graphs
- **Max Flow**: Classic bottleneck scenario - flow limited by smallest capacity (20 units)
- **Voronoi**: Linear arrangement creates elongated regions

**Expected Behavior**:
- MST equals the input graph (all 5 edges)
- TSP may fail or find limited routes due to missing connections
- Max flow severely limited by the final bottleneck edge (20 units)

---

### input4.txt - Large Mixed Topology (7 nodes)
**Purpose**: Scalability test with larger graph and mixed topology

**Characteristics**:
- 7 neighborhoods (larger scale than other inputs)
- **Mixed topology**: Neither fully connected nor linear
- Moderate connectivity: ~14 edges out of 21 possible
- Edge weights range from 12 to 31 km
- Capacity values vary significantly (30-70 units)
- Coordinates form an irregular heptagonal pattern

**Stress Tests**:
- **MST Algorithm**: Larger search space with multiple viable paths
- **TSP Algorithm**: 720 possible permutations (6! = 720) - significantly more complex
- **Max Flow**: Complex multi-path routing with varying capacities
- **Voronoi**: Irregular polygon tests edge case handling

**Expected Behavior**:
- Tests algorithm performance with increased problem size
- TSP becomes computationally more expensive
- Max flow must navigate multiple paths of varying quality
- All algorithms should still complete in reasonable time for N=7

---

## Key Differences Summary

| Input | Nodes | Edges | Density | Key Feature | Primary Stress |
|-------|-------|-------|---------|-------------|----------------|
| input1.txt | 4 | ~12 | High | Baseline | Validation |
| input2.txt | 5 | 20 | Complete | Fully connected | Choice complexity |
| input3.txt | 6 | 5 | Minimal | Linear chain | Bottlenecks & sparsity |
| input4.txt | 7 | ~14 | Medium | Mixed topology | Scale & variety |

## Testing Recommendations

1. **Run all inputs sequentially** to compare algorithm behavior across different graph types
2. **Monitor execution time** especially for input4.txt TSP calculations
3. **Verify output quality**:
   - MST total weight should be minimal
   - TSP route should visit all nodes exactly once
   - Max flow should not exceed the minimum cut capacity
   - Voronoi regions should partition the plane appropriately

4. **Expected Algorithm Performance**:
   - **Prim's MST**: O(N²) - scales well across all inputs
   - **Brute-force TSP**: O(N!) - noticeable slowdown on input4.txt
   - **Edmonds-Karp Max Flow**: O(VE²) - handles all inputs efficiently
   - **Voronoi approximation**: Performance depends on sampling resolution

## Conclusion

These input files comprehensively test the network optimization algorithms by covering:
- **Density variations**: From sparse chains to complete graphs
- **Scale testing**: From 4 to 7 nodes
- **Topology diversity**: Linear, regular, and irregular arrangements
- **Capacity patterns**: Uniform, decreasing, and mixed distributions

Together, they demonstrate the algorithms' capabilities, limitations, and performance characteristics across realistic network scenarios.
