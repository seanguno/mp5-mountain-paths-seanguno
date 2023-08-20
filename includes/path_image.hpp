#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>
#include <limits>

#include "color.hpp"
#include "path.hpp"
#include "grayscale_image.hpp"
#include "elevation_dataset.hpp"

class PathImage {
public:
  PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color>>& GetPathImage() const;
  void ToPpm(const std::string& name) const;
  
private:
  std::vector<Path> paths_;
  size_t height_ = 0;
  size_t width_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  size_t CalcEleChange(const ElevationDataset &dataset, size_t row, size_t col, int row_change, int col_change);
  size_t GreedyStep(const ElevationDataset &dataset, size_t current_row, size_t current_col);
  void  GreedyPath(const ElevationDataset &dataset, size_t starting_row, Path &path);
  void ColorPath(const Path &path);
  void ColorGreenPath(const Path &path);
  const int kRedPathRed = 252;
  const int kRedPathGreen = 25;
  const int kRedPathBlue = 63;
  const int kGreenPathRed = 31;
  const int kGreenPathGreen = 253;
  const int kGreenPathBlue = 13;
  Color red_path_ = Color(kRedPathRed, kRedPathGreen, kRedPathBlue);
  Color green_path_ = Color(kGreenPathRed, kGreenPathGreen, kGreenPathBlue);
};

#endif
