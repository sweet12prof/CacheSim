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

    Cache::TagField.at(2047) = 123;
    Cache::validField.at(2047) = true;
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

void Cache::setIndex(){
    this->index = ( (( this->cacheSize * 1024 ) / (this->blockSize) )/ Cache::associativity) ;
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


void Cache::valid_dirty_LRU_Initialise(){
    std::fill(Cache::validField.begin(), Cache::validField.end(), false);
    std::fill(Cache::dirtyField.begin(), Cache::dirtyField.end(), false);

    for(int i{0}; i < (Cache::index * Cache::associativity); i+=Cache::associativity){
        for(int j{0}; j < Cache::associativity; j++){
            Cache::LRUBitField.at(i + j) = j; 
        }
            
    }
}


std::pair <bool, std::pair<int, int>> Cache::isHitAccess(const int & Tag, const int & address, int i){
    
        if( (address >= (this->index * this->associativity) ) )
            return {false, {address, -1}};
        
        else  if((Cache::TagField.at(address) == Tag) &&  ( Cache::validField.at(address)) == true)
            return {true, {address, i}};

        else     
            return Cache::isHitAccess(Tag, (address + Cache::index), ++i);
            
}


int Cache::Read_Hit_LRU_Update(std::pair <bool, std::pair<int, int>> hitResult, bool isRead){
    
    int set_mod{hitResult.second.first % Cache::index};
    std::vector<int> iniVec; 

    for(int i{Cache::associativity * set_mod}; i <  (Cache::associativity * set_mod) + Cache::associativity; i++)
        iniVec.push_back(Cache::LRUBitField.at(i));

    std::vector <int > result = Cache::lruUpdate(iniVec, isRead, hitResult.second.second);

    int j{0};     
    for(int i{Cache::associativity * set_mod}; i <  ((Cache::associativity * set_mod) + Cache::associativity); i++)
        {   
            Cache::LRUBitField.at(i) = result.at(j);
            ++j;
        }
        
    return result.front();
}


 std::pair <bool, bool> Cache::ReadAccess(const int & Tag, const int index){
    std::pair <bool, std::pair<int, int>> hit = Cache::isHitAccess(Tag, (index % Cache::index), 0); // Determine if Access is a hit or not
    bool isDirtymiss=false;
    bool hitFirst = hit.first;
    if(hit.first == false)
            {
                std::cout << "Cache doesnt hold requested Data, fetching from main Memory"  << std::endl; 
                 std::pair <bool, bool> writeBackResult = Cache::cacheWrite(Tag, index);
                 isDirtymiss = writeBackResult.second;
                hit = Cache::isHitAccess(Tag, (index % Cache::index), 0);
            }
     else {
            int factor = Cache::Read_Hit_LRU_Update(hit, true); // Refresh LRU 

     }
       
    return {hitFirst, isDirtymiss};
}




 std::pair <bool, bool> Cache::cacheWrite(const int & Tag, const int & indexInput){
   
  auto hitresult = Cache::isHitAccess(Tag, (indexInput % Cache::index), 0);  
    if(hitresult.first == false){
        int factor = Cache::Read_Hit_LRU_Update(hitresult, false);
        Cache::TagField.at( (Cache::index * (factor)) + (indexInput % Cache::index) ) = Tag;
        Cache::validField.at( (Cache::index * (factor)) + (indexInput % Cache::index) ) = true;
        Cache::dirtyField.at( (Cache::index * (factor)) + (indexInput % Cache::index) ) = false;       
        return {hitresult.first, Cache::dirtyField.at( (Cache::index * (factor)) + (indexInput % Cache::index))};     
    }
    else 
        {
            Cache::dirtyField.at(hitresult.second.first) = true;
            Cache::TagField.at(hitresult.second.first) = Tag;
            Cache::validField.at(hitresult.second.first) = true;
            int factor = Cache::Read_Hit_LRU_Update(hitresult, true);
            return {hitresult.first, Cache::dirtyField.at( hitresult.second.first) };
        }  
    
}




std::vector <int> Cache::lruUpdate (std::vector<int> iniVec, bool  isRead, int & wayPos){
    std::vector <int> result;

    if(isRead == true)
        {
            int p =  ( ( std::find(iniVec.begin(), iniVec.end(), wayPos) ) - iniVec.cbegin() );
                result.push_back(iniVec.at(p));
                if(p > 0){
                    for(int i{0}; i < p; i++)
                        result.push_back(iniVec.at(i));
                    for(int j{p + 1}; j < iniVec.size(); j++)
                        result.push_back(iniVec.at(j));
                }            
                else
                    result = iniVec;
                
        }
    
    else {
            result.push_back(iniVec.back());
            for(int i{0}; i < iniVec.size() - 1; i++)
                result.push_back(iniVec.at(i));
    }

    return result;

}   


 void Cache::readLRUStruc(){
      int i {0};
    for(auto item : Cache::LRUBitField)
      {
        if(i == Cache::getAssociativity() ){
          std::cout << std::endl;
          i = 0;
        }
          
        std:: cout << item <<  " ";
        ++i;
      }
    std::cout << std::endl;
 }


void Cache::readSpecificLRUset(const int & index){
     int set_mod{index % Cache::index};
     for(int i{Cache::associativity * set_mod}; i <  (Cache::associativity * set_mod) + Cache::associativity; i++)
        std::cout << Cache::LRUBitField.at(i) << "  ";
    std::cout << std::endl;
}


void Cache::readSpecificTagSet(const int & index){
     int i{index % Cache::index};
      
     while(i < Cache::TagField.size()){
            std::cout << Cache::TagField.at(i) << " ";
            i += Cache::getIndex();
        }
    std::cout << std::endl;
}