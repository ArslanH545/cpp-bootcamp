#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ifstream readFile("frames.csv");
    if (!readFile){
        cerr << "could not open frames.csv" << endl;
        return 1;
    }
    vector<double> frameTimes;
    string line;
    int count = 0;
    int droppedCount = 0;
    double sumMs = 0.0;
    long long totalBytes = 0;
    double minMs = numeric_limits<double>::max();
    double maxMs = numeric_limits<double>::lowest();
    getline(readFile, line);
    while (getline(readFile, line)){
        stringstream ss(line);
        string field;
        getline(ss, field, ',');
        getline(ss, field, ',');
        double ms = stod(field);
        if (ms < minMs) minMs = ms;
        if (ms > maxMs) maxMs = ms;
        frameTimes.push_back(ms);
        getline(ss, field, ',');
        int dropped = stoi(field);
        getline(ss, field, ',');
        int bytes = stoi(field);

        if (dropped == 1){
            droppedCount++;
        }
        sumMs += ms;
        totalBytes += bytes;
        count++;
    }
    cout << fixed << setprecision(2);
    cout << "frames: " << count << endl;
    cout << "Dropped: " << droppedCount << " (" << ( 100.0 * droppedCount / count) << "%)" << endl;
    cout << "avg ms: " << (sumMs / count) << endl;
    cout << "min ms: " << minMs << endl;
    cout << "max ms: " << maxMs << endl;
    cout << "total bytes: " << totalBytes << endl;

    sort(frameTimes.begin(), frameTimes.end());
    double p95 = frameTimes[(int)(0.95 * frameTimes.size())];
    cout << "p95 ms: " << p95 << endl;
    return 0;
}