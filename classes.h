#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <vector>

using namespace std;

///////////////////////////////////////////////////////// NODE CLASS DEFINITION /////////////////////////////////////////////////////////
class Node {
    public:
        Node(int, int[]);
        //~Node();
        int size; 
        int* nums;
        int** board;
        int** boardFromNUmbers(int, int*);

};

Node::Node( int n, int numbers[] ) {
    size = n;
    nums = numbers;
    // Create a 2d array which represents the puzzle board with size n*n
    boardFromNUmbers(size, numbers);

}

/*Node::~Node() {
    delete [] board;
}*/

int** Node::boardFromNUmbers(int n, int numbers[] ) {
    board = new int*[n];
    for (int i = 0; i < n; i++) {
        board[i] = new int[n];
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = numbers[count];
            count++;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////// STATE CLASS DEFINITION /////////////////////////////////////////////////////////
class State  : public Node {
    public:
        State(int, int[]);
        State* predecessor;
        void findIndex(int *i, int *j, int elem);
        void swapElementes(int* arr, int i, int j, int a, int b);
        vector<State> findSuccessors();
        void setPredecessor(State s);
};

State::State( int n, int numbers[] ):Node(n, numbers) {
    // Constructor calls Node constructor here.
}

void State::setPredecessor(State s) {
    predecessor = &s;
}

void State::findIndex(int *first, int *second, int elem) {
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            if (board[i][j] == elem){
                *first = i;
                *second = j;
                return;
            } 
        }
    }    
}

void State::swapElementes(int* arr, int i, int j, int a, int b) {
    copy(nums, nums+(size*size), arr);
    swap(arr[size*i + j], arr[size*a + b]);
}

vector<State> State::findSuccessors() {
    // Create successors vector.
    vector<State> succ;
    // Find the index of element "0" on the board.
    int first = 0;
    int second = 0;
    this->findIndex(&first, &second, 0);
    // Find the elements on the board that are neighbour with the element "0".
    // There can be maximum 4 swaps with element "0". Find these four possibile moves and ignore the illegal ones.
    for (int i = -1; i<=1; i+=2){
        if (first+i >= 0 && first+i < size){
            cout<<"i = "<<first+i<<" j = "<<second<< endl;
            int tempNums[size*size];
            copy(nums, nums+(size*size), tempNums);
            // Swap elements, create states and add to the vector.
            swapElementes(tempNums, first, second, first+i, second);
            succ.push_back(State(size, tempNums));
        }
        if (second+i >= 0 && second+i < size){
            cout<<"i = "<<first<<" j = "<<second+i<< endl;
            int tempNums[size*size];
            copy(nums, nums+(size*size), tempNums);
            // Swap elements, create states and add to the vector.d);
            swapElementes(tempNums, first, second, first, second+i);
            succ.push_back(State(size, tempNums));
        }        
    }
    return succ;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////// SEARCH CLASS DEFINITION /////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////