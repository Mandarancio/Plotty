#include "fft.h"
#include <fftw3.h>


Eigen::VectorXcd fft::fft(Eigen::VectorXd in)
{
  unsigned int n = in.size();

  Eigen::VectorXcd out(n);
  fftw_plan p = fftw_plan_dft_r2c_1d(n, &in(0), (fftw_complex*)&out(0),   FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  return out/n;
}

Eigen::VectorXd fft::ifft(Eigen::VectorXcd in)
{
  unsigned int n = in.size();
  Eigen::VectorXd out(n);
  fftw_plan p = fftw_plan_dft_c2r_1d(n, (fftw_complex*)&in(0), &out(0),  FFTW_ESTIMATE);
  fftw_execute(p);

  fftw_destroy_plan(p);

  return out;
}


Eigen::MatrixXcd fft::fft2(Eigen::MatrixXd data)
{
  const int n0 = data.rows();
  const int n1 = data.cols();
  const int n = n0*n1;
  Eigen::MatrixXcd out(n0, n1);
  fftw_plan p = fftw_plan_dft_r2c_2d(n1, n0, &data(0), (fftw_complex*) &out(0),   FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

  return out;
}

Eigen::MatrixXd fft::ifft2(Eigen::MatrixXcd data)
{
  unsigned int n0 = data.rows();
  unsigned int n1 = data.cols();
  unsigned int n = n0*n1;
  Eigen::MatrixXd out(n0, n1);

  fftw_plan p = fftw_plan_dft_c2r_2d(n1, n0, (fftw_complex*) &data(0), &out(0),   FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

  return out;
} 
