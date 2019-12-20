#ifndef CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
#define CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include <queue>

using namespace std;

struct Vertex {
    list<pair<int,int>> adjList;
    Vertex * path = nullptr;
    long long int dist = -1;
    vector<long long int> magicPower = {-1,-1,-1};
    bool known = false;
    bool operator() (const Vertex* lhs, const Vertex* rhs){
        return lhs->dist > rhs->dist;
    }
};
struct ComparatorForFifth {
    bool operator() (const pair<Vertex*,int> lhs, const pair<Vertex*,int> rhs){
        return lhs.first->magicPower[lhs.second] > rhs.first->magicPower[lhs.second];
    }
};

class HelpStudents{

public:
    HelpStudents(int  N, int  M, int K, vector < pair< pair <int,int> , int > > ways);
    long long int firstStudent();
    long long int secondStudent();
    long long int thirdStudent();
    long long int fourthStudent();
    long long int fifthStudent();
private:
    vector<Vertex> vertexs;
    int M, K;
};

#endif //CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
