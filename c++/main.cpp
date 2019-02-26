#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<memory>
#include<vector>

#include"BSTree.h"

int TreeKeys[9] = {8,10,14,13,3,6,7,4,1};
int Treevalues[9] = {8,10,14,13,3,6,7,4,1};

int main(int argc, char** argv) {

  BSTree<int,int> myTree;
  std::pair<int,int> keyval;

  std::cout << "Before inserting numbers, print the tree in order:\n";
  myTree.TreeTraversal();

  for(int i=0; i < 9; i++) {
    keyval.first = TreeKeys[i];
    keyval.second = Treevalues[i];
    myTree.InsertKey(keyval); }

  std::cout << "\nPrinting the original tree after inserting numbers -- print the tree in order: " << std::endl;
  myTree.TreeTraversal(); 
  std::cout << "\n "; 

  /* Calling the class iterator to print the tree */
  for (auto iter = myTree.begin(); iter != myTree.end(); ++iter){
    keyval = *iter;
    std::cout << keyval.first <<":"<< keyval.second << "\n"; }

  return 0;
}
