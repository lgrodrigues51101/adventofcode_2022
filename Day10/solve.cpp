#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int cycle = 0;
int X = 1;
int sum_strenght = 0;

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

void update_cycle()
{
    cycle++;
    if (cycle == 20 || (cycle - 20) % 40 == 0)
    {
        int signal_s = cycle*X;
        sum_strenght += signal_s;
        cout << "(cycle " << cycle << ")Current signal strenght : " << signal_s << endl;
    }
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
    cout << sum_strenght << endl;
}