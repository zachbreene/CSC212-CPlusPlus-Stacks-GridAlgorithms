#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <utility>
using namespace std;

bool opIsOp(string Op);
void stackFunc(stack<char> * inStack, char op);
void parentheseStack(stack<char> * inStack);

int main(int argc, char* argv[]){
    // Reads the standard infix equation from command line.
    istringstream ss(argv[1]);
    stack<char> Stack;
    string str;

    // Applies the Shunting Yard algorithm to sort numbers and operators.
    while(ss >> str){
        if(str[0] == '('){
            Stack.push(str[0]); // Push open parentheses to the stack.
        }
        else if(opIsOp(str)){
            stackFunc(&Stack, str[0]); // Process operators based on precedence.
        }
        else if(str[0] == ')'){
            parentheseStack(&Stack); // Resolve everything inside the parentheses.
        }
        else{
            cout << str << " "; // Output numbers immediately.
        }
    }
    
    // Empty the remaining operators from the stack to the output.
    while((!Stack.empty()) and (Stack.size() != 1)){
        cout << Stack.top() << " ";
        Stack.pop();
    }
    while(!Stack.empty()){
        cout << Stack.top();
        Stack.pop();
    }
    cout << '\n';
}

// Validates if the token is a supported operator.
bool opIsOp(string Op){
    char PEMDAS[6] = {'(','^','*','/','+','-'};
    int i;
    for(i = 0; i < 6; i++){
        if((Op.length() == 1) and (Op[0] == PEMDAS[i])){
            return true;
        }
    }
    return false;
}

// Pops and outputs operators until the matching open parenthesis is found.
void parentheseStack(stack<char> * inStack){
    while(inStack -> top() != '('){
        cout << inStack -> top() << " ";
        inStack -> pop();
    }
    inStack -> pop(); // Discard the open parenthesis.
}

// Determines operator precedence and pushes/pops accordingly to maintain PEMDAS.
void stackFunc(stack<char> * inStack, char op){
    if(inStack -> empty()){
        inStack -> push(op);
        return;
    }
    int i, oper, top;
    char PEMDAS[6] = {'^','*','/','-','+', '('};
    
    // Assigns numerical precedence values to operators.
    for(i = 0; i < 6; i++){
        if(inStack -> top() == PEMDAS[i]){
            top = (i + 1) / 2;
        }
        if(op == PEMDAS[i]){
            oper = (i + 1) / 2;
        }
    }
    
    // If incoming operator is lower or equal precedence, pop the top operator first.
    if((oper >= top) and (oper != 0)){
        cout << inStack -> top() << " ";
        inStack -> pop();
        stackFunc(inStack, op); // Recursively check the next top item.
    }
    else{
        inStack -> push(op);
    }
}