#include <iostream>
#include <fstream>
#include <random>
using namespace std;

int main(){
    // Open the file (create if missing, WIPES if exists)
    ofstream out("frames.csv");
    if (!out) {
        return 1;
    }
    mt19937 rng(42);

    // 2. shapes bits into ints in [20000, 80000]
    uniform_int_distribution<int> bytesDist(20000, 80000); 
    // same, doubles in [14.0, 20.0] 
    uniform_real_distribution<double> msDist(14.0, 20.0); 
    
    // with the other distributions:
    uniform_int_distribution<int> pct(1, 100);
    uniform_real_distribution<double> spikeDist(40.0, 120.0); 
    double ms;
    out << "frame_id" << "," << "frame_ms" << "," << "dropped" << "," << "bytes_sent\n";
    for (int i = 0; i < 100000; i++){
        int bytes = bytesDist(rng);
        if (pct(rng) <= 2){
            ms = spikeDist(rng);
        } else {
            ms = msDist(rng);
        }
        out << i << "," << ms << "," << ((ms > 33.0) ? 1 : 0) << "," <<  bytes << "\n";
    }
    cout << "wrote 100000 rows\n";
    return 0;
}