#include "path_image.hpp"

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset):
    height_(image.GrayscaleImage::Height()),
    width_(image.GrayscaleImage::Width()) {
  std::vector<Path> vect(width_, Path(width_, 0));
  paths_ = vect;
  size_t best_path_row = 0;
  size_t min = std::numeric_limits<int>::max();
  for (size_t row = 0; row < height_; ++row) {
    Path path = Path(width_, row);
    PathImage::GreedyPath(dataset, row, path);
    paths_.at(row) = path;
    if (path.Path::EleChange() < min) {
      min = path.Path::EleChange();
      best_path_row = row;
    }
  }
  std::vector<std::vector<Color>> vect_image(height_, std::vector<Color>(width_, Color(0, 0, 0)));
  path_image_ = vect_image;
  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      path_image_.at(row).at(col) = image.GrayscaleImage::GetImage().at(row).at(col);
    }
  }
  for (size_t row = 0; row < height_; ++row) {
    PathImage::ColorPath(paths_.at(row));
  }
  PathImage::ColorGreenPath(paths_.at(best_path_row));
}

void PathImage::ColorPath(const Path &path) {
  for (size_t col = 0; col < width_; ++col) {
    path_image_.at(path.GetPath().at(col)).at(col) = red_path_;
  }
}

void PathImage::ColorGreenPath(const Path &path) {
  for (size_t col = 0; col < width_; ++col) {
    path_image_.at(path.GetPath().at(col)).at(col) = green_path_;
  }
}

size_t PathImage::Width() const { return width_; }
size_t PathImage::Height() const { return height_; }
unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }
const std::vector<Path>& PathImage::Paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};
  if (!ofs.is_open()) {
    throw std::runtime_error("file not open");
  }
  ofs << "P3"
      << "\n";
  ofs << std::to_string(width_) + " " + std::to_string(height_) << "\n";
  ofs << "255"
      << "\n";
  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      ofs << std::to_string(path_image_.at(row).at(col).Red()) + " " +
                 std::to_string(path_image_.at(row).at(col).Green()) + " " +
                 std::to_string(path_image_.at(row).at(col).Blue()) + " ";
    }
    ofs << "\n";
  }
}

size_t PathImage::CalcEleChange(const ElevationDataset& dataset,
                                size_t row,
                                size_t col,
                                int row_change,
                                int col_change) {
  return abs(dataset.GetData().at(row).at(col) -
             dataset.GetData().at(row + row_change).at(col + col_change));
}

size_t PathImage::GreedyStep(const ElevationDataset& dataset,
                             size_t current_row,
                             size_t current_col) {
  if (current_row == 0 &&
      current_row == dataset.ElevationDataset::Height() - 1) {
    return current_row;
  }
  if (current_row == 0) {
    if (PathImage::CalcEleChange(dataset, current_row, current_col, 1, 1) <
        PathImage::CalcEleChange(dataset, current_row, current_col, 0, 1)) {
      return current_row + 1;
    }
    return current_row;
  }
  if (current_row == dataset.ElevationDataset::Height() - 1) {
    if (PathImage::CalcEleChange(dataset, current_row, current_col, -1, 1) <
        PathImage::CalcEleChange(dataset, current_row, current_col, 0, 1)) {
      return current_row - 1;
    }
    return current_row;
  }
  if (PathImage::CalcEleChange(dataset, current_row, current_col, 1, 1) <
          PathImage::CalcEleChange(dataset, current_row, current_col, 0, 1) &&
      PathImage::CalcEleChange(dataset, current_row, current_col, 1, 1) <
          PathImage::CalcEleChange(dataset, current_row, current_col, -1, 1)) {
    return current_row + 1;
  }
  if (PathImage::CalcEleChange(dataset, current_row, current_col, -1, 1) <
          PathImage::CalcEleChange(dataset, current_row, current_col, 0, 1) &&
      PathImage::CalcEleChange(dataset, current_row, current_col, -1, 1) <
          PathImage::CalcEleChange(dataset, current_row, current_col, 1, 1)) {
    return current_row - 1;
  }
  if (PathImage::CalcEleChange(dataset, current_row, current_col, 1, 1) ==
      PathImage::CalcEleChange(dataset, current_row, current_col, -1, 1)) {
    return current_row - 1;
  }
  return current_row;
}

void PathImage::GreedyPath(const ElevationDataset& dataset,
                           size_t starting_row,
                           Path &path) {
  /*
  if (col == 0) {
    path.Path::SetLoc(col, PathImage::GreedyStep(dataset, starting_row, col));
    path.Path::IncEleChange(PathImage::CalcEleChange(
        dataset,
        starting_row,
        col,
        PathImage::GreedyStep(dataset, starting_row, col) - starting_row,
        1));
  } else {
    path.Path::SetLoc(col, PathImage::GreedyStep(dataset, PathImage::GreedyStep(dataset, starting_row - 1, col - 1), 1));
  }
  */
  size_t next_row = PathImage::GreedyStep(dataset, starting_row, 0);
  path.Path::SetLoc(0, starting_row);
  path.Path::IncEleChange(PathImage::CalcEleChange(
    dataset,
    starting_row,
    0,
    static_cast<int>(next_row) - static_cast<int>(starting_row), 
    1));
  for (size_t col = 1; col < width_ - 1; ++col) {
    path.Path::SetLoc(col, next_row);
    path.Path::IncEleChange(PathImage::CalcEleChange(
        dataset,
        next_row,
        col,
        static_cast<int>(PathImage::GreedyStep(dataset, next_row, col)) - static_cast<int>(next_row),
        1));
    next_row = PathImage::GreedyStep(dataset, next_row, col);
  }
  path.Path::SetLoc(width_ - 1, next_row);
}
