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
        int index;

        std::vector <bool> validField;
        std::vector <bool> dirtyField;
        std::vector <int> TagField;
        std::vector <bool> LRUBitField;

        std::vector <int> DataField;



    public:
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

        Cache();
        Cache(const int &, const int &, const int &);
        ~Cache();

        //
        template <typename T>
        void resizeIndexFields(std::vector<T>);

        //set Index
        void setIndex();
        int getIndex() const;
};

#endif