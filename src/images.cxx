#include "images.h"
#include <CImg.h>

using namespace cimg_library;
using namespace img;

Eigen::MatrixXd img::load(std::string name)
{
  CImg<double> image(name.c_str());
  int w = image.width();
  int h = image.height();
  Eigen::MatrixXd img(w,h);
  for (int i=0;i<w*h;i++)
  {
      img(i) = image[i]/255.;
  }

  return img;
}
