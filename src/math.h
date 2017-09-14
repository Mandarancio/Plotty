#ifndef MATH_HXX
#define MATH_HXX

#include <Eigen/Core>

namespace m{
  const double pi = 3.14159265359;

  Eigen::VectorXd linspace(double start, double stop, unsigned int n=10);
  /* Eigen::VectorXd logspace(double start, double stop, unsigned int n=10); */

  Eigen::MatrixXd cos(Eigen::MatrixXd x);
  Eigen::MatrixXd sin(Eigen::MatrixXd x);



  Eigen::MatrixXd pow(Eigen::MatrixXd x, double a);
  Eigen::MatrixXd sqrt(Eigen::MatrixXd x);
  Eigen::MatrixXd exp(Eigen::MatrixXd x);
  Eigen::MatrixXd log(Eigen::MatrixXd x);
  Eigen::MatrixXd log10(Eigen::MatrixXd x);

  double mean(Eigen::MatrixXd x);
  double var(Eigen::MatrixXd x);
  double std(Eigen::MatrixXd x);

  /* Eigen::MatrixXd abs(Eigen::MatrixXd x); */
  Eigen::MatrixXd abs(Eigen::MatrixXcd x);
  Eigen::MatrixXd real(Eigen::MatrixXcd x);
  Eigen::MatrixXd imag(Eigen::MatrixXcd x);
};
#endif
