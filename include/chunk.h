#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <array>
#include <memory>
#include <cstdint>
#include "block.h"

 //max X
static const int worldFloor = -64;
static const int heightLimit = 192;

static const int chunkWidth = 16; //total blocks in x dir in a chunk
static const int chunkHeight = heightLimit + (-worldFloor); //total height of chunk
static const int chunkLength = 16;


static const int totalBlocksInChunk = chunkWidth * chunkHeight * chunkLength;

class Chunk{
public:
    int chunkX, chunkZ; //world pos of chunk
    //each element is the id
    //pos: x=i%16, z=(i/16)%16, y=i/256
    std::unique_ptr<std::array<uint16_t, totalBlocksInChunk>> chunkData;
    
    Chunk() : chunkData(std::make_unique<std::array<uint16_t, totalBlocksInChunk>>()) {}
    
    uint16_t getBlockId(int x, int y, int z);
    std::vector<float> generateData();
};

#endif //CHUNK_H