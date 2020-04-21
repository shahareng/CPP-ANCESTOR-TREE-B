#include <iostream>
using namespace std;

struct node
{
    string name;
    node *left;
    node *right;
    node *prev;
};

namespace family
{
    class Tree
    {
        public:

        Tree(string name);
        
        node *search(string name, node *leaf);
        Tree& addFather(string kid, string father);
        Tree& addMother(string kid, string mother);
        string relation(string name);
        string find(string relat);
        void printBT(const string& prefix, const node* node, bool isLeft);
        void display();
        void remove(string name);
        void delete_tree(node *leaf);

        struct node *root;
    };
};