#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>
using namespace std;

int cord_size = 10;

class cord
{
public:
    int x;
    int y;
    cord()
    {
        x = 0;
        y = 0;
    }
    cord(int c_x, int c_y)
    {
        x = c_x;
        y = c_y;
    }
    bool operator==(const cord &other) const
    {
        return x == other.x && y == other.y;
    }
    struct HasFunction
    {
        size_t operator()(const cord &k) const
        {
            return hash<int>()(k.x) ^ (hash<int>()(k.y) << 1);
        }
    };
    string to_string()
    {
        return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
    }
    int euclidian_distance(cord other)
    {
        return sqrt(abs(pow(other.x - x, 2) + pow(other.y - y, 2)));
    }
    cord copy()
    {
        return cord(x, y);
    }
};

vector<string> split(string str, string delimiter)
{
    vector<string> res;
    size_t pos = str.find(delimiter);

    while (pos != string::npos)
    {
        string token = str.substr(0, pos);
        res.push_back(token);
        str.erase(0, pos + delimiter.length());
        pos = str.find(delimiter);
    }
    res.push_back(str);
    return res;
}

void update(cord *head, string move)
{
    if (move.find("R") != string::npos)
    {
        head->x++;
    }
    else if (move.find("L") != string::npos)
    {
        head->x--;
    }

    if (move.find("U") != string::npos)
    {
        head->y++;
    }
    else if (move.find("D") != string::npos)
    {
        head->y--;
    }
}

void print_board(cord knots[]) // TODO
{
    int max_x = 20;
    int max_y = 20;
    int min_x = -max_x;
    int min_y = -max_y;

    string s = "";

    for (int i = max_y; i >= min_y; i--)
    {
        for (int j = min_x; j <= max_x; j++)
        {
            bool found = false;
            for (int w = 0; w < cord_size; w++)
            {
                if (j == knots[w].x && i == knots[w].y)
                {
                    s += 'H';
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                if (j == 0 && i == 0)
                {
                    s += 's';
                }
                else
                {
                    s += '.';
                }
            }
        }
        s += '\n';
    }
    cout << s << endl;
}

int main()
{
    ifstream file("input");
    string line;

    unordered_set<cord, cord::HasFunction> tail_visited;
    cord knots[cord_size];

    while (getline(file, line))
    {
        vector<string> tokens = split(line, " ");
        int reps = stoi(tokens[1]);
        string move = tokens[0];

        // cout << "== " << line << " ==" << endl;

        for (size_t i = 0; i < reps; i++)
        {
            update(&knots[0], move); // move only head

            for (size_t i = 1; i < cord_size; i++)
            {
                if (knots[i].euclidian_distance(knots[i - 1]) > 1)
                {
                    string tail_move = "";
                    if (knots[i - 1].y > knots[i].y)
                    {
                        tail_move += "U";
                    }
                    if (knots[i - 1].y < knots[i].y)
                    {
                        tail_move += "D";
                    }
                    if (knots[i - 1].x > knots[i].x)
                    {
                        tail_move += "R";
                    }
                    if (knots[i - 1].x < knots[i].x)
                    {
                        tail_move += "L";
                    }
                    update(&knots[i], tail_move);
                }
            }
            tail_visited.insert(knots[cord_size - 1]); // save tail cord
        }
        // cout << "Head: " << knots[0].to_string() << "; Tail: " << knots[cord_size - 1].to_string() << endl;
        // print_board(knots);
    }

    cout << "Total cords visited by tail : " << tail_visited.size() << endl;
}