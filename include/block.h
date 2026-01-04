#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <vector>
#include <array>
#include <cstdint> // Good practice for uint16_t

class BlockType{
public:
    uint16_t id;
    std::string name;
    bool is_transparent;
    std::array<std::array<float,2>,6> uvCoords; //top left uv coord in atlas for 6 faces
    
    BlockType(uint16_t id, std::string name, bool is_transparent, std::array<std::array<float,2>,6> uvCoords) : 
    id(id), name(name), is_transparent(is_transparent), uvCoords(uvCoords) {}
};

// A simple vector acting as your "Dictionary"
//extern std::vector<BlockType> blockRegistry;

std::vector<BlockType>& getBlockRegistry();

#endif //BLOCK_H