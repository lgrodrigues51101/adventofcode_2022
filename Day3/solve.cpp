#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

char get_rep(string first, string second) {
    for (size_t i = 0; i < first.length(); i++)
    {
        char c = first[i];
        if (second.find(c) != string::npos)
            return c;
    }
    return '-';
}

char get_badge(string elf_one, string elf_two, string elf_three) {
    for (size_t i = 0; i < elf_one.length(); i++)
    {
        char c = elf_one[i];
        if (elf_two.find(c) != string::npos && elf_three.find(c) != string::npos)
            return c;
    }
    return '-';
}

int main()
{

    ifstream file("input");
    string line1, line2, line3;

    int sum = 0;

    while (getline(file, line1) && getline(file, line2) && getline(file, line3))
    {
        
        char rep = get_badge(line1, line2, line3);
        int value = int(rep)-96;
        if(value <= 0)
            value += 58;
        sum += value;
    }

    cout << "SUM: " << sum << endl;
}

// int main()
// {

//     ifstream file("input");
//     string line;

//     int sum = 0;

//     while (getline(file, line))
//     {
//         string head = line.substr(0, line.length()/2);
//         string tail = line.substr(line.length()/2, line.length());
//         char rep = get_rep(head, tail);
//         int value = int(rep)-96;
//         if(value < 0)
//             value += 58;
//         sum += value;
//     }

//     cout << "SUM: " << sum << endl;
// }