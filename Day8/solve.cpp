#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream file("input");
    string line;

    int l = 0;
    int c = 0;
    while (getline(file, line))
    {
        c = line.length();
        l++;
    }
    cout << "grid size " << l << "X" << c << endl;

    int grid[l][c];

    file.clear();
    file.seekg(ios::beg);
    l = 0;
    while (getline(file, line))
    {
        for (size_t i = 0; i < line.length(); i++)
        {
            grid[l][i] = line[i] - '0';
        }
        l++;
    }

    // for (size_t i = 0; i < l; i++)
    // {
    //     for (size_t j = 0; j < c; j++)
    //     {
    //         cout << grid[i][j];
    //     }
    //     cout << endl;
    // }

    int v_trees = l * 2 + c * 2 - 4;

    for (size_t i = 1; i < l - 1; i++)
    {
        for (size_t j = 1; j < c - 1; j++)
        {
            bool visible = true;
            for (size_t w = 0; w < j; w++) // check left
            {
                // cout << grid[i][j] << " " << grid[i][w] << endl;
                visible = visible && grid[i][j] > grid[i][w];
            }

            if (!visible)
            {
                visible = true;
                for (size_t w = j + 1; w < c; w++) // check right
                {
                    visible = visible && grid[i][j] > grid[i][w];
                }
            }

            if (!visible)
            {
                visible = true;
                for (size_t w = 0; w < i; w++) // check top
                {
                    visible = visible && grid[i][j] > grid[w][j];
                }
            }

            if (!visible)
            {
                visible = true;
                for (size_t w = i + 1; w < l; w++) // check bottom
                {
                    visible = visible && grid[i][j] > grid[w][j];
                }
            }

            if (visible)
            {
                v_trees++;
            }
        }
    }
    cout << "Visible Trees : " << v_trees << endl;
}