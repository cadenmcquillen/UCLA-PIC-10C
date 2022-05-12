#include<vector>

#ifndef SimpleSet_h
#define SimpleSet_h
namespace pic10c{

/**
@class Simple set class that stores unique elements of type T
@tparam T any type T that the set will store objects of
*/
template<typename T>
class simple_set{
private:
    std::vector<T> data;
public:
    /**
    Default constuctor for simple set
    */
    simple_set(){}
    
    /**
    Function that returns the number of elements in the set
     @return the number of elements in the set
    */
    size_t size() const{
        return data.size();
    }
    
    /**
    Function that removes specfied value if it exist in the set
     @param value the value we want to erase
    */
    void erase(const T value){
        size_t vecSize = size();
        for(size_t i = 0; i<vecSize; ++i){ //loop through set
            if(data[i]==value){ //if we find value we want to remove
                size_t j = i;
                while(j<vecSize-1){ //iterate through rest of set
                    data[j] = data[j+1]; //shift everything over by 1
                    j++;
                }
                data.pop_back(); //remove the last element
            }
        }
    }
    
    /**
    Function that returns true if we find the value, false otherwise
     @param value the value we want to find
     @return Returns true if we find the value in the set, false otherwise
    */
    bool find(const T value){
        size_t vecSize = size();
        for(size_t i = 0; i<vecSize; ++i ){ //loop through set
            if(data[i]==value){ //if we find the value we want
                return true;
            }
        }
        return false;
    }
    
    /**
    Function that inserts given element if not already in the set
     @param value the value we want to insert
    */
    void insert(const T value){
        if(find(value)!= true){ //if we dont find the value
            data.push_back(value); //add the value to the set
        }
    }
   
};
/**
@class Simple set class that stores unique elements of type T pointer
@tparam T A type that the set will store, in this case a partial specilzation that takes in pointers of type T
*/
template<typename T>
class simple_set<T*>{
private:
    std::vector<T*> data;
public:
    /**
    Default constuctor for simple set
    */
    simple_set(){}
    
    /**
    Function that returns the number of elements in the set
     @return the number of elements in the set
    */
     size_t size() const{
        return data.size();
    }
    
    /**
    Function that removes specfied value if it exist in the set
     @param value the value we want to erase
    */
    void erase(const T value){
        size_t vecSize = size();
        for(size_t i = 0; i<vecSize; ++i){ //loop through set
            if(*(data[i]) == value){ //if the value that pointer is pointing to equals the value we want to remove
                size_t j = i;
                while(j<vecSize-1){ //iterate through rest of set
                    data[j] = data[j+1]; //shift everything by 1
                    j++;
                }
                data.pop_back(); //remove the last element
            }
        }
    }
    
    /**
    Function that returns true if we find the value, false otherwise
     @param value the value we want to find
     @return Returns true if we find the value in the set, false otherwise
    */
    bool find(const T value) const{
        size_t vecSize = size();
        for(size_t i = 0; i<vecSize; ++i ){ //loop through set
            if(*(data[i])==value){ //if the value that pointer is pointing to equals the value we want to find
                return true;
            }
        
        }
        return false;
    }
    
    /**
    Function that inserts given element if not already in the set
     @param value the value we want to insert
    */
    void insert(T* value){
        if(find(*value)!= true){ //if we do not find the value already in the set
            data.push_back(value);
        }
    }
   
};

/**
@class Explicit speclializtion of Simple set class that stores unique elements of type bool
*/
template<>
class simple_set<bool>{
private:
    std::vector<bool> data;
    bool has_true;
    bool has_false;
public:
    /**
    Default constuctor for simple set
    */
    simple_set():has_true(false),has_false(false){}
    
    /**
    Function that returns the number of elements in the set
     @return the number of elements in the set
    */
    size_t size() const{
        return data.size();
    }
    
    /**
    Function that removes specfied value if it exist in the set
     @param value the value we want to erase
    */
    void erase(const bool value){
        size_t vecSize = size();
        for(size_t i = 0; i<vecSize; ++i){ //loop through set
            if(data[i]==value){ //if we find value we want to erase
                size_t j = i;
                while(j<vecSize-1){ //iterate through rest of set
                    data[j] = data[j+1]; //shift everything over by 1
                    j++;
                }
                data.pop_back(); //remove last element
                if(value){ //if value we removed was true
                    has_true = false; //update has true
                }
                else{ //if value we removed was false
                    has_false = false; //update has false
                }
            }
        }
    }
    
    /**
    Function that returns true if we find the value, false otherwise
     @param value the value we want to find
     @return Returns true if we find the value in the set, false otherwise
    */
    bool find(const bool value) const{
        size_t vecSize = size();
        for(size_t i = 0; i<vecSize; ++i ){ //loop through set
            if(data[i]==value){ //if we find the value we are looking for
                return true;
            }
        }
        return false;
    }
    
    /**
    Function that inserts given element if not already in the set
     @param value the value we want to insert
    */
    void insert(const bool value){
        if(find(value)!= true){ //if we dont find the value we want to insert
            data.push_back(value); //insert it
            if(value){ //if the value is true
                has_true = true; //update has true
            }
            else{ //if the value is false
                has_false = true; //update has false
            }
        }
    }
   
};

}

#endif /* SimpleSet_h */
