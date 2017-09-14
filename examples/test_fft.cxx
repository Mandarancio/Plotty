
#include "../src/plotty.h"
#include "../src/math.h"
#include "../src/fft.h"
#include <Eigen/Dense>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <iostream>
#include <cmath>
#include <fftw3.h>


int main(int argc, char** argv)
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");


  Figure f1("Figure 1");


  Eigen::VectorXd t = m::linspace(0, 2, 100);
  Eigen::VectorXd x = m::sin(m::pi*4*t);
  Eigen::VectorXcd X = fft::fft(x);
  std::cout<<x.size()<<" -> "<<X.size()<<std::endl;

  Eigen::VectorXd y = fft::ifft(X, x.size());

  f1.plt.plot(t, y, RED, 1.5, LS_CONTINUOS_KEY, PS_NONE, "reconstruction");
  f1.plt.plot(t, x, BLUE, 1.5, LS_DOTS_KEY, PS_NONE, "Original");
  f1.plt.legend();

  Figure f2("Figure 2");

  f2.plt.plot(m::abs(X),BLUE, 1.5, LS_CONTINUOS_KEY, PS_NONE, "FFT");
  f2.plt.legend();
  f2.show();

  return app->run(f1);
}
