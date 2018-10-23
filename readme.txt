This program computes the most efficient activities to complete. It does this using a Last-to-start implementation.
Data is read from a file named act.txt, in the following format:

3       //number of Activities in the set
3 6 8   //each activity has three values:
1 7 9   //an id, a start value, and an end value.
2 1 2   //all values are separated by spaces.

The program will read in as many sets as are in the file, and output the results both to the console, as well as to a file named act.out

In order to use this program:
Compile the program with: g++ -o activitySelection activitySelection.cpp
Run the program with: ./activitySelection
