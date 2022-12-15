#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int max_round = 20;

class monkey
{
public:
    int id;
    queue<int> items;
    int test_n;
    int times_inspected;
    string op;
    string op_n;
    int true_monkey;
    int false_monkey;
    monkey(int iid, int itest_n, string iop, string iop_n, int itru_monkey, int ifalse_monkey, queue<int> iitems)
    {
        id = iid;
        test_n = itest_n;
        op = iop;
        op_n = iop_n;
        times_inspected = 0;
        true_monkey = itru_monkey;
        false_monkey = ifalse_monkey;
        items = iitems;
    }
    void give_item(int item)
    {
        items.push(item);
    }
    void inspect(vector<monkey> *monkeys)
    {
        while (!items.empty())
        {
            int item = items.front();
            items.pop();

            int op_value;
            if (op_n == "old")
            {
                op_value = item;
            }
            else
            {
                op_value = stoi(op_n);
            }

            if (op == "*")
            {
                item = item * op_value;
            }
            else if (op == "/")
            {
                item = item / op_value;
            }
            else if (op == "+")
            {
                item = item + op_value;
            }
            else if (op == "-")
            {
                item = item - op_value;
            }

            item = item / 3;
            times_inspected++;

            int index = item % test_n == 0 ? true_monkey : false_monkey;
            (*monkeys)[index].give_item(item);
        }
    }
    string toString()
    {
        string s = "Monkey " + to_string(id) + ":\n";
        s += "\tStarting items: " + to_string(items.size()) + "\n";
        s += "\tOperation: new = old " + op + " " + op_n + "\n";
        s += "\tTest: divisible by " + to_string(test_n) + "\n";
        s += "\t\tIf true: throw to monkey " + to_string(true_monkey) + "\n";
        s += "\t\tIf false: throw to monkey " + to_string(false_monkey) + "\n";
        return s;
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

int main()
{
    ifstream file("input");
    string line;

    vector<monkey> monkeys;

    while (getline(file, line)) // monkey id
    {
        vector<string> token = split(line, " ");
        token = split(token[1], ":");
        int monkey_id = stoi(token[0]);

        getline(file, line); // monkey items
        token = split(line, ":");
        token = split(token[1], ",");
        queue<int> items;
        for (size_t i = 0; i < token.size(); i++)
        {
            items.push(stoi(token[i]));
        }

        getline(file, line); // monkey operation
        token = split(line, " ");
        string op = token[6];
        string op_n = token[7]; // this is string since it can be "old"

        getline(file, line); // monkey Test
        token = split(line, " ");
        int test_n = stoi(token[5]);

        getline(file, line); // true
        token = split(line, " ");
        int true_monkey = stoi(token[9]);

        getline(file, line); // false
        token = split(line, " ");
        int false_monkey = stoi(token[9]);

        monkeys.push_back(monkey(monkey_id, test_n, op, op_n, true_monkey, false_monkey, items));
        getline(file, line);
    }

    // for (size_t i = 0; i < monkeys.size(); i++)
    // {
    //     cout << monkeys[i].toString() << endl;
    // }

    for (size_t i = 0; i < max_round; i++)
    {
        for (size_t j = 0; j < monkeys.size(); j++)
        {
            monkeys[j].inspect(&monkeys);
        }
        // cout << "Round " << i << endl;
        // for (size_t j = 0; j < monkeys.size(); j++)
        // {
        //     cout << "monkey " << j << ": ";
        //     queue<int> Q = monkeys[j].items;
        //     while (!Q.empty())
        //     {
        //         cout << " " << Q.front();
        //         Q.pop();
        //     }
        //     cout << endl;
        // }
    }

    int monkey_business;
    int best_2[2] = {0,0};

    for (size_t j = 0; j < monkeys.size(); j++)
    {
        cout << "Monkey " << to_string(j) << " inspected items " << monkeys[j].times_inspected << " times" << endl;
        if (monkeys[j].times_inspected > best_2[0])
        {
            best_2[1] = best_2[0];
            best_2[0] = monkeys[j].times_inspected;
        } else if(monkeys[j].times_inspected > best_2[1]){
            best_2[1] = monkeys[j].times_inspected;
        }       
    }
    cout << best_2[0] << " " << best_2[1] << endl;
    monkey_business = best_2[0] * best_2[1];
    cout << "Monkey business : " << monkey_business << endl;
}