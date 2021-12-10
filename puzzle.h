#include "classes.h"
//#include "tempclasses.h"
void triggerSearch(int argc, int algo, char **argv);

void triggerSearch(int size, int algo, string *argv){
    int numbers[size*size];
    // Get input numbers from user.
    for (int i = 0; i < size*size; i++) {
        numbers[i] = stoi(argv[i]);
    }
    State s = State(size, numbers);
    /*vector<State> succ = findSuccessors(s);
    for_each(succ.cbegin(), succ.cend(), [](State s) {printState(&s);});*/

    vector<State> soln;
    if (algo == 1){
        soln = BreadthFirstSearch(size, numbers).search();
    }

    // Print solution
    cout<<"Size of vector = "<< soln.size() << endl;
    for_each(soln.cbegin(), soln.cend(), [](State s) {printState(&s);});
}
