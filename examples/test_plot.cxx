#include "plotty.h"
#include "math.h"
#include <Eigen/Dense>
#include <gtkmm/application.h>

#include <iostream>


int main(int argc, char** argv)
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  Figure f;


  Eigen::VectorXd x = m::linspace(0, 1, 50);
  Eigen::VectorXd gauss = m::exp(-(m::pow(x,2)));
  Eigen::VectorXd sinc  = m::abs(m::sin(m::pi*4*x).cwiseProduct((m::pi*4*x).cwiseInverse()));
  Eigen::VectorXd lapl  = m::exp(-x.cwiseAbs()*4);
  f.plt.plot(x, sinc, BLUE, 1.5, LS_CONTINUOS_KEY, PS_CROSS, "sinc");
  f.plt.plot(x, lapl, RED, 1.5, LS_DASH_KEY, PS_DOT, "lapl");
  f.plt.plot(x, gauss, GREEN, 1.5, LS_DOTS_KEY, PS_DIAMOND, "gauss");
  f.plt.legend();

  return app->run(f);
}
