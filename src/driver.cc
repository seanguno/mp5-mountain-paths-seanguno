#include "/home/vagrant/src/mp5-mountain-paths-seanguno/includes/grayscale_image.hpp"
#include "/home/vagrant/src/mp5-mountain-paths-seanguno/includes/path_image.hpp"
#include "/home/vagrant/src/mp5-mountain-paths-seanguno/includes/elevation_dataset.hpp"
#include <iostream>
#include <string>
int main() {
    //GrayscaleImage image = GrayscaleImage("/home/vagrant/src/mp5-mountain-paths-seanguno/example-data/ex_input_data/prompt_5w_2h.dat", 5, 2);
    //image.ToPpm("/home/vagrant/src/mp5-mountain-paths-seanguno/example-data/ex_output_grayscale/test_5w_2h.ppm");
    //GrayscaleImage image2 = GrayscaleImage("/home/vagrant/src/mp5-mountain-paths-seanguno/example-data/ex_input_data/map-input-w480-h480.dat", 480, 480);
    //image2.ToPpm("/home/vagrant/src/mp5-mountain-paths-seanguno/example-data/ex_output_grayscale/test-480-480.ppm");
    //GrayscaleImage image = GrayscaleImage("/home/vagrant/src/mp5-mountain-paths-seanguno/example-data/ex_input_data/map-input-w4-h4.dat", 4, 4);
    //image.ToPpm("/home/vagrant/src/mp5-mountain-paths-seanguno/example-data/ex_output_grayscale/test-4-4.ppm");
    //GrayscaleImage image = GrayscaleImage("/home/vagrant/src/mp5-mountain-paths-seanguno/example-data/ex_input_data/map-input-w51-h55.dat", 51, 55);
    //image.ToPpm("/home/vagrant/src/mp5-mountain-paths-seanguno/example-data/ex_output_grayscale/test-51-55.ppm");
    //GrayscaleImage image = GrayscaleImage("/home/vagrant/src/mp5-mountain-paths-seanguno/example-data/ex_input_data/map-input-w7-h7.dat", 7, 7);
    //image.ToPpm("/home/vagrant/src/mp5-mountain-paths-seanguno/example-data/ex_output_grayscale/test-7-7.ppm");
    PathImage image = PathImage(GrayscaleImage("/home/vagrant/src/mp5-mountain-paths-seanguno/example-data/ex_input_data/prompt_5w_2h.dat", 5, 2), ElevationDataset("/home/vagrant/src/mp5-mountain-paths-seanguno/example-data/ex_input_data/prompt_5w_2h.dat", 5, 2));
}
