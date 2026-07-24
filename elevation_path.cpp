#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
using namespace std;

bool findGoodPath(vector<vector<int>> * grid, vector<vector<int>> * previousVisit, int row, int column, int x1, int y1, int x2, int y2, int x3, int y3);
void fRead(string f_name, vector<vector<int>> * grid, vector<vector<int>> * previousVisit);

int main(int argc, char* argv[]){
    int row, column, x, y, minVar, maxVar;
    string infile = argv[1];
    row = stoi(argv[2]);
    column = stoi(argv[3]);
    vector<vector<int>> grid;
    vector<vector<int>> previousVisit;

    fRead(infile, &grid, &previousVisit);
    pair<int, int> min = make_pair(0,0);
    pair<int, int> max = make_pair(0,0);
    minVar = grid[0][0];
    maxVar = grid[0][0];

    // Scans the grid to locate the absolute lowest and highest elevation coordinates.
    int i,j;
    for(i = 0; i < row; i++){
        for(j = 0; j < column; j++){
            if(grid[i][j] < minVar){
                minVar = grid[i][j];
                min.first = i;
                min.second = j;
            }
            if(grid[i][j] > maxVar){
                maxVar = grid[i][j];
                max.first = i;
                max.second = j;
            }
        }
    }
    
    // Initiates the recursive search to find a valid path.
    bool goodPath = findGoodPath(&grid, &previousVisit, row, column, min.first, min.second, -1, -1, max.first, max.second);
    
    // Outputs the start and end coordinates, plus 'yes' or 'no' depending on path success.
    if(goodPath == true){
        cout << min.first + 1 << " " << min.second + 1 << " " << max.first + 1 << " " << max.second + 1 << " yes" << '\n';
    }
    else{
        cout << min.first + 1 << " " << min.second + 1 << " " << max.first + 1 << " " << max.second + 1 << " no" << '\n';
    }
}

// Recursive Depth-First Search to find a path that never decreases in elevation.
bool findGoodPath(vector<vector<int>> * grid, vector<vector<int>> * previousVisit, int row, int column, int x1, int y1, int x2, int y2, int x3, int y3){
    (*previousVisit)[x1][y1] = 1; // Mark current cell as visited.
    
    // Base case: Reached the highest elevation point.
    if((x1 == x3) && (y1 == y3)){
        return true;
    }
    
    bool u, d, l, r;
    // Check bounds, ensure elevation is >= current, and ensure cell is unvisited for all 4 directions.
    u = ((((x1-1) != x2) && ((x1-1) >= 0) && ((*grid)[x1-1][y1] >= (*grid)[x1][y1])) && ((*previousVisit)[x1-1][y1] == 0));
    d = ((((x1+1) != x2) && ((x1+1) < row) && ((*grid)[x1+1][y1] >= (*grid)[x1][y1])) && ((*previousVisit)[x1+1][y1] == 0));
    l = ((((y1-1) != y2) && ((y1-1) >= 0) && ((*grid)[x1][y1-1] >= (*grid)[x1][y1])) && ((*previousVisit)[x1][y1-1] == 0));
    r = ((((y1+1) != y2) && ((y1+1) < column) && ((*grid)[x1][y1+1] >= (*grid)[x1][y1])) && ((*previousVisit)[x1][y1+1] == 0));
    
    // Recursively step into valid adjacent cells.
    if((u) && (findGoodPath(grid, previousVisit, row, column, x1-1, y1, x1, y1, x3, y3))) return true;
    if((d) && (findGoodPath(grid, previousVisit, row, column, x1+1, y1, x1, y1, x3, y3))) return true;
    if((l) && (findGoodPath(grid, previousVisit, row, column, x1, y1-1, x1, y1, x3, y3))) return true;
    if((r) && (findGoodPath(grid, previousVisit, row, column, x1, y1+1, x1, y1, x3, y3))) return true;
    
    return false; // Dead end.
}

// Reads the space-separated matrix from a text file.
void fRead(string f_name, vector<vector<int>> * grid, vector<vector<int>> * previousVisit){
  string str;
  ifstream file(f_name);

  while (getline(file, str)){
    vector<int> rowCreate;
    vector<int> zeroRow;
    istringstream ss(str);
    double tok;

    while(ss >> tok) {
      rowCreate.push_back(tok);
      zeroRow.push_back(0); // Builds a blank parallel tracking grid full of zeros.
    }

    grid -> push_back(rowCreate);
    previousVisit -> push_back(zeroRow);
  }
}