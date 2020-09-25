#include <iostream>
#include <iomanip>
#include <sstream>
#include "../Headers/CacheConfig/CacheAnalyze.hpp"
int main(){
    // Cache someCache(8, 64, 128);
   
    	 CacheAnalyzer someCache(8, 16, 128, 30, 2);
         someCache.Cache_Access(12345678, false, 10);
          std::cout << someCache.getexecutionTimeCycles();
          

         
        

    }
    











    // std::pair  <bool, int> somePair {false, 4}; 
    // int index {25};
    // int Tag{225};

    // std::cout << std::endl; 
    
    // for(int i{0}; i < 15; i++){
    //       if( i % 2 == 1){
    //           std::cout << "i is " << i << " Making a read for Tag " <<  Tag +  ( (6 * i + 5) % (i + 2)) << std::endl;
    //            someCache.ReadAccess(Tag + ( (6 * i + 5) % (i + 2)), index );
    //            someCache.readSpecificTagSet(index);
    //            someCache.readSpecificLRUset(index);
    //           // std::cout << "Tag is " << someCache.TagField.at(index) << std::endl;
    //           //  continue;
    //       }

    //       someCache.cacheWrite(Tag + i , index + (i * someCache.getIndex() ));
           
    //     someCache.readSpecificTagSet(index);
    //     someCache.readSpecificLRUset(index);
       
    //     //std::cout << "Tag is " <<  someCache.TagField.at(index) << std::endl;





