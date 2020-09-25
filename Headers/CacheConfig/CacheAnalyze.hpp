#include "./Cache.hpp"
#include <bitset>
#include <cmath>


#ifndef CACHE_ANAL_H
#define CACHE_ANAL_H

    class CacheAnalyzer : Cache{
        private :
            
            //int accessMissPenalty;
            int executionTime_cycles;

            int loadMissCount;
            int loadMissRate;
            int loadhitCount;
            int loadhitRate;
            int loadCount;
            
            int storeMissCount;
            int storeMissRate;
            int storehitCount;
            int storehitRate;
            int storeCount;

            int memAcesses;

            int dirtyEvictCount;

            int missPenalty;
            int cycleTime;
            int instructionCountTotal;
        
        public :
            CacheAnalyzer(const int &, const int &, const int & , const int & , const int &);
            void setCycleTime();
            void fineTuneMissPenalty();
            void Cache_Load_Access(const int &, const int & );
            void Cache_Store_Access(const int &, const int &);
            void Cache_Access(const int &, bool , int);

            //accessors
            int getexecutionTimeCycles() const;
            
            int getLoadMissCount() const;
            int getLoadHitCount() const;
            int getLoadCount() const;

            int getStoreMissCount() const;
            int getStoreHitCount() const;
            int getStoreCount() const;

            int getMemoryAccessCount() const;
            int getInstructionCount() const;

            int getDirtyEvictCount() const;

    };

#endif