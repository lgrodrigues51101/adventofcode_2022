#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int face_off(char adv, char me, map<char, char> win)
{
    int value = int(me) - 87;
    if (int(adv) - 64 == value)
        return 3 + value; // draw
    if (win[adv] == me)
        return 6 + value; // win
    return value;         // lose
}

int chose_play(char adv, char goal, map<char, char> win, map<char, char> lose)
{
    if (goal == 'X') // lose
    {
        return int(lose[adv]) - 87 + 0;
    }
    if (goal == 'Y') // draw
    {
        return int(adv) - 64 + 3;
    }
    if (goal == 'Z') // win
    {
        return int(win[adv]) - 87 + 6;
    }
    return -1;
}

int main()
{

    ifstream file("input");
    string line;

    map<char, char> win_map;
    win_map['A'] = 'Y';
    win_map['B'] = 'Z';
    win_map['C'] = 'X';

    map<char, char> lose_map;
    lose_map['A'] = 'Z';
    lose_map['B'] = 'X';
    lose_map['C'] = 'Y';

    int total_points = 0;

    while (getline(file, line))
    {
        string token = line.substr(0, 1);
        char adv = token[0];
        token = line.substr(2, 3);
        char goal = token[0];

        // total_points += face_off(adv, me, win_map);

        total_points += chose_play(adv, goal, win_map, lose_map);
    }

    cout << "Total point: " << total_points << endl;
}