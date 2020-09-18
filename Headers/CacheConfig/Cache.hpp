#include <vector>

#ifndef CAHCE_H
#define CACHE_H

enum class associativityEnum { direct=1, two, four, eight };
//enum class blockSizeEnum {sixteen=16, }
enum class replacementEnum { lru=1, random, fifo, lifo};


class Cache {
    private:
        // 
        int associativity;

        //in KB
        int blockSize;

        //
        int cacheSize;

        //
        int replacementPolicy;

        //
        int blockOffset;

        //
        int index;

        std::vector <bool> validField;
        std::vector <bool> dirtyField;
        std::vector <int> TagField;
        

        std::vector <int> DataField;

        int dataIndex;


    public:
    std::vector <int> LRUBitField;
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

        //Determine if write oOperation is associated with a dirty block
        bool isDirtyAccess( const int &);

        //Cache Write
        void CacheWrite(const int &, const int &, bool);
        
        //refresh LRU priorities after read 
        void LRUreadUpdate(const int &);


        static std::vector<int> lru (std::vector<int>, int);
        
};

#endif