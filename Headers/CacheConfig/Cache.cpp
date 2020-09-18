#include "./Cache.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>


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
    Cache::resizedataIndexField(this->DataField);
    
    Cache::valid_dirty_LRU_Initialise();
    
    std::cout << std::endl;
    
    std::cout << "Index Field is :  " << Cache::getIndex() << std::endl;
    std::cout << "Data Field has index : " << Cache::getDataIndex() << std::endl;
    std::cout << "LRU Field index is: " << Cache::LRUBitField.capacity()<< std::endl;

    Cache::TagField.at(256) = 123;
    Cache::validField.at(256) = true;
    //Cache::dirtyField.at(256) = true;

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

// template <typename T>
// void Cache::resizeIndexFields(std::vector<T> & someField){
//     someField.resize(this->index);
// }


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
    this->dataIndex = this->blockOffset * this->index * this->associativity;
}

int Cache::getDataIndex() const{
    return this->dataIndex;
} 

template <typename T>
void Cache::resizedataIndexField(std::vector<T> & dataStruc){
    dataStruc.resize(this->dataIndex);
}

template <typename T>
    void Cache::resizeIndexFields(std::vector<T> & LRUStruc){
        LRUStruc.resize((this->index * this->associativity));
    }

std::pair <bool, int> Cache::isHitAccess(const int & Tag, const int & address){
    
        if( (address >= (this->index * this->associativity) ) )
            return {false, -1};
        
        else  if((Cache::TagField.at(address) == Tag) &&  ( Cache::validField.at(address)) == true)
            return {true, address};

        else     
            return Cache::isHitAccess(Tag, (address + Cache::index));
            
}


bool Cache::isDirtyAccess( const int & address)
{
    return Cache::dirtyField.at(address);
}

void Cache::CacheWrite(const int & Tag, const int & address, const int & way){
    int fullAddress {(address + (way * Cache::index) )};
    TagField.at(fullAddress) = Tag;
    validField.at(fullAddress) = true;
}

void Cache::CacheDirtyWrite(const int & address, const int & way, bool dirty){
    int fullAddress { address + (way *  Cache::index) };
    dirtyField.at(fullAddress) = dirty;
}

void Cache::valid_dirty_LRU_Initialise(){
    std::fill(Cache::validField.begin(), Cache::validField.end(), false);
    std::fill(Cache::dirtyField.begin(), Cache::dirtyField.end(), false);

    for(int i{0}; i < (Cache::index * Cache::associativity); i+=Cache::associativity){
        for(int j{0}; j < Cache::associativity; j++){
            Cache::LRUBitField.at(i + j) = j + 1; 
        }
            
    }
}


// std::pair<int, int> Cache::LRUplacement(const int & index){
//         int LRUaddress{index * Cache::associativity};
        
//         return {index, Cache::LRUBitField.at(LRUaddress + Cache::associativity)};
// }


// void Cache::updateLRU(const int & index, const int & way){
//     std::vector <int> LRUarray;
//     int LRUaddress{index * Cache::associativity};
//     for(int i{LRUaddress}; i < LRUaddress + Cache::associativity; i++)
//         LRUarray.push_back(Cache::LRUBitField.at(i));
//     std::vector <int> newLRUarray = Cache::lru(LRUarray, associativity -1);
//     int j= 0
//     for(int i{LRUaddress}; i < LRUaddress + Cache::associativity; i++)
//         Cache::LRUBitField.at(i) =  
// }


// static std::vector<int> lru (std::vector<int> que, int pos){
//     std::vector<int> newVec;
//     if (pos >= 1)
//     {
//         newVec.push_back(que.at(pos));
//         for(int i{0}; i < pos; i++)
//             newVec.push_back(que.at(i));
//         for(int j{pos + 1}; j<que.size(); j++)
//             newVec.push_back(que.at(j));
//     }
//     else 
//         newVec.insert(que.begin(), que.end(), newVec.begin());
//     return newVec;
// }