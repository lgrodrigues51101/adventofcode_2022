#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node
{
    int data;
    struct Node *next;
};

void displayList(struct Node *node)
{
    while (node != NULL)
    {
        cout << node->data << "-->";
        node = node->next;
    }
    cout << "NULL" << endl;
}

void append(struct Node **head, int node_data)
{
    struct Node *newNode = new Node;
    struct Node *last = *head;
    newNode->data = node_data;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = newNode;
    return;
}

void insert_sort(struct Node **head, int data)
{
    if (*head == NULL)
    {
        struct Node *newNode = new Node;
        newNode->data = data;
        newNode->next = NULL;
        *head = newNode;
        return;
    }

    if (data > (*head)->data)
    {
        int next_data = (*head)->data;
        (*head)->data = data;
        insert_sort(&((*head)->next), next_data);
    }
    else
    {
        insert_sort(&((*head)->next), data);
    }
}

int main()
{

    string line;
    int T = 3;

    ifstream file("input");
    Node *head = NULL;

    int value = 0;

    while (getline(file, line))
    {
        if (line == "")
        {
            append(&head, value);
            value = 0;
        }
        else
        {
            value += stoi(line);
        }
    }
    append(&head, value);
    file.close();

    cout << endl;

    Node *sorted = NULL;
    Node *current = head;

    while (current != NULL)
    {
        insert_sort(&sorted, current->data);
        current = current->next;
    }

    int total = 0;
    for (size_t i = 0; i < T; i++)
    {
        cout << "Best Elf " << i << ": " << sorted->data << endl;
        total += sorted->data;
        sorted = sorted->next;
    }
    cout << "Total: " << total << endl;
}