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

    int scenic_score, l_score, r_score, t_score, b_score;

    int final_s_score = 0;

    for (size_t i = 1; i < l - 1; i++)
    {
        for (size_t j = 1; j < c - 1; j++)
        {
            scenic_score = 0;
            l_score = 0;
            r_score = 0;
            t_score = 0;
            b_score = 0;

            // cout << "(" << i << "," << j << ")" << endl;
            for (int w = j - 1; w >= 0; w--) // check left
            {
                // cout << grid[i][j] << " " << grid[i][w] << endl;
                if (grid[i][j] > grid[i][w])
                {
                    l_score++;
                }
                else
                {
                    l_score++;
                    break;
                }
            }
            // cout << "\tleft score : " << l_score << endl;

            for (int w = j + 1; w < c; w++) // check right
            {
                if (grid[i][j] > grid[i][w])
                {
                    r_score++;
                }
                else
                {
                    r_score++;
                    break;
                }
            }
            // cout << "\tright score : " << r_score << endl;

            for (int w = i-1; w >= 0; w--) // check top
            {
                if (grid[i][j] > grid[w][j])
                {
                    t_score++;
                }
                else
                {
                    t_score++;
                    break;
                }
            }
            // cout << "\ttop score : " << t_score << endl;

            for (int w = i + 1; w < l; w++) // check bottom
            {
                if (grid[i][j] > grid[w][j])
                {
                    b_score++;
                }
                else
                {
                    b_score++;
                    break;
                }
            }
            // cout << "\tbot score : " << b_score << endl;

            scenic_score = l_score * r_score * t_score * b_score;
            final_s_score =  scenic_score > final_s_score ? scenic_score : final_s_score;
        }
    }
    cout << "Final score : " << final_s_score << endl;
}