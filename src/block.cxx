#include "block.h"
//block.cxx
//order front, back, top, bottom, left, right
//origin is botton left (0, 0)

std::vector<BlockType>& getBlockRegistry() {
    // This 'static' variable is initialized ONLY once, 
    // the first time this function is called.
    static std::vector<BlockType> registry = {
        BlockType(0, "air", true, {{{0,0}}}),
        BlockType(1, "dirt", false, {{
            {0.125f, 0.9375f}, {0.125f, 0.9375f}, {0.125f, 0.9375f},
            {0.125f, 0.9375f}, {0.125f, 0.9375f}, {0.125f, 0.9375f}
        }})
    };
    return registry;
}