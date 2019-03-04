#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<memory>
#include <chrono>
#include <map>
#include"BSTree.h"

int TreeKeys[9] = {8,10,14,13,3,6,7,4,1};
int TreeValues[9] = {8,10,14,13,3,6,7,4,1};
int GetSize = *(&TreeKeys + 1) - TreeKeys;


int main(int argc, char** argv) {

  if (argc != 2){
    fprintf ( stderr , " Usage : %s [Tree size] \n", argv[0] );
    exit(1) ; }
 
  else{ fprintf( stdout, "running BST... \n" ); }
 

  BSTree<int,int> myTree;
  std::pair<int,int> keyval;


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

  int num = 6;
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

  /* Printing time */
  std::cout << "Elapsed time to look for the element(s) in the ORIGINAL tree of size [" << GetSize <<"] is "
            << diff.count() << " [s]\n";

  /* Calling copy semantics */
  BSTree<int,int> myTree_copy;
  BSTree<int,int> myTree_move;
  
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
  //myTree.TreeTraversal(); 

  /* Calling Tree Clear function */
  std::cout << "\nRunning Tree Clear function...\n";
  myTree.TreeClear();
  std::cout<<'\n';

  /* Make sure that the ORIGINAL tree is freed */
  std::cout << "\nPrinting the ORIGINAL tree after calling Clear() function...\n" 
  << myTree << std::endl;





  /** Running the Tree functions with NEW tree of random values **/
  int size = atol(argv[1]);
  int NewKeys[size];
  int NewValues[size];
  int GetSizeNew = *(&NewKeys + 1) - NewKeys;

  std::map<int,int> keyval_map;

  /* Generating new tree of random values */
  std::cout << "Generating a new tree of random values" << std::endl;
  for(int i=0; i<  size; i++){
    NewKeys[i] = NewValues[i] = (rand()%size)+1;
    //NewValues[i] = (rand()%size)+1;

    /* print new keys and values */
    //std::cout << NewKeys[i] << " " << NewValues[i] << std::endl;

    /* Refilling randomly "tree keyval" -- std::pair */
    keyval.first = NewKeys[i];
    keyval.second = NewValues[i];
    //std::cout << "Random values  " << keyval.first << ":" << keyval.second << std::endl; 
    myTree.InsertKey(keyval);
    
    /* std::map -- insert */
    keyval_map.insert(std::pair<int, int>(NewKeys[i], NewValues[i]));
  }

  
  /* Calling Copy semantics */
  BSTree<int,int> myTree_copy_new;
  BSTree<int,int> myTree_move_new;
  
  std::cout << "\nRunning copy semantics [new tree]...\n";
  myTree_copy_new = myTree;
  std::cout << "\nPrinting the [new tree] after copying ...\n" << myTree_copy_new;


  /* Calling move semantics */
  std::cout << "Running move semantics [new tree]...\n";
  myTree_move_new = std::move(myTree_copy_new);
  std::cout << "\nPrinting the [new tree] after moving ...\n" << myTree_move_new;
  std::cout<<'\n';

  /* Measuring time of find an element in unbalanced [new tree] */
  #define NMAX 10
  int random_unbalanced;
  srand(time(NULL));
  std::chrono::duration<double> diff_new_unbalanced;
  
  for(int i = 0; i < NMAX; i++)
  {
    random_unbalanced = (rand()%size)+1;

    auto start_new_unbalanced = std::chrono::high_resolution_clock::now();

    if (myTree_move_new.TreeFind(random_unbalanced))
      std::cout << "Yes! Number [" << random_unbalanced << "] is found in the [new unbalanced tree]...\n"; 
    else
      std::cout << "No! Number [" << random_unbalanced << "] is NOT found in the [new unbalanced tree]...\n"; 

    auto end_new_unbalanced = std::chrono::high_resolution_clock::now();

    diff_new_unbalanced = (end_new_unbalanced - start_new_unbalanced);

    std::cout << "Elapsed time to look for the element(s) in the [new unbalanced tree] of size [" << size <<"] is "
            << diff_new_unbalanced.count() << " [s]\n"; 

    /* print benchmarking data to a file */
    myTree_move_new.TreeBenchUnBalance(size, random_unbalanced, diff_new_unbalanced.count());
    }

 
  
  /* Calling Tree Balance function for the new tree  */
  std::chrono::duration<double> diff_new_balance;
  std::cout << "\nRunning Balance function [new tree]...";

  /* Measuring balance time */
  auto start_new_balance = std::chrono::high_resolution_clock::now();
  
  myTree_move_new.TreeBalance(myTree_move_new.begin(), GetSizeNew);

  auto end_new_balance = std::chrono::high_resolution_clock::now();

  diff_new_balance = (end_new_balance - start_new_balance);
  std::cout << "\nElapsed time of balance function of the [new tree] of size [" << size <<"] is "
            << diff_new_balance.count() << " [s]\n";

  /* Save benchmarking data resulted from map find function to a file */
  myTree_move_new.TreeBenchBalance(size, diff_new_balance.count());

  std::cout << "\nPrinting the [new tree] after balance...\n" << myTree_move_new << std::endl;




  /* Calling Tree Find function */
  std::cout << "\nRunning Find function [new tree]...\n";

  /* Find the largest number in the tree and record the elapsed time*/
  std::cout << "The largest element in the [new tree] is" << " ["
  << myTree_move_new.TreeFindLargest(keyval) << "] " << std::endl;

  /* Find the smallest element in the tree (not used in the benchmarking process) */
  std::cout << "The smallest element in the [new tree] is" << " ["
  << myTree_move_new.TreeFindSmallest(keyval) << "] " << std::endl;

  /* Find element(s) in the NEW tree -- WITHOUT using the iterator */
  /* Using std::chrono to measure the time */
  std::cout << "Find element(s) in the [new tree] WITHOUT using iterator \n";
  

  int random;
  srand(time(NULL));
  std::chrono::duration<double> diff_new;

  for(int i=0;i < NMAX;i++)
  {
    random = (rand()%size)+1;
     
    auto start_new = std::chrono::high_resolution_clock::now();

    if (myTree_move_new.TreeFind(random))
      std::cout << "Yes! Number [" << random << "] is found in the [new tree]...\n"; 
    else
      std::cout << "No! Number [" << random << "] is NOT found in the [new tree]...\n"; 

    auto end_new = std::chrono::high_resolution_clock::now();

    diff_new = (end_new - start_new);
    std::cout << "Elapsed time to look for the element(s) in the [new tree] of size [" << size <<"] is "
            << diff_new.count() << " [s]\n";

    /* print benchmarking data to a file */
    myTree_move_new.TreeBench(size, random, diff_new.count());
  }

 
  /* Find element(s) in the new tree -- niavely I used const_iterator to compare with */
  int randnom_iter;
  srand(time(NULL));
  std::chrono::duration<double> diff_new_iter;

  for(int i=0;i < NMAX;i++)
  {
    randnom_iter = (rand()%size)+1;
     
    auto start_new_iter = std::chrono::high_resolution_clock::now();
  
    myTree_move_new.TreeFind_iter(randnom_iter);
  
    auto end_new_iter = std::chrono::high_resolution_clock::now();

    diff_new_iter = end_new_iter - start_new_iter;
    std::cout << "Elapsed time to look for the element(s) in the [new tree] of size [" << size <<"] using iterator is "
    	      << diff_new_iter.count() << " [s]\n";

    /* Save benchmarking data resulted from iterator to a file */
    myTree_move_new.TreeBenchIter(size, randnom_iter, diff_new_iter.count()); 
  }	


  /* Find element(s) -- std::map */
  int randnom_map;
  srand(time(NULL));
  std::map<int,int>::iterator iter_map;
  std::chrono::duration<double> diff_new_map;
  
  for(int i=0;i < NMAX;i++)
  {
    randnom_map = (rand()%size)+1;
  
    auto start_new_map = std::chrono::high_resolution_clock::now();

    iter_map = keyval_map.find(randnom_map);
    
    auto end_new_map = std::chrono::high_resolution_clock::now();

    diff_new_map = end_new_map - start_new_map;
    std::cout << "Elapsed time of looking for the element(s) using std::map of size [" << size <<"] is "
            << diff_new_map.count() << " [s]\n";

    std::cout << "Number [" << keyval_map.find(randnom_map)->second << "] is found (std::map) \n";

    /* Erease the iterator after find the element(s) */
    if (iter_map != keyval_map.end()) { keyval_map.erase (iter_map); }
   
    /* Save benchmarking data resulted from map find function to a file */
    myTree_move_new.TreeBenchMap(size, randnom_map, diff_new_map.count());
  }
 
 
  /* Calling Tree Clear function */
  std::cout << "\nRunning Tree Clear function...\n";
  myTree_move_new.TreeClear();
  std::cout<<'\n';

  /* Make sure that the NEW tree is freed */
  std::cout << "\nPrinting the NEW tree after calling Clear() function...\n"
  << myTree_move_new<< std::endl;


  return 0;
}
