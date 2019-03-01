#include<iostream>
#include<cstdlib>
#include<algorithm>
#include <memory>
#include <utility>      // std::pair, std::make_pair

template<class K, class V>
class BSTree
{

private:

  /* to sort number of nodes */
  std::size_t _size;

  struct Node;
  typedef std::unique_ptr<Node> SmartTreeNode;
  struct Node{

    std::pair<const K,V> keyval;
    Node* parent;
    SmartTreeNode left;
    SmartTreeNode right;

    Node(const std::pair<const K,V> & value, Node* p):keyval{value},parent{p},left{nullptr},right{nullptr}
    {
	std::cout << "Constructing: " << keyval.first << ":" << keyval.second << std::endl;
    }

    ~Node(){std::cout << "Destructing: " << keyval.first << ":" << keyval.second << std::endl;}
  };

  /* Declaring the head pointer */
  SmartTreeNode head;

public:

  template<class KOS, class VOS>
  friend std::ostream& operator<<(std::ostream&, const BSTree<KOS, VOS>&);

  /* Iterator class */
  class Iterator{
    using Node = BSTree<K, V>::Node;
    Node* current;

    public:
      Iterator(Node* n) : current{n} {}
      std::pair<const K,V>& operator*() const { return {current->keyval}; }

      Iterator& operator++(){
        if (! (current-> right.get()) ){
          current = current-> parent;
        return *this; }

        current = current->right.get();

        while (current->left.get()){
          current = current->left.get(); }
      return *this;
      }

      bool operator==(const Iterator& other) { return current == other.current; }  // they watch same node
      bool operator!=(const Iterator& other) { return !(*this == other); }
  };


  /* ConstIterator class */
  class ConstIterator: public Iterator{
    public:
      using parent = BSTree<K,V>::Iterator;
      using parent::Iterator;

      const std::pair<const K,V>& operator*() const { return parent::operator*(); }
  };

  /* begin function of the iterator class */
  Iterator begin() {
    Node *current = head.get();
    while (current->left){
      current = current->left.get(); }
  return Iterator(current); }

  Iterator begin() const {
    Node *current = head.get();
    while (current->left){
      current = current->left.get(); }
  return Iterator(current); }


  /* end function of the iterator class */
  Iterator end() {
  return Iterator{nullptr}; }

  Iterator end() const{
  return Iterator{nullptr}; }

  /* cbegin function of the ConstIterator class */
  ConstIterator cbegin(){
    Node *current = head.get();
    while (current->left.get()){
      current = current->left.get(); }
  return ConstIterator(current); }

  /* end function of the ConstIterator class */
  ConstIterator cend() {
  return ConstIterator{nullptr}; }

  /* Tree Constructor */
  BSTree(): _size{0} {}
  /* Tree Destructor */
  ~BSTree() noexcept = default;

  /* Copy Tree constructor -- deep copy */
  BSTree(const BSTree&);

  /* Copy Constructor assignment -- deep copy */
  BSTree& operator=(const BSTree& Tree);


  /* Move Constructor */
  BSTree(BSTree&& Tree) noexcept;

  /* Move Constructor assignment */
  BSTree& operator=(BSTree&& Tree) noexcept;

  /* Methods -- memebr functions */
  void InsertKey(const std::pair<const K,V>& pair);
  void TreeTraversal();
  void TreeFind_iter(const std::pair<const K,V>& pair); /* in a naive way (useing the class iterator) */
  bool TreeFind(const std::pair<const K,V>& pair, int);
  int TreeFindLast(const std::pair<const K,V>& pair);
  void TreeBalance(Iterator begin_balance, std::size_t _size, const BSTree<K, V>& Tree);
  bool Search(const std::pair<const K,V>& pair, int); /* same as TreeFind */
  void TreeClear();
  void InsertKeyRecursive(const std::pair<const K,V>& pair, Node* Ptr);
  void TreeTraversalRecursive(Node* Ptr);
  bool TreeFindRecursive(const std::pair<const K,V>& pair, int, Node* Ptr);
  int TreeFindLastRecursive(const std::pair<const K,V>& pair, Node* Ptr);
  void TreeBalanceRecursive(Iterator begin_balance, std::size_t _size, const BSTree<K, V>& Tree);
  void CopyTreeRecursive(const BSTree<K, V>::Node* Ptr);
  void TreeClearRecursive(Node* Ptr);
};


/* Tree Insert function */
template<class K, class V>
void BSTree<K,V>::InsertKey(const std::pair<const K,V>& keyval)
{
  /* head "up" has to be pointed to nullptr */
  if(head == nullptr){ head.reset(new Node{keyval, nullptr}); }

  else {InsertKeyRecursive(keyval, head.get());}

  return;
}

/* Tree Insert recursive function */
template<class K, class V>
void BSTree<K,V>::InsertKeyRecursive(const std::pair<const K,V>& keyval, Node* Ptr)
{
  /* case 1 */
  if(keyval.first < Ptr->keyval.first)
  {
    if(Ptr-> left.get() != nullptr)
    {
      InsertKeyRecursive(keyval, Ptr->left.get());
    }
    else
    {
      Ptr->left.reset(new Node{keyval, Ptr});
    }
  }

  /* case 2 */
  if(keyval.first > Ptr->keyval.first)
  {
    if(Ptr-> right.get() != nullptr)
    {
      InsertKeyRecursive(keyval, Ptr->right.get());
    }
    else
    {
      Ptr->right.reset(new Node{keyval, Ptr->parent});
    }
  }

  else
  {
    std::cout << "key" << " " << keyval.first << " " << "has been already added to the tree" << std::endl;
  }
  return;
}


/* Tree traversal order */
template<class K, class V>
void BSTree<K,V>::TreeTraversal()
{
  TreeTraversalRecursive(head.get());
  return;
}

/* Recursive Tree traversal order */
template<class K, class V>
void BSTree<K,V>::TreeTraversalRecursive(Node* Ptr)
{
  if(head != nullptr)
  {
    if(Ptr->left.get() != nullptr)
    {
      /* function is called recursivly */
      TreeTraversalRecursive(Ptr->left.get());
    }

    /* print contents of the current node */
    std::cout << Ptr->keyval.first << ":" << Ptr->keyval.second << " ";

    /* if possible to go to right, call the functon recursively */
    if(Ptr->right.get() != nullptr)
    {
      TreeTraversalRecursive(Ptr->right.get());
    }
  }
  else
  {
    std::cout << "The original tree has no numbers [empty tree!]\n\n";
  }
  return;
}


/* Tree Find function can nively find a specific number in the tree using (const_iterator) */
template<class K, class V>
void BSTree<K,V>::TreeFind_iter(const std::pair<const K,V>& keyval)
{
  const int num = 3;
  for (auto iter = cbegin(); iter != cend(); ++iter) {
    auto keyval = *iter;
    //std:: cout << "TESTCONST " << keyval.first << "\n";
    if (keyval.first == num) {
      std::cout << "Number [" << num << "] is found in the tree!" << "\n"; break; }}
}


/* Tree Find largest function */
template<class K, class V>
int BSTree<K,V>::TreeFindLast(const std::pair<const K,V>& keyval)
{
  /* Checking if the tree is empty */
  if (head == nullptr) {
    std::cout << "The original tree has no elements! \n";
    return -1; } // returning a negative value, which is not included in the tree

  return TreeFindLastRecursive(keyval, head.get());
}


template<class K, class V>
int BSTree<K,V>::TreeFindLastRecursive(const std::pair<const K,V>& keyval, Node* Ptr)
{
  /* check if right pointer is pointing to a Node. The function
     is looking for the smallest element of the tree. */
  if (Ptr-> right.get() != nullptr) {
    return TreeFindLastRecursive(keyval, Ptr-> right.get()); }
  else {
    return Ptr->keyval.first; }
}


template<class K, class V>
bool BSTree<K,V>::TreeFind(const std::pair<const K,V>& keyval, int num)
{
  /* Checking if the tree is empty */
  if (head == nullptr) {
    std::cout << "The original tree has no elements! \n";
    return -1; } // returning a negative value ouside the tree range

  return TreeFindRecursive( keyval, num, head.get() );
}


