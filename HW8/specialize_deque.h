#include<memory>
#include<climits>
#include<stdexcept>
#include<type_traits>


#ifndef specialize_deque_h
#define specialize_deque_h

namespace pic10c{

/**
 @class deque A double ended queue
 @tparam T a type T that the deque will store elements of
 */
template<typename T>
class deque{
    
/**
 @class iterator An input iterator for deque classs
 */
class iterator{
    friend deque;
private:
    deque<T>* Deque;
    size_t index; //index in data[]
    size_t increment; //increment for ++, used for end functin to allow for 1 past the end and not iterating over an element more than once
public:
    /**
     Constructor for Iterator object
     @param A_Deque a pointer to the deque we want to iterate over
     @param An_index an index we start at
     @param An_increment A counter for how many times we have ++ to make sure to only visit each element once
     */
    iterator(deque* A_Deque, size_t An_index, size_t An_increment):Deque(A_Deque),index(An_index),increment(An_increment){};
    
    /**
     Overloaded Pretfix ++ operator for iterator class
     @return A new forward incremented iterator
     */
    iterator &operator++(){
        if(index<Deque->right){
            ++index;
        }
        else{ //wrap around
            index = Deque->left;
        }
        increment+=1;
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
     Overloaded Derefernce Operator for iterator class
     @return a refrence to a copy of the value at current index
     */
    T& operator*(){
         T& temp = Deque->data[index];
         return temp;
        
    }
    
    /**
     Overloaded Arrow Operator for iterator class
     @return A refrence to the value at the current index
     */
    T* operator->(){ //arrow operator
        return & Deque->data[index];
    }
    
    /**
     Overloaded == Comparison Operator  for iterator class
     @param left A reference to a iterator
     @param right A reference to another iterator
     @return A boolean for if two iterators are equal
     */
    friend bool operator==(const iterator& left, const iterator& right) //comparison operator
    {
        if( (left.Deque == right.Deque) && (left.index == right.index) && (left.increment == right.increment)){
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
 @class const_iterator A const input iterator for deque classs
 */
class const_iterator{
    friend deque;
private:
    const deque<T>* Deque;
    size_t index; //index in data[]
    size_t increment; //increment for ++, used for end functin to allow for 1 past the end and not iterating over an element more than once
public:
    /**
     Constructor for Const_Iterator object
     @param A_Deque a pointer to the deque we want to iterate over
     @param An_index an index we start at
     @param An_increment A counter for how many times we have ++ to make sure to only visit each element once
     */
    const_iterator(const deque* const A_Deque, size_t An_index, size_t An_increment):Deque(A_Deque),index(An_index),increment(An_increment){};
    
    /**
     Overloaded Pretfix ++ operator for const_iterator class
     @return A new forward incremented iterator
     */
    const_iterator &operator++(){
        if(index<Deque->right){
            ++index;
        }
        else{ //wrap around
            index = Deque->left;
        }
        increment+=1;
        return *this;
    }
    
    /**
     Overloaded Postfix ++ operator for const_iterator class
     @return A new forward incremented iterator
     */
    const_iterator &operator++ (int){
        const_iterator temp(*this); //create temp variable
        operator++(); //call ++ on temp
        return temp;
    }
    
    /**
     Overloaded Derefernce Operator for Const_iterator class
     @return a refrence to a copy of the value at the current index
     */
    const T& operator*() const{
        const T& temp = Deque->data[index];
         return temp;
        
    }
    
    /**
     Overloaded Arrow Operator for const_iterator class
     @return A refrence to the value at the current index
     */
     const T* operator->() const{ //arrow operator
        return & Deque->data[index];
    }
    
    /**
     Overloaded == Comparison Operator  for const_iterator class
     @param left A reference to a iterator
     @param right A reference to another iterator
     @return A boolean for if two iterators are equal
     */
    friend bool operator==(const const_iterator& left, const const_iterator& right) //comparison operator
    {
        if( (left.Deque == right.Deque) && (left.index == right.index) && (left.increment == right.increment)){
            return true;
        }
        else{
            return false;
        }
    }
    
    /**
     Overloaded != Comparison Operator  for const_iterator class
     @param left A reference to a iterator
     @param right A reference to another iterator
     @return A boolean for if two iterators are not equal
     */
    friend bool operator!=(const const_iterator& left, const const_iterator& right){
        return !(left == right);
    }

};
private:
    std::unique_ptr<T[]> data;
    size_t cap;
    size_t sz;
    size_t left;
    size_t right;
    size_t front;
    size_t back;
public:
    /**
     Default constructor for deque object
     */
    deque(): data(nullptr),cap(0), sz(0),left(0),right(0){};
    
    /**
     Overloaded subscript operator for deque object
     @return the value at given index
    */
    T& operator[] (size_t index){
        return data[left+index];
    }
   
    /**
     Overloaded const subscript operator for deque object
     @return the value at given index
     */
    T& operator[] (size_t index) const{
        return data[left+index];
    }
    
    /**
     Destructor for deque object
     */
    ~deque(){
        data.reset();
    }
    
    /**
    Copy constructor for deque
     @param rhs A reference to a deque that we would like to copy
     */
    deque(const deque& rhs){
        sz = rhs.sz;
        cap = rhs.cap;
        left = rhs.left;
        right = rhs.right;
        front = rhs.front;
        back = rhs.back;
        data = std::make_unique<T[]>(cap);
        for(size_t i=0;i<cap; ++i){
            data[i] = rhs.data[i];
        }
    }
    
    /**
    Move constructor for deque
     @param other A deque that we would like to move to our deque
     */
    deque(deque&& other){
        sz = other.sz;
        cap = other.cap;
        left = other.left;
        right = other.right;
        front = other.front;
        back= other.back;
        data = other.data.release();
        other.sz = 0;
        other.cap = 0;
        other.left = 0;
        other.right = 0;
        other.back = 0;
        other.front = 0;
        other.data = nullptr;
    }
    
    /**
    Copy Assignment Operator for deque
     @param other A deque that we would like to assign to our deque
     @return A pointer to deque
     */
    deque& operator=(const deque& other){// copy assignment operator
        sz = other.sz;
        cap = other.cap;
        left = other.left;
        right = other.right;
        front = other.front;
        back = other.back;
        data = std::make_unique<T[]>(cap);
        for(size_t i=0;i<cap; ++i){
            data[i]= other.data[i];
        }
        return *this;
    }

    /**
    Move Assignment Operator for deque
     @param other A deque that we would like to assign to our deque
     @return A pointer to deque
     */
    deque& operator=(deque&& other){
        sz = other.sz;
        cap = other.cap;
        left = other.left;
        right = other.right;
        front = other.front;
        back = other.back;
        data = other.data.release();
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
        other.left = 0;
        other.right = 0;
        other.front = 0;
        other.back = 0;
        return *this;
    }
    
    /**
     Function that determining if deque's array is full
     @return True if its full, false otherwise
     */
    bool isFull()
    {
        if(sz==cap){
            return true;
        }
        else{
            return false;
        }
    }
    
    /**
     Function that returns size of deque
     @return The current number of elemenrts in the deque
     */
    size_t size() const{
        return sz;
    }
    
    /**
     Function that returns capcity of deque
     @return The current capcity of the deque
     */
    size_t capacity() const{
        return cap;
    }
    
    /**
     Function that gets the current leftmost index
     @return the leftmost index of the deque
     */
    size_t GetLeft() const{
        if(front<back){
            return front;
        }
        else{ //wrap around case, left most index must be 0
            return 0;
        }
    }
    
    /**
     Function that gets the current rightmost index
     @return the rightmost index of the deque
     */
    size_t GetRight() const{
        if(front<back){
            return back;
        }
        else{ //wrap around case, right most index must be cap-1
            return cap-1;
        }
    }
    
    /**
    Begin Function for deque incrementation
     @return  A iterator to the 0th index
     */
    iterator begin(){
        return iterator(this, front,0);
    }
    
    /**
    Begin Function for deque incrementation overloaded on const
     @return  A iterator to the 0th index
     */
    const_iterator begin() const{
        return const_iterator(this,front, 0);
    }
    
    /**
    End Function for deque incrementation
     @return  A iterator to one past the final index
     */
    iterator end(){
        return iterator(this,back,sz); //there indices 0 through sz-1, so 1 past the end would be sz
    }
    
    /**
    End Function for deque incrementation overloaded on const
     @return  A iterator to one past the final index
     */
    const_iterator end() const{
        return const_iterator(this,back,sz);
    }
    
    /**
     Function to append values to the beginning of the deque
     */
    void push_front(const T value){
        if(isFull()){
            if(sz==0){ //empty deque
                data = std::make_unique<T[]>(1);
                data[0]=value;
                sz =1;
                cap = 1;
                front = 0;
                back = 0;
                left = 0;
                right = 0;
                return;
            }
            else{ //reached capcity and non empty deque
                size_t doubleCap = 2*cap;
                auto temp = data.release();
                data = std::make_unique<T[]>(doubleCap);
                cap = doubleCap;
                if(front<back){ //if front index is less than back index
                    for(size_t i=front;i<back+1;++i){ //copy from front index up to and including back index
                        data[i]=temp[i];
                    }
                }
                else{ //front index is greater than back index
                    for(size_t i = front; i<sz; ++i){ //copy from front to end
                        data[i]= temp[i];
                    }
                    for(size_t i = 0; i<back+1; ++i){ //copy from index 0 up to and including back
                        data[i+sz]=temp[i];
                    }
                    back +=sz;
                
                }
            }
        }
        sz+=1;
        if(front==0){ //wrap around
            front = cap-1;
        }
        else{
            front-=1;
        }
        data[front]= value; //add new value
        left = GetLeft(); //update left and right
        right = GetRight();
    }
    
    /**
     Function to append values to the end of the deque
     */
    void push_back(const T value){
        if(isFull()){
            if(sz==0){ //empty deque
                data = std::make_unique<T[]>(1);
                data[0]=value;
                sz =1;
                cap = 1;
                front = 0;
                back = 0;
                left = 0;
                right = 0;
                return;
            }
            else{ //reached capcity and non empty deque
                size_t doubleCap = 2*cap;
                auto temp = data.release();
                data = std::make_unique<T[]>(doubleCap);
                cap = doubleCap;
                if(front<back){ //if front is less than back
                    for(size_t i=front;i<back+1;++i){ //copy values from front up to and including back
                        data[i]=temp[i];
                    }
                }
                else{ //if front is ahead of back in terms of index
                    for(size_t i = front; i<sz; ++i){ //copy from front to end
                        data[i]= temp[i];
                    }
                    for(size_t i = 0; i<back+1; ++i){ //then copy from index 0 up to and including back
                        data[i+sz]=temp[i];
                    }
                    back +=sz; //update back posistion
                }
            }
        }
        sz+=1;
        data[back] = value; //insert new value
        left = GetLeft(); //update left and right
        right = GetRight();
        back+=1; //update back position
        if(back == cap){ //wrap around
            back = 0;
        }
    }
    
    /**
     Function to remove values to the beginning of the deque
     */
    void pop_front(){
        if(sz==0){
            throw std::logic_error {"Deque is empty"};
        }
        else if(front==back){ //1 element
            front = 0;
            back = 0;
            
        }
        else{
            front +=1;
            if(front ==cap){ //wrap around
                front = 0;
            }
            
        }
        left = GetLeft(); //update left and right
        right = GetRight();
        sz-=1;
    }
    
    /**
     Function to remove values to the end of the deque
     */
    void pop_back(){
        if(sz==0){
            throw std::logic_error {"Deque is empty"};
        }
        
        if(front==back){ //1 element
            front = 0;
            back = 0;
        }
        else if(back==0){ //wrap around
            back = cap-1;
        }
        else{
            back-=1;
        }
        left = GetLeft();//update left and right
        right = GetRight();
        sz-=1;
       
    }
    
    /**
     Function to swap a deque with this deque
     @param Other another deque we wish to swap with this one
     */
    void swap(deque& Other){
        using std::swap;
        swap(sz,Other.sz);
        swap(cap, Other.cap);
        swap(left,Other.left);
        swap(right,Other.right);
        swap(front, Other.front);
        swap(back, Other.back);
        swap(data,Other.data);
    }
    
};

/**
 @class deque A double ended queue specializationx for bool
 */
template<>
class deque<bool>{
    class iterator; //forward declaration of iterator and const_iterator classes
    class const_iterator;
    
    /**
     @class proxy a class to store boolean values as bits within a char
     */
    class proxy{
        friend deque<bool>;
        friend iterator;
        friend const_iterator;
    private:
        unsigned char* ptr;
        size_t pos;
        /**
         Constructor for proxy object
         @param _ptr A pointer to an unsigned char
         @param _pos A bit index within that unsigned char
         */
        inline proxy(unsigned char* _ptr, size_t _pos):ptr(_ptr),pos(_pos){};
    public:
        /**
         Assignment operator for proxy object
         @param b a boolean we want to create a proxy for
         */
        const proxy& operator=(bool b) const{
            if(b){
                *ptr = (*ptr | (1<<pos));
            }
            else{
                *ptr = (*ptr & ~(1<<pos));
            }
            return *this;
        }
        
        /**
         Bool conversion operator
         */
        inline operator bool() const{
            unsigned char& u = *ptr;
            return (u>>pos) &1;
        }
        
    };
    
    /**
     @class const_proxy a const class to store boolean values as bits within a char
     */
    class const_proxy{
        friend deque<bool>;
        friend iterator;
        friend const_iterator;
    private:
        unsigned char* ptr;
        size_t pos;
        /**
         Constructor for const_ proxy object
         @param _ptr A pointer to an unsigned char
         @param _pos A bit index within that unsigned char
         */
        inline const_proxy(unsigned char* _ptr, size_t _pos):ptr(_ptr),pos(_pos){};
    public:
        /**
         Bool conversion operator
         */
        operator bool() const{
            const unsigned char& u = *ptr;
            return(u>>pos)&1;
        }
        
        
    };
    
    /**
     @class iterator an iterator for bool queue
     */
    class iterator{
        friend deque<bool>;
        friend proxy;
        friend const_proxy;
    private:
        deque<bool>* Deque;
        size_t index;
        size_t increment;
    public:
        /**
         Constructor for Iterator object
         @param A_Deque a pointer to the deque we want to iterate over
         @param An_index an index we start at
         @param An_increment A counter for how many times we have ++ to make sure to only visit each element once
         */
        iterator(deque<bool>* A_Deque, size_t An_index, size_t An_increment):Deque(A_Deque),index(An_index),increment(An_increment){}
        
        /**
         Overloaded Pretfix ++ operator for iterator class
         @return A new forward incremented iterator
         */
        iterator &operator++(){
            if(index<Deque->right_bit){
                ++index;
            }
            else{ //wrap around
                index = Deque->left_bit;
            }
            increment+=1;
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
         Overloaded Derefernce Operator for iterator class
         @return a refrence to a copy of the value at the current index
         */
        proxy operator*(){
            size_t byteIndex =(((index+Deque->left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1; // index lets say 10, plus we need to start from leftmost byte that is apart of of deque so we add left index times 8 bc each byte (char) in data contains 8 bools. Then add 8 and divide by 8 to get ceiling interger division. subtract 1 to account for starting at index 0.
            size_t bitIndex = index-(CHAR_BIT*byteIndex); //within byte X, which bit 0-7 going right to left. Need to add any extra unused bits left of the leftmost bit then subtract off the bits of the bytes left of our byte of interest.
            proxy temp = proxy(&Deque->data[byteIndex],bitIndex);
            return temp;
            
        }
        
        /**
         Overloaded == Comparison Operator  for iterator class
         @param left A reference to a iterator
         @param right A reference to another iterator
         @return A boolean for if two iterators are equal
         */
        friend bool operator==(const iterator& left, const iterator& right) //comparison operator
        {
            if( (left.Deque == right.Deque)&&(left.index==right.index)&&(left.increment==right.increment)){
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
     @class const_iterator a constß iterator for bool queue
     */
    class const_iterator{
        friend deque<bool>;
        friend proxy;
        friend const_proxy;
    private:
        const deque<bool>* Deque;
        size_t index;
        size_t increment;
    public:
        /**
         Constructor for const_Iterator object
         @param A_Deque a pointer to the deque we want to iterate over
         @param An_index an index we start at
         @param An_increment A counter for how many times we have ++ to make sure to only visit each element once
         */
        const_iterator(const deque<bool>* const A_Deque, size_t An_index, size_t An_increment):Deque(A_Deque),index(An_index),increment(An_increment){}
        
        /**
         Overloaded Pretfix ++ operator for const_iterator class
         @return A new forward incremented const_iterator
         */
        const_iterator &operator++(){
            if(index<Deque->right_bit){
                ++index;
            }
            else{ //wrap around
                index = Deque->left_bit;
            }
            increment+=1;
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
         Overloaded Derefernce Operator for const_iterator class
         @return a refrence to a copy of the value at the current index
         */
        const const_proxy operator*() const{
            size_t byteIndex =(((index+Deque->left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1; // index lets say 10, plus we need to start from leftmost byte that is apart of of deque so we add left index times 8 bc each byte (char) in data contains 8 bools. Then add 8 and divide by 8 to get ceiling interger division. subtract 1 to account for starting at index 0.
            size_t bitIndex = index-(CHAR_BIT*byteIndex); //within byte X, which bit 0-7 going right to left. Need to add any extra unused bits left of the leftmost bit then subtract off the bits of the bytes left of our byte of interest.
            const_proxy temp = const_proxy(&Deque->data[byteIndex],bitIndex);
             return temp;
            
        }
        
        /**
         Overloaded == Comparison Operator  for const_iterator class
         @param left A reference to a const_iterator
         @param right A reference to another const_iterator
         @return A boolean for if two const_iterators are equal
         */
        friend bool operator==(const const_iterator& left, const const_iterator& right) //comparison operator
        {
            if( (left.Deque == right.Deque)&&(left.index==right.index)&&(left.increment==right.increment)){
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
         @return A boolean for if two const_iterators are not equal
         */
        friend bool operator!=(const const_iterator& left, const const_iterator& right){
            return !(left == right);
        }

    };
public:
    std::unique_ptr<unsigned char[]> data;
    size_t cap;
    size_t sz;
    size_t left_byte;
    size_t right_byte;
    size_t left_bit;
    size_t right_bit;
    size_t front;
    size_t back;
public:
    /**
     Default constructor for bool specalized deque
     */
    deque(): data(nullptr),cap(0), sz(0),left_byte(0),right_byte(0),left_bit(0),right_bit(0){};
    
    /**
     Subscript operator for bool specalized deque
     */
    inline proxy operator[] (size_t index){
        size_t byteIndex = (((index+left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1; // index lets say 10, plus we need to start from leftmost byte that is apart of of deque so we add left index times 8 bc each byte (char) in data contains 8 bools. Then add 8 and divide by 8 to get ceiling interger division. subtract 1 to account for starting at index 0.
        size_t bitIndex = index+(left_bit)-(CHAR_BIT*byteIndex); //within byte X, which bit 0-7 going right to left. Need to add any extra unused bits left of the leftmost bit then subtract off the bits of the bytes left of our byte of interest.
        return {&data[byteIndex],bitIndex};
    }
   
    /**
     Subscript operator for bool specalized deque overloaded on const
     */
    inline const_proxy operator[] (size_t index) const{
        size_t byteIndex =(((index+left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1; //same logic as above
        size_t bitIndex = index-(CHAR_BIT*byteIndex);
        return {&data[byteIndex],bitIndex};
    }
    
    /**
     Destructor for bool specalized deque
     */
    ~deque(){
        data.reset();
    }
    
    /**
    Copy constructor for bool specalized deque
     @param rhs A reference to a bool specalized deque that we would like to copy
     */
    deque<bool>(const deque<bool>& rhs){
        sz = rhs.sz;
        cap = rhs.cap;
        left_bit = rhs.left_bit;
        right_bit = rhs.right_bit;
        left_byte = rhs.left_byte;
        right_byte = rhs.right_byte;
        front = rhs.front;
        back = rhs.back;
        data = std::make_unique<unsigned char[]>(cap);
        for(size_t i=0;i<cap; ++i){
            data[i] = rhs.data[i];
        }
    }
    
    /**
    Move constructor for bool specalized deque
     @param other A bool specalized deque that we would like to move to our bool specalized deque
     */
     deque(deque&& other){
         using std::swap;
         sz = other.sz;
         cap = other.cap;
         left_bit = other.left_bit;
         right_bit = other.right_bit;
         left_byte = other.left_byte;
         right_byte = other.right_byte;
         front = other.front;
         back= other.back;
         swap(data,other.data);
         other.sz = 0;
         other.cap = 0;
         other.left_bit = 0;
         other.right_bit = 0;
         other.left_byte = 0;
         other.right_byte = 0;
         other.back = 0;
         other.front = 0;
         other.data = nullptr;
     }
    
    /**
    Copy Assignment Operator for bool specalized deque
     @param other A bool specalized deque that we would like to assign to our bool specalized deque
     @return A pointer to bool specalized deque
     */
    deque& operator=(const deque& other){
        sz = other.sz;
        cap = other.cap;
        left_bit = other.left_bit;
        right_byte = other.right_bit;
        left_byte = other.left_byte;
        right_bit = other.right_byte;
        front = other.front;
        back = other.back;
        data = std::make_unique<unsigned char[]>(cap);
        for(size_t i=0;i<cap; ++i){
            data[i]= other.data[i];
        }
        return *this;
    }

    /**
    Move Assignment Operator for bool specalized deque
     @param other A bool specalized deque that we would like to assign to our bool specalized deque
     @return A pointer to bool specalized deque
     */
    deque& operator=(deque&& other){
        using std::swap;
        sz = other.sz;
        cap = other.cap;
        left_bit = other.left_bit;
        right_byte = other.right_bit;
        left_byte = other.left_byte;
        right_bit = other.right_byte;
        front = other.front;
        back = other.back;
        swap(data,other.data);
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
        other.left_bit = 0;
        other.left_byte = 0;
        other.right_bit = 0;
        other.right_byte = 0;
        other.front = 0;
        other.back = 0;
        return *this;
    }
    
    /**
     Function that determines if deque's array is currently at capcity
     @return True if it is at capacity, false otherwise
     */
    bool isFull() const{
        if(sz==cap){
            return true;
        }
        else{
            return false;
        }
    }
    
    /**
     Function that determines  deque's current number of elements
     @return The number of elements in the deque
     */
    size_t size() const{
        return sz;
    }
    
    /**
     Function that returns deque's current capcity
     @return The current capacity
     */
    size_t capacity() const{
        return cap;
    }
    
    /**
     Function that gets the current leftmost bit index
     @return the leftmost bit index of the deque
     */
    size_t GetLeft() const{
        if(front<back){
            return front;
        }
        else{ //wrapping around so leftmost bit has to be 0
            return 0;
        }
    }
    
    /**
     Function that gets the current rightmost bit index
     @return the rightmost bit index of the deque
     */
    size_t GetRight() const{
        if(front<back){
            return back;
        }
        else{ //wrapping around so right most bit must be cap -1
            return cap-1;
        }
    }

    /**
    Begin Function for deque incrementation
     @return  A iterator to the 0th index
     */
    iterator begin(){
        return iterator(this, front,0);
    }
    
    /**
    Begin Function for deque incrementation overloaded on const
     @return  A iterator to the 0th index
     */
    const_iterator begin() const{
        return const_iterator(this,front, 0);
    }

    /**
    End Function for deque incrementation
     @return  A iterator to one past the final index
     */
    iterator end(){
        if(back==right_bit){
            return iterator(this,left_bit,sz);
        }
        else{
            return iterator(this,back+1,sz);
        }
        //there indices 0 through sz-1, so 1 past the end would be sz
    }
    
    /**
    End Function for deque incrementation overloaded on const
     @return  A iterator to one past the final index
     */
    const_iterator end() const{
        if(back==right_bit){
            return const_iterator(this,left_bit,sz);
        }
        else{
            return const_iterator(this,back+1,sz);
        }
    }
    
    /**
     Function that append value at the beginning of deque
     */
    void push_front(const bool value){
        if(isFull()){
            if(sz==0){ //empty deque
                data = std::make_unique<unsigned char[]>(1);
                proxy GetBit(&data[0],0);
                GetBit = value;
                data[0]= *(GetBit.ptr);
                sz =1;
                cap = CHAR_BIT;
                front = 0;
                back = 0;
                left_bit = 0;
                right_bit = 0;
                left_byte = 0;
                right_byte = 0;
                return;
            }
            else{ //reached capcity and non empty deque
                size_t doubleCap = 2*cap;
                auto temp = data.release();
                data = std::make_unique<unsigned char[]>(doubleCap);
                cap = doubleCap;
                if(front<back){ //if front index is less than back index
                    for(size_t i=front;i<(back)+1;++i){ //copy from front index up to and including back index
                        data[i]=temp[i];
                        size_t byteIndex = (((i+left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1; //get byte we want
                        size_t bitIndex = i-(CHAR_BIT*byteIndex); //get index of bit we want within a single byte
                        proxy GetBit(&temp[byteIndex],bitIndex); //create proxy
                        //GetBit = value; // convert bit within byte to hold bool value we want to add
                        data[byteIndex]= *(GetBit.ptr); //add new byte that now holds a bit storing value
                    }
                    
                }
                else{ //front index is greater than back index
                    for(size_t i = front; i<sz; ++i){ //copy from front to end
                        //data[i]= temp[i];
                        size_t byteIndex = (((i+left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1; //get byte we want
                        size_t bitIndex = i-(CHAR_BIT*byteIndex); //get index of bit we want within a single byte
                        proxy GetBit(&temp[byteIndex],bitIndex); //create proxy
                        data[byteIndex]= *(GetBit.ptr); //add new byte that now holds a bit storing value
                    }
                    for(size_t i = 0; i<back+1; ++i){ //copy from index 0 up to and including back
                        //data[i+(sz/CHAR_BIT)]=temp[i];
                        size_t NewbyteIndex = ((((i+sz)+left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1; //get byte we want in newly sized array
                      
                        size_t OldbyteIndex = ((((i)+left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1; //get byte we want from old array
                        size_t OldbitIndex = i+-(CHAR_BIT*OldbyteIndex); //get index of bit we want within a single byte from old array
                        proxy GetBit(&temp[OldbyteIndex],OldbitIndex); //create proxy
                        data[NewbyteIndex]= *(GetBit.ptr); //add new byte that now holds a bit storing value
                    }
                    back +=sz; //shift over to next byte
                
                }
            }
        }
        sz+=1;
        if(front==0){ //wrap around
            front = cap-1;
        }
        else{
            front-=1;
        }
        size_t byteIndex = (((back+left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1; //get byte we want
        size_t bitIndex = front-(CHAR_BIT*byteIndex); //get index of bit we want within a single byte
        proxy GetBit(&data[byteIndex],bitIndex); //create proxy
        GetBit = value; // convert bit within byte to hold bool value we want to add
        data[byteIndex]= *(GetBit.ptr); //add new byte that now holds a bit storing value
        //data[front]= value;
        left_bit = GetLeft();//front;
        right_bit = GetRight();
        left_byte = left_bit/CHAR_BIT;
        right_byte = right_byte/CHAR_BIT;
        
    }
       
    /**
     Function that append value at the end of deque
     */
    void push_back(const bool value){
        if(isFull()){
            if(sz==0){ //empty deque
                data = std::make_unique<unsigned char[]>(1);
                proxy GetBit(&data[0],0);
                GetBit = value;
                data[0]= *(GetBit.ptr);
                sz =1;
                cap = CHAR_BIT;
                front = 0;
                back = 0;
                left_bit = 0;
                right_bit = 0;
                left_byte = 0;
                right_byte = 0;
                return;
            }
            else{ //reached capcity and non empty deque
                size_t doubleCap = 2*cap;
                auto temp = data.release();
                data = std::make_unique<unsigned char[]>(doubleCap);
                cap = doubleCap;
                if(front<back){ //if front is less than back
                    for(size_t i=front;i<(back)+1;++i){ //copy values from front up to and including back
                        //data[i]=temp[i];
                        size_t byteIndex = (((i+left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1; //get byte we want
                        size_t bitIndex = i-(CHAR_BIT*byteIndex); //get index of bit we want within a single byte
                        proxy GetBit(&temp[byteIndex],bitIndex); //create proxy
                        data[byteIndex]= *(GetBit.ptr); //add new byte that now holds a bit storing value
                    }
                   
                }
                else{ //if front is ahead of back in terms of index
                    for(size_t i = front; i<sz; ++i){ //copy from front to end
                        //data[i]= temp[i];
                        size_t byteIndex = (((i+left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1; //get byte we want
                        size_t bitIndex = i-(CHAR_BIT*byteIndex); //get index of bit we want within a single byte
                        proxy GetBit(&temp[byteIndex],bitIndex); //create proxy
                        data[byteIndex]= *(GetBit.ptr); //add new byte that now holds a bit storing value
                    }
                    for(size_t i = 0; i<back+1; ++i){ //then copy from index 0 up to and including back
                        //data[i+(sz/CHAR_BIT)]=temp[i];
                        size_t NewbyteIndex = ((((i+sz)+left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1; //get byte we want from new array
                        size_t OldbyteIndex = ((((i)+left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1; //get byte we want from old array
                        size_t OldbitIndex = i-(CHAR_BIT*OldbyteIndex); //get index of bit we want from old array
                        proxy GetBit(&temp[OldbyteIndex],OldbitIndex); //create proxy
                        data[NewbyteIndex]= *(GetBit.ptr); //add new byte that now holds a bit storing value
                    }
                    back +=sz; //shift over to next byte
                    
                }
                
            }
        }
        sz+=1;
        back+=1;
        size_t byteIndex = (((back+left_byte*CHAR_BIT)+CHAR_BIT)/CHAR_BIT)-1;
        size_t bitIndex = back-(CHAR_BIT*byteIndex); //get index of bit we want within a single byte
        proxy GetBit(&data[byteIndex],bitIndex); //create proxy
        GetBit = value;
        data[byteIndex]= *(GetBit.ptr);
       
        if(back == cap){ //wrap around
            back = 0;
        }
        left_bit = GetLeft();
        right_bit = GetRight();
        left_byte = left_bit/CHAR_BIT;
        right_byte = right_bit/CHAR_BIT;
    }
    
    /**
     Function that removes value at the beginning of deque
     */
    void pop_front(){
        if(sz==0){
            throw std::logic_error {"Deque is empty"};
        }
        else if(front==back){ //1 element
            front = 0;
            back = 0;
            
        }
        else{
            front +=1;
            if(front ==cap){ //wrap around
                front = 0;
            }
            
        }
        sz-=1;
        left_bit = GetLeft();
        right_bit = GetRight();
        left_byte = left_bit/CHAR_BIT;
        right_byte = right_bit/CHAR_BIT;
    }

    /**
     Function that removes value at the end of deque
     */
    void pop_back(){
        if(sz==0){
            throw std::logic_error {"Deque is empty"};
        }
        
        if(front==back){ //1 element
            front = 0;
            back = 0;
        }
        else if(back==0){ //wrap around
            back = (cap)-1;
        }
        else{
            back-=1;
        }
        sz-=1;
        left_bit = GetLeft();
        right_bit = GetRight();
        left_byte = left_bit/CHAR_BIT;
        right_byte = right_bit/CHAR_BIT;
       
    }
    
    /**
     Function to swap a deque with this deque
     @param Other another deque we wish to swap with this one
     */
    void swap(deque<bool>& Other){
        using std::swap;
        swap(sz,Other.sz);
        swap(cap, Other.cap);
        swap(left_byte,Other.left_byte);
        swap(right_byte,Other.right_byte);
        swap(left_bit,Other.left_bit);
        swap(right_bit,Other.right_bit);
        swap(front, Other.front);
        swap(back, Other.back);
        swap(data,Other.data);
    }
  

};

/**
 Function that adds all elements of a deque if it is of non boolean intergral type
 @tparam T A type of which the deque holds elements of
 @param deque_
 A deque of type T
 @return the
 */
template<typename T>
constexpr std::enable_if_t<std::is_integral<T>::value && !std::is_same<T, bool>::value,T> //make sure T is integral type, then make sure it is NOT bool
sum(const deque<T> deque_){
    T sum = 0;
    for (auto i : deque_) { // for all elements in the deque
        sum+=i;
    }
    return sum;
}

}

#endif /* specialize_deque_h */
