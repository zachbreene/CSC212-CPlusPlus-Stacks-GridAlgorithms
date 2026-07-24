<h1 align=center> C++ Stacks & Grid Traversal Algorithms </h1>
<h2 align=center> A CSC212: Data Structures Project by Zachary Breene </h2>
<h4 align=center> Created at The University of Rhode Island, November 2021 </h4>
</n>
<h4 align=center> *NO AI WAS USED IN THE CREATION OF THIS PROJECT* </h4>

## Introduction
This repository contains a collection of five C++ programs designed to explore advanced data structures and search algorithms. The assignment is split into two primary themes: using Stack data structures to parse and compute complex mathematical strings, and using Depth-First Search (DFS) recursive algorithms to navigate and analyze 2D coordinate matrices. 

---

## Implementation + Functions
### Mathematical Parsing via Stacks
These programs utilize the Last-In, First-Out (LIFO) nature of Stacks to process strings of math.

*   `postfix_eval.cpp`: Calculates the result of equations written in postfix notation (e.g., `3 4 +`). It pushes integers to a stack and pops them to apply calculations whenever an operator is encountered. Includes custom floor-division logic to appropriately handle negative numbers.
*   `infix_to_postfix.cpp`: Translates standard human-readable equations (infix) into postfix notation. It utilizes the Shunting Yard algorithm, assigning precedence values to operators to correctly resolve PEMDAS order of operations and nested parentheses.

### Grid Traversal via Depth-First Search (DFS)
These programs ingest 2D matrices from text files and utilize recursive DFS pathfinding to analyze the terrain. 

*   `elevation_path.cpp`: Analyzes a grid of numbers representing topographical elevation. It locates the lowest and highest points on the map, then calculates if a continuous path exists between them where the traveler never steps downhill. 
*   `blob_counter.cpp`: Scans a matrix of 1s and 0s to calculate the total number of connected components (blobs) of 1s. When a 1 is found, a recursive function triggers, converting the entire connected blob into 0s to prevent double-counting. 
*   `blob_size.cpp`: Similar to the counter, but requires a specific starting `(x, y)` coordinate. The DFS algorithm traverses outwards from that specific point to calculate the total area/size of that single isolated blob.

---

## How To Run
To execute any of these programs, compile the individual `.cpp` file using a standard C++ compiler (e.g., `g++ elevation_path.cpp -o pathfinder`). 

Run the executable via the command line, providing the appropriate arguments:
*   **For Math Programs:** Enclose the equation string in quotation marks.
    *   *Example:* `./evaluator "4 5 * 2 /"`
*   **For Path/Blob Programs:** Provide the text file name, the grid rows, and the grid columns. For the blob programs, you must also specify `4` or `8` to dictate the connectivity rules (4-way vs 8-way directional connection). The size calculator also requires the target X and Y coordinates.
    *   *Example:* `./blob_counter matrix.txt 10 10 8`

---

## Contribution
I was the sole member of this project and contributed to the whole of the project.
