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
  std::cout<<I<<std::endl;
  f1.plt.imshow(i);
  f2.plt.imshow(m::log(m::abs(I.block(0,0,128,128).array()+0.001)));
  f2.show();
  f1.plt.savepdf("imgage.pdf");
  f2.plt.savepdf("fft2.pdf");
  return app->run(f1);
}
