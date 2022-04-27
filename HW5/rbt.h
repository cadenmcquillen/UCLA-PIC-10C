//TO DO:  Do commentening and

#include<utility>
#include<iostream>
#include<stdexcept>


#ifndef rbt_h
#define rbt_h

namespace pic10c{
template <typename T, typename compare_type =  std::less<T>>
/**
 @class rbt A red black binary search tree with parent node
 @tparam T The type of object that the rbt holds
 @tparam compare_type The comparison function used to evaulate node placement of rbt
 */
class rbt{
public:
    class iterator; //forward declared to be friend of node class
    class const_iterator; //forward declared to be friend of node class
    /**
     @class A node object within a RBT
     */
    class node{
        friend rbt;
        friend iterator;
        friend const_iterator;
    private:
        T value;
        node *left;
        node *right;
        node *parent;
        std::string color;
    public:
        /**
         Node Constructor
         @param nodeVal  A value of type T for that node to hold
         */
        node(T nodeVal): value(nodeVal), left(nullptr), right(nullptr), parent(nullptr), color("Red"){} //constructor
       
    };
    /**
     @class An iterator for RBT
     */
    class iterator{
        friend rbt;
    private:
        /**
         Iterator Constructor
         @param CurrentNode  A pointer to a node that we are currently at
         @param Tree The rbt we are iterating on
         */
        iterator(node* CurrentNode, const rbt* Tree): CurrentPos(CurrentNode), Tree(Tree){} //constructor
        node *CurrentPos;
        const rbt *Tree;
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
        T& operator*(){
            T& temp = (CurrentPos->value);
             return temp;
            
        }
        /**
         Overloaded Arrow Operator for iterator class
         @return A refrence to the value at the current node
         */
         T* operator->(){ //arrow operator
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
     @class An const iterator for RBT
     */
    class const_iterator{
        friend rbt;
    private:
        /**
         Const_Iterator Constructor
         @param CurrentNode  A pointer to a node that we are currently at
         @param Tree The rbt we are iterating on
         */
        const_iterator(node* CurrentNode, const rbt* Tree): CurrentPos(CurrentNode), Tree(Tree){} //constructor
        node *CurrentPos;
        const rbt *Tree;
    public:
        /**
         Overloaded Prefix ++ operator for const_iterator class
         @return forward incremented const_iterator
         */
        const_iterator &operator++(){
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
         Overloaded Postfix ++ operator for const_iterator class
         @return A new forward incremented const_iterator
         */
        const_iterator &operator++ (int){
            const_iterator temp(*this); //create temp variable
            operator++(); //call ++ on temp
            return temp;
        }
        /**
         Overloaded Pretfix -- operator for const_iteratorr class
         @return A decremented const_iterator
         */
        const_iterator &operator--(){ //similar to prefix ++ but for --
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
         Overloaded Postfix -- operator for const_iterator class
         @return A new decremented const_iterator
         */
        const_iterator &operator-- (int){
            const_iterator temp(*this); //create temp variable
            operator--(); //call -- on temp
            return temp;
        }
        /**
         Overloaded Derefernce Operator for const_iterator class
         @return a refrence to a copy of the value at the current node
         */
        const T& operator*() const{ //might need to fix
            const T& temp = (CurrentPos->value);
            return temp;
        }
        /**
         Overloaded Arrow Operator for const_iterator class
         @return A refrence to the value at the current node
         */
        const T* operator->() const{ //arrow operator might need to fix
            return & (CurrentPos->value);
        }
        /**
         Overloaded == Comparison Operator  for const_iterator class
         @param left A reference to a const_iterator
         @param right A reference to another const_iterator
         @return A boolean for if two const_iterator are equal
         */
        friend bool operator==(const const_iterator& left, const const_iterator& right) //comparison operator
        {
            if( (left.CurrentPos == right.CurrentPos) && (left.Tree == right.Tree)){
                return true;
            }
            else{
                return false;
            }
        }
        /**
         Overloaded != Comparison Operator  for const_iterator class
         @param left A reference to a const_iterator
         @param right A reference to another const_iterator
         @return A boolean for if two const_iterator are not equal
         */
        friend bool operator!=(const const_iterator& left, const const_iterator& right){
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
     RBT Default Constructor
     */
    rbt() noexcept :pred(compare_type{}),TreeSize(0),root(nullptr){} //default constuctor with std:less<> as default pred
    /**
     RBT Constructor
     @param Comparison_Function A comparison operator to be used
     */
    rbt(const compare_type& Comparison_Function): pred(Comparison_Function),TreeSize(0),root(nullptr){}
    /**
     RBT Destructor
     */
    ~rbt(){  //destructor
        deleteTree(root);
    }
    /**
     Function that determines if given node is a left child
     @param Node A node we wish to determine if is a left child
     @return True if node is left child, false if not
     */
    bool IsLeftChild(const node* Node) const{
        node* Parent = Node->parent;
        node* ParentLeftChild = Parent->left;
        if(ParentLeftChild==Node){ // if node is same as parents left child
            return true;
        }
        else{
            return false;
        }
    }
    /**
     Function that gets sibling of given node
     @param Node A node we wish to get the sibling of
     @return pointer to the sibling node of given node
     */
    node* GetSibling(const node* Node) const{
        node* Parent = Node->parent;
        if(Parent != nullptr){ //if parent isn't nullptr
            node* ParentLeftChild = Parent->left;
            node* ParentRightChild = Parent->right;
            if(ParentLeftChild==Node){
                return ParentRightChild;
            }
            else{
                return ParentLeftChild;
            }
        }
        else{
            return nullptr;
        }
    }
    /**
     Function that gets Grandparent of given node
     @param Node A node we wish to get the Grandparent of
     @return pointer to the Grandparent node of given node
     */
    node* GetGrandParent(const node* Node) const{
        node* Parent = Node->parent;
        if(Parent!=nullptr){ //if we are not at the root
            return Parent->parent;
        }
        else{
            return nullptr;
        }
    }
    /**
     Function that gets Uncle of given node
     @param Node A node we wish to get the Uncle of
     @return pointer to the Uncle node of given node
     */
    node* GetUncle(const node* Node) const{
        node* Parent = Node->parent;
        node* GrandParent = GetGrandParent(Node);
        if(GrandParent!= nullptr){ //if we are not at root
            node* GrandParentLeftChild = GrandParent->left;
            node* GrandParentRightChild = GrandParent->right;
            if(GrandParentLeftChild==Parent){ //if parent is grandparent's left child
                return GrandParentRightChild; //return the right child
            }
            else{
                return GrandParentLeftChild;
            }
        }
        else{
            return nullptr;
        }
    }
    /**
     Function that changes color of given node
     @param NewColor  New color for given node
     */
    void ReColor(node* Node, std::string NewColor){
        if(NewColor != "Red" && NewColor != "Black" && NewColor!= "2Black"){ //only change color if Red or Black or double black
            return;
        }
        Node->color = NewColor;
    }
    /**
     Function that performs left rotation
     @param Node  node to be rotated around
     */
    void LeftRotate(node* Node){
        node* Parent = Node->parent;
        bool isLeftChild = false;
        if(Parent->left == Node){
            isLeftChild = true;
        }
        //node* Temp = Node;
        node* ReplacingNode = Node->right;
        if(isLeftChild){
            Parent->left = ReplacingNode; //replace Node with its right child
            Node->right = ReplacingNode->left; //replace Node's right child with the replacing node's left child
            ReplacingNode->parent = Parent; //replace replacing node's parent with Node's parent
            ReplacingNode->left = Node; //replace replacing node's left child with Node
            Node->parent = ReplacingNode; //change Node's parent to replacing Node
            
        }
        else{
            Parent->right = ReplacingNode; //replace Node with its right child
            Node->right = ReplacingNode->left; //replace Node's right child with the replacing node's left child
            ReplacingNode->parent = Parent; //replace replacing node's parent with Node's parent
            ReplacingNode->left = Node; //replace replacing node's left child with Node
            Node->parent = ReplacingNode; //change Node's parent to replacing Node
        }
    }
    /**
     Function that performs right rotation
     @param Node  node to be rotated around
     */
    void RightRotate(node* Node){
        node* Parent = Node->parent;
        bool isLeftChild = false;
        if(Parent->left == Node){
            isLeftChild = true;
        }
        //node* Temp = Node;
        node* ReplacingNode = Node->left;
        if(isLeftChild){
            Parent->left = ReplacingNode; //replace Node with its left child
            Node->left = ReplacingNode->right; //replace Node's left child with the replacing node's right child
            ReplacingNode->parent = Parent; //replace replacing node's parent with Node's parent
            ReplacingNode->right = Node; //replace replacing node's right child with Node
            Node->parent = ReplacingNode; //change Node's parent to replacing Node
            
        }
        else{
            Parent->right = ReplacingNode; //replace Node with its right child
            Node->left = ReplacingNode->right; //replace Node's left child with the replacing node's right child
            ReplacingNode->parent = Parent; //replace replacing node's parent with Node's parent
            ReplacingNode->right = Node; //replace replacing node's right child with Node
            Node->parent = ReplacingNode; //change Node's parent to replacing Node
        }
    }
    /**
     Function that corrects red/black structure after  insertion
     @param NewlyInsertedNode  node thats newly inserted
     */
    void CorrectRedsInsert(node* NewlyInsertedNode){
        node* Grandparent = GetGrandParent(NewlyInsertedNode);
        node* Uncle = GetUncle(NewlyInsertedNode);
        node* Parent = NewlyInsertedNode->parent;
        if(NewlyInsertedNode == root){ //case 1: Node is root
            ReColor(NewlyInsertedNode, "Black");
        }
        else if ( NewlyInsertedNode != root && Parent!= nullptr && Parent->color == "Black"){ //case 2: black parent, Parent!=nullptr to prevent bad access on Parent->color
            return;
        }
        else if( NewlyInsertedNode != root && (Parent!= nullptr && Parent->color == "Red")){
            if(Uncle!= nullptr && Uncle->color == "Red"){ //case 3: red parent and red uncle
                ReColor(Uncle, "Black");
                ReColor(Parent, "Black");
                ReColor(Grandparent, "Red");
                CorrectRedsInsert(Grandparent);
            }
            else{ //uncle is either nullptr which is black or exist and is black
                if(IsLeftChild(NewlyInsertedNode) && IsLeftChild(Parent)){ //case 4: both n and p are left children
                        RightRotate(Grandparent);
                        ReColor(Parent,"Black");
                        ReColor(Grandparent, "Red");
                        
                    }
                else if(!IsLeftChild(NewlyInsertedNode) && IsLeftChild(Parent)){ //case 5: n is right child, p is left child
                    LeftRotate(Parent);
                    CorrectRedsInsert(Parent);
                }
            }
        }
    }
    /**
     Function that corrects red/black structure in preperation for deletion of a node
     @param ToBeDeleted  node thats is about to be deleted
     */
    void CorrectRedsDelete(node* ToBeDeleted){
        node* Sibling = GetSibling(ToBeDeleted);
        node* Parent = ToBeDeleted->parent;
        if(ToBeDeleted->right!=nullptr && ToBeDeleted->right->color =="Red"){ //if its only red child is right child
            ReColor(ToBeDeleted->right, "Black");
            return; //everything is correct, just remove node as normal now
        }
        else if(ToBeDeleted->left!=nullptr && ToBeDeleted->left->color =="Red"){//if its only red child is left child)
            ReColor(ToBeDeleted->left, "Black");
            return; //everything is correct, just remove node as normal now
        }
        else if(ToBeDeleted->color =="Red" && ToBeDeleted->left ==nullptr && ToBeDeleted->right == nullptr){ //red with no children
            return; // everything is correct, just remove node as normal now
        }
        else if(ToBeDeleted->color =="Black" && ToBeDeleted->left ==nullptr && ToBeDeleted->right == nullptr){ //black with no children
            ReColor(ToBeDeleted, "2Black"); //Recolor to double black
        }
        if(ToBeDeleted->color == "2Black"){ //If we have a double black
            if(Parent==nullptr){ //If its the root
                ReColor(ToBeDeleted, "Black");
                return; //everything is correct, just remove node as normal now
            }
            else if(Sibling->color == "Red" && IsLeftChild(ToBeDeleted)){ //red sibling and if a left child
                LeftRotate(Parent);
                ReColor(Parent, "Red");
                ReColor(Sibling, "Black");
                CorrectRedsDelete(ToBeDeleted);
            }
            else if(Sibling->color =="Black" && IsLeftChild(ToBeDeleted) && (Sibling->left->color == "Red" && Sibling->right->color != "Red")){ //black sibling and is left child and sibling has 1 left red child
                node* SiblingLeftChild = Sibling->left;
                RightRotate(Sibling);
                std::swap(Sibling->color,SiblingLeftChild->color);
                CorrectRedsDelete(ToBeDeleted);
            }
            else if(Sibling->color =="Black" && IsLeftChild(ToBeDeleted) && Sibling->right->color == "Red" ){ //black sibling, is left child, and sibling has right black child
                if(Parent->color == "Red"){ //Case A: Parent is red
                    node* SiblingRightChild = Sibling->right;
                    LeftRotate(Parent);
                    ReColor(Sibling, "Red");
                    ReColor(Parent,"Black");
                    ReColor(ToBeDeleted, "Black");
                    ReColor(SiblingRightChild, "Black");
                }
                else{//Case B: Parent is Black
                    node* SiblingRightChild = Sibling->right;
                    LeftRotate(Parent);
                    ReColor(ToBeDeleted, "Black");
                    ReColor(SiblingRightChild, "Black");
                }
            }
            else if(Sibling->color == "Black" && Sibling->right->color =="Black" && Sibling->left->color == "Black"){ //black sibling with two black children
                if(Parent->color == "Red"){ //Case A: Parent is red
                    ReColor(Parent,"Red");
                    ReColor(ToBeDeleted, "Black");
                    ReColor(Sibling, "Red");
                    
                }
                else{//Case B: Parent is Black
                    ReColor(Sibling, "Red");
                    ReColor(Parent, "2Black");
                    ReColor(ToBeDeleted, "Black");
                    CorrectRedsDelete(Parent);
                }
            }
            
        }
        
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
    Copy constructor for RBT
     @param rhs A reference to a RBT that we would like to copy
     */
    rbt(const rbt& rhs){ //copy constructor
        root = CopyHelper(rhs.root); //copy tree recursively
        TreeSize = rhs.TreeSize; //copy size
        pred = rhs.pred; //copy pred
    }
    /**
    Move constructor for RBT
     @param other A RBT that we would like to move to our RBT
     */
    rbt(rbt&& other){ // move constructor
        root = other.root; //copy everything from other bst
        TreeSize = other.TreeSize;
        pred = other.pred;
        other.root = nullptr; //set other bst to null
        other.TreeSize = 0;
    }
    /**
    Copy Assignment Operator for RBT
     @param other A RBT that we would like to assign to our RBT
     @return A pointer to RBT
     */
    rbt& operator=(const rbt& other){// copy assignment operator
        root = CopyHelper(other.root);
        TreeSize = other.TreeSize;
        pred = other.pred;
        return *this;
    }
    /**
    Move Assignment Operator for RBT
     @param other A RBT that we would like to assign to our RBT
     @return A pointer to RBT
     */
    rbt& operator=(rbt&& other){// move assignment operator
        root = other.root; //copy everything from other bst
        TreeSize = other.TreeSize;
        pred = other.pred;
        other.root = nullptr; //set other bst to null
        other.TreeSize = 0;
        return *this;
    }
    /**
    Find Helper Function that checks if RBT contains object of type T
     @param Value A reference to the value we are looking for in the RBT
     @param root A node from which we would like to start search from (usually the root node)
     @return A iterator to the node where we found value
     */
    iterator findHelper(const T& Value, node* root){ // check if contains a object of type T
        if(root == nullptr){ //empty bst or reach end of tree without finding Value
            return iterator(nullptr,this);
        }
        else if(pred(Value, root->value)){ //traverse left if less than current node's value
            return findHelper(Value, root->left);
        }
        else if(pred(root->value, Value)){ //traverse right if greater than current node's value
            return findHelper(Value, root->right);
        }
        else{ //if equal to Value aka we found it
            return iterator(root,this);
        }
    }
    /**
    Find Helper Function that checks if RBT contains object of type T (Overloaded on const)
     @param Value A reference to the value we are looking for in the RBT
     @param root A node from which we would like to start search from (usually the root node)
     @return A const_iterator to the node where we found value
     */
    const_iterator const_findHelper(const T& Value, node* root) const{ // check if contains a object of type T
        if(root == nullptr){ //empty bst or reach end of tree without finding Value
            return const_iterator(nullptr,this);
        }
        else if(pred(Value, root->value)){ //traverse left if less than current node's value
            return const_findHelper(Value, root->left);
        }
        else if(pred(root->value, Value)){ //traverse right if greater than current node's value
            return const_findHelper(Value, root->right);
        }
        else{ //if equal to Value aka we found it
            return const_iterator(root,this);
        }
    }
    /**
    Find  Function that checks if RBT contains object of type T (Overloaded on const)
     @param Value A reference to the value we are looking for in the RBT
     @return An iterator to the node where we found value
     */
    iterator find(const T& Value){
        return findHelper(Value, root);
    }
    /**
    Find  Function that checks if RBT contains object of type T (Overloaded on const)
     @param Value A reference to the value we are looking for in the RBT
     @return A const_iterator to the node where we found value
     */
    const_iterator find(const T& Value) const{
        return const_findHelper(Value, root);
    }
    /**
    Swap Function that swaps two RBT
     @param other Another RBT that we wish to swap with
     */
    void swap(rbt& other){// swap two Trees: as a member function
        using std::swap;
        std::swap(root, other.root);
        std::swap(TreeSize, other.TreeSize);
        std::swap(pred, other.pred);
    }
    /**
     Size function that returns number of nodes in RBT
     @return  The number of nodes aka the size of the RBT
     */
    size_t size() const{
        return TreeSize;
    }
    /**
    Begin Function for RBT incrementation
     @return  A iterator to the smallest value of the RBT aka the first node
     */
    iterator begin(){
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
    Begin Function for RBT incrementation (overloaded on const)
     @return  A iterator to the smallest value of the RBT aka the first node
     */
    const_iterator begin() const{
        if(root == nullptr){ //empty tree
            return const_iterator(nullptr,this);
        }
        node *temp = root;
        while(temp->left!= nullptr){ // traverse down to smallest value
            temp = temp->left;
        }
        return const_iterator(temp,this); //return iterator of smallest value
    }
    /**
    Begin Function for RBT  incrementation
     @return  A iterator to one past the final node
     */
    iterator end(){
        return iterator(nullptr,this);
    }
    /**
    Begin Function for RBT  incrementation (0verloaded on const)
     @return  A iterator to one past the final node
     */
    const_iterator end() const{
        return const_iterator(nullptr,this);
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
            CorrectRedsInsert(Node); //Correct Red/Black structure
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
    Insert Function for RBT
     @param NewVal A value of type T that we would like to insert
     */
    void insert(T const NewVal){
        insertHelper(NewVal, root, nullptr, false); //call helper function
        return;
    }
    /**
    Delete Function for RBT
     @param DeleteNode An iterator for the Node we want to remove
     */
    void erase(iterator DeleteNode){
       
        if(DeleteNode.CurrentPos->left == nullptr && DeleteNode.CurrentPos->right== nullptr){ //node we want to delete has no childern
            CorrectRedsDelete(DeleteNode.CurrentPos); //correct red/black
            node* Parent = DeleteNode.CurrentPos->parent;
            if(Parent!= nullptr && IsLeftChild(DeleteNode.CurrentPos)){ //make parent of deleted node left child nullptr
                Parent->left = nullptr;
            }
            else if(Parent!=nullptr && !IsLeftChild(DeleteNode.CurrentPos)){//make parent of deleted node right child nullptr
                Parent->right = nullptr;
            }
            DeleteNode.CurrentPos->parent =nullptr; //set parent to nullptr
            delete DeleteNode.CurrentPos;
            TreeSize-=1;
            if(TreeSize==0){ //if that was the only node in the tree
                root = nullptr; //set the bst's root to nullptr
            }
            return;
        }
        else if(DeleteNode.CurrentPos->left == nullptr){ //We know node has a child due to above if statement, here we check if left or right
            CorrectRedsDelete(DeleteNode.CurrentPos); //correct red/black
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
            CorrectRedsDelete(DeleteNode.CurrentPos); //correct red/black
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
    Emplace Function for RBT
     */
    void emplace(){
        T emptyObject; //create an object of type T
        insert(emptyObject); //try and insert it
        return;
    }
        
    template <typename B, typename... Types>
    /**
    Overloaded Emplace Function for RBT with variadic list of arguments
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
    /**
    Helper function to print RBT
     @param spacing how much spacing we want when printing
     @param Node a node we will recursively call the function on
     */
    void printHelper(int spacing, node* Node)
    {
        if (Node == nullptr)
            return;
        spacing+= 10;
        // Process right child first
        printHelper(spacing, Node->right);
        // Print current node after space
        std::cout<<"\n";
        for (int i = 10; i < spacing; i++)
            std::cout<<" ";
        if(Node==root){ //special case if root ie no slash
            if(Node->color == "Red"){
                std::cout<<Node->value<<"(r)"<<"\n";
            }
            else{
                std::cout<<Node->value<<"(b)"<<"\n";
            }
        }
        else{ //if not the root
            if(IsLeftChild(Node)){ //if node is left child
                if(Node->color == "Red"){
                    std::cout<<"\\"<<Node->value<<"(r)"<<"\n";
                }
                else{
                    std::cout<<"\\"<<Node->value<<"(b)"<<"\n";
                }
            }
            else{ //if node is a right
                if(Node->color == "Red"){
                    std::cout<< "/" <<Node->value<< "(r)" << "\n";
                }
                else{
                    std::cout<< "/"<<Node->value<<"(b)"<<"\n";
                }
            }
        }
        // Process left child
        printHelper(spacing, Node->left);
    }
    /**
    Function to print RBT
     */
    void print(){
        printHelper(10, root);
    }

private:
    node* root;
    compare_type pred;
    size_t TreeSize;
};

template <typename T, typename compare_type =  std::less<T>>
/**
Non-Member function version of Swap to swap two RBTs
 @tparam T Type of object that the RBTs (Tree1 and Tree2)  contain
 @tparam compare_type A comparison function that the RBTs (Tree1 and Tree2) contain
 @param Tree1 A RBT to be swapped
 @param Tree2 The other RBT to be swapped
 */
void swap(rbt<T,compare_type>& Tree1, rbt<T,compare_type>& Tree2){ //non member version of swap
    Tree1.swap(Tree2); //call the member version
    return;
}


}

#endif /* rbt_h */

