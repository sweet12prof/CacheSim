#include <iostream>
#include <iomanip>
#include "../Headers/CacheConfig/Cache.hpp"
int main(){
    Cache someCache(4, 64, 128);

    std::pair  <bool, int> somePair {false, 4}; 
  // bool ishit = someCache.ReadAccess(123, 511);

    
    int i{25};
    int index {25};
    int Tag{235};
    someCache.cacheWrite(Tag, index);
    someCache.cacheWrite(Tag + 1 , index + (1 * someCache.getIndex() ));
    someCache.cacheWrite(Tag + 2, index + (2 * someCache.getIndex() ));
    someCache.cacheWrite(Tag, index + (3 * someCache.getIndex() ));

    someCache.ReadAccess((Tag - 1), index);
    someCache.ReadAccess(Tag + 1 , index + (1 * someCache.getIndex()));


    // while(i < someCache.TagField.size()){
    //   std::cout << someCache.TagField.at(i) << " ";

    //  i += someCache.getIndex();
    // }
    // std::cout << std::endl;


    //  i = 0;
    // for(auto item : someCache.LRUBitField)
    //   {
    //     if(i == someCache.getAssociativity() ){
    //       std::cout << std::endl;
    //       i = 0;
    //     }
          
    //     std:: cout << item <<  " ";
    //     ++i;
    //   }
    // std::cout << std::endl;

    // // auto p = someCache.isHitAccess(123, 511, 0);

    // // std::cout << std::boolalpha << p.first << std::endl;
}





















  // for(int i{0}; i < someCache.getIndex(); i++ )
    //   {
    //     for(int j{0}; j < someCache.getAssociativity(); j++)
    //       {
    //           std::cout << someCache.LRUBitField.at( (i * someCache.getAssociativity() ) + j) << " ";
    //       }
    //         std::cout << std::endl;
    //   }
   // std::cout <<"VAlue to remove is at: " << someCache.LRUplacement(0).first << someCache.LRUplacement(0).second;