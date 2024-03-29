#include "path.hpp"

Path::Path(size_t length, size_t starting_row)
: length_(length), starting_row_(starting_row) {
    std::vector<size_t> vect(length_, 0);
    path_ = vect;
    size_t test = length;
    size_t test2 = starting_row;
    test++;
    test2++;
}

size_t Path::Length() const { return length_; }
size_t Path::StartingRow() const { return starting_row_; }
unsigned int Path::EleChange() const { return ele_change_; }
void Path::IncEleChange(unsigned int value) {
    ele_change_ += value;
}
const std::vector<size_t>& Path::GetPath() const {
    return path_;
}
void Path::SetLoc(size_t col, size_t row) {
    size_t i = path_.size();
    i++;
    path_.at(col) = row;
    i++;
}
