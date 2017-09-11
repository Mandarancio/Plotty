#include "fft.h"
#include <fftw3.h>


Eigen::VectorXcd fft::fft(Eigen::VectorXd data)
{
  unsigned int n = data.size();
  fftw_complex * out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*n);
  fftw_complex * in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*n);
  for (unsigned int i=0;i<n;i++)
  {
    in[i][0] = data(i);
  }
  fftw_plan p = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  Eigen::VectorXcd output(n);
  for (unsigned int i=0;i<n;i++)
  {
    output(i) = std::complex<float>(out[i][0]/n, out[i][1]/n);
  }

  fftw_destroy_plan(p);
  fftw_free(in);
  fftw_free(out);
  return output;
}

Eigen::VectorXd fft::ifft(Eigen::VectorXcd data)
{
  unsigned int n = data.size();
  fftw_complex * out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*n);
  fftw_complex * in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*n);
  for (unsigned int i=0;i<n;i++)
  {
    in[i][0] = data(i).real();
    in[i][1] = data(i).imag();

  }

  fftw_plan p = fftw_plan_dft_1d(n, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(p);

  Eigen::VectorXd output(n);
  for (unsigned int i=0;i<n;i++)
  {
    output(i) = out[i][0];
  }

  fftw_destroy_plan(p);
  fftw_free(in);
  fftw_free(out);
  return output;
}


Eigen::MatrixXcd fft::fft2(Eigen::MatrixXd data)
{
  unsigned int n0 = data.rows();
  unsigned int n1 = data.cols();
  unsigned int n = n0*n1;
  fftw_complex * out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*n);
  fftw_complex * in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*n);
  for (unsigned int i=0;i<n;i++)
  {
    in[i][0] = data(i);
    in[i][1] = 0;
  }
  fftw_plan p = fftw_plan_dft_2d(n0, n1, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);

  Eigen::MatrixXcd output(n0, n1);
  for (unsigned int i=0;i<n;i++)
  {
    output(i) =  std::complex<float>(out[i][0]/n, out[i][1]/n);
  }

  fftw_destroy_plan(p);
  fftw_free(in);
  fftw_free(out);
  return output;
}

Eigen::MatrixXd fft::ifft2(Eigen::MatrixXcd data)
{
  unsigned int n0 = data.rows();
  unsigned int n1 = data.cols();
  unsigned int n = n0*n1;
  fftw_complex * out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*n);
  fftw_complex * in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*n);
  for (unsigned int i=0;i<n;i++)
  {
    in[i][0] = data(i).real();
    in[i][1] = data(i).imag();
  }
  fftw_plan p = fftw_plan_dft_2d(n0, n1, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(p);

  Eigen::MatrixXd output(n0, n1);
  for (unsigned int i=0;i<n;i++)
  {
    output(i) =  out[i][0];
  }

  fftw_destroy_plan(p);
  fftw_free(in);
  fftw_free(out);
  return output;
}
