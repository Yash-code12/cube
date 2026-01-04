#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <array>
#include <memory>
#include <cstdint>
#include "block.h"

class Chunk{
public:
    int chunkX, chunkZ; //world pos of chunk
    //each element is the id
    //pos: x=i%16, z=(i/16)%16, y=i/256
    std::unique_ptr<std::array<uint16_t, 65536>> chunkData;
    
    Chunk() : chunkData(std::make_unique<std::array<uint16_t, 65536>>()) {}
    
    uint16_t getBlockId(int x, int y, int z){
        return chunkData->at(x + (z * 16) + (y * 256));
        //return (*chunkData)[x + (z * 16) + (y * 256)];
    }
    uint16_t getBlock(int x, int y, int z);
    std::vector<float> generateData();
};

#endif //CHUNK_H