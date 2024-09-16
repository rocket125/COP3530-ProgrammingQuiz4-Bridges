#include <iostream>
#include <string>
#include <vector>
#include "Bridges.h"
#include "DataSource.h"
#include "BSTElement.h"
#include <queue>
using namespace std;
using namespace bridges;

BSTElement<string, string>* insertIntoBST(string actor, string movie, BSTElement<string, string> *root) {
    if (root == nullptr)
    {
        root = new BSTElement<string, string>(actor);
        root->setLabel(movie);
        return root;
    }

    if (actor > root->getKey())
    {
        root->setRight(insertIntoBST(actor, movie, root->getRight()));
    }
    else
    {
        root->setLeft(insertIntoBST(actor, movie, root->getLeft()));
    }

    return root;
}

void deleteTree(BSTElement<string, string> *root) {
    if (root == nullptr)
        return;
    if (root->getLeft() != nullptr) {
        deleteTree(root->getLeft());
    }
    if (root->getRight() != nullptr) {
        deleteTree(root->getRight());
    }
    delete root;
}

int getHeight(BSTElement<string, string> *node) {
    if (node == nullptr)
        return 0;
    int leftH = getHeight(node->getLeft());
    int rightH = getHeight(node->getRight());
    return max(leftH, rightH) + 1;
}

void colorize(queue<BSTElement<string, string> *> &q) {
    const Color colors[] =
        {
        Color("red"),
        Color("orange"),
        Color("yellow"),
        Color("green"),
        Color("blue"),
        Color("purple")
        };
    BSTElement<string, string> *currentNode = nullptr;
    while (!q.empty()) {
        currentNode = q.front();
        // Coloring node according to height
        currentNode->setColor(colors[getHeight(currentNode) % 6]);

        q.pop();
        if (currentNode->getLeft() != nullptr)
            q.push(currentNode->getLeft());
        if (currentNode->getRight() != nullptr)
            q.push(currentNode->getRight());
    }
}


/*
  Step 1: Get the Bridges USER ID and API KEY for your program
          by creating an account and signing up (You can use any
          email): https://bridges-cs.herokuapp.com/login

  Step 2: User ID (Username) and Key (API Sha1 Key) can be
          found under Profile on the top left
*/


int main(int argc, char **argv)
{

    // Step 3: Test if the following print statement is being run
    cout << "Bridges: IMDB Data in a BST\n";

    /*
     Step 4: Create a Bridges object by uncommenting the next line
     and inserting the values from steps 1 and 2
    */
    Bridges bridges(1, "EnderRogue", "999505044859");

    /*
       Step 5: Import IMDB data into a vector<ActorMovieIMDB> by
               referring to the Bridges IMDB documentation:
               https://bridgesuncc.github.io/tutorials/Data_IMDB.html
    */
    bridges.setTitle("Accessing IMDB Data");
    DataSource ds(&bridges);
    vector<ActorMovieIMDB> actor_list = ds.getActorMovieIMDBData((1814));
    /*
       Step 6: Open the file "insertIntoBST.txt" and copy the provided
               function for inserting an actor/movie pair into a BST.
               Paste the function into this file above your "main" function.
    */

    /*
       Step 7: Use the insertion function from the previous step to insert
               any 100 actor/movie pairs into a Bridges BST. Refer to the
               Bridges IMDB documentation:
               https://bridgesuncc.github.io/tutorials/Data_IMDB.html
    */
    BSTElement<string, string> *tree = new BSTElement<string, string>(actor_list[0].getActor());
    tree->setLabel(actor_list[0].getMovie());
    string name, movie;
    for (int i = 1; i < 100; i++) {
        name = actor_list[i].getActor();
        movie = actor_list[i].getMovie();
        insertIntoBST(name, movie, tree);
    }


    /*
       Step 8: Visualize this tree by referring to the Bridges BST documentation:
               https://bridgesuncc.github.io/tutorials/BinarySearchTree.html
    */

    /*
       Step 9: Color each level of the tree using a level-order traversal.
               Every node in a given level should have the same color.
               Do not use the same color in two consecutive levels. A starter
               queue has been provided in case you wish to use an iterative
               implementation of BFS.

               Refer to the Bridges BST Styling documentation:
               https://bridgesuncc.github.io/tutorials/BinarySearchTree.html

    */

    queue<BSTElement<string, string> *> q;

    q.push(tree);
    colorize(q);
    /*
      Step 10: Visualize the updated tree. Comment out or remove the old
               visualization code from Step 8
    */
    bridges.setDataStructure(tree);
    bridges.visualize();

    deleteTree(tree);

    return 0;
}