#include <iostream>
#include <iomanip>
#include "../Headers/CacheConfig/Cache.hpp"
int main(){
    Cache someCache(8, 64, 128);

  //  std::cout << "Index is : " << someCache.getIndex();
    
   //  std::vector<int> someVec;
   //  someVec.resize(100);
   //  std::cout << "Some vec size is: " << someVec.capacity();

   auto p = someCache.isHitAccess(123, 0);
   std::cout << std::boolalpha << "Hit is: " << p.first << "\naddress is: " << p.second << std::endl;
   std::cout << std::boolalpha << "Field Dirty is " << someCache.isDirtyAccess(p.second) << std::endl;

   // std::cout <<"VAlue to remove is at: " << someCache.LRUplacement(0).first << someCache.LRUplacement(0).second;
}