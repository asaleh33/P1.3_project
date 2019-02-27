#include<iostream>
#include<cstdlib>
#include<algorithm>
#include <memory>

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
	std::cout << "constructor: " << keyval.first << std::endl;
    }

    ~Node(){std::cout << "destructing: " << keyval.first << std::endl;} 
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
  void TreeClear(); 
  
  void InsertKeyRecursive(const std::pair<const K,V>& pair, Node* Ptr); 
  void TreeTraversalRecursive(Node* Ptr);
  void CopyTreeRecursive(const BSTree<K, V>::Node* Ptr);
  void TreeClearRecursive(Node* Ptr); 
};


/* Tree Insert function */ 
template<class K, class V>  
void BSTree<K,V>::InsertKey(const std::pair<const K,V>& keyval)
{
  /* head has to be pointed to nullptr */
  if(head == nullptr){ head.reset(new Node{keyval, nullptr}); }

  else
    InsertKeyRecursive(keyval, head.get());

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


/* Copy semantics:: copy Tree constructor -- deep copy */
template <class K, class V>
BSTree<K,V>::BSTree(const BSTree<K, V>& Tree)
{    
  std::cout << "Copy Tree constructor" << std::endl;
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

  std::cout << "End of copy assignment" << std::endl;
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
    std::cout << "Move Tree\n";
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
    return os <<"" << std::endl;}

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




