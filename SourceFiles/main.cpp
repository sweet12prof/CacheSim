#include <iostream>
#include <iomanip>
#include "../Headers/CacheConfig/Cache.hpp"
int main(){
    Cache someCache(1, 64, 128);

    std::pair  <bool, int> somePair {false, 4}; 
    int index {25};
    int Tag{225};

    std::cout << std::endl; 
    
    for(int i{0}; i < 15; i++){
          if( i % 2 == 1){
              std::cout << "i is " << i << " Making a read for Tag " <<  Tag +  ( (6 * i + 5) % (i + 2)) << std::endl;
               someCache.ReadAccess(Tag + ( (6 * i + 5) % (i + 2)), index );
               someCache.readSpecificTagSet(index);
               someCache.readSpecificLRUset(index);
              // std::cout << "Tag is " << someCache.TagField.at(index) << std::endl;
              //  continue;
          }

          someCache.cacheWrite(Tag + i , index + (i * someCache.getIndex() ));
           
        someCache.readSpecificTagSet(index);
        someCache.readSpecificLRUset(index);
       
        //std::cout << "Tag is " <<  someCache.TagField.at(index) << std::endl;
    }
    

std::cout  << std::endl << std::endl;










    //
    // someCache.cacheWrite(Tag + 1 , index + (1 * someCache.getIndex() ));
    // someCache.cacheWrite(Tag + 2, index + (2 * someCache.getIndex() ));
    // someCache.cacheWrite(Tag, index + (3 * someCache.getIndex() ));

    // someCache.ReadAccess((Tag - 1), index);
    // someCache.ReadAccess(Tag + 1 , index + (1 * someCache.getIndex()));
}










