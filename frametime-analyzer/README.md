
# Frametime Analyzer
Generates synthetic game-streaming telemetry (100k frames) and computes frame-time stats: avg, min/max, drop rate, p95.

## Build & Run
g++ -std=c++17 -O2 generate.cpp -o generate
g++ -std=c++17 -O2 analyze.cpp -o analyze
./generate && ./analyze

## Sample Output
frames: 100000
Dropped: 1971 (1.97%)
avg ms: 18.24
min ms: 14.00
max ms: 119.96
total bytes: 4994698430
p95 ms: 19.81