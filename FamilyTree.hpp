#include <iostream>
#include <string>
using namespace std;

namespace family
{
    class Tree
    {
        string name;
        Tree* mother;
        Tree* father;
        Tree* kid;

        public:

        Tree(string nameR)
        {
            name = nameR;
            mother = NULL;
            father = NULL;
            kid = NULL;
        }

        ~Tree()
        {
            delete this->father;
            delete this->mother;
        }
        
        Tree& addFather(string, string);
        Tree& addMother(string, string);
        string relation(string);
        string find(string);
        void display();
        void remove(string);

        private:

        Tree* search(string, Tree*);
        void printBT(const string& prefix, Tree* node, bool isLeft);
        string findH(int, Tree*, int);
    };
};