#include "./Cache.hpp"

Cache::Cache(){}
Cache::~Cache(){}
Cache::Cache(const int & asso, const int & block, const int & Size)
: associativity{asso}, blockSize{blockSize}, cacheSize{Size}
{
    Cache::setIndex();
    Cache::resizeIndexFields(this->TagField);
    Cache::resizeIndexFields(this->validField);
    Cache::resizeIndexFields(this->LRUBitField);
    Cache::resizeIndexFields(this->dirtyField);
}

int Cache::getAssociativity() const{
    return this->associativity;
}

void Cache::setAssociativity(const int & asso){
    this->associativity = asso;
}


int Cache::getBlockSize() const {
    return this->blockSize;
}

void Cache::setBlockSize(const int & bSize){
    this->blockSize = bSize;
}


void Cache::setCacheSize(const int & cSize){
    this->cacheSize = cSize;
}


int Cache::getCacheSize() const {
    return this->cacheSize;
}

template <typename T>
void Cache::resizeIndexFields(std::vector<T> someField){
    someField.resize(this->index);
}


void Cache::setIndex(){
    int index{ ( Cache::getCacheSize() * 1024)/blockSize };
}

int Cache::getIndex() const {
    return this->index;
}

