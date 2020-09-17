#include "./Cache.hpp"
#include <iostream>
Cache::Cache(){}
Cache::~Cache(){}
Cache::Cache(const int & asso, const int & block, const int & Size)
: associativity{asso}, blockSize{block}, cacheSize{Size}
{
    Cache::setIndex();
    Cache::setBlockOffset();
    Cache::setDataIndex();
    Cache::resizeIndexFields(this->TagField);
    Cache::resizeIndexFields(this->validField);
    Cache::resizeIndexFields(this->LRUBitField);
    Cache::resizeIndexFields(this->dirtyField);
    
    std::cout << "Index Field is :  " << Cache::getIndex() << std::endl;
    std::cout << "Data Field has index : " << Cache::getDataIndex() << std::endl;
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
    this->index = (( this->cacheSize * 1024 ) / (this->blockSize)/ Cache::associativity) ;
    //std::cout << this->index;
}

int Cache::getIndex() const {
    return this->index;
}


void Cache::setBlockOffset(){
    this->blockOffset = this->blockSize/4;
}

int Cache::getBlockOffset() const{
    return this->blockOffset;
}

void Cache::setDataIndex(){
    this->dataIndex = this->blockOffset * this->index;
}

int Cache::getDataIndex() const{
    return this->dataIndex;
} 

template <typename T>
void Cache::resizedataIndexField(std::vector<T> dataStruc){
    dataStruc.resize(this->dataIndex);
}