#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <unistd.h>

using namespace std;

///////////////////////////////////////////////////////// NODE CLASS DEFINITION /////////////////////////////////////////////////////////
class Node {
    public:
        Node();
        Node(int, int[]);
        //~Node();
        int size; 
        int* nums;
        int** board;
        int** boardFromNUmbers(int, int*);

};

Node::Node() {
    // Default constructor.
}

Node::Node( int n, int numbers[] ) {
    this->size = n;
    this->nums = new int[this->size*this->size];
    for (int i = 0; i < this->size*this->size; i++){
      this->nums[i] = numbers[i];
    }
    // Create a 2d array which represents the puzzle board with size n*n
    this->board = boardFromNUmbers(this->size, this->nums);
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
    return board;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////// STATE CLASS DEFINITION /////////////////////////////////////////////////////////
class State  : public Node {
    public:
        State();
        State(const State &);
        State(int, int[]);
        // ~State();
        State* predecessor;
        int depth;
        void setPredecessor();
        void setPredecessor(State &s);
        bool operator== (State & other) {
            for (int i = 0; i < size*size; i++){
                if (this->nums[i] != other.nums[i])
                    return false;
            }
            return true;
        }
};

State::State():Node() {
    // Default constructor.
    depth = 0;
}

State::State(const State &obj):Node() {
    this->size = obj.size;
    this->nums = new int[obj.size];
    this->nums = obj.nums;
    this->board = boardFromNUmbers(this->size, this->nums);
    predecessor = obj.predecessor;
    depth = obj.depth;
}

State::State( int n, int numbers[] ):Node(n, numbers) {
    // Constructor calls Node constructor here.
    //size = n;
    //nums = numbers;
    //predecessor = this;
    depth = 0;
}

/*State::~State() {
    delete[] predecessor;
}*/

void State::setPredecessor() {

    predecessor = this;
}

void State::setPredecessor(State &s) {
    predecessor = &s;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printState(State *s);
void showq(queue<State*> gq);

void printState(State *s){
  for (int i = 0; i < s->size; i++) {
      for (int j = 0; j < s->size; j++) {
          cout << s->board[i][j] << " ";
      }
      cout << endl;
  }
  cout << "-------------" << endl;
 }

 // Print the queue
void showq(queue<State> gq)
{
    queue<State> g = gq;
    while (!(g.empty())) {
        printState(&g.front());
        g.pop();
    }
}
 
///////////////////////////////////////////////////////// SEARCH CLASS DEFINITION /////////////////////////////////////////////////////////
class Puzzle {
    public:
        Puzzle(int n, int numbers[], int algo);
        int size;
        int* numbers;
        int algo;
        void findIndex(State &, int *, int *, int);
        void swapElementes(int*, int, int, int, int, int);
        vector<State> findSuccessors(State);
        vector<State> solve(int &);
        vector<State> BreadthFirstSearch(int &);
        vector<State> DepthFirstSearch(int &, float deepness = numeric_limits<double>::infinity());
        vector<State> IterativeDeepeningSearch(int &iter);
};

Puzzle::Puzzle(int n, int numbers[], int algo) {
    this->size = n;
    this->numbers = new int[this->size * this->size];
    this->numbers = numbers;
    this->algo = algo;
}

void Puzzle::findIndex(State & s, int *first, int *second, int elem) {
    for (int i=0; i<s.size; i++) {
        for (int j=0; j<s.size; j++) {
            if (s.board[i][j] == elem){
                *first = i;
                *second = j;
                return;
            } 
        }
    }    
}

void Puzzle::swapElementes(int* arr, int i, int j, int a, int b, int size) {
    swap(arr[size*i + j], arr[size*a + b]);
}

vector<State> Puzzle::findSuccessors(State s) {
    int size = s.size;
    // Create successors vector.
    vector<State> succ;
    // Find the index of element "0" on the board.
    int first = 0;
    int second = 0;
    findIndex(s, &first, &second, 0);
    // Find the elements on the board that are neighbour with the element "0".
    // There can be maximum 4 swaps with element "0". Find these four possibile moves and ignore the illegal ones.
    int tempNums[size*size];
    for (int i = -1; i<=1; i+=2){
        if (first+i >= 0 && first+i < size){
            copy(s.nums, (s.nums)+(size*size), tempNums);
            // Swap elements, create states and add to the vector.
            swapElementes(tempNums, first, second, first+i, second, size);
            succ.push_back(State(size, tempNums));
        }
        if (second+i >= 0 && second+i < size){
            //int tempNums[size*size];
            copy(s.nums, (s.nums)+(size*size), tempNums);
            // Swap elements, create states and add to the vector.d);
            swapElementes(tempNums, first, second, first, second+i, size);
            succ.push_back(State(size, tempNums));
        }        
    }
    return succ;
}

vector<State> Puzzle::solve(int &iter) {
    if (algo == 0)
        return BreadthFirstSearch(iter);
    else if (algo == 1)
        return DepthFirstSearch(iter);
    else if (algo == 2)
        return IterativeDeepeningSearch(iter);

}

vector<State> Puzzle::BreadthFirstSearch(int &iter) {
    // Create goal state for given size.
    int goalNumbers[size*size];
    for (int i = 0; i < size*size - 1; i++) {
        goalNumbers[i] = i+1;
    }
    goalNumbers[size*size - 1] = 0;
    int flag = 0;

    vector<State> solution;
    list<State> visited;
    queue<State> toBeExplored;


    State goalState = State(size, goalNumbers);
    State currentState = State(this->size, this->numbers);

    if (currentState == goalState){
        solution.push_back(currentState);
        return solution;
    }
    // Optionally print a board view of current state.
    //printState(&currentState);

    visited.push_back(currentState);
    visited.back().setPredecessor();

    vector<State> s = findSuccessors(currentState);

    for (auto& it : s) {
        toBeExplored.push(it);
        toBeExplored.back().setPredecessor(visited.back());
    }

    while (!toBeExplored.empty()) {
        iter++;
        cout << "ITERATION : " << iter << endl;

        currentState = toBeExplored.front();
        toBeExplored.pop();
        visited.push_back(currentState);

        if (currentState == goalState){
            cout << "ENTERED GOAL STATE 1" << endl;
            State* check; 
            check = &(visited.back());
            solution.push_back(*check);
            while (check->predecessor != check) {
                check = check->predecessor;
                solution.push_back(*check);
            }
            return solution;
        }

        vector<State> succ = findSuccessors(currentState);
        for (auto& it : succ) {
            if (it == goalState){
                it.setPredecessor(visited.back());
                cout << "ENTERED GOAL STATE 2" << endl;
                solution.push_back(it);
                State *sPtr;
                sPtr = &it;
                while (sPtr->predecessor != sPtr) {
                    sPtr = sPtr->predecessor;
                    solution.push_back(*sPtr);
                }
                return solution;
            }
            else {;
                for (auto& v : visited) {
                    if (v == it) {
                        flag = 1;
                        break;
                    }
                }              
                if (flag==0){
                    it.setPredecessor(visited.back());
                    toBeExplored.push(it);
                }
                flag = 0;
            }
        }
    }
    
    return solution;
}

vector<State> Puzzle::DepthFirstSearch(int &iter, float maxDeepness) {
    // Create goal state for given size.
    int goalNumbers[size*size];
    for (int i = 0; i < size*size - 1; i++) {
        goalNumbers[i] = i+1;
    }
    goalNumbers[size*size - 1] = 0;
    int flag = 0;

    vector<State> solution;
    list<State> visited;
    stack<State> toBeExplored;

    State goalState = State(size, goalNumbers);
    State currentState = State(this->size, this->numbers);
    currentState.depth = 0;

    if (currentState == goalState){
        solution.push_back(currentState);
        return solution;
    }
    // Optionally print a board view of current state.
    //printState(&currentState);

    visited.push_back(currentState);
    visited.back().setPredecessor();

    vector<State> s = findSuccessors(currentState);

    for (auto& it : s) {
        it.setPredecessor(visited.back());
        it.depth = currentState.depth + 1;
        toBeExplored.push(it);
    }

    while (!toBeExplored.empty()) {
        iter++;
        cout << "ITERATION : " << iter << endl;

        currentState = toBeExplored.top();
        toBeExplored.pop();
        visited.push_back(currentState);

        if (currentState == goalState){
            cout << "ENTERED GOAL STATE 1" << endl;
            State* check; 
            check = &(visited.back());
            solution.push_back(*check);
            while (check->predecessor != check) {
                check = check->predecessor;
                solution.push_back(*check);
            }
            return solution;
        }
        // If current state is in max deepness, don't add its successors to the stack.
        if (currentState.depth < maxDeepness){
            vector<State> succ = findSuccessors(currentState);
            for (auto& it : succ) {
                it.depth = currentState.depth + 1;
                if (it == goalState){
                    it.setPredecessor(visited.back());
                    cout << "ENTERED GOAL STATE 2" << endl;
                    solution.push_back(it);
                    State *sPtr;
                    sPtr = &it;
                    while (sPtr->predecessor != sPtr) {
                        sPtr = sPtr->predecessor;
                        solution.push_back(*sPtr);
                    }
                    return solution;
                }
                else {;
                    for (auto& v : visited) {
                        if (v == it) {
                            flag = 1;
                            break;
                        }
                    }              
                    if (flag==0){
                        it.setPredecessor(visited.back());
                        toBeExplored.push(it);
                    }
                    flag = 0;
                }
            }
        }
    }
    
    return solution;
}


vector<State> Puzzle::IterativeDeepeningSearch(int &iter) {
    // Call DepthFirstSearch by incrementing the deepness value each time.
    int deepness = 0;
    vector<State> solution;
    while (solution.size() == 0) {
        deepness++;
        solution = DepthFirstSearch(iter, deepness);
    }

    return solution;
}