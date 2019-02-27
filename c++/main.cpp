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
    std::cout << "Print the tree using the iterator\n";
    std::cout << keyval.first <<":"<< keyval.second << "\n"; }

  /* Calling the class iterator to print the tree */
  for (auto iter = myTree.cbegin(); iter != myTree.cend(); ++iter){
    keyval = *iter;
    std::cout << "Print the tree using the const_iterator\n";
    std::cout << keyval.first <<":"<< keyval.second << "\n"; }


  /* Testing copy semantics */
  std::cout << "Running copy semantics...\n";
  BSTree<int,int> myTree_copy;
  myTree_copy = myTree;
  std::cout << "Print the tree after copying...\n" << myTree_copy;
  std::cout<<'\n';


  /* Calling Tree Clear function */
  std::cout << "\nRunning Tree Clear function...\n";
  myTree.TreeClear();
  std::cout<<'\n';




  return 0;
}
