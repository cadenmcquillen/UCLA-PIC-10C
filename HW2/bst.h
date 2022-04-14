#include<utility>
#include<functional>
#include<stdexcept>


#ifndef bst_h
#define bst_h
namespace pic10c{
template <typename T, typename compare_type =  std::less<T>>
/**
 @class bst A binary search tree with parent node
 @tparam T The type of object that the bst holds
 @tparam compare_type The comparison function used to evaulate node placement of bst
 */
class bst{
public:
    class iterator; //forward declared to be friend of node class
    
    class node{
        friend bst;
        friend iterator;
    private:
        T value;
        node *left;
        node *right;
        node *parent;
    public:
        /**
         Node Constructor
         @param nodeVal  A value of type T for that node to hold
         */
        node(T nodeVal): value(nodeVal), left(nullptr), right(nullptr), parent(nullptr){} //constructor
       
    };
    
    class iterator{
        friend bst;
    private:
        /**
         Iterator Constructor
         @param CurrentNode  A pointer to a node that we are currently at
         @param Tree The bst we are iterating on
         */
        iterator(node* CurrentNode, const bst* Tree): CurrentPos(CurrentNode), Tree(Tree){} //constructor
        node *CurrentPos;
        const bst *Tree;
    public:
        /**
         Overloaded Prefix ++ operator for iterator class
         @return forward incremented iterator
         */
        iterator &operator++(){
            if(CurrentPos==nullptr){
                CurrentPos = Tree->root; //start at the root
            
                if (CurrentPos == nullptr){ //++ on empty tree
                    throw std::logic_error {"Tree is empty"};
                }
                while(CurrentPos->left != nullptr){ //go to smallest value of tree
                    CurrentPos = CurrentPos->left;
                }
            }
            else{
                if (CurrentPos->right != nullptr){// if there is a right child
                    CurrentPos = CurrentPos->right; // move right once
                    
                    while(CurrentPos->left!=nullptr){ //then as far left as possible
                        CurrentPos = CurrentPos->left;
                    }
                }
                else{ //if no right subtree
                     node *temp = CurrentPos->parent; //move up
                     while(temp!=nullptr && CurrentPos == temp->right){ //keep moving up until parent is null or reach left child
                        CurrentPos = temp;
                        temp = temp->parent;
                    }
                    CurrentPos = temp;
                }

            }
            return *this;
        }
        /**
         Overloaded Postfix ++ operator for iterator class
         @return A new forward incremented iterator
         */
        iterator &operator++ (int){
            iterator temp(*this); //create temp variable
            operator++(); //call ++ on temp
            return temp;
        }
        /**
         Overloaded Pretfix -- operator for iterator class
         @return A decremented iterator
         */
        iterator &operator--(){ //similar to prefix ++ but for --
            if(CurrentPos == nullptr){
                
                CurrentPos = Tree->root; //start at root
                while(CurrentPos->right != nullptr){ //traverse to largest value
                    CurrentPos = CurrentPos->right;
                }
            }
            else{
                if(CurrentPos->left != nullptr){ //if there is a left child
                    
                    CurrentPos = CurrentPos->left; //move left
                    while(CurrentPos->right!=nullptr){ //then as far right as possible
                        CurrentPos = CurrentPos->right;
                    }
                }
                else{ //if there is a node to the right
                    
                    node *temp = CurrentPos->parent;
                    while(temp!= nullptr && CurrentPos == temp->left){ //backtrack to reach right child
                        CurrentPos = temp;
                        temp = temp->parent;
                    }
                    CurrentPos = temp;
                }
            }
            return *this;
        }
        /**
         Overloaded Postfix -- operator for iterator class
         @return A new decremented iterator
         */
        iterator &operator-- (int){
            iterator temp(*this); //create temp variable
            operator--(); //call -- on temp
            return temp;
        }
        /**
         Overloaded Derefernce Operator for iterator class
         @return a refrence to a copy of the value at the current node
         */
        const T& operator*() const{
            T& temp = (CurrentPos->value);
            return temp;
            
        }
        /**
         Overloaded Arrow Operator for iterator class
         @return A refrence to the value at the current node
         */
        const T* operator->() const{ //arrow operator
            return & (CurrentPos->value);
        }
        /**
         Overloaded == Comparison Operator  for iterator class
         @param left A reference to a iterator
         @param right A reference to another iterator
         @return A boolean for if two iterators are equal
         */
        friend bool operator==(const iterator& left, const iterator& right) //comparison operator
        {
            if( (left.CurrentPos == right.CurrentPos) && (left.Tree == right.Tree)){
                return true;
            }
            else{
                return false;
            }
        }
        /**
         Overloaded != Comparison Operator  for iterator class
         @param left A reference to a iterator
         @param right A reference to another iterator
         @return A boolean for if two iterators are not equal
         */
        friend bool operator!=(const iterator& left, const iterator& right){
            return !(left == right);
        }

    };
    /**
     Helper Function for destructor that recursively deletes each node
     @param root A pointer to root of a bst
     */
    void deleteTree(node* root){// to recursively delete the tree
        if (root == nullptr){ //recursive base case
            return;
        }
        else{
            deleteTree(root->left); //delete left child first
            deleteTree(root->right);// then delete right child
            delete root; //delete itself
        }
        return;
    }

