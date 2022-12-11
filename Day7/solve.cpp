#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int max_size = 100000;
int filesystem_size = 70000000;
int space_needed_to_update = 30000000;

class tree
{
public:
    char type; // can be 'D' for dir or 'F' for file
    tree *p;
    string name;
    int size; // if dir this value is 0
    vector<tree> childs;

    tree get_tree_dir(string goal)
    {
        for (size_t i = 0; i < childs.size(); i++)
        {
            if (childs[i].name == goal)
            {
                return childs[i];
            }
        }
    }

    void add_child(tree child)
    {
        if (type == 'D')
        {
            childs.push_back(child);
        }
    }

    void add_child_To(string id, tree child)
    {
        if (type == 'D')
        {
            if (name == id)
            {
                add_child(child);
            }
            else
            {
                for (size_t i = 0; i < childs.size(); i++)
                {
                    childs[i].add_child_To(id, child);
                }
            }
        }
    }

    bool has_child(string id){
        for (size_t i = 0; i < childs.size(); i++)
        {
            if (childs[i].name == id)
            {
                return true;
            }
        }
        return false;
    }

    tree *get_child(string id){
        for (size_t i = 0; i < childs.size(); i++)
        {
            if (childs[i].name == id)
            {
                return &childs[i];
            }
        }
        return NULL; // how to return NULL;
    }

    int get_file_size()
    {   
        if (type == 'F')
        {
            // cout << "will return size from " << name << ": " << size << endl;
            return size;
        }
        else
        {
            int size_collect = 0;
            for (size_t i = 0; i < childs.size(); i++)
            {
                size_collect += childs[i].get_file_size();
            }
            // cout << "will return collected size from " << name << ": " << size_collect << endl;
            return size_collect;
        }
    }

    void print_tree(int depth)
    {
        for (size_t i = 0; i < depth; i++)
        {
            cout << "  ";
        }
        cout << "- " << name << " ";
        if (type == 'D')
        {
            cout << "(dir)" << endl;
        }
        else
        {
            cout << "(file, size=" << size << ")" << endl;
        }
        for (size_t i = 0; i < childs.size(); i++)
        {
            childs[i].print_tree(depth + 1);
        }
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

void fill_size_vector(tree root, int bound, vector<int> *v)
{
    if (root.type == 'F')
    {
        return;
    }
    
    int size = root.get_file_size();
    if (size <= bound)
    {   
        // cout << "Added Size to vector " << size << " from " << root.name << endl;
        (*v).push_back(size);
    }
    for (size_t i = 0; i < root.childs.size(); i++)
    {
        fill_size_vector(root.childs[i], bound, v);
    }
}

int main()
{
    ifstream file("input");
    string line;

    string dir;

    tree root;
    root.name = "/";
    root.type = 'D';
    root.p = NULL;

    tree *current = &root;

    getline(file,line); // ignore first cd

    while (getline(file, line))
    {
        vector<string> tokens = split(line, " ");
        if (tokens[0] == "$") // command
        {
            if (tokens[1] == "cd")
            {
                string dir_name = tokens[2];
                if (dir_name == "..")
                {
                    current = current->p;
                } else {
                    tree *new_node;
                    if (current->has_child(dir_name))
                    {
                        new_node = current->get_child(dir_name);
                    } else { // this should never happen since after a ls the directory is created
                        new_node->name = dir_name;
                        new_node->type = 'D';
                        new_node->p = current;
                    }
                    current = new_node;  
                }
            }
        }
        else // result from a ls
        {
            tree to_add;
            if (tokens[0] == "dir") // dir
            {
                to_add.type = 'D';
                to_add.name = tokens[1];
            }
            else // file
            {
                to_add.type = 'F';
                to_add.name = tokens[1];
                to_add.size = stoi(tokens[0]);
            }
            to_add.p = current;
            // root.add_child_To(dir, to_add);
            current->add_child(to_add);
        }
    }
    // root.print_tree(0);
    vector<int> sizes;
    // fill_size_vector(root, 100000, &sizes);

    // int final_size = 0;

    // for (size_t i = 0; i < sizes.size(); i++)
    // {
    //     // cout << sizes[i] << endl;
    //     final_size += sizes[i];
    // }
    // cout << "Total size : " << final_size << endl;

    fill_size_vector(root, filesystem_size, &sizes);

    int outermost_size = root.get_file_size(); 
    cout << "Outermost directory size : " << outermost_size << endl;

    int current_unused = filesystem_size - outermost_size;
    cout << "Unused space : " << current_unused << endl;

    int space_required = space_needed_to_update - current_unused;
    cout << "Required space to free : " << space_required << endl;

    int min = filesystem_size;
    for (size_t i = 0; i < sizes.size(); i++)
    {
        if (sizes[i] >= space_required && sizes[i] < min)
        {
            min = sizes[i];
        }
    }
    cout << "Smallest directory space : " << min << endl;
}