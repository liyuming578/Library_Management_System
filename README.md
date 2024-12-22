# Library Management System

## Overview
This library management system facilitates the computerized management of basic library operations such as cataloging, inventory clearance, borrowing, and returning of books. The system operates entirely in-memory, without the use of file storage. It uses a B-tree (specifically a 2-3 tree) to index books by their numbers, ensuring efficient data retrieval and manipulation.

## System Features
- **Cataloging**: Allows new books to be entered into the system once they are categorized and assigned a number. If a book is already present, it increases the total inventory count.
- **Inventory Clearance**: Enables the removal of books that no longer hold value or relevance, completely erasing their records from the system.
- **Borrowing**: Books with a positive inventory count can be loaned out. The system records the borrower's library card number and the return due date.
- **Returning**: Upon return, the system updates the inventory count and cancels the borrower's registration.
- **Display**: For debugging and maintenance purposes, the system can display the B-tree structure in a concave table format to visualize the indexing of book numbers.

## Implementation Details
- The system is implemented using key-value pairs within a B-tree structure, where the key type is assumed to be an integer for the experimental setup.
- Each node in the B-tree can contain up to a pre-defined maximum number of children (M), ensuring efficient search and insertion operations typical for B-trees.
- Operations like book addition, deletion, and borrowing checks are all facilitated through this B-tree structure, which is pivotal in maintaining the integrity and speed of the system.

## Conclusion
The library management system is a robust example of how traditional library processes can be streamlined using data structures such as B-trees. This system is designed to handle multiple library tasks efficiently without the need for persistent storage, making it ideal for demonstration and educational purposes.