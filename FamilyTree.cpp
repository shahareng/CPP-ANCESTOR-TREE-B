#include "FamilyTree.hpp"

#include <iostream>
using namespace std;

string relation[] = {"", "grand", "great-grand"};

namespace family
{

    Tree::Tree(string name)
    {
        root = new node;
        root->name = name;
        root->left = NULL;
        root->right = NULL;
        root->prev = NULL;
    }

    // search a name in the tree
    node *Tree::search(string name, node *leaf)
    {
        if(leaf != NULL)
        {
            if(leaf->name.compare(name) == 0)
            {
                return leaf;
            }
            search(name, leaf->left);
            search(name, leaf->right);
        }
        return NULL;
    }
    
    // add father to someone that apear in the tree
    Tree& Tree::addFather(string kid, string father)
    {
        node * leaf = search(kid, root);
        if (leaf == NULL)
        {
            throw runtime_error("that name doesn't exist!");
        }
        else if (leaf->left != NULL)
        {
            throw runtime_error("she/he had a father yet!");
        }
        else
        {
            leaf->left = new node;
            leaf->left->name = father;
            leaf->left->left = NULL; 
            leaf->left->right = NULL;
            leaf->left->prev = leaf;
        }
        return *this;
    }

    // add mother to someone that apear in the tree
    Tree& Tree::addMother(string kid, string mother)
    {
        node * leaf = search(kid, root);
        if (leaf == NULL)
        {
            throw runtime_error("that name doesn't exist!");
        }
        else if (leaf->right != NULL)
        {
            throw runtime_error("she/he had a mother yet!");
        }
        else
        {
            leaf->right = new node;
            leaf->right->name = mother;
            leaf->right->left = NULL; 
            leaf->right->right = NULL;
            leaf->right->prev = leaf;
        }
        return *this;   
    }

    // return the relation in the tree ; e.g: mothre, father, unrelated and more..
    string Tree::relation(string name)
    {
        node * leaf = search(name, root);
        node * ans = *leaf;
        if(leaf == NULL)
        {
            return "unrelated";
        }
        if(leaf == root)
        {
            return "me";
        }
        int count;
        string rela = "";
        while (prev != root)
        {
            count++;
            leaf = leaf->prev;
        }
        while(count>3)
        {
            rela+="great-";
            count--;
        }
        ans = ans->prev;
        if(ans->left->name.compare(name) == 0)
        {
            rela+=relation[count-1];
            return rela+="father";
        }
        else if(ans->right->name.compare(name) == 0)
        {
            rela+=relation[count];
            return rela+="mother";
        }
    }

    // return the name of the relation
    string Tree::find(string relat)
    {
        if(relat.compare("me"))
        {
            return root->name;
        }
        else if(relat.compare("father"))
        {
            return root->left->name;
        }
        else if(relat.compare("mother"))
        {
            return root->right->name;
        }
        else if(relat.find("grand") == 0)
        {
            if(relat.find("mother") != string::npos)
            {
                if(root->left->right->name != NULL)
                    return root->left->right->name;
                else if(root->right->right->name != NULL)
                    return root->right->right->name;
                else throw runtime_error("that relation doesn't exist!");
            }
            else if(relat.find("father") != string::npos)
            {
                if(root->left->left->name != NULL)
                    return root->left->right->name;
                else if(root->right->left->name != NULL)
                    return root->right->right->name;
                else throw runtime_error("that relation doesn't exist!");
            }
        }
        else if(relat.find("great-") == 0)
        {
            size_t found = relat.find("great-");
            int count=2;
            node * leaf = root;
            found = str.find("great-",found+1,6);
            while(found != string::npos)
            {
                count++;
            }
            if(relat.find("mother") != string::npos)
            {
                while(count>0)
                {
                    leaf = leaf->left;
                }
                return leaf->right->name;
            }
            else if(relat.find("father") != string::npos)
            {
                while(count>0)
                {
                    leaf = leaf->left;
                }
                return leaf->left->name;
            }
        }
        else throw runtime_error("that relation doesn't exist!");
    }

    void Tree::printBT(const string& prefix, const node* node, bool isLeft)
    {
        if(node != NULL)
        {
            cout << prefix;

            cout << (isLeft ? "├──" : "└──" );

            // print the value of the node
            cout << node->name << endl;

            // enter the next tree level - left and right branch
            printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
            printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
        }
    }

    // display the tree
    void Tree::display()
    {
        printBT("", root, false);
    }

    // delete the name and all his parents from the tree
    void Tree::remove(string name)
    {
        node * leaf = search(name, root);
        if(leaf == NULL)
        {
            throw runtime_error("that name doesn't exist!");
        }
        else if(leaf->name.compare(root->name) == 0)
        {
            throw runtime_error("You can't delete the root!");
        }
        else
        {
            delete_tree(leaf);
        }
    }

    // help function to remove
    void Tree::delete_tree(node *leaf)
    {
        if(leaf != NULL)
        {
            delete_tree(leaf->left);
            delete_tree(leaf->right);
            delete leaf;
        }
    }
};