#include <iostream>
#include "../Headers/CacheConfig/Cache.hpp"
int main(){
    Cache someCache(1, 16, 16);

    std::cout << someCache.getIndex();
}