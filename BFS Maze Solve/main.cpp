//  Copyright Chase Clarke cfclarke@bu.edu 
/*
 To solve this problem:
    • I first imported the text file and entered its contents into a 2d array.
    • I then execute BFS on the array to find the shortest path:
        - This is done with 1) a queue, 2) an additional 2d vector with identical dimensions to the text file that is used to check if visited
            and 3) a node struct 'pointDist' that holds the location of the node and its distance to (0,0).
        - A for loop is then run checking if there is a valid adjacent node above, below, right or left of current location. nodes are added
            to queue as they are visited along with their distance (distance is increment by one each time adjacencies are checked).
        - If the bottom right node is found at the head of the queue, the node distance is the length of the shortest path.
    • Done!
 
 
 Challenge:
    Consider a 2D array of 1s and 0s of size NxN. The array is a "maze." You must start
 from the top left (index (0,0)) and find the length of the shortest path to the bottom
 right (index (n-1,n-1)). You may only travel across elements that have value "1". The
 top left and bottom right indices are guaranteed to be "1". You may only move
 horizontally or vertically one index position with each step (both left-right and updown).
 
 Runtime: O(n^2) because it is an NxN matrix and we are using Breadth-First-Search (BFS)
 Space complexity: Space needed for extra matrices
 
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <string.h>
#include <stdio.h>
#include <queue>
#include <utility>
int n = 0; // n*n size of maze

using namespace std;

struct pointDist
{
    pair<int,int> position;  // The cordinates of a cell
    int dist;  // cell's distance of from the source
};

void getn(string filename){
    //opens text file to determine n
    ifstream getSize(filename);
    string line = "";
    int count = 0;
    
    while (getline(getSize, line)) {
        if (count == 0) {
            n = line.length() - 1;
        } count++;
    } getSize.close(); //ensuring file is closed as it needs to be opened again
}

void print(int** mazeArr){
    //prints the contents of the imported array mazeArr
    cout << endl;
    for (int i = 0 ; i < n; i++) {
        for (int j = 0 ; j < n; j++) {
            cout << mazeArr[j][i];
        } cout << endl;
    }
}

int** readFile(string filename) {
    //enters 'maze.txt' contents into a 2D array mazeArr
    int col = 0;
    int **mazeArr = new int *[n]; //creating a one dimensional array
    
    for (int i = 0; i < n; i++) { //entering another array in each index of mazeArr to create 2D array
        mazeArr[i] = new int[n];
    }
    
    //re-opening file to read contents with correctly initialized mazeArr
    ifstream input(filename);
    string newline = "";
    
    //getting contents of 'maze.txt' line-by-line
    while (getline(input, newline)) {
        for (int row = 0 ; row < n; row++) {
            if (newline[row] != ' ') {
            mazeArr[row][col] = stoi(string(1, newline[row]));
            //cout << "added: " << newline[row] << " at location: " << row << " x " << col << endl;
            }
        } col++;
    } return mazeArr;
}

void findPath(int** mazeArr) {
    //finds the shortest path using BFS
    
    bool found = false;
    int distance = 0;
    pointDist position;
    pointDist tempPos;
    queue<pointDist> bfsQueue; //initializing the BFS queue containing NodePositions
    
    position.position.first = 0;
    position.position.second = 0; //making the initial position the top left
    position.dist = 0;
    bfsQueue.push(position);
    
    bool isVisited[n][n]; //initializing a 2d array with dimensions identical to mazeArr
    memset (isVisited, false, sizeof isVisited);//setting all values to false
    isVisited[position.position.first][position.position.second] = true; //acknowledging that the first node has been visited
    
    while (!bfsQueue.empty()) {
        position = bfsQueue.front(); //setting the current node = new position
        if (position.position.first == n-1 && position.position.second == n-1) { //found bottom right, exit algorithm
            cout << position.dist << endl;
            found = true;
            break;
        }
        //cout << "\nremoving: " << bfsQueue.front().position.first << "," << bfsQueue.front().position.second << endl;
        bfsQueue.pop(); //removing the node from the head of the queue

        for (int i = 0; i < 4; i++) { //checking all adjacent nodes
            if(i == 0) { //down
                tempPos.position.first = position.position.first;
                tempPos.position.second = position.position.second+1;
                tempPos.dist = position.dist+1;
                
                if (isVisited[tempPos.position.first][tempPos.position.second] == false  && tempPos.position.second <= n - 1) {
                    if (mazeArr[tempPos.position.first][tempPos.position.second] == 1) {
                        //cout << "in D: " << tempPos.position.first <<"," << tempPos.position.second << " dist: " << tempPos.dist << endl;
                        bfsQueue.push(tempPos);
                        isVisited[tempPos.position.first][tempPos.position.second] = true;
                    }
                }
            } else if(i == 1) { //up
                tempPos.position.first = position.position.first;
                tempPos.position.second = position.position.second-1;
                tempPos.dist = position.dist+1;
                
                if (isVisited[tempPos.position.first][tempPos.position.second] == false && tempPos.position.second >= 0) {
                    if (mazeArr[tempPos.position.first][tempPos.position.second] == 1) {
                        //cout << "in U: " << tempPos.position.first <<"," << tempPos.position.second << " dist: " << tempPos.dist << endl;
                        bfsQueue.push(tempPos);
                        isVisited[tempPos.position.first][tempPos.position.second] = true;
                    }
                }
            } else if(i == 2) { //left
                tempPos.position.first = position.position.first-1;
                tempPos.position.second = position.position.second;
                tempPos.dist = position.dist+1;

                if (isVisited[tempPos.position.first][tempPos.position.second] == false && tempPos.position.first >= 0) {
                    if (mazeArr[tempPos.position.first][tempPos.position.second] == 1) {
                        //cout << "in L: " << tempPos.position.first <<"," << tempPos.position.second << " dist: " << tempPos.dist << endl;
                        bfsQueue.push(tempPos);
                        isVisited[tempPos.position.first][tempPos.position.second] = true;
                    }
                }
            } else {// i == 3 -- right
                tempPos.position.first = position.position.first+1;
                tempPos.position.second = position.position.second;
                tempPos.dist = position.dist+1;
                
                if (isVisited[tempPos.position.first][tempPos.position.second] == false && tempPos.position.first <= n - 1) {
                    if (mazeArr[tempPos.position.first][tempPos.position.second] == 1) {
                        //cout << "in R: " << tempPos.position.first <<"," << tempPos.position.second << " dist: " << tempPos.dist << endl;
                        bfsQueue.push(tempPos);
                        isVisited[tempPos.position.first][tempPos.position.second] = true;
                    }
                }
            }
        }
    } if (found == false) {cout << "0\n";}
}



int main(int argc, char** argv){
    
    string filename = argv[1]; //getting the file name from the command line
    
    getn(filename); //finding the dimensions of the matrix n*n
    
    int** mazeArr; //initializing mazeArr
    mazeArr = readFile(filename); //using n to fill mazeArr with appropriate vaules

    //print(mazeArr);
    
    findPath(mazeArr); //determines the shortest path
    
    return 0;
}