    /**
     BST Default Constructor
     */
    bst():pred(compare_type{}),TreeSize(0),root(nullptr){} //default constuctor with std:less<> as default pred
    /**
     BST Constructor
     @param Comparison_Function A comparison operator to be used
     */
    bst(const compare_type& Comparison_Function): pred(Comparison_Function),TreeSize(0),root(nullptr){}
    /**
     BST Destructor
     */
    ~bst(){  //destructor
        deleteTree(root);
    }
    /**
     Helper function for copy constructor that recursively copies each node
     @param rhs A pointer to a root node from which we would like to copy the rest of the tree
     @return A pointer to the root node of the copied tree
     */
    node* CopyHelper(node* rhs){
        if(rhs==nullptr){ //base case
            return nullptr;
        }
        else{
            node* lhs = new node(rhs->value); //create new node
            lhs->left = CopyHelper(rhs->left); //copy each node recursively
            if(lhs->left!= nullptr){ //if it has a left child
                lhs->left->parent = lhs; //make that child's parent itself
            }
            lhs->parent = rhs->parent;
            lhs->right = CopyHelper(rhs->right); //same thing for right child
            if(lhs->right!=nullptr){
                lhs->right->parent = lhs;
            }
            return lhs;
        }
  
    }
    /**
    Copy constructor for BST
     @param rhs A reference to a BST that we would like to copy
     */
    bst(const bst& rhs){ //copy constructor
        root = CopyHelper(rhs.root); //copy tree recursively
        TreeSize = rhs.TreeSize; //copy size
        pred = rhs.pred; //copy pred
    }
    /**
    Move constructor for BST
     @param other A BST that we would like to move to our BST
     */
    bst(bst&& other){ // move constructor
        root = other.root; //copy everything from other bst
        TreeSize = other.TreeSize;
        pred = other.pred;
        other.root = nullptr; //set other bst to null
        other.TreeSize = 0;
    }
    /**
    Assignment Operator for BST
     @param other A BST that we would like to assign to our BST
     @return A pointer to BST
     */
    bst& operator=(bst other) &{// assignment operators
        using std::swap;
        std::swap(root,other.root);
        std::swap(TreeSize, other.TreeSize);
        std::swap(pred, other.pred);
        return *this;
    }
    /**
    Find Function that checks if BST contains object of type T
     @param Value A reference to the value we are looking for in the BST
     @param root A node from which we would like to start search from (usually the root node)
     @return A iterator to the node where we found value
     */
    iterator find(const T& Value, node* root) const{ // check if contains a object of type T
        if(root == nullptr){ //empty bst or reach end of tree without finding Value
            return iterator(nullptr,this);
        }
        else if(pred(Value, root->value)){ //traverse left if less than current node's value
            return find(Value, root->left);
        }
        else if(pred(root->value, Value)){ //traverse right if greater than current node's value
            return find(Value, root->right);
        }
        else{ //if equal to Value aka we found it
            return iterator(root,this);
        }
    }
    /**
    Swap Function that swaps two BST
     @param other Another BST that we wish to swap with
     */
    void swap(bst& other){// swap two Trees: as a member function
        using std::swap;
        std::swap(root, other.root);
        std::swap(TreeSize, other.TreeSize);
        std::swap(pred, other.pred);
    }
    /**
    Swap Function that swaps two BST
     @return  The number of nodes aka the size of the BST
     */
    size_t size() const{
        return TreeSize;
    }
    /**
    Begin Function for BST incrementation
     @return  A iterator to the smallest value of the BST aka the first node
     */
    iterator begin() const{
        if(root == nullptr){ //empty tree
            return iterator(nullptr,this);
        }
        node *temp = root;
        while(temp->left!= nullptr){ // traverse down to smallest value
            temp = temp->left;
        }
        return iterator(temp,this); //return iterator of smallest value
    }
    /**
    Begin Function for BST incrementation
     @return  A iterator to one past the final node
     */
    iterator end() const{
        return iterator(nullptr,this);
    }
    /**
    Helper Function for insert
     @param NewVal A value of type T that we would like to insert
     @param Node A pointer to the node from which we would like to start our insertion
     @param Parent A pointer to the parent of Node which we will store for recursive calls
     @param IsLeft A boolean for if a node is a left child which we will store for recursive calls
     */
    void insertHelper(const T NewVal, node* Node, node*Parent, bool IsLeft){
        if (Node == nullptr){ // recursive base case

            Node = new node(NewVal);
            
            if(size() != 0){//if its a leaf node and not the root of an empty tree
                Node->parent = Parent;
                if(IsLeft==true){ //if it should be added as left child
                    Parent->left = Node;
                }
                else{ //if it should be added as right child
                    Parent->right = Node;
                }
            }
            else{ //if it is the root of empty tree
                root = Node;
            }
            TreeSize+=1;
        }
        else if( pred(NewVal, Node->value)){ //NewVal < Node->value
            insertHelper(NewVal,Node->left,Node,true); //move left
        }
        else if( pred(Node->value, NewVal)){ //NewVal > Node->value
            insertHelper(NewVal,Node->right,Node,false); //move right
        }
        return;
    }
    /**
    Insert Function for BST
     @param NewVal A value of type T that we would like to insert
     */
    void insert(T const NewVal){
        insertHelper(NewVal, root, nullptr, false); //call helper function
        return;
    }
    /**
    Delete Function for BST
     @param DeleteNode An iterator for the Node we want to remove
     */
    void erase(iterator DeleteNode){
       
        if(DeleteNode.CurrentPos->left == nullptr && DeleteNode.CurrentPos->right== nullptr){ //node we want to delete has no childern
            DeleteNode.CurrentPos->parent =nullptr; //set parent to nullptr
            delete DeleteNode.CurrentPos;
            TreeSize-=1;
            if(TreeSize==0){ //if that was the only node in the tree
                root = nullptr; //set the bst's root to nullptr
            }
            return;
        }
        else if(DeleteNode.CurrentPos->left == nullptr){ //We know node has a child due to above if statement, here we check if left or right
            if(DeleteNode.CurrentPos == root){ //if we are at root
                DeleteNode.CurrentPos = DeleteNode.CurrentPos->right; //We now know its a right child so we move to that node
                DeleteNode.CurrentPos->parent = DeleteNode.CurrentPos->parent->parent; //set right child of given node parent to given node's parent
                delete DeleteNode.CurrentPos->parent; //delete given node
                root = DeleteNode.CurrentPos; //update root
                TreeSize-=1;
                return;
            }
            else{ //if not at the root
                DeleteNode.CurrentPos = DeleteNode.CurrentPos->right; //We now know its a right child so we move to that node
                DeleteNode.CurrentPos->parent = DeleteNode.CurrentPos->parent->parent; //set right child of given node parent to given node's parent
                DeleteNode.CurrentPos->parent->right = DeleteNode.CurrentPos; //set given node's parent's right child to given node's right child
                delete DeleteNode.CurrentPos->parent; //delete given node
                TreeSize-=1;
                return;
            }
        }
        else if(DeleteNode.CurrentPos->right == nullptr){ //similar to right child case except with left child
            if(DeleteNode.CurrentPos == root){ //if we are at the root
                DeleteNode.CurrentPos = DeleteNode.CurrentPos->left;
                DeleteNode.CurrentPos->parent = DeleteNode.CurrentPos->parent->parent;
                delete DeleteNode.CurrentPos->parent;
                root = DeleteNode.CurrentPos;
                TreeSize-=1;
                return;
            }
            else{ //if not at the root
                DeleteNode.CurrentPos = DeleteNode.CurrentPos->left;
                DeleteNode.CurrentPos->parent = DeleteNode.CurrentPos->parent->parent;
                DeleteNode.CurrentPos->parent->left = DeleteNode.CurrentPos;
                delete DeleteNode.CurrentPos->parent; //delete given node
                TreeSize-=1;
                return;
            }
        }
        else{ //if we are NOT in the case of having 0 or 1 children
            iterator temp = DeleteNode;
            temp.CurrentPos = temp.CurrentPos->right;//move over once to the right
            while(temp.CurrentPos->left != nullptr){ //move as far left as possible
                temp.CurrentPos = temp.CurrentPos->left;
            }
            DeleteNode.CurrentPos->value = temp.CurrentPos->value; //replace given node's value with right-far-left value
            erase(temp); //recursively call erase on right-far-left node
        }
    }
    /**
    Emplace Function for BST
     */
    void emplace(){
        T emptyObject; //create an object of type T
        insert(emptyObject); //try and insert it
        return;
    }
        
    template <typename B, typename... Types>
    /**
    Overloaded Emplace Function for BST with variadic list of arguments
     @tparam B The type for InsertVAl
     @tparam Types The types for InsertValN, may or may not be the same as B
     @param InsertVal An object of type B that will be used in the constuction of an object of type T
     @param InsertValN N more object of various types that may also be used in the constuction of an object of type T
     */
    void emplace(B InsertVal, Types... InsertValN){
        T NewObject(InsertVal,InsertValN...); //create an object of type T with variadic parameters
        insert(NewObject); //try and insert it
        return;
    }
    
private:
    node* root;
    compare_type pred;
    size_t TreeSize;
};

template <typename T, typename compare_type =  std::less<T>>
/**
Non-Member function version of Swap to swap two BSTs
 @tparam T Type of object that the BSTs (Tree1 and Tree2)  contain
 @tparam compare_type A comparison function that the BSTs (Tree1 and Tree2) contain
 @param Tree1 A BST to be swapped
 @param Tree2 The other BST to be swapped
 */
void swap(bst<T,compare_type>& Tree1, bst<T,compare_type>& Tree2){ //non member version of swap
    Tree1.swap(Tree2); //call the member version
    return;
}


}



#endif /* bst_h */
