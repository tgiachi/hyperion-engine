//
// Created by squid on 5/16/24.
//

#ifndef IMAGE_SCALER_H
#define IMAGE_SCALER_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#include <stdexcept>


namespace hyperion::utils::images {

    void scaleTileset(const char *sourcePath, const char *destPath, const double scale) {
        int width, height, channels;
        unsigned char *img = stbi_load(sourcePath, &width, &height, &channels, 0);

        int newWidth = (int) (width * scale);
        int newHeight = (int) (height * scale);

        if (img == nullptr) {
            throw std::runtime_error("Failed to load image");
        }

        unsigned char *imgResized = (unsigned char *) malloc(newWidth * newHeight * channels);
        if (imgResized == nullptr) {
            stbi_image_free(img);
            throw std::runtime_error("Failed to allocate memory for resized image");
        }

        if (!stbir_resize_uint8(img, width, height, 0, imgResized, newWidth, newHeight, 0, channels)) {
            free(imgResized);
            stbi_image_free(img);
            throw std::runtime_error("Failed to resize image");
        }

        if (!stbi_write_png(destPath, newWidth, newHeight, channels, imgResized, newWidth * channels)) {
            free(imgResized);
            stbi_image_free(img);
            throw std::runtime_error("Failed to write resized image");
        }

        free(imgResized);
        stbi_image_free(img);
    }
}

#endif //IMAGE_SCALER_H
