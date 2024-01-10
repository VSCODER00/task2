
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool isValidMove(int row, int col, int numRows, int numCols, const vector<vector<char>> &labyrinth, vector<vector<bool>> &visited)
{
    return (row >= 0 && row < numRows && col >= 0 && col < numCols && labyrinth[row][col] == '.' && !visited[row][col]);
}

int DFS(int row, int col, int count, vector<vector<char>> &labyrinth, vector<vector<bool>> &visited)
{
    visited[row][col] = true;
    labyrinth[row][col] = '0' + count;

    int numRows = labyrinth.size();
    int numCols = labyrinth[0].size();

    int maxCount = count;

    int moves[8][2] = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};

    for (int i = 0; i < 8; ++i)
    {
        int newRow = row + moves[i][0];
        int newCol = col + moves[i][1];

        if (isValidMove(newRow, newCol, numRows, numCols, labyrinth, visited))
        {
            maxCount = max(maxCount, DFS(newRow, newCol, count + 1, labyrinth, visited));
        }
    }

    visited[row][col] = false;
    return maxCount;
}

int findLargestPathway(vector<vector<char>> &labyrinth)
{
    int numRows = labyrinth.size();
    int numCols = labyrinth[0].size();

    vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));

    int maxLength = 0;

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            if (labyrinth[i][j] == '.' && !visited[i][j])
            {
                int length = DFS(i, j, 1, labyrinth, visited);
                maxLength = max(maxLength, length);
            }
        }
    }

    return maxLength;
}

int main()
{
    ifstream inputFile("labyrinth_input.txt");

    int numRows, numCols;
    inputFile >> numRows >> numCols;

    vector<vector<char>> labyrinth(numRows, vector<char>(numCols));

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            inputFile >> labyrinth[i][j];
        }
    }

    inputFile.close();

    int maxLength = findLargestPathway(labyrinth);

    if (maxLength > 0)
    {
        cout << maxLength << endl;

        for (int i = 0; i < numRows; ++i)
        {
            for (int j = 0; j < numCols; ++j)
            {
                cout << labyrinth[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << -1 << endl;
    }

    return 0;
}
