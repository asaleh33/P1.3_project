#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<memory>
#include <chrono>
#include<time.h>
#include"BSTree.h"


int TreeKeys[9] = {8,10,14,13,3,6,7,4,1};
int TreeValues[9] = {8,10,14,13,3,6,7,4,1};
int GetSize = *(&TreeKeys + 1) - TreeKeys;


int main(int argc, char** argv) {

  BSTree<int,int> myTree;
  BSTree<int,int> myTree_copy;
  BSTree<int,int> myTree_move;
  BSTree<int,int> myTree_copy_new;
  BSTree<int,int> myTree_move_new;
  std::pair<int,int> keyval;


  if (argc != 2){
    fprintf ( stderr , " Usage : %s [Tree size] \n", argv[0] );
    exit(1) ; }
 
  else{ fprintf( stdout, "running BST... \n" ); }
 

  std::cout << "Before inserting numbers, print the tree in a traversal order:\n";
  myTree.TreeTraversal();


  for(int i = 0; i < GetSize; i++) {
    keyval.first = TreeKeys[i];
    keyval.second = TreeValues[i];
    myTree.InsertKey(keyval); }

  std::cout << "\nPrinting the ORIGINAL tree in a traversal order after inserting numbers " << std::endl;
  myTree.TreeTraversal();
  std::cout << "\n ";

  /* Calling the class iterator to print the ORIGINAL tree */
  std::cout << "\nPrinting keys & values of the ORIGINAL tree using the class iterator\n";
  for (auto iter = myTree.begin(); iter != myTree.end(); ++iter){
    keyval = *iter;
    std::cout << keyval.first <<":"<< keyval.second << " ";
    std::cout << " " << std::endl; }


  /* Calling the class const_iterator to print the ORIGINAL tree */
  std::cout << "\nPrinting keys & values of the ORIGINAL tree using the class const_iterator\n";
  for (auto iter = myTree.cbegin(); iter != myTree.cend(); ++iter){
    keyval = *iter;
    std::cout << keyval.first <<":"<< keyval.second << "\n"; }


  /* Calling Tree Find function */
  std::cout << "\nRunning Find function...\n";
  
  /* Find the largest element in the tree (not used in the benchmarking process) */
  std::cout << "The largest element in the ORIGINAL tree is" << " ["
  << myTree.TreeFindLargest(keyval) << "] " << std::endl;

  /* Find the smallest element in the tree (not used in the benchmarking process) */
  std::cout << "The smallest element in the ORIGINAL tree is" << " ["
  << myTree.TreeFindSmallest(keyval) << "] " << std::endl;


  /* Find element(s) in the tree -- WITHOUT using the const_iterator */
  /* Using std::chrono to measure the time needed to find element(s) */
  std::cout << "Find element(s) in the tree WITHOUT using iterator \n";
  auto start = std::chrono::high_resolution_clock::now();

  int num = 14;
  if (myTree.TreeFind(num))
    std::cout << "Yes! Number [" << num << "] is found in the tree...\n"; 
  else
    std::cout << "No! Number [" << num << "] is NOT found in the tree...\n"; 

  /* Same job can be executed using "IsFound Function" */
  /*if (myTree.IsFound(keyval, num)) 
    std::cout << "Yes! Number [" << num << "] is found in the tree...\n"; 
  else
    std::cout << "No! Number [" << num << "] is NOT found in the tree...\n"; */
  
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end-start;

  /* printing time */
  std::cout << "Elapsed time to look for the element(s) in the ORIGINAL tree of size [" << GetSize <<"] is "
            << diff.count() << " [s]\n";

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
  myTree_move.TreeBalance(myTree_move.begin(), GetSize);
  std::cout << "Printing the ORIGINAL tree after balance...\n" << myTree_move << std::endl;
  //myTree.TreeTraversal(); // 

  /* Calling Tree Clear function */
  std::cout << "\nRunning Tree Clear function...\n";
  myTree.TreeClear();
  std::cout<<'\n';

  /* Make sure that the ORIGINAL tree is freed */
  std::cout << "\nPrinting the ORIGINAL tree after calling Clear() function...\n" 
  << myTree << std::endl;





  /** Running the Tree functions with NEW tree of random values **/
  int size = atol(argv[1]);
  int TestKeys[size];
  int TestValues[size];
  int GetSizeNew = *(&TestKeys + 1) - TestKeys;

  /* Generating new tree of random values */
  std::cout << "Generating a new tree of random values" << std::endl;
  for(int i=0; i<  size; i++){
    TestKeys[i] = TestValues[i] = (rand()%size)+1;
    //TestValues[i] = (rand()%size)+1;

    /* print new keys and values */
    //std::cout << TestKeys[i] << " " << TestValues[i] << std::endl;

    /* Refilling randomly "tree keyval" -- std::pair */
    keyval.first = TestKeys[i];
    keyval.second = TestValues[i];
    std::cout << "Random values  " << keyval.first << ":" << keyval.second << std::endl; 
    myTree.InsertKey(keyval); }

  
  /* Calling Copy semantics */
  std::cout << "\nRunning copy semantics [new tree]...\n";
  myTree_copy_new = myTree;
  std::cout << "\nPrinting the [new tree] after copying ...\n" << myTree_copy_new;


  /* Calling move semantics */
  std::cout << "Running move semantics [new tree]...\n";
  myTree_move_new = std::move(myTree_copy_new);
  std::cout << "\nPrinting the ORIGINAL tree after moving...\n" << myTree_move_new;
  std::cout<<'\n';


  /* Testing Tree Balance function for the new tree  */
  std::cout << "\nRunning Balance function [new tree]...";
  myTree_move_new.TreeBalance(myTree.begin(), GetSizeNew);
  std::cout << "\nPrinting the NEW tree after balance...\n" << myTree_move_new << std::endl;

  /* Testing Tree Find function */
  std::cout << "\nRunning Find function [new tree]...\n";

  /* Find the largest number in the tree and record the elapsed time*/
  std::cout << "The largest element in the NEW tree is" << " ["
  << myTree_move_new.TreeFindLargest(keyval) << "] " << std::endl;

  /* Find the smallest element in the tree (not used in the benchmarking process) */
  std::cout << "The smallest element in the NEW tree is" << " ["
  << myTree_move_new.TreeFindSmallest(keyval) << "] " << std::endl;

  /* Find element(s) in the NEW tree -- WITHOUT using the iterator */
  /* Using std::chrono to measure the time */
  std::cout << "Find element(s) in the NEW tree WITHOUT using iterator \n";
  
  #define NMAX 5
  int randnum;
  srand(time(NULL));
  for(int i=0;i < NMAX;i++)
  {
    randnum = (rand()%size)+1;
     
    auto start_new = std::chrono::high_resolution_clock::now();
    if (myTree_move_new.TreeFind(randnum))
      std::cout << "Yes! Number [" << randnum << "] is found in the NEW tree...\n"; 
    else
      std::cout << "No! Number [" << randnum << "] is NOT found in the NEW tree...\n"; 
    auto end_new = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> diff_new = end_new - start_new;
  std::cout << "Elapsed time to look for the element(s) in the NEW tree of size [" << size <<"] is "
            << diff_new.count() << " [s]\n";

  /* print benchmarking data to a file */
  myTree_move_new.TreeBench(randnum, size, diff_new.count()); 
  }

 

  /* Find element(s) in the new tree -- niavely I used const_iterator */
  myTree_move_new.TreeFind_iter(7);

  
  /* Calling Tree Clear function */
  std::cout << "\nRunning Tree Clear function...\n";
  myTree_move_new.TreeClear();
  std::cout<<'\n';

  /* Make sure that the NEW tree is freed */
  std::cout << "\nPrinting the NEW tree after calling Clear() function...\n"
  << myTree_move_new<< std::endl;


  return 0;
}
