/*
Student Name: Muhammed Furkan Atasoy
Student Number: 2017400216
Project Number: 2
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "RestaurantOrganizer.h"

using namespace std;

RestaurantOrganizer::RestaurantOrganizer(const vector<int>& tableCapacityInput){
    numberOfTables = tableCapacityInput.size();
    for(int i=0;i<numberOfTables;i++){
        tableCapacity[i] = tableCapacityInput[i];
        heap[i] = i;
        heapUp(i);
    }
}

void RestaurantOrganizer::addNewGroup(int groupSize, ofstream& outFile){
    if(groupSize > tableCapacity[heap[0]]) {
        outFile << "-1" << endl;
    }
    else {
        outFile << heap[0] << endl;
        tableCapacity[heap[0]] -= groupSize;
        heapDown(0);
    }
}

int parent(int child) {
    return (child - 1) / 2;
}
int leftChild(int parent) {
    return parent * 2 + 1;
}
int rightChild(int parent) {
    return parent * 2 + 2;
}

void RestaurantOrganizer::heapUp(int index){
    int & hole = index;
    int copy = std::move(heap[hole]);

    while(hole > 0 && tableCapacity[copy] > tableCapacity[heap[parent(hole)]]) {
        heap[hole] = std::move(heap[parent(hole)]);
        hole = parent(hole);
    }

    heap[hole] = std::move(copy);
}

void RestaurantOrganizer::heapDown(int index){
    int & hole = index;
    int copy = std::move(heap[index]);

    while(leftChild(hole) < numberOfTables) {
        int &leftHeap = heap[leftChild(hole)];
        int &rightHeap = heap[rightChild(hole)];
        int &parentHeap = heap[hole];
        int &parentCapacity = tableCapacity[parentHeap];
        int &leftCapacity = tableCapacity[leftHeap];
        int &rightCapacity = tableCapacity[rightHeap];

        if (rightChild(hole) < numberOfTables) {
            int * maxHeap;
            int * maxCapacity;
            int maxChildHole;
            if(leftCapacity > rightCapacity) {
                maxHeap = &leftHeap;
                maxCapacity = &leftCapacity;
                maxChildHole = leftChild(hole);
            }
            else if(leftCapacity < rightCapacity) {
                maxHeap = &rightHeap;
                maxCapacity = &rightCapacity;
                maxChildHole = rightChild(hole);
            }
            else if(leftCapacity == rightCapacity) {
                if(leftHeap < rightHeap) {
                    maxHeap = &leftHeap;
                    maxCapacity = &leftCapacity;
                    maxChildHole = leftChild(hole);
                } else {
                    maxHeap = &rightHeap;
                    maxCapacity = &rightCapacity;
                    maxChildHole = rightChild(hole);
                }
            }

            if(parentCapacity > *maxCapacity) {
                break;
            }
            else if(parentCapacity < *maxCapacity) {
                swap(parentHeap, *maxHeap);
                hole = maxChildHole;
            }
            else if(parentCapacity == *maxCapacity) {
                if(parentHeap < *maxHeap) break;
                else {
                    swap(parentHeap, *maxHeap);
                    hole = maxChildHole;
                }
            }

        } else {
            if(parentCapacity > leftCapacity) {
                break;
            }
            else if(parentCapacity == leftCapacity) {
                if(parentHeap < leftHeap) break;
                else {
                    swap(parentHeap, leftHeap);
                    hole = leftChild(hole);
                }
            }
            else if(parentCapacity < leftCapacity) {
                swap(parentHeap, leftHeap);
                hole = leftChild(hole);
            }
        }
    }

    heap[hole] = std::move(copy);
}


void RestaurantOrganizer::printSorted(ofstream& outFile){
    while(numberOfTables > 0) {
        outFile << tableCapacity[heap[0]] << " ";
        heap[0] = heap[numberOfTables - 1];
        numberOfTables--;
        heapDown(0);
    }
}