#include "elevation_dataset.hpp"

ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height) 
: width_(width), height_(height){
    max_ele_ = std::numeric_limits<int>::min();
    min_ele_ = std::numeric_limits<int>::max();
    std::ifstream ifs(filename);
    int value = 0;
    size_t count = 0;
    std::vector<std::vector<int>> vect(height_, std::vector<int>(width_, 0));
    data_ = vect;
    if (ifs.is_open()) {
        if (ifs.peek() == EOF) {
        throw std::runtime_error("file is empty");
        }
        while (ifs.good()) {
            for (size_t row = 0; row < height_; ++row) {
                for (size_t col = 0; col < width_; ++col) {
                    ifs >> value;
                    if (ifs.fail()) {
                    throw std::runtime_error("formatted-read failure");
                    }
                    data_.at(row).at(col) = value;
                    count++;
                    max_ele_ = ElevationDataset::IsMax(value, max_ele_);
                    min_ele_ = ElevationDataset::IsMin(value, min_ele_);
                }
            }
            if (count != (width_ * height_)) {
                throw std::runtime_error("incorrect number of elevation points");
            }
            break;
        }
    } else {
        throw std::runtime_error("file is not open");
    }
    
}

int ElevationDataset::IsMax(int test, int max) {
    if (test > max) {
        return test;
    }
    return max;
}

int ElevationDataset::IsMin(int test, int min) {
    if (test < min) {
        return test;
    }
    return min;
}

size_t ElevationDataset::Width() const {
    return width_;
}
size_t ElevationDataset::Height() const {
    return height_;
}
int ElevationDataset::MaxEle() const {
    return max_ele_;
}
int ElevationDataset::MinEle() const {
    return min_ele_;
}
int ElevationDataset::DatumAt(size_t row, size_t col) const {
    int i = static_cast<int>(row);
    int j = static_cast<int>(col);
    int test = data_.at(i).at(j);
    test++;
    return data_.at(i).at(j);
}
const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
    return data_;
}
