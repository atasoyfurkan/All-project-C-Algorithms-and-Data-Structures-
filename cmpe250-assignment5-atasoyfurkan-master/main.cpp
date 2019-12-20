/*
Student Name: Muhammed Furkan Atasoy
Student Number: 2017400216
Project Number: 5
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void readInput(int & N, int & M, vector<int> & prices, ifstream& inFile) {
    inFile >> N;
    inFile >> M;
    prices.resize(N);
    for(int i = 0; i < N; i++)
        inFile >> prices[i];
}

void countSort(vector<int> & array, int exp) {
    int count[10] = {0};
    vector<int> output(array.size());

    for(int i =0; i < array.size(); i++)
        count[(array[i] / exp) % 10]++;

    for(int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for(int i = array.size() - 1; i >= 0;i--)
        output[count[(array[i] / exp) % 10]-- - 1] = array[i];

    array = std::move(output);
}

void radixSort(vector<int> & array) {
    int max = array[0];
    for (int i = 1; i < array.size(); i++) {
        if (max < array[i])
            max = array[i];
    }
    for(int exp = 1; max/exp > 0; exp*=10)
        countSort(array, exp);
}

void calculatePrice(vector<int> & prices, int & M, vector<long long int> & sum) {
    for(int K = 0; K < prices.size(); K++) {
        sum[K] = prices[K];
        if(K - 1 >= 0) sum[K] += sum[K - 1];
        if(K - 1 - (M - 1) >= 0) sum[K] += sum[K - 1 - (M - 1)];
        if(K - 1 - (M - 1) - 1 >= 0) sum[K] -= sum[K - 1 - (M - 1) - 1];
    }
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Run the code with the following command: ./cmpe250-assignment4 [input_file] [output_file]" << endl;
        return 1;
    }

    ifstream inFile(argv[1]);
    if (!inFile) { // operator! is synonymous to .fail(), checking if there was a failure
        cerr << "There was a problem opening \"" << argv[1] << "\" as input file" << endl;
        return 1;
    }

    ofstream outFile(argv[2]);
    if (!outFile) {
        cerr << "There was a problem opening \"" << argv[2] << "\" as output file" << endl;
        return 1;
    }

    int N, M;
    vector<int> prices;
    readInput(N, M, prices, inFile);

    radixSort(prices);

    vector<long long int> sum(prices.size());
    calculatePrice(prices, M, sum);

    for(int i =0 ; i < sum.size(); i++)
        outFile << sum[i] << " ";

    return 0;
}