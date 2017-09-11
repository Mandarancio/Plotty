#ifndef IMAGES_HXX
#define IMAGES_HXX

#include <Eigen/Core>
#include <string>

namespace img{
  Eigen::MatrixXd load(std::string path);
};

#endif