template<class K, class V>
bool BSTree<K,V>::TreeFindRecursive(const std::pair<const K,V>& keyval, int num, Node*Ptr)
{

  Ptr = head.get();
  while (Ptr != nullptr) 
  { 
    /* go to right subtree */
    if (num > Ptr->keyval.first) 
      Ptr = Ptr->right.get(); 
  
    /* go to left subtree  */ 
    else if (num < Ptr->keyval.first) 
      Ptr = Ptr->left.get(); 
    else
      /* if the key is found return 1 */
      return true; 
  } 
  return false;
}


template<class K, class V>
bool BSTree<K,V>::Search(const std::pair<const K,V>& keyval, int num)
{
    Node*Ptr;
    Ptr = head.get();

    while (Ptr != nullptr) 
    { 
        // go to right subtree 
        if (num > Ptr->keyval.first) 
            Ptr = Ptr->right.get(); 
  
        // go to left subtree  
        else if (num < Ptr->keyval.first) 
            Ptr = Ptr->left.get(); 
        else
            // if the key is found return 1
            return true; 
    } 
    return false; 

} 







    /*else
    {
      Ptr->left.reset(new Node{keyval, Ptr});
    }
  }*/

  /* case 2 */
  /*if(keyval.first > Ptr->keyval.first)
  {
    if(Ptr-> right.get() != nullptr)
    {
      InsertKeyRecursive(keyval, Ptr->right.get());
    }
    else
    {
      Ptr->right.reset(new Node{keyval, Ptr->parent});
    }
  }

  else
  {
    std::cout << "key" << " " << keyval.first << " " << "has been already added to the tree" << std::endl;
  }*/
  
  
   
  

















/* Tree Balance function */
template<class K, class V>
void BSTree<K,V>::TreeBalance(Iterator begin_balance, std::size_t _size, const BSTree<K, V>& Tree)
{

  std::size_t median, lhs, rhs;
  median = _size/2 + 1;
  //Iterator iter = begin_balance;    // ------------>> or
  Iterator iter{begin_balance};

  lhs = median - 1;
  TreeBalanceRecursive(begin_balance, _size, Tree);

  rhs = median -1 + (_size % 2);
  TreeBalanceRecursive(begin_balance, lhs, Tree);
  TreeBalanceRecursive(++iter, rhs, Tree);

  return;
}


/* Tree Balance recursive function */
template<class K, class V>
void BSTree<K,V>::TreeBalanceRecursive(Iterator begin_balance, std::size_t _size, const BSTree<K, V>& Tree)
{

  if(_size == 1) InsertKey(*begin_balance);

  std::size_t median = _size/2 + 1;
  Iterator iter = begin_balance;
  for(std::size_t i=0; i < median; i++)
    ++iter;
    InsertKey(*iter);

  return;
}


/* int veckey[] = {100, 200, 300, 40, 500, 60, 70, 8000, 900};
  int vecval[] = {100, 200, 300, 40, 500, 60, 70, 8000, 900};
  std::pair<int,int> vec_keyval; */

  /*std::pair<int,int> vec_left;
  std::pair<int,int> vec_right; */

  //int _size_vec = sizeof(veckey)/sizeof(veckey[0]);

  /* Declaring std vector of pairs */
  //std::vector<std::pair <int,int> > Vector;

  /* Inserting values in pairs */
  //for (int i=0; i<=8; i++) Vector.push_back( std::make_pair(veckey[i], vecval[i]) );

  /* Printing the pair vector */
  /*for (int i=0; i< Vector.size(); i++) {
    std::cout << Vector[i].first << ":" << Vector[i].second << std::endl; }*/

  /* Calling the class iterator and print the vector contents */
  //std::cout << "Printing vector of size [" << Vector.size() << "] in pairs...\n";
  /*for (auto iter = Vector.begin(); iter != Vector.end(); ++iter){
    vec_keyval = *iter; } */
    //std::cout << vec_keyval.first << ":" << vec_keyval.second << std::endl;

  //std::cout << "\nTEST FROM BALANCE\n";


    //std::size_t const vec_med = Vector.size() / 2;


  //InsertKey(vec_keyval);
  //TreeTraversal(vec_keyval); }


  /*if (Vector.size() > 1){
    std::size_t const VecMedian = Vector.size() / 2+1;
    //std::cout << "TEST_MEDIAN:" << " " << VecMedian << std::endl;
    TreeBalanceRecursive();

    std::vector<std::pair <int,int> > VecLeft(Vector.begin(), Vector.begin() + VecMedian);
    TreeBalanceRecursive();

    std::vector<std::pair <int,int> > split_hi(Vector.begin() + VecMedian, Vector.end());
    TreeBalanceRecursive();
  } */

  /*else{
    std::cerr << "[Error!] Vector size [" <<  Vector.size() << "]"<< " is indivisible. Try bigger size..." << '\n';
    std::exit(-100);
  } */


