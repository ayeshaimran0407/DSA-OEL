Hospital Patient Priority System (DSA OEL)
This repository contains the implementation of a Hospital Patient Priority System, developed as part of a Data Structures and Algorithms (DSA) Open-Ended Lab (OEL). The project utilizes various data structures to manage patient records, prioritize care based on severity, and perform complex algorithmic operations.

 Project Overview
The system models a hospital's patient intake process using a Doubly Circular Linked List. It supports priority-based scheduling, where patients with higher severity scores are attended to first.

 Tech Stack
Language: C++

Core Concepts:

Doubly Circular Linked List: For efficient bidirectional patient traversal and management.

Priority Queue: Implementation using linked list insertion logic.

Stack: Used for patient ID processing and expression evaluation.

Binary Search Tree (BST): For hierarchical data organization, featuring deletion and balancing.

Sorting Algorithms: Bubble Sort (on linked lists) and Merge Sort (on arrays).

Key Functionalities
Patient Management: Circular insertion, forward/backward traversal, and average severity analysis.

Priority Scheduling: Dynamic enqueue/dequeue operations based on patient severity and arrival order.

Stack Operations: Includes a stack reversal algorithm using a single queue and infix-to-postfix expression conversion.

BST Operations: Full implementation of BST insertion, deletion (using inorder successor), and height-based tree balancing.

Analysis: Performance comparison and memory complexity analysis for the implemented data structures.


📂 Repository Structure
Plaintext
DSA-OEL/
├── src/
│   └── OEL_Code.cpp    # Full implementation of all DSA modules
├── docs/
│   └── Report.pdf      # Detailed lab report with diagrams and analysis
└── README.md
📈 Performance Analysis
Bottleneck: The current implementation uses Bubble Sort for list organization, resulting in O(n 
2
 ) time complexity.

Optimization: A Heap-based Priority Queue is recommended for large-scale systems to improve insertion/deletion complexity to O(logn).

Memory Trade-off: The use of a Doubly Linked List requires an additional 8 bytes per node (for the prev pointer), which is justified by the requirement for bidirectional traversal and efficient deletions.

Developed by Ayesha Imran | BSAI Student at NASTP Institute of Information Technology (NIIT).
