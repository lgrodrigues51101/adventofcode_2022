#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

int MAX_STACK_SIZE = 9;

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

void print_stack(stack<char> stack)
{
    while (!stack.empty())
    {
        cout << stack.top() << endl;
        stack.pop();
    }
}

int main()
{
    ifstream file("input");
    string line;

    stack<char> r_stack[MAX_STACK_SIZE];
    stack<char> stacks[MAX_STACK_SIZE];

    while (getline(file, line))
    {
        if (line.find("[") == string::npos)
        {
            getline(file, line);
            // invert stacks
            for (size_t i = 0; i < MAX_STACK_SIZE; i++)
            {
                while (!r_stack[i].empty())
                {
                    stacks[i].push(r_stack[i].top());
                    r_stack[i].pop();
                }
            }
            cout << "finished parsing stack" << endl;
            break;
        }

        int stack_index = 0;
        for (size_t i = 0; i < line.length(); i = i + 4)
        {
            string token = line.substr(i, 3);

            if (token.find("[") != string::npos)
            {
                r_stack[stack_index].push(token[1]);
            }
            stack_index++;
        }
    }

    while (getline(file, line))
    {
        int reps, from, dest;

        string token1;
        int pos = 0;
        string delim = " ";
        int index = 0;

        vector<string> substr = split(line, " ");
        reps = stoi(substr[1]);
        from = stoi(substr[3]);
        dest = stoi(substr[5]);

        stack<char> aux;
        for (size_t i = 0; i < reps; i++)
        {
            aux.push(stacks[from - 1].top());
            stacks[from - 1].pop();
        }

        for (size_t i = 0; i < reps; i++)
        {
            stacks[dest - 1].push(aux.top());
            aux.pop();
        }
    }

    for (size_t i = 0; i < MAX_STACK_SIZE; i++)
    {
        cout << stacks[i].top();
    }
    cout << endl;
}