#include "images.h"
#include <CImg.h>

using namespace cimg_library;
using namespace img;

Eigen::MatrixXd img::load(std::string name)
{

  CImg<double> image(name.c_str());
  double * d = image.data();
  int w = image.width();
  int h = image.height();
  return Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> > (d,w,h);
}
