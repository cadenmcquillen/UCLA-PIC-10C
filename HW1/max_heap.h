#ifndef max_heap_h
#define max_heap_h
#include <vector>
#include <utility>
#include <stdexcept>

namespace pic10c{
template <typename T, typename compare_type =  std::less<T>>
/**
 @class max_heap a max heap implemention using std::vector
 @tparam T a data type for which std::vector will take and thus the the max heap will take
 @tparam compare_type the comparison function we wish to use for the max heap
 */
    class max_heap {
    private:
        std::vector<T> values; //vector on which max heap is built
        compare_type pred; //comparison operator to be used in max heap
    public:
        /**
        Default Costructor for class max_heap
         */
        max_heap(){
            pred = compare_type{};
        }
        
        /**
        Constructor for class max_heap
        @param Comparison_Function type of comparison operator to be used in max_heap
         */
        max_heap(const compare_type& Comparison_Function): pred(Comparison_Function){}
        
        /**
        Function that returns index of parent of given index
        @param Index the index
        @return the index of the parent
         */
        size_t GetParent(const size_t& Index){
            if(Index == 0){ //In case GetParent is called when Index is already at the top
                return 0;
            }
            else{
                return (Index - 1)/2;
            }
        }
        
        /**
        Function that returns the index of left child of given index
        @param Index the index
        @return the index of the left child
         */
        size_t GetLeft(const size_t& Index){
            size_t parent = GetParent(Index);
                return (2*parent)+1;
        }
        /**
        Function that returns the index of right child of given index
        @param Index the index
        @return the index of the right child
         */
        
        size_t GetRight(const size_t& Index){
            size_t parent = GetParent(Index);
            return (2*parent)+2;
        }
        
        /**
        Function that Inserts a new element into max heap
        @param NewValue an element of type T
         */
        void insert(T NewValue){
            if (values.size() == 0){ //if vector is empty, add "NewValue" to top of values
                values.push_back(NewValue);
            }
            else{
                values.push_back(NewValue);
                size_t CurrentPosition = size() - 1;
               
                while (CurrentPosition > 0){ //continue until we reach top
                    
                    size_t CurrentParent = GetParent(CurrentPosition);
                    
                    if(pred(values[CurrentParent],values[CurrentPosition])  ){ //if child is greater than parent or parent greater than child depending on if pred is < or > direction
                        std::swap(values[CurrentPosition],values[CurrentParent]);
                        CurrentPosition = CurrentParent; //update CurrentPosition of "NewValue"
                    }
                    
                    else{ //Once no longer "larger" or "smaller" than parent depending on pred
                        break;
                    }
                }
            }
            
        }
        
        /**
        Function that returns the size of max heap
        @return the size of max heap
         */
        size_t size(){
            return values.size();
        }
        
        /**
        Function that returns the largest value of max heap
        @return values[0] aka the largest value of the max heap
         */
        T top(){
            if(values.size()==0){ // if top is called with empty heap
                throw std::logic_error("heap is empty");
            }
            return values[0];
        }
        
        
        /**
        Function that pops off top value of max heap
         */
        void pop(){
            if (values.size()==0){ // if pop is called with empty heap
                throw std::logic_error("pop empty");
            }
            else{
                if(values.size()== 1 ){ // if pop called with only one object in heap
                    values.pop_back();
                }
                else{
                    values[0] = values.back(); // move value from end of vector to front replacing old value at the top
                    values.pop_back(); // remove old last element of vector
                    
                    size_t LeftChild = GetLeft(0);
                    size_t RightChild = GetRight(0);
                    size_t GreatestChild = 0;
                    size_t CurrentPosition = 0;
                    const size_t& VectorLength = values.size();
                    
                    while(CurrentPosition < VectorLength){
                        if(LeftChild < VectorLength && pred(values[CurrentPosition],values[LeftChild] )){ //check if left child index is out of bounds, then also check if left child is greater than current value
                            GreatestChild = LeftChild;
                        }
                        if (RightChild < VectorLength && pred(values[GreatestChild],values[RightChild] )){ //check if right child index is out of bounds, then also check if right child is greater than max(value of current position, value of left child)
                            GreatestChild = RightChild;
                        }
                        std::swap(values[CurrentPosition],values[GreatestChild]);
                        CurrentPosition = GreatestChild;
                        
                        if(CurrentPosition < VectorLength){ //check if current position is at end of vector before updating left and right child
                            break;
                        }
                        else{
                            LeftChild = GetLeft(CurrentPosition);
                            RightChild = GetRight(CurrentPosition);
                        }
                    }

                }
            }
        
            
        }
                
    };
}
#endif /* max_heap_h */

