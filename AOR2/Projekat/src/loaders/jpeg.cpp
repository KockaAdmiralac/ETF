#include <loaders/jpeg.hpp>
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

Image JPEGLoader::load(const std::string& filename) const {
    int width;
    int height;
    int channels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 3);
    ImageData pixels;
    pixels.resize(width * height * channels);
    for (size_t i = 0; i < pixels.size(); ++i) {
        pixels[i] = ((float) data[i]) / 255.0f;
    }
    free(data);
    return {(uint32_t) width, (uint32_t) height, pixels};
}

void JPEGLoader::save(const std::string& filename, const Image& image) const {
    std::vector<unsigned char> pixels;
    pixels.resize(image.data.size());
    for (size_t i = 0; i < pixels.size(); ++i) {
        pixels[i] = std::max(std::min(image.data[i], 1.0f), 0.0f) * 255;
    }
    stbi_write_jpg(filename.c_str(), image.width, image.height, 3, pixels.data(), 100);
}
