# Project One – Runtime and Memory Analysis

In Project One, I compared different data structures to determine which would be most efficient for storing and retrieving course information. I evaluated vectors, hash tables, and binary search trees using Big-O notation.

## Vector
- Search: O(n)
- Insert: O(1) at end, O(n) if inserting elsewhere
- Sorting required before efficient search

Vectors are simple to use, but searching becomes inefficient as the dataset grows unless the data is sorted.

## Hash Table
- Search: Average O(1)
- Insert: Average O(1)
- No natural ordering

Hash tables provide very fast lookup times but do not maintain sorted order, which makes printing an alphabetical list more difficult.

## Binary Search Tree
- Search: Average O(log n)
- Insert: Average O(log n)
- In-order traversal: O(n)

The binary search tree offered a good balance between search efficiency and maintaining sorted order. Because the advising program needed to print courses in alphanumeric order, the BST was the most appropriate choice.

## Conclusion

After analyzing runtime and memory usage, I determined that a binary search tree was the best structure for the advising application since it allows efficient searching while naturally supporting sorted output.
