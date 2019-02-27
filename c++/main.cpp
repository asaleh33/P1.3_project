#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<memory>
//#include<vector>
#include <utility>      // std::pair, std::make_pair

#include"BSTree.h"

int TreeKeys[9] = {8,10,14,13,3,6,7,4,1};
int Treevalues[9] = {8,10,14,13,3,6,7,4,1};

int main(int argc, char** argv) {

  BSTree<int,int> myTree;
  std::pair<int,int> keyval;
  BSTree<int,int> myTree_copy;
  BSTree<int, int> myTree_move; 

  std::cout << "Before inserting numbers, print the tree in order:\n";
  myTree.TreeTraversal(keyval);

  for(int i=0; i < 9; i++) {
    keyval.first = TreeKeys[i];
    keyval.second = Treevalues[i];
    myTree.InsertKey(keyval); }

  std::cout << "\nPrinting the original tree after inserting numbers -- print the tree in order: " << std::endl;
  myTree.TreeTraversal(keyval); 
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


  /* Calling Tree Find function */
  std::cout << "\nRunning Find function...\n";
  /* Find a specific element in the tree */
  myTree.TreeFind(keyval); 
  /* Find the largest number in the tree */
  std::cout << "The largest element in the tree is:" << " " << myTree.TreeFindLargest(keyval) << std::endl;
   
 

  /* Testing copy semantics */
  std::cout << "\nRunning copy semantics...\n";
  myTree_copy = myTree;
  std::cout << "\nAGAIN: printing the tree BEFORE copying...\n";
  myTree.TreeTraversal(keyval); 
  std::cout << "\nPrinting the tree after copying...\n" << myTree_copy;

  /* Testing move semantics */
  std::cout << "Running move semantics...\n";
  myTree_move = std::move(myTree_copy);
  std::cout << "\nPrint the tree after moving...\n" << myTree_move;
  std::cout<<'\n';


  /* Calling Tree Balance function  */
  std::cout << "\nRunning Balance function...\n";
  myTree.TreeBalance();
  


  /* Calling Tree Clear function */
  std::cout << "\nRunning Tree Clear function...\n";
  myTree.TreeClear();
  std::cout<<'\n';


  return 0;
}
