
#include "../src/math.h"
#include "../src/images.h"
#include "../src/fft.h"
#include <Eigen/Core>

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

#include <ctime>

using namespace std;

int getpngs (string dir, vector<string> &files)
{
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
    cout << "Error(" << errno << ") opening " << dir << endl;
    return errno;
  }

  while ((dirp = readdir(dp)) != NULL) {
    string fn = string(dirp->d_name);
    if (fn.substr(fn.find_last_of(".") + 1) == "png")
    {
      files.push_back(fn);
    }
  }
  closedir(dp);
  return 0;
}

int main(int argc, char** argv)
{
  if (argc == 1)
  {
    cout<<"Missing argument...\n";
    return errno;
  }
  string dir = string(argv[1]);
  vector<string> files = vector<string>();
  vector<Eigen::MatrixXd> images;
  getpngs(dir,files);
  clock_t begin_time = clock();
  for (auto file: files) {
    images.push_back(img::load(dir+"/"+file));
  }
  cout <<"loading: "<< float( clock () - begin_time ) /  CLOCKS_PER_SEC<<" s\n";
  begin_time = clock();
  for (auto i: images) {
    auto I = fft::fft2(i);
  }
  cout <<"fft: "<< float( clock () - begin_time ) /  CLOCKS_PER_SEC<<" s\n";
  return 0;
}
