#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<memory>
#include <utility>      // std::pair, std::make_pair
#include <chrono> // clock()
//#include <cstdio> // clock()
//#include <ctime> // clock()

#include"BSTree.h"


int TreeKeys[9] = {8,10,14,13,3,6,7,4,1};
int TreeValues[9] = {8,10,14,13,3,6,7,4,1};

std::size_t GetSize(int arrkeys[]) {
  std::size_t _size = sizeof(TreeKeys)/sizeof(TreeKeys[0]);
  return _size; }


int main(int argc, char** argv) {

  BSTree<int,int> myTree;
  BSTree<int,int> myTree_copy;
  BSTree<int, int> myTree_move;
  BSTree<int, int> myTree_tests;
  std::pair<int,int> keyval;

  std::cout << "Before inserting numbers, print the tree in order:\n";
  myTree.TreeTraversal();

  for(int i=0; i < 9; i++) {
    keyval.first = TreeKeys[i];
    keyval.second = TreeValues[i];
    myTree.InsertKey(keyval); }

  std::cout << "\nPrinting the ORIGINAL tree after inserting numbers -- print the tree in order: " << std::endl;
  myTree.TreeTraversal();
  std::cout << "\n ";

  /* Calling the class iterator to print the tree */
  std::cout << "\nPrinting keys & values of the ORIGINAL tree using the iterator\n";
  for (auto iter = myTree.begin(); iter != myTree.end(); ++iter){
    keyval = *iter;
    std::cout << keyval.first <<":"<< keyval.second << " ";
    std::cout << " " << std::endl; }


  /* Calling the class iterator to print the tree */
  std::cout << "\nPrinting keys & values of the ORIGINAL tree using the const_iterator\n";
  for (auto iter = myTree.cbegin(); iter != myTree.cend(); ++iter){
    keyval = *iter;
    std::cout << keyval.first <<":"<< keyval.second << "\n"; }

  /* Calling Tree Find function */
  std::cout << "\nRunning Find function...\n";
  /* Find a specific element in the tree */
  myTree.TreeFind_iter(keyval);

  /* Find the last number in the tree and record the elapsed time*/
  //double interval_original;
  //std::clock_t start;
  //start = std::clock();

  /* Using std::chrono */
  auto start = std::chrono::high_resolution_clock::now();

  std::cout << "The last element in the ORIGINAL tree has a key of" << " ["
  << myTree.TreeFindLast(keyval) << "] " << std::endl;


  int num = 3;
  std::cout << "TEST FIND " << std::endl;

  /*if (myTree.Search(keyval, num)) 
    std::cout << "Yes! Number [" << num << "] is found in the tree...\n"; 
  else
    std::cout << "No! Number [" << num << "] is NOT found in the tree...\n"; */

  if (myTree.TreeFind(keyval, num))
    std::cout << "Yes! Number [" << num << "] is found in the tree...\n"; 
  else
    std::cout << "No! Number [" << num << "] is NOT found in the tree...\n"; 

 





  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> diff = end-start;
  std::cout << "Elapsed time to find the element is "
            << diff.count() << " [s]\n";

  //interval_original = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  //std::cout<< "Elapsed time to find the element is " << interval_original << " [s]\n";


  /* Calling copy semantics */
  std::cout << "\nRunning copy semantics...\n";
  myTree_copy = myTree;
  std::cout << "\nPrinting the ORIGINAL tree after copying...\n" << myTree_copy;

  /* Calling move semantics */
  std::cout << "Running move semantics...\n";
  myTree_move = std::move(myTree_copy);
  std::cout << "\nPrinting the ORIGINAL tree after moving...\n" << myTree_move;
  std::cout<<'\n';

  /* Calling Tree Balance function  */
  std::cout << "\nRunning Balance function...\n";
  std::cout << "Balance the ORIGINAL tree after moving...\n";
  myTree.TreeBalance(myTree.begin(), GetSize(TreeKeys), myTree_move);
  std::cout << "\nPrinting the ORIGINAL tree after balance...\n" << myTree_move << std::endl;
  //myTree.TreeTraversal(); // i will use range for

  /* Calling Tree Clear function */
  std::cout << "\nRunning Tree Clear function...\n";
  myTree.TreeClear();
  std::cout<<'\n';

  /* Make sure that the ORIGINAL tree is freed */
  std::cout << "\nPrinting the ORIGINAL tree calling Clear() function...\n" 
  << myTree << std::endl;





  /** Running TESTS **/
  const int size = 10;
  int TestKeys[size];
  int TestValues[size];

  /* Generating new tree of random values */
  std::cout << "Generating a new tree of random values" << std::endl;
  for(int i=0; i<  size; i++){
    TestKeys[i] = (rand()%size)+1;
    TestValues[i] = (rand()%size)+1;

    /* print the two arrays of keys and values */
    std::cout << TestKeys[i] << " " << TestValues[i] << std::endl;

    /* Filling "tree keyval" -- std::pair */
    keyval.first = TestKeys[i];
    keyval.second = TestValues[i];
    myTree.InsertKey(keyval); }

  /* Testing Copy semantics */
  std::cout << "\nRunning copy semantics [new tree]...\n";
  myTree_tests = myTree;
  std::cout << "\nPrinting the [new tree] tree after copying ...\n" << myTree_tests;

  /* Testing Tree Balance function for the new tree  */
  std::cout << "\nRunning Balance function [new tree]...\n";
  myTree_tests.TreeBalance(myTree_tests.begin(), GetSize(TestKeys), myTree_tests);
  std::cout << "\nPrinting the NEW tree after balance...\n" << myTree_tests << std::endl;

  /* Testing Tree Find function */
  std::cout << "\nRunning Find function [new tree]...\n";

  /* Find a specific element in the tree */
  myTree_tests.TreeFind_iter(keyval);

  


  /* Find the last number in the tree and record the elapsed time*/
  //double interval_new;
  //std::clock_t start_new;
  //start_new = std::clock();

  /* Using std::chrono */
  auto start_new = std::chrono::high_resolution_clock::now();

  std::cout << "The last element in the NEW tree has a key of" << " ["
  << myTree_tests.TreeFindLast(keyval) << "] " << std::endl;

  auto end_new = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> diff_new = end_new - start_new;
  std::cout << "Elapsed time to find the element is "
            << diff_new.count() << " [s]\n";

  //interval_new = ( std::clock() - start_new ) / (double) CLOCKS_PER_SEC;
  //std::cout<< "Elapsed time to find the element is " << interval_new << " [s]\n";


 // int num = 2;
  //std::cout << "TEST FIND POST " << std::endl;
  //myTree_tests.FindNum(keyval, num);

     














  /* Calling Tree Clear function */
  std::cout << "\nRunning Tree Clear function...\n";
  myTree.TreeClear();
  std::cout<<'\n';

  /* Make sure that the NEW tree is freed */
  std::cout << "\nPrinting the NEW tree calling Clear() function...\n"
  << myTree << std::endl;


  return 0;
}
