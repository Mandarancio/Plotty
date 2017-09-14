#ifndef FFT_HXX
#define FFT_HXX

#include <Eigen/Core>

namespace fft{
Eigen::VectorXcd fft(Eigen::VectorXd data);
Eigen::VectorXd ifft(Eigen::VectorXcd data, unsigned int k = 0);

// TODO Implement 2D fft and ifft
Eigen::MatrixXcd fft2(Eigen::MatrixXd data);
Eigen::MatrixXd ifft2(Eigen::MatrixXcd data);
};

#endif
