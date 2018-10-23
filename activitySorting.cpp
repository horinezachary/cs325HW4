#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <vector>

using namespace std;

struct activity {
  int id;
  int start;
  int end;
};
void mergeSort(activity* arr, int min, int max);
void merge(activity* arr, int min, int mid, int max);
string activitySorting(int numItems, activity* caseItems);

int main(){
  ifstream inFile;  //set up the file reader and attempt to read the file
  inFile.open("act.txt");
  if (!inFile) {  //make sure the file exists
    cout << "Unable to open act.txt" << endl;
    exit(1);   // EXIT PROGRAM
  }
  string line;
  int caseNumber = 0;
  bool firstCaseLine = true;
  int numCaseItems = 0;
  int caseItemCounter = 0;

  activity* caseItems;

  int linecount = 1;
  string fileout = "";
  while(getline(inFile,line)){ //gets one line
    linecount++;
    stringstream lineStream(line);
    string cell;
    vector<string> parsedRow;
    while(getline(lineStream,cell,' ')){  //parses line and puts numbers into string vector
      parsedRow.push_back(cell);
      //cout << cell;
    }
    if (firstCaseLine){  //first line in the set (numItems)
      //cout << "case" << endl;
      numCaseItems = stoi(parsedRow.at(0));
      firstCaseLine = false;
      caseItems = new activity[numCaseItems];
      caseItemCounter = 0;
      caseNumber++;
    }
    else if (caseItemCounter < numCaseItems) {  //add item to item array
      //cout << "Item " << caseItemCounter << endl;
      caseItems[caseItemCounter].id    = stoi(parsedRow.at(0));
      caseItems[caseItemCounter].start = stoi(parsedRow.at(1));
      caseItems[caseItemCounter].end   = stoi(parsedRow.at(2));
      caseItemCounter++;
    }
    if (caseItemCounter == numCaseItems){ //all Items have been read, execute
      caseItemCounter++;
      firstCaseLine = true; //reset for next case

      mergeSort(caseItems,0,numCaseItems);
      fileout.append("Set: ");
      fileout.append(to_string(caseNumber));
      fileout.append("\n");
      fileout.append(activitySorting(numCaseItems,caseItems));
    }
  }
  //cout << fileout;

  //Write string to file
  ofstream outfile;
  outfile.open("act.out");
  if (!outfile) {  //make sure the file exists
    cout << "Unable to open act.out";
    exit(1);   // EXIT PROGRAM
  }
  outfile << fileout;
  outfile.close();
}

string activitySorting(int numItems, activity* caseItems){
  string outString = "";
  string activityString = "";
  int numSelected = 0;

  for (int i = 0; i < numItems; i++) {
    cout << caseItems[i].id << " " << caseItems[i].start << " " << caseItems[i].end << endl;
  }



  outString.append("Number of activities selected = ");
  outString.append(to_string(numSelected));
  outString.append("\nActivities:");
  outString.append(activityString);
  outString.append("\n\n");
  return outString;
}

void mergeSort(activity* arr, int min, int max){  //sorts array by start time, lowest to highest
  if (max - min > 1){
    int mid = (min+max)/2;
    mergeSort(arr,min,mid);
    mergeSort(arr,mid,max);
    merge(arr,min,mid,max);
  }
}

void merge(activity* arr, int min, int mid, int max){
  activity* temp = new activity[max-min];
  int left_low = min;
  int right_low = mid;
  int count;
  for (count = 0; left_low < mid && right_low < max; count++){
    if (arr[left_low].start > arr[right_low].start){
      temp[count] = arr[right_low];
      right_low++;
    }
    else{
      temp[count] = arr[left_low];
      left_low++;
    }
  }
  while(left_low < mid){
    temp[count] = arr[left_low];
    count++;
    left_low++;
  }
  while(right_low < max){
    temp[count] = arr[right_low];
    count++;
    right_low++;
  }
  for(int i = 0; i < max-min; i++){
    arr[min+i] = temp[i];
  }
  delete[] temp;
}
