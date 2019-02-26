#include<iostream>
#include<cstdlib>
#include<algorithm>
#include <memory>

template<class K, class V>
class BSTree
{

private:

  /* to sort number of nodes */
  std::size_t TreeSize; 

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
    
  /* Tree Constructor */  
  BSTree(): TreeSize{0} {}

  /* Tree Destructor */
  ~BSTree() noexcept = default;
    
  /* Methods -- memebr functions */
  void InsertKey(const std::pair<const K,V>& pair);
  void TreeTraversal();
  
  void InsertKeyRecursive(const std::pair<const K,V>& pair, Node* Ptr); 
  void TreeTraversalRecursive(Node* Ptr);
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
