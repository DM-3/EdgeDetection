#include <iostream>
#include <string>

#include "image.h"
#include "filter.h"

void parseArguments(int, char**, std::string&, std::string&);

int main(int argc, char** argv) {
    std::string load_path;
    std::string store_path;
    parseArguments(argc, argv, load_path, store_path);

    Image image_0(load_path);
    Image image_1(image_0.getWidth(), image_0.getHeight());

    passConvolution(image_0, image_1);
    passAvgPooling(image_1, image_0);
    passThreshold(image_0, image_1, 64);

    image_1.store(store_path);

    return 1;
}

void parseArguments(int t_argc, char** t_argv, std::string& t_load_path, std::string& t_store_path) {
    // parse load path
    if(t_argc < 2) {
        std::cout << "Please enter a path to the file you'd like to load: ";
        std::cin >> t_load_path;
    } else {
        t_load_path = std::string(t_argv[1]);
    }

    // create store path
    t_store_path = std::string(t_load_path);
    int insert_pos = t_store_path.find('.', t_store_path.find('/'));
    if(insert_pos >= t_store_path.length()) {
        throw std::invalid_argument("missing file extension");
    }
    t_store_path.erase(insert_pos);
    t_store_path.append("_edge.bmp");
}
