#define STB_IMAGE_IMPLEMENTATION
#include "image_loader.h"
#include "stb_image.h"

using namespace std;

GLuint loadTexture(const char* filePath){
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); //texture appears upside down
    
    unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    if (!data) {
        cerr << "Failed to load texture: " << filePath << endl;
        stbi_image_free(data); // Even if data is null, stbi_image_free is safe
        return 0;
    }
    
    GLenum format;
    if (nrChannels == 1)
        format = GL_LUMINANCE; // Or GL_ALPHA if it's an alpha map
    else if (nrChannels == 3)
        format = GL_RGB;
    else if (nrChannels == 4)
        format = GL_RGBA;
    else {
        cerr << "Unsupported number of channels: " << nrChannels << " in " << filePath << endl;
        stbi_image_free(data);
        return 0;
    }
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Set texture wrapping parameters
    // GL_REPEAT is default, but GL_CLAMP_TO_EDGE is often better for non-tiling textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // Set texture filtering parameters
    // GL_LINEAR provides smoother results than GL_NEAREST but GL_NEAREST is better in this case because the textures are pixelated and very small 16x16 no need for smoothing (causes bluriness) we want it to look same from everywhere
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    //use for textures which arent pixelated
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Use mipmaps for minification
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Upload the image data to the texture object
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    // Generate mipmaps but not in our case as the texture should look the same from all distances and we arent using the mipmap settings
    //glGenerateMipmap(GL_TEXTURE_2D);

    // After uploading to GPU and generating mipmaps, you can free the CPU memory
    stbi_image_free(data);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}