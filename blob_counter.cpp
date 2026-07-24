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
    connected = stoi(argv[4]); // Defines 4-way or 8-way connectivity.
    
    vector<vector<int>> grid;
    fRead(infile, &grid);
    
    int Blobs = 0;
    int i,j;
    
    // Iterates through every cell in the grid.
    for(i = 0; i < row; i++){
        for(j = 0; j < column; j++){
            // If a '1' is found, a new blob is discovered.
            if(grid[i][j] == 1){
                // Recursively clears out the entire blob so it isn't counted twice.
                countingCells(&grid, row, column, i, j, connected);
                Blobs += 1;
            }
        }
    }
    // Outputs the total number of distinct blobs.
    cout << Blobs << '\n';
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

// Recursively consumes connected cells in a blob.
int countingCells(vector<vector<int>> * grid, int row, int column, int x, int y, int connected){
    // Base case: Out of bounds or hit a '0'.
    if(((x >= row) or (x < 0) or (y >= column) or (y < 0)) or ((*grid)[x][y] == 0)){
        return 0;
    }
    else{
        (*grid)[x][y] = 0; // "Consumes" the 1 by turning it into a 0 to prevent infinite loops.
    }

    // Recursively branches out in 4 directions.
    if(connected == 4){
        return 1 + countingCells(grid, row, column, x + 1, y, connected) + countingCells(grid, row, column, x - 1, y, connected) + countingCells(grid, row, column, x, y + 1, connected) + countingCells(grid, row, column, x, y - 1, connected);
    }
    // Recursively branches out in 8 directions (including diagonals).
    else{
        return 1 + countingCells(grid, row, column, x + 1, y + 1, connected) + countingCells(grid, row, column, x + 1, y, connected) + countingCells(grid, row, column, x + 1, y - 1, connected) + countingCells(grid, row, column, x, y + 1, connected) + countingCells(grid, row, column, x, y - 1, connected) + countingCells(grid, row, column, x - 1, y + 1, connected) + countingCells(grid, row, column, x - 1, y, connected) + countingCells(grid, row, column, x - 1, y - 1, connected);
    }
}