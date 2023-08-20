#include "grayscale_image.hpp"
#include <iostream>
#include <string>

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) 
: width_(dataset.Width()), height_(dataset.Height()) {
    std::vector<std::vector<int>> data = dataset.ElevationDataset::GetData();
    int shade_of_gray = 0;
    std::vector<std::vector<Color>> vect(height_, std::vector<Color>(width_, Color(0, 0, 0)));
    image_ = vect;
    for (size_t row = 0; row < height_; ++row) {
                for (size_t col = 0; col < width_; ++col) {
                    if (!(dataset.MaxEle() == dataset.MinEle())) {
                        shade_of_gray = static_cast<int>(std::round((static_cast<double>(data.at(row).at(col) - dataset.MinEle()) / static_cast<double>(dataset.MaxEle() - dataset.MinEle())) * static_cast<double>(kMaxColorValue)));
                    }
                    image_.at(row).at(col) = Color(shade_of_gray, shade_of_gray,  shade_of_gray);
                }
            }
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) 
: width_(width), height_(height) {
    const ElevationDataset& dataset = ElevationDataset(filename, width, height);
    std::vector<std::vector<int>> data = dataset.ElevationDataset::GetData();
    int shade_of_gray = 0;
    std::vector<std::vector<Color>> vect(height_, std::vector<Color>(width_, Color(0, 0, 0)));
    image_ = vect;
    for (size_t row = 0; row < height_; ++row) {
                for (size_t col = 0; col < width_; ++col) {
                    if (!(dataset.MaxEle() == dataset.MinEle())) {
                        shade_of_gray = static_cast<int>(std::round((static_cast<double>(data.at(row).at(col) - dataset.MinEle()) / static_cast<double>(dataset.MaxEle() - dataset.MinEle())) * static_cast<double>(kMaxColorValue)));
                    }
                    image_.at(row).at(col) = Color(shade_of_gray, shade_of_gray,  shade_of_gray);
                }
            }
}
size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const { return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }
const Color& GrayscaleImage::ColorAt(int row, int col) const {
    return image_.at(row).at(col);
}
const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
   return image_;
}
void GrayscaleImage::ToPpm(const std::string& name) const {
    std::ofstream ofs {name};
    if (!ofs.is_open()) {
        throw std::runtime_error("file not open");
    }
    ofs << "P3" << "\n";
    ofs << std::to_string(width_) + " " + std::to_string(height_) << "\n";
    ofs << "255" << "\n";
    for (size_t row = 0; row < height_; ++row) {
        for (size_t col = 0; col < width_; ++col) {
            ofs << std::to_string(image_.at(row).at(col).Red()) + " " + std::to_string(image_.at(row).at(col).Blue()) + " " + std::to_string(image_.at(row).at(col).Green()) + " ";
        }
        ofs << "\n";
    }
}

