#include "texture.hh"

#include <SOIL/SOIL.h>
#include <GL/glew.h>

namespace gl {
    texture::texture() 
        : initialized(false),
          id(0)
    {
    }

    texture::texture(std::filesystem::path path) {
        // Load the image. SOIL is being used right now because it was thought at the 
        // start that all the texture things would be done through that library. Right
        // now is only used as a replacement of stb_image
        int32 width, height, channels;
        uint8* image = SOIL_load_image(path.c_str(), &width, &height, &channels, 4);

        // Create the texture and bind it
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        // Setup the settings of the texture:
        //  - Min and mag filters are set to nearest as the game will be using 
        //    pixel art, and interpolation would break that pixel art
        //  - Wrapping is set to clamping with no reasoning behind
        /// TODO: expose as parameters to the constructor?
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        // Upload the data to the gpu and generate the mipmaps for completeness
        // sake
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        SOIL_free_image_data(image);

        initialized = true;
    }

    void texture::bind_to_slot(uint32 slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, id);
    }
}