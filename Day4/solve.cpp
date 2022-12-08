#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{

    ifstream file("input");
    string line;

    int count = 0;

    int x, y, w, z;

    while (getline(file, line))
    {
        int split = line.find(',');
        string part_one = line.substr(0, split);
        string part_two = line.substr(split + 1, line.length());

        split = part_one.find('-');
        x = stoi(part_one.substr(0, split));
        y = stoi(part_one.substr(split + 1));
        split = part_two.find('-');
        w = stoi(part_two.substr(0, split));
        z = stoi(part_two.substr(split + 1));

        int min = x < w ? x : w;
        int target = x < w ? y : z;

        int cmp_min = min == x ? w : x;

        while (min <= target)
        {
            if (min == cmp_min)
            {
                count++;
                break;
            }
            min++;
        }
    }
    cout << "COUNT: " << count << endl;
}