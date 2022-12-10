#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

int MAX_STACK_SIZE = 9;

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
    bool parse_stack = true;

    while (getline(file, line))
    {
        if (parse_stack && line.find("[") == string::npos)
        {
            parse_stack = false;
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
            continue;
        }

        if (parse_stack)
        {
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
        else
        {
            int reps, from, dest;

            string token1;
            int pos = 0;
            string delim = " ";
            int index = 0;
            while ((pos = line.find(delim)) != std::string::npos)
            {
                token1 = line.substr(0, pos); // store the substring
                // cout << token1 << endl;
                line.erase(0, pos + delim.length()); /* erase() function store the current positon and move to next token. */

                if (index == 1)
                {
                    // cout << "reps " << token1 << endl;
                    reps = stoi(token1);
                }
                else if (index == 3)
                {
                    // cout << "from " << token1 << endl;
                    from = stoi(token1);
                }
                index++;
            }

            // cout << "dest " << line << endl;
            dest = stoi(line);
            // cout << "Final " << reps << " " << from << " " << dest << " " << endl;

            stack<char> aux;
            for (size_t i = 0; i < reps; i++)
            {
                aux.push(stacks[from-1].top());
                stacks[from-1].pop();
            }

            for (size_t i = 0; i < reps; i++)
            {
                stacks[dest-1].push(aux.top());
                aux.pop();
            }
            
        }
    }

    for (size_t i = 0; i < MAX_STACK_SIZE; i++)
    {
        cout << stacks[i].top();
    }
    cout << endl;

    // print_stack(stack[0]);
    // // cout << endl;
    // print_stack(stack[1]);
    // // cout << endl;
    // print_stack(stack[2]);
    // cout << endl;
}