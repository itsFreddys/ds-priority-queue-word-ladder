Word Ladder Priority Queue implementation

This program provides a C++ implementation of a WordSet (priority queue) data structure and a word conversion algorithm. The WordSet data structure is a custom made priority queue utilizing its efficient data extraction and sorting mechanisms.

The convert function implements a breadth-first search algorithm to find the shortest word ladder between two given words. It uses my custom queue, WordSet, to efficiently extract next word that fits top priority standard, then checks word's validity to explore possible transformations.

example: converting from start word to end word in the fewest steps. Cat -> Dog Requires the following steps: cat -> cot -> dot -> dog
