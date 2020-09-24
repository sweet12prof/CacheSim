#include <vector>

#ifndef CAHCE_H
#define CACHE_H

enum class associativityEnum { direct=1, two, four, eight };
//enum class blockSizeEnum {sixteen=16, }
enum class replacementEnum { lru=1, random, fifo, lifo};


class Cache {
    private:
        // Specifies associativity of Cache
        int associativity;

        // Specifies the size of a Cache line
        int blockSize;

        //Specifies the total size of the Cache
        int cacheSize;

        //Specifies the replacement policy to be used by the Cache 
        int replacementPolicy;

        //Specifies the number of words in a block
        int blockOffset;

        // Specifies the number of Sets in the Cache
        int index;

        // Specifies miss penalty

        //Flattened Structure of the Valid field of the Blocks in the Sets =>  size For Flattened : (Cache Size ) / (Block Offset ) 
        std::vector <bool> validField;
        
        //Flattened Structure of the Data field of the words in all the Blocks of each set in the. 
        //Cache => size For Flattened =>  index * associativity * Block index(offset)
        std::vector <int> DataField;

        // Flattened Structure of the LRU bit fields of the Blocks in the Sets
        std::vector <int> LRUBitField;
        
        // Flattened Structure of the Tag fields of the Blocks in the Sets
        

        //Flattened Structure of the dirty bit fields of the Blocks in the Sets
        std::vector <bool> dirtyField;

        // size of size of the flattened data structure
        int dataIndex;


    public:

        std::vector <int> TagField;
        //accessor and mutator for cache sIZE
        void setCacheSize(const int &);
        int getCacheSize() const;

        //Accessor and mutator for Block Size
        void setBlockSize(const int &);
        int getBlockSize() const;

        //Acessor and mutator for associativity
        void setAssociativity(const int &);
        int getAssociativity() const;

        //
        void setReplacementPolicy(const int &);
        int getReplacementPolicy() const;

        //
        void setBlockOffset();
        int getBlockOffset() const;

        Cache();
        Cache(const int &, const int &, const int &);
        ~Cache();

        //
        template <typename T>
        void resizeIndexFields(std::vector<T> &);

        //set Index
        void setIndex();
        int getIndex() const;

        //
        void setDataIndex();
        int getDataIndex() const;

        template <typename T>
        void resizedataIndexField(std::vector<T> &);

         //Initialise Valid and FDirtyField
        void valid_dirty_LRU_Initialise();

        //Determine if access is hit
        std::pair <bool, std::pair<int, int>> isHitAccess(const int &, const int &, int);   
        
        //Cache Access
        int Read_Hit_LRU_Update(std::pair <bool, std::pair<int, int>> hitResult, bool );
        
        // LRU update for read and Write
        static std::vector <int> lruUpdate (std::vector<int>, bool , int &);

        //Read Cache Access function returns whether an access was a hit/miss or a dirty/Clean miss
        std::pair <bool, bool> ReadAccess(const int &, const int );

        //Writes Cache line
        //Read Cache Access function returns whether an access was a hit/miss or a dirty/Clean miss
         std::pair <bool, bool> cacheWrite(const int &, const int &);

        //Read All LRU bits in the LRUbitfild
        void readLRUStruc();

        //Read Tag bits of a specific Set
        void readSpecificTagSet(const int & );

        //Read LRU bits of a specific Set
        void readSpecificLRUset(const int & );

        
};

#endif