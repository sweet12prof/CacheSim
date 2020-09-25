#include "./CacheAnalyze.hpp"
#include <iostream>

CacheAnalyzer::CacheAnalyzer(const int & asso, const int & blockSize, const int & cacheSize, const int & missPen, const int & ctime)
    :Cache(asso, blockSize, cacheSize), 
    missPenalty{missPen}, 
    cycleTime{ctime},
    executionTime_cycles{0},
    loadMissCount{0},
    loadhitCount{0},
    loadhitRate{0}, 
    loadCount{0}, 
    storeMissCount{0}, 
    storeMissRate{0}, 
    storehitCount{0}, 
    storehitRate{0}, 
    storeCount{0}, 
    memAcesses{0}, 
    dirtyEvictCount{0}, 
    instructionCountTotal{0}
    
{
    CacheAnalyzer::setCycleTime();
    CacheAnalyzer::fineTuneMissPenalty();
}

void  CacheAnalyzer::setCycleTime(){
    switch(CacheAnalyzer::getCacheSize()){
        case 32 : 
            CacheAnalyzer::cycleTime *= 1.05;
        break;

        case 128 :
            CacheAnalyzer::cycleTime *= 1.15;
        
        default :
            CacheAnalyzer::cycleTime = CacheAnalyzer::cycleTime;
    }

    switch(CacheAnalyzer::getAssociativity()){
        case 2 :
             CacheAnalyzer::cycleTime *= 1.05;
        break;
            
        case 4 : 
             CacheAnalyzer::cycleTime *= 1.07;
        break;

        case 8 :
             CacheAnalyzer::cycleTime *= 1.10;
        break;

         default :
            CacheAnalyzer::cycleTime = CacheAnalyzer::cycleTime;
    }
}


void  CacheAnalyzer::fineTuneMissPenalty(){
    switch( CacheAnalyzer::getBlockSize()){
        case 32:
            CacheAnalyzer::missPenalty += 2;
        break;

        case 64:
            CacheAnalyzer::missPenalty += 6;
        break; 

        default:
            CacheAnalyzer::missPenalty = CacheAnalyzer::missPenalty;
    }
}


void CacheAnalyzer::Cache_Load_Access(const int & Tag, const int & index){
    std::pair <bool, bool> access_results = CacheAnalyzer::ReadAccess(Tag, (index % CacheAnalyzer::getIndex()));
       
        ++CacheAnalyzer::loadCount;
        ++executionTime_cycles;
    //std::cout <<std::boolalpha << access_results.first;
    if( access_results.first)
        ++CacheAnalyzer::loadhitCount;
   
    else {
        
        ++CacheAnalyzer::loadMissCount;
        CacheAnalyzer::executionTime_cycles += CacheAnalyzer::missPenalty;
        
      
       if(access_results.second == true)
        {
            ++CacheAnalyzer::dirtyEvictCount;
            executionTime_cycles += 2;
        }
   
    }
}


void CacheAnalyzer::Cache_Store_Access(const int & Tag, const int & index){
    std::pair <bool, bool> access_results = CacheAnalyzer::cacheWrite(Tag, (index % CacheAnalyzer::getIndex()));
         ++CacheAnalyzer::storeCount;
         ++executionTime_cycles;

    if(access_results.first)
        ++CacheAnalyzer::storehitCount;
    else 
    {
         ++CacheAnalyzer::storeMissCount;
         CacheAnalyzer::executionTime_cycles += CacheAnalyzer::missPenalty;

         if(access_results.second == true)
        {
            ++CacheAnalyzer::dirtyEvictCount;
            executionTime_cycles += 2;
        }

    }   
}

void CacheAnalyzer::Cache_Access(const int & address, bool isRead, int priorInstructions){
    std::bitset<32> address_in_bits (address);
    address_in_bits = address_in_bits >> 2;
    int block_offset_bits {std::log2(CacheAnalyzer::getBlockOffset() )};
    address_in_bits = address_in_bits >> block_offset_bits;
   
   int addressSliced = address_in_bits.to_ulong();

   address_in_bits = address_in_bits >> std::log2(CacheAnalyzer::getIndex() );

   int Tag = address_in_bits.to_ulong();

    address_in_bits = address;

    

   address_in_bits =  address_in_bits << ( 32 - (2 + std::log2(CacheAnalyzer::getBlockOffset() ) + std::log2(CacheAnalyzer::getIndex() )) );
   address_in_bits =  address_in_bits >> ( 32 - (2 + std::log2(CacheAnalyzer::getBlockOffset() ) + std::log2(CacheAnalyzer::getIndex() )) );
   address_in_bits = address_in_bits >> (2 + std::log2(CacheAnalyzer::getBlockOffset() ));

   int Index = address_in_bits.to_ulong();
   CacheAnalyzer::memAcesses++;

   if (isRead == true)
        CacheAnalyzer::Cache_Load_Access(Tag, Index);
    else
        CacheAnalyzer::Cache_Store_Access(Tag, Index);
    
    CacheAnalyzer::executionTime_cycles += priorInstructions;

    CacheAnalyzer::instructionCountTotal  = CacheAnalyzer::instructionCountTotal + priorInstructions + 1;
}


int CacheAnalyzer::getexecutionTimeCycles() const {
    return this->executionTime_cycles;
}

int CacheAnalyzer::getLoadMissCount() const {
    return this->loadMissCount;
}

int CacheAnalyzer::getLoadCount() const{
    return this->loadCount;
}

int CacheAnalyzer::getLoadHitCount() const {
    return this->loadhitCount;
}

int CacheAnalyzer::getStoreMissCount() const {
    return this->storeMissCount;
}

int CacheAnalyzer::getStoreCount() const {
    return this->storeMissCount;
}

int CacheAnalyzer::getStoreHitCount() const {
    return this->storehitCount;
}