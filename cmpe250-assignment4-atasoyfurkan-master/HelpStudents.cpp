/*
Student Name: Muhammed Furkan Atasoy
Student Number: 2017400216
Project Number: 4
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "HelpStudents.h"

using namespace std;

HelpStudents::HelpStudents(int  N, int  M, int K, vector < pair< pair <int,int> , int > > ways) {
    this->M = M;
    this->K = K;

    vertexs.resize(N + 1);

    for(int i = 0; i < ways.size(); i++) { // construct adj. list for all vertex and push it
        int & node1 = ways[i].first.first;
        int & node2 = ways[i].first.second;

        pair<int, int> edgeFor1(node2, ways[i].second);
        vertexs[node1].adjList.push_back(edgeFor1);

        pair<int, int> edgeFor2(node1, ways[i].second);
        vertexs[node2].adjList.push_back(edgeFor2);
    }
}

long long int HelpStudents::firstStudent() {
    priority_queue<Vertex*,vector<Vertex*>,Vertex> q;
    q.push(&vertexs[1]);
    vertexs[1].dist = 0;

    while(!q.empty()) {
        Vertex* v;
        v = q.top();
        q.pop();

        for (auto const & pair : v->adjList) { // control all adj. elements and find minimum distance and push it to priority queue
            Vertex & w = vertexs[pair.first];
            if(v->dist + pair.second < w.dist || w.dist == -1) {
                w.dist = v->dist + pair.second;
                q.push(&w);
            }
        }
    }
    return vertexs[this->K].dist;
}
long long int HelpStudents::secondStudent() {
    priority_queue<Vertex*,vector<Vertex*>,Vertex> q;
    q.push(&vertexs[1]);
    vertexs[1].dist = 0;

    int counter = 1;
    while(!q.empty() && counter < vertexs.size()) {
        Vertex* v;
        do {
            v = q.top();
            q.pop();
        }while(v->known && !q.empty());
        v->known = true;
        counter++;

        for (auto const & pair : v->adjList) {
            Vertex & w = vertexs[pair.first];
            if(!w.known && (pair.second < w.dist || w.dist == -1)) {
                w.dist = pair.second;
                w.path = v;
                q.push(&w);
            }
        }
    }
    Vertex* v = &vertexs[this->K];
    int maxDist = -1;
    while(v->path != nullptr) {
        if(maxDist < v->dist)
            maxDist = v->dist;
        v = v->path;
    }

    return maxDist;
}
long long int HelpStudents::thirdStudent() {
    queue<Vertex*> q;
    q.push(&vertexs[1]);
    vertexs[1].dist = 0;

    while(!q.empty()) {
        Vertex* v = q.front();
        q.pop();

        for (auto const & pair : v->adjList) {
            Vertex & w = vertexs[pair.first];
            if(w.dist == -1) {
                w.dist = v->dist + 1;
                q.push(&w);
            }
        }
    }
    return vertexs[this->K].dist;
}
long long int HelpStudents::fourthStudent() {
    Vertex *v = &vertexs[1];
    int index = 1;
    long long int dist = 0;

    while(v) {
        if(index == this->K) {
            return dist;
        }

        Vertex * minVertex = nullptr;
        pair<int, int> * minPair;
        for (auto & pair : v->adjList) {
            if(pair.second != -1 && (!minVertex || pair.second < minPair->second || (pair.second == minPair->second && pair.first < minPair->first))) {
                minVertex = &vertexs[pair.first];
                minPair = &pair;
            }
        }

        if(minVertex) {
            dist += minPair->second;
            minPair->second = -1;
            Vertex & w = vertexs[minPair->first];
            for(auto & pair : w.adjList) {
                if(index == pair.first) {
                    pair.second = -1;
                    break;
                }
            }
            index = minPair->first;
        }
        v = minVertex;
    }
    return -1;
}
long long int HelpStudents::fifthStudent() {
    priority_queue<pair<Vertex*,int>,vector<pair<Vertex*,int>>,ComparatorForFifth> q;
    q.push(make_pair(&vertexs[1], 0));

    while(!q.empty()) {
        Vertex* v = q.top().first;
        int index = q.top().second;
        q.pop();

        for (auto const & pair : v->adjList) {
            Vertex & w = vertexs[pair.first];

            int newIndex = (index + 1) % 3;
            if(v->magicPower[index] + pair.second < w.magicPower[newIndex] || w.magicPower[newIndex] == -1 || (index == 2 && v->magicPower[index] < w.magicPower[newIndex])) {
                if(index == 2)
                    w.magicPower[newIndex] = v->magicPower[index];
                else
                    w.magicPower[newIndex] = v->magicPower[index] + pair.second;
                q.push(make_pair(&w,newIndex));
            }
        }
    }
    long long int minNumber = vertexs[this->K].magicPower[0];
    for(int i = 1; i < 3; i++) {
        if((minNumber > vertexs[this->K].magicPower[i] || minNumber == -1) && vertexs[this->K].magicPower[i] != -1)
            minNumber = vertexs[this->K].magicPower[i];
    }
    return minNumber + 1;
}