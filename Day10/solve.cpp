#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int cycle = 0;
int X = 1;
string crt = "";

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

void print_sprite()
{
    string s = "";
    for (size_t i = 0; i < 40; i++)
    {
        s += '.';
    }
    if (X >= 0)
    {
        s[X] = '#';
        if (X - 1 >= 0)
        {
            s[X - 1] = '#';
        }
        if (X + 1 < 40)
        {
            s[X + 1] = '#';
        }
    }
    cout << "X value = " << X << endl;
    cout << "Sprite position: " << s << endl;
}

void print_crt()
{
    cout << crt << endl;
}

void update_cycle()
{
    int rest = cycle % 40;
    if (rest == 0)
    {
        crt += '\n';
    }

    if (rest == X || rest == X + 1 || rest == X - 1)
    {
        crt += '#';
    }
    else
    {
        crt += '.';
    }
    cycle++;
}

int main()
{
    ifstream file("input");
    string line;

    int signal_strenght;

    while (getline(file, line))
    {
        vector<string> token = split(line, " ");
        int add = 0;
        if (token[0] == "noop")
        {
            // do nothing
        }
        else if (token[0] == "addx")
        {
            add = stoi(token[1]);
        }

        update_cycle();

        if (token[0] == "addx")
        {
            update_cycle();
            X += add;
        }
    }
    print_crt();
}