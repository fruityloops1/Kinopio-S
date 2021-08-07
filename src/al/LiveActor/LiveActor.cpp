#include "al/LiveActor/LiveActor.h"

#include <string.h>

namespace al
{

    ActorScoreKeeper::ActorScoreKeeper() = default;

    void ActorScoreKeeper::init(const al::ByamlIter& iter){
        if(iter.isTypeArray()){
            size = iter.getSize();
            allocArray();
            for(int i=0;i<size;i++){
                al::ByamlIter subIter;
                iter.tryGetIterByIndex(&subIter, i);
                putEntry(i, subIter);
            }
        }
        else {
            size = 1;
            allocArray();
            putEntry(0, iter);
        }
    }

    inline void ActorScoreKeeper::allocArray(){
        Entry* local_array = new Entry[size];
        if(size)
            memset(local_array, 0, sizeof(Entry)*size);
        array = local_array;
    }

    inline void ActorScoreKeeper::putEntry(int index, const al::ByamlIter& iter){
        auto& entry = array[index];
        iter.tryGetStringByKey(&entry.factorName, "FactorName");
        iter.tryGetStringByKey(&entry.categoryName, "CategoryName");
    }

};