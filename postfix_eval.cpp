#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <cmath>
using namespace std;

bool opIsOp(string string);
int floorDivisionPos(int x);
int floorDivision(int x, int y);
void eval(stack<int> * inStack, char oper);

int main(int argc, char* argv[]){
    // Reads the postfix equation from the command line arguments.
    istringstream ss(argv[1]);
    stack<int> stack;
    string str;

    // Parses the equation token by token.
    while(ss >> str){
        if(!opIsOp(str)){
            // If it's a number, push it onto the stack.
            stack.push(stoi(str));
        }
        else{
            // If it's an operator, evaluate the top numbers on the stack.
            eval(&stack, str[0]);
        }
    }
    // Prints the final calculated result.
    while(!stack.empty()){
        cout << stack.top() << '\n';
        stack.pop();
    }
}

// Checks if the string token is a valid mathematical operator.
bool opIsOp(string string){
    char PEMDAS[6] = {'(','^','*','/','+','-'};
    int i;
    for(i = 0; i < 6; i++){
        if((string.length() == 1) and (string[0] == PEMDAS[i])){
            return true;
        }
    }
    return false;
}

// Helper function to return the absolute (positive) value for division.
int floorDivisionPos(int x){
    if(x < 0){
        x = x * -1;
    }
    return x;
}

// Custom floor division logic to handle negative numbers correctly.
int floorDivision(int x, int y, int total){
    if((floorDivisionPos(x) < floorDivisionPos(y)) and ((x < 0) or (y < 0))){
        total = x / y - 1;
    }
    else if((floorDivisionPos(x) < floorDivisionPos(y)) and ((x < 0) and (y < 0))){
        total = x / y;
    }
    else{
        total = x / y;
    }
    return total;
}

// Pops the top two numbers off the stack, applies the operator, and pushes the result.
void eval(stack<int> * inStack, char oper){
    int n1, n2;
    n1 = inStack -> top();
    inStack -> pop();
    n2 = inStack -> top();
    inStack -> pop();

    if(oper == '*'){
        int total = n2 * n1;
        inStack -> push(total);
    }
    else if(oper == '/'){
        int total = floorDivision(n2, n1, total);
        inStack -> push(total);
    }
    else if(oper == '+'){
        int total = n2 + n1;
        inStack -> push(total);
    }
    else if(oper == '-'){
        int total = n2 - n1;
        inStack -> push(total);
    }
    else{
        // Handles exponents (^).
        int i, total = 1;
        for(i = 0; i < n1; i++){
            total = total * n2;
        }
        inStack -> push(total);
    }
}