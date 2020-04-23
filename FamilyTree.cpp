#include "FamilyTree.hpp"

#include <iostream>
using namespace std;


namespace family
{
    // search a name in the tree
    Tree* Tree::search(string name, Tree* node)
    {
        if(node == NULL) return NULL;
        if(node->name == name) return node;
        Tree* treeFather = search(name, node->father);
        Tree* treeMother = search(name, node->mother);
        if(treeFather != NULL) return treeFather;
        if(treeMother != NULL) return treeMother;
        return NULL;
    }
    
    // add father to someone that apear in the tree
    Tree& Tree::addFather(string kid, string father)
    {
        Tree* leaf = search(kid, this);
        if (leaf == NULL)
        {
            throw runtime_error("that name doesn't exist!");
        }
        else if (leaf->father != NULL)
        {
            throw runtime_error("she/he had a father yet!");
        }
        else
        {
            leaf->father = new Tree(father);
            leaf->father->kid = leaf;
        }
        return *this;
    }

    // add mother to someone that apear in the tree
    Tree& Tree::addMother(string kid, string mother)
    {
        Tree* leaf = search(kid, this);
        if (leaf == NULL)
        {
            throw runtime_error("that name doesn't exist!");
        }
        else if (leaf->mother != NULL)
        {
            throw runtime_error("she/he had a mother yet!");
        }
        else
        {
            leaf->mother = new Tree(mother);
            leaf->mother->kid = leaf;
        }
        return *this;   
    }

    // return the relation in the tree ; e.g: mothre, father, unrelated and more..
    string Tree::relation(string name)
    {
        Tree* leaf = search(name, this);
        Tree* ans = leaf;
        if(leaf == NULL)
        {
            return "unrelated";
        }
        if(leaf == this)
        {
            return "me";
        }
        int count = 0;
        string rela = "";
        string relation[] = {"", "grand", "great-grand"};
        while (leaf != this)
        {
            count++;
            leaf = leaf->kid;
        }
        while(count>3)
        {
            rela+="great-";
            count--;
        }
        ans = ans->kid;
        if(ans->father->name.compare(name) == 0)
        {
            rela+=relation[count-1];
            return rela+="father";
        }
        else if(ans->mother->name.compare(name) == 0)
        {
            rela+=relation[count-1];
            return rela+="mother";
        }
        return NULL;
    }

    string Tree::findH(int count, Tree* leaf, int type)
    {
        if(leaf == NULL) return "NULL";
        if(count == 1)
        {
            if(type==1 && leaf->mother != NULL)
            {
                return leaf->mother->name;
            }
            else if(type==0 && leaf->father != NULL)
            {
                return leaf->father->name;
            }
            else return "NULL";
        }
        string treeFather = findH(count-1, leaf->father, type);
        string treeMother = findH(count-1, leaf->mother, type);
        if(treeMother.compare("NULL"))
            return treeMother;
        return treeFather;
    }

    // return the name of the relation
    string Tree::find(string relat)
    {
        if(relat.compare("me") == 0)
        {
            return this->name;
        }
        else if(relat.compare("father") == 0 )
        {
            if(this->father != NULL)
            {
                return this->father->name;
            }
            throw runtime_error("that relation doesn't exist!");
        }
        else if(relat.compare("mother") == 0)
        {
            if(this->mother != NULL)
            {
                return this->mother->name;
            }
            throw runtime_error("that relation doesn't exist!");
        }
        else if(relat.compare("grandmother") == 0)
        {
            if(this->father != NULL && this->father->mother != NULL)
                return this->father->mother->name;
            else if(this->mother != NULL && this->mother->mother != NULL)
                return this->mother->mother->name;
            else throw runtime_error("that relation doesn't exist!");
        }
        else if(relat.compare("grandfather") == 0)
        {
            if(this->father != NULL && this->father->father != NULL)
                return this->father->father->name;
            else if(this->mother != NULL && this->mother->father != NULL)
                return this->mother->father->name;
            else throw runtime_error("that relation doesn't exist!");
        }
        else if(relat.find("great-") == 0)
        {
            size_t found = relat.find("great-");
            int count=2;
            Tree* leaf = this;
            found = relat.find("great-",found+1,6);
            while(found != string::npos)
            {
                count++;
                found = relat.find("great-",found+1,6);
            }
            if(relat.find("mother") != string::npos)
            {
                string str = findH(count, this, 1);
                if (str == "NULL")
                {
                    throw runtime_error("that relation doesn't exist!");
                }
                return str;
            }
            else if(relat.find("father") != string::npos)
            {
                string str = findH(count, this, 0);
                if (str == "NULL")
                {
                    throw runtime_error("that relation doesn't exist!");
                }
                return str;
            }
        }
        else throw runtime_error("that relation doesn't exist!");
        return NULL;
    }

    void Tree::printBT(const string& prefix, Tree* node, bool isLeft)
    {
        if(node != NULL)
        {
            cout << prefix;

            cout << (isLeft ? "├──" : "└──" );

            // print the value of the node
            cout << node->name << endl;

            // enter the next tree level - left and right branch
            printBT(prefix + (isLeft ? "│   " : "    "), node->father, true);
            printBT(prefix + (isLeft ? "│   " : "    "), node->mother, false);
        }
    }

    // display the tree
    void Tree::display()
    {
        printBT("", this, false);
    }

    // delete the name and all his parents from the tree
    void Tree::remove(string name)
    {
        Tree* leaf = search(name, this);
        if(leaf == NULL)
        {
            throw runtime_error("that name doesn't exist!");
        }
        else if(leaf->name.compare(this->name) == 0)
        {
            throw runtime_error("You can't delete the root!");
        }
        else
        {
            Tree* temp = leaf->kid;
            if(temp != NULL)
            {
                if(temp->father != NULL && temp->father->name == name)
                {
                    temp->father=NULL;
                }
                else if (temp->mother != NULL && temp->mother->name == name)
                {
                    temp->mother=NULL;
                }
                delete leaf;
            }
        }
    }
};