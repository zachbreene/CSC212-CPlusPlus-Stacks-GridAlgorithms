#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
using namespace std;

void fRead(string f_name, vector<vector<int>> * grid);
int countingCells(vector<vector<int>> * grid, int row, int column, int x, int y, int connected);

int main(int argc, char* argv[]){
    int row, column, x, y, connected;
    string infile = argv[1];
    row = stoi(argv[2]);
    column = stoi(argv[3]);
    
    // Adjusts coordinates to match 0-indexed arrays.
    x = stoi(argv[4]) - 1;
    y = stoi(argv[5]) - 1;
    connected = stoi(argv[6]); // 4-way or 8-way connectivity.

    vector<vector<int>> grid;
    fRead(infile, &grid);

    // Initiates the counting algorithm exactly at the target coordinate.
    int Cells;
    Cells = countingCells(&grid, row, column, x, y, connected);
    
    // Outputs the total size of the targeted blob.
    cout << Cells << '\n';
}

void fRead(string f_name, vector<vector<int>> * grid){
  string str;
  ifstream file(f_name);

  while (getline(file, str)){
    vector<int> rowCreate;
    istringstream ss(str);
    double tok;

    while(ss >> tok){
      rowCreate.push_back(tok);
    }
    grid -> push_back(rowCreate);
  }
}

// Recursively calculates the total number of connected 1s in a single blob.
int countingCells(vector<vector<int>> * grid, int row, int column, int x, int y, int connected){
    // Base case: Out of bounds or hit an empty space (0).
    if(((x >= row) or (x < 0) or (y >= column) or (y < 0)) or ((*grid)[x][y] == 0)){
        return 0;
    }
    else{
        (*grid)[x][y] = 0; // Turns the 1 into a 0 so it isn't double-counted.
    }

    // Accumulates size using 4-way connection rules.
    if(connected == 4){
        return 1 + countingCells(grid, row, column, x + 1, y, connected) + countingCells(grid, row, column, x - 1, y, connected) + countingCells(grid, row, column, x, y + 1, connected) + countingCells(grid, row, column, x, y - 1, connected);
    }
    // Accumulates size using 8-way connection rules.
    else{
        return 1 + countingCells(grid, row, column, x + 1, y + 1, connected) + countingCells(grid, row, column, x + 1, y, connected) + countingCells(grid, row, column, x + 1, y - 1, connected) + countingCells(grid, row, column, x, y + 1, connected) + countingCells(grid, row, column, x, y - 1, connected) + countingCells(grid, row, column, x - 1, y + 1, connected) + countingCells(grid, row, column, x - 1, y, connected) + countingCells(grid, row, column, x - 1, y - 1, connected);
    }
}