
#include "classes.h"

void printState(State *s);

int main(int argc, char **argv){
    int n = (int)argv[1][0] - (int)'0';
    int numbers[n*n];
    // Get input numbers from user.
    for (int i = 0; i < n*n; i++) {
        numbers[i] = stoi(argv[i+2]);
    }
    // Create the initial state.
    State a = State(n, numbers);
    printState(&a);

    // Print successors
    vector<State> st = a.findSuccessors();
    cout<<"Size of vector = "<< st.size() << endl;
    for_each(st.cbegin(), st.cend(), [](State s) {printState(&s);});
    
    return 0;
}

void printState(State *s){
    for (int i = 0; i < s->size; i++) {
        for (int j = 0; j < s->size; j++) {
            cout << s->board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-------------" << endl;
 }