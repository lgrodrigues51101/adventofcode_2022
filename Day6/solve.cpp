#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int char_sequence_size = 14;

bool repeats(char q[])
{
    for (size_t i = 0; i < char_sequence_size; i++)
    {
        for (size_t j = i+1; j < char_sequence_size; j++)
        {
            if (q[i] == q[j])
            {
                return true;
            }
        }
    }
    return false;
}

void shift(char q[])
{
    for (size_t i = 0; i < char_sequence_size-1; i++)
    {
        q[i] = q[i + 1];
    }
}

string toStringQ(char q[])
{
    string s;
    for (size_t i = 0; i < char_sequence_size; i++)
    {
        s = s + q[i];
    }
    return s;
}

int main()
{
    ifstream file("input");
    string line;

    char q[char_sequence_size];
    int size = 0;

    while (getline(file, line))
    {
        for (size_t i = 0; i < line.size(); i++)
        {
            char c = line[i];
            q[size] = c;
            size++;
            // cout << "Current state " << toStringQ(q) << endl;
            if (size == char_sequence_size)
            {
                if (!repeats(q))
                {
                    cout << "Sequence " << toStringQ(q) << " after processing " << i + 1 << " chars" << endl;
                    break;
                } 
                shift(q);
                size--;
            }
        }
    }
}