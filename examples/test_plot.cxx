#include "../src/plotty.h"
#include "../src/math.h"
#include <Eigen/Dense>
#include <gtkmm/application.h>

#include <iostream>


int main(int argc, char** argv)
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  Figure f;


  Eigen::VectorXd x = m::linspace(0, 1, 100);
  Eigen::VectorXd gauss = m::exp(-(m::pow(x,2)));
  Eigen::VectorXd sinc  = m::abs(m::sin(m::pi*2*x).cwiseProduct((m::pi*2*x).cwiseInverse()));
  Eigen::VectorXd lapl  = m::exp(-x.cwiseAbs()*2);
  f.plt.plot(x, sinc, BLUE, 1.5, LS_CONTINUOS_KEY, PS_NONE, "sinc");
  f.plt.plot(x, lapl, RED, 1.5, LS_DASH_KEY, PS_DOT, "lapl");
  f.plt.plot(x, gauss, GREEN, 1.5, LS_DOTS_KEY, PS_DIAMOND, "gauss");
  f.plt.legend();

  f.plt.savepdf("ex_plot.pdf");
  return app->run(f);
}
