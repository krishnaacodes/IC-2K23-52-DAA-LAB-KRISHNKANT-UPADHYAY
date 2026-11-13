
# Section D: Space Optimization Analysis

## 1. Space Complexity of Full and Sparse Matrix Representations

For an m × n matrix containing k non-zero elements:

### (a) Full 2D Representation

A full matrix stores all elements, including zeros.

**Space Complexity:**

O(m × n)

Total elements stored = **m × n**

### (b) Sparse Triple Representation

A sparse matrix stores only non-zero elements. Each element requires three values:

- Row index
- Column index
- Element value

**Space Complexity:**

O(3k) = O(k)

Total values stored = **3k**, excluding the header.

---

## 2. Testing Sparse Matrix Conversion

Tested two matrices of dimensions 6 × 6.

### Matrix 1: Approximately 80% Zero Elements

**Input Matrix:**

```text
0 0 5 0 0 0
0 8 0 0 0 0
3 0 0 0 0 0
0 0 0 7 0 0
0 0 0 0 2 0
0 0 0 0 0 9
```

- Total elements = 36
- Non-zero elements = 7
- Zero elements = 29

Percentage of zeros:

(29 / 36) × 100 = 80.56%

**Storage Comparison:**

| Representation | Values Stored |
|---|---:|
| Full 2D Representation | 36 |
| Sparse Representation | 21 |

Sparse representation stores 3 × 7 = 21 values, excluding the header.

### Matrix 2: Fewer Than 20% Zero Elements

**Input Matrix:**

```text
1 2 3 4 5 0
6 7 8 9 1 2
3 4 5 6 7 8
9 1 2 3 4 5
6 7 8 9 1 2
3 4 5 6 7 8
```

- Total elements = 36
- Non-zero elements = 35
- Zero elements = 1

Percentage of zeros:

(1 / 36) × 100 = 2.78%

**Storage Comparison:**

| Representation | Values Stored |
|---|---:|
| Full 2D Representation | 36 |
| Sparse Representation | 105 |

Sparse representation stores 3 × 35 = 105 values, excluding the header.

### Observation

The first matrix benefits from sparse representation because most of its elements are zero.

The second matrix requires more storage in sparse representation because most elements are non-zero.

---

## 3. Percentage at Which Sparse Representation Stops Saving Space

In a full matrix:

Space = m × n

In a sparse matrix:

Space = 3k

For equal storage:

3k = m × n

Therefore:

k / (m × n) = 1 / 3

Percentage:

(1 / 3) × 100 = 33.33%

**Answer:**

Sparse representation stops saving space when approximately 33.33% or more elements are non-zero.

**Explanation:**

Each non-zero element requires three stored values: row index, column index, and element value.

A full matrix stores only one value per position.

Therefore, when the number of non-zero elements reaches approximately one-third of the total elements, sparse representation requires equal or greater storage.

Note: This calculation excludes the three-value header. Including the header makes the break-even point slightly lower.

---

## 4. Real-World Application of Sparse Matrices

### Graph Representation Using Adjacency Matrix

An adjacency matrix is used to represent connections between nodes in a graph.

For example, in a social networking application, thousands of users may exist, but each user is connected to only a small number of other users.

Therefore, most entries in the adjacency matrix are zero because most users do not have a direct connection with each other.

Sparse matrix representation saves memory by storing only the existing connections instead of storing every zero value.

---

## Conclusion

Sparse matrix representation is useful when a matrix contains a large number of zero elements.

It reduces storage requirements by storing only non-zero elements with their row and column indices.

However, when most elements are non-zero, a full 2D representation may be more memory-efficient.
