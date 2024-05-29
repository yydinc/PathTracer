#include <iostream>

int main() {

    //  Image descriptors

    int image_width = 256;
    int image_height = 256;

    //  Writing image to the output in the ppm format

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            auto r = static_cast<double>(i) / (image_width-1);
            auto g = static_cast<double>(j) / (image_height-1);
            auto b = static_cast<double>(i);

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}