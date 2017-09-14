#include "../src/plotty.h"
#include "../src/math.h"
#include "../src/images.h"
#include "../src/fft.h"
#include <Eigen/Dense>
#include <gtkmm/application.h>

#include <iostream>


int main(int argc, char** argv)
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.plotty");

  Figure f1("Image");
  Figure f2("FFT");

  Eigen::MatrixXd i = (img::load("../data/test.gif"));
  Eigen::MatrixXcd I = fft::fft2(i);
  f1.plt.imshow(i);
  f2.plt.imshow(m::log(m::abs(I)));
  f2.show();
  return app->run(f1);
}
