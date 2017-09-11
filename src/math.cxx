#include "math.h"
#include <cmath>

using namespace m;


Eigen::VectorXd m::linspace(double start, double stop, unsigned int n)
{
  Eigen::VectorXd x(n);
  double delta = (stop-start)/(n-1);
  for (unsigned int i = 0; i<n; i++)
  {
    x(i) = (start+i*delta);
  }
  return x;
}

Eigen::MatrixXd m::cos(Eigen::MatrixXd x)
{
  Eigen::MatrixXd y(x.rows(), x.cols());
  for (unsigned int i = 0; i<x.size();i++)
  {
    y(i) = (std::cos(x(i)));
  }
  return y;
}

Eigen::MatrixXd m::sin(Eigen::MatrixXd x)
{
  Eigen::MatrixXd y(x.rows(), x.cols());
  for (unsigned int i = 0; i<x.size();i++)
  {
    y(i) = (std::sin(x(i)));
  }
  return y;
}

Eigen::MatrixXd m::pow(Eigen::MatrixXd x, double a)
{
  Eigen::MatrixXd y(x.rows(), x.cols());
  if (a==2)
  {
    for (unsigned int i =0; i<x.size();i++){
      y(i) = x(i)*x(i);
    }
  }else
  {
    for (unsigned int i = 0; i<x.size();i++)
    {
      y(i) = (std::pow(x(i),a));
    }
  }
  return y;
}

Eigen::MatrixXd m::exp(Eigen::MatrixXd x)
{
  Eigen::MatrixXd y(x.rows(), x.cols());
  for (unsigned int i = 0; i<x.size();i++)
  {
    y(i) = (std::exp(x(i)));
  }
  return y;
}


Eigen::MatrixXd m::log(Eigen::MatrixXd x)
{
  Eigen::MatrixXd y(x.rows(), x.cols());
  for (unsigned int i = 0; i<x.size();i++)
  {
    y(i) = std::log(x(i));
  }
  return y;
}

Eigen::MatrixXd m::log10(Eigen::MatrixXd x)
{
  Eigen::MatrixXd y(x.rows(), x.cols());
  double base = std::log(10);
  for (unsigned int i = 0; i<x.size();i++)
  {
    y(i) = (std::log(x(i))/base);
  }
  return y;
}


Eigen::MatrixXd m::sqrt(Eigen::MatrixXd x)
{
  return x.cwiseSqrt();
}

/* Eigen::MatrixXd math::abs(Eigen::MatrixXd x) */
/* { */
/*   return x.cwiseAbs(); */
/* } */

Eigen::MatrixXd m::abs(Eigen::MatrixXcd x)
{
  return x.cwiseAbs();
}

double m::mean(Eigen::MatrixXd x)
{
  return x.mean();
}

double m::var(Eigen::MatrixXd x)
{
  double avg = mean(x);
  return mean(pow((x.array()-avg),2));
}

double m::std(Eigen::MatrixXd x)
{
  return std::sqrt(var(x));
}
