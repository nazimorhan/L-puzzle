#include "classes.h"
#include <chrono>

using namespace std::chrono;

void triggerSearch(int argc, int algo, char **argv);

void triggerSearch(int size, int algo, string *argv){
    int numbers[size*size];
    // Get input numbers from user.
    for (int i = 0; i < size*size; i++) {
        numbers[i] = stoi(argv[i]);
    }
    // Create a vector to hold the solution sequence.
    vector<State> soln;
    int iter = 0;
    int heur = 1; // 0 for misplaced, 1 for manhattan heuristic.

    auto start = high_resolution_clock::now();
    soln = Puzzle(size, numbers, algo).solve(iter, heur);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);    

    // Print solution
    for_each(soln.cbegin(), soln.cend(), [](State s) {printState(&s);});
    // Print total iteration
    cout<<"Number of moved tiles  = "<< soln.size() - 1 << endl;
    cout << "Total Iteration For Solution = " << iter << endl;
    cout << "Total time consumed to solve the problem = " << duration.count() << " miliseconds " << endl;

    State a = State(size, numbers);
    int anothernumbers[] = {3,5,8,4,0,1,7,2,6};
    State b = State(size, anothernumbers);
    /*cout << "Misplaced Cost = " << heuristicMisplaced(a, b) << endl;
    cout << "Manhattan Cost = " << heuristicManhattan(a, b) << endl;*/

}
