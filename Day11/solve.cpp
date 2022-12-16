#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int max_round = 10000;

class Item
{
public:
    vector<size_t> values;
    vector<size_t> div;
    Item(size_t n_monkeys, size_t value, vector<size_t> Idiv)
    {
        div = Idiv;
        for (size_t i = 0; i < n_monkeys; i++)
        {
            values.push_back(value);
        }
    }
};

class monkey
{
public:
    int id;
    queue<Item> items_s;
    vector<size_t> items; // these are only the starting values
    size_t test_n;
    int times_inspected;
    string op;
    string op_n;
    int true_monkey;
    int false_monkey;
    monkey(int iid, int itest_n, string iop, string iop_n, int itru_monkey, int ifalse_monkey, vector<size_t> iitems)
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
        items.push_back(item);
    }
    void give_item(Item item)
    {
        items_s.push(item);
    }
    void inspect(vector<monkey> *monkeys)
    {
        while (!items_s.empty())
        {
            Item item = items_s.front();
            items_s.pop();

            for (size_t i = 0; i < item.values.size(); i++)
            {
                size_t op_value;
                if (op_n == "old")
                {
                    op_value = item.values[i];
                }
                else
                {
                    op_value = stoi(op_n);
                }

                if (op == "*")
                {
                    item.values[i] = (item.values[i] * op_value) % item.div[i];
                }
                else if (op == "/")
                {
                    item.values[i] = (item.values[i] / op_value) % item.div[i];
                }
                else if (op == "+")
                {
                    item.values[i] = (item.values[i] + op_value) % item.div[i];
                }
                else if (op == "-")
                {
                    item.values[i] = (item.values[i] - op_value) % item.div[i];
                }
            }
            times_inspected++;

            int index = item.values[id] % test_n == 0 ? true_monkey : false_monkey;

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
    vector<size_t> test_ns;

    while (getline(file, line)) // monkey id
    {
        vector<string> token = split(line, " ");
        token = split(token[1], ":");
        int monkey_id = stoi(token[0]);

        getline(file, line); // monkey items
        token = split(line, ":");
        token = split(token[1], ",");
        vector<size_t> items;
        for (size_t i = 0; i < token.size(); i++)
        {
            items.push_back(stoi(token[i]));
        }

        getline(file, line); // monkey operation
        token = split(line, " ");
        string op = token[6];
        string op_n = token[7]; // this is string since it can be "old"

        getline(file, line); // monkey Test
        token = split(line, " ");
        int test_n = stoi(token[5]);

        test_ns.push_back(test_n);

        getline(file, line); // true
        token = split(line, " ");
        int true_monkey = stoi(token[9]);

        getline(file, line); // false
        token = split(line, " ");
        int false_monkey = stoi(token[9]);

        monkeys.push_back(monkey(monkey_id, test_n, op, op_n, true_monkey, false_monkey, items));
        getline(file, line);
    }

    for (size_t i = 0; i < monkeys.size(); i++)
    {
        for (size_t j = 0; j < monkeys[i].items.size(); j++)
        {
            Item it = Item(monkeys.size(), monkeys[i].items[j], test_ns);
            monkeys[i].give_item(it);
        }
    }

    // for (size_t i = 0; i < monkeys.size(); i++)
    // {
    //     cout << monkeys[i].toString() << endl;
    // }

    for (size_t i = 1; i <= max_round; i++)
    {
        for (size_t j = 0; j < monkeys.size(); j++)
        {
            monkeys[j].inspect(&monkeys);
        }

        // cout << "Round " << i << endl;
        // for (size_t j = 0; j < monkeys.size(); j++)
        // {
        //     cout << "monkey " << j << ": ";
        //     queue<size_t> Q = monkeys[j].items;
        //     while (!Q.empty())
        //     {
        //         cout << " " << Q.front();
        //         Q.pop();
        //     }
        //     cout << endl;
        // }

        if (i % 1000 == 0 || i == 1 || i == 20)
        {
            cout << "Round " << i << endl;
            for (size_t j = 0; j < monkeys.size(); j++)
            {
                cout << "Monkey " << to_string(j) << " inspected items " << monkeys[j].times_inspected << " times" << endl;
            }
        }
    }

    size_t monkey_business;
    size_t best_2[2] = {0, 0};

    for (size_t j = 0; j < monkeys.size(); j++)
    {
        // cout << "Monkey " << to_string(j) << " inspected items " << monkeys[j].times_inspected << " times" << endl;
        if (monkeys[j].times_inspected > best_2[0])
        {
            best_2[1] = best_2[0];
            best_2[0] = monkeys[j].times_inspected;
        }
        else if (monkeys[j].times_inspected > best_2[1])
        {
            best_2[1] = monkeys[j].times_inspected;
        }
    }
    cout << best_2[0] << " " << best_2[1] << endl;
    monkey_business = best_2[0] * best_2[1];
    cout << "Monkey business : " << monkey_business << endl;
}