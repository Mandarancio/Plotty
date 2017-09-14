#include "fft.h"
#include <fftw3.h>

#include <cmath>


Eigen::VectorXcd fft::fft(Eigen::VectorXd in)
{
  unsigned int n = in.size();

  Eigen::VectorXcd out((in.size()+1)/2);
  fftw_plan p = fftw_plan_dft_r2c_1d(n, &in(0), (fftw_complex*)&out(0), FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
  fftw_execute(p);
  fftw_destroy_plan(p);
  return out/n;
}

Eigen::VectorXd fft::ifft(Eigen::VectorXcd in, unsigned int k)
{

  unsigned int n = k>0 ? k : ((in.size())*2-1);
  Eigen::VectorXd out(n);
  fftw_plan p = fftw_plan_dft_c2r_1d(n, (fftw_complex*)&in(0), &out(0), FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
  fftw_execute(p);
  fftw_destroy_plan(p);
  return out;
}


Eigen::MatrixXcd fft::fft2(Eigen::MatrixXd in)
{
  const int n0 = in.rows();
  const int n1 = in.cols();
  const int n = n0*n1;
  Eigen::MatrixXcd out(n0/2+1, n1);

  fftw_plan p =  fftw_plan_dft_r2c_2d(n1, n0, &in(0), (fftw_complex*)&out(0), FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

  return out;
}

Eigen::MatrixXd fft::ifft2(Eigen::MatrixXcd data)
{
  unsigned int n0 = data.rows()*2-1;
  unsigned int n1 = data.cols();
  unsigned int n = n0*n1;
  Eigen::MatrixXd out(n0, n1);

  fftw_plan p = fftw_plan_dft_c2r_2d(n1, n0, (fftw_complex*) &data(0),&out(0), FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

  return out;
} 