/* Copy semantics:: copy Tree constructor -- deep copy */
template <class K, class V>
BSTree<K,V>::BSTree(const BSTree<K, V>& Tree)
{
  std::cout << "Copy Tree constructor\n" << std::endl;
  CopyTreeRecursive( Tree.head.get() );
}

/* Copy assignemt for the tree */
template<class K, class V>
BSTree<K, V>& BSTree<K, V>::operator=(const BSTree<K, V>& Tree)
{
  //(*this).TreeClear();              // clear memory
  head.reset();			      // clear memory
  auto Tree_temp = Tree;              // copy Tree to Tree_temp
  (*this) = std::move(Tree_temp);     // implement move assignment

  std::cout << "End of copy assignment\n" << std::endl;
  return *this;
}


/* Copy helper function  */
template <class K, class V>
void BSTree<K,V>::CopyTreeRecursive(const BSTree<K, V>::Node* Ptr)
{
  if (Ptr) {
    InsertKey(Ptr->keyval);
    CopyTreeRecursive(Ptr->left.get());
    CopyTreeRecursive(Ptr->right.get());
  }

  return;
}


/* Move semantics */
template <class K, class V>
BSTree<K, V>::BSTree(BSTree&& Tree) noexcept
  :head{std::move(Tree.head)}, _size{std::move(Tree._size)}{
    Tree._size = 0;
    std::cout << "\nMove Tree\n";
}

/* Move assignment */
template <class K, class V>
BSTree<K, V>& BSTree<K, V>::operator=(BSTree&& Tree) noexcept
{
  std::cout << "Move assignment\n";
  _size = std::move(Tree._size);
  head = std::move(Tree.head);
  Tree._size = 0;
  std::cout << "End of move assignment" << std::endl;
  return *this;
}


template <class K, class V>
std::ostream& operator<<(std::ostream& os, const BSTree<K, V>& Tree)
{
  if(!Tree._size){
    return os <<"The original tree is empty" << std::endl;}

  for (const auto& x : Tree)
    os << x.first << ":" << x.second << " ";
    os << " " << std::endl;
  return os;
}


/* Tree Clear function */
template<class K, class V>
void BSTree<K,V>::TreeClear()
{
  /* It starts its recursive process from the head node */
  TreeClearRecursive(head.get());

  /* Checking if the tree is already cleared */
  if (head == nullptr) {
    std::cout << "The tree has been cleared..." << std::endl; }
  return;
}

/* Tree Clear recursive function */
template<class K, class V>
void BSTree<K,V>::TreeClearRecursive(Node* Ptr)
{
  /* Check if the tree is empty or not, then clear the tree*/
  if (head != nullptr){
    /* Reset head to nullptr and then set empty tree of 0 size */
    head.reset();
    _size=0; }

  else
  {
    std::cout << "From the Clear function, the original tree has no elements to be cleared!" << std::endl; 
  }
  return;
}


/* Make arrays function */

void MakeArray(int arr[], int length) {
  for (int n=0; n < length; ++n)
    std::cout << "Making an array for Testing Balance function\n" << arr[n] << ' ';
  std::cout << '\n';
}





