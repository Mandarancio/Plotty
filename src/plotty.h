#ifndef PLOTTY_HXX
#define PLOTTY_HXX

#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>
#include <cairomm/cairomm.h>


#include <string>
#include <vector>

#include <Eigen/Core>

#define PS_NONE 'n'
#define PS_DOT '.'
#define PS_CIRCLE 'o'
#define PS_VCIRCLE 'O'
#define PS_CROSS '+'
#define PS_XCROSS 'x'
#define PS_SQUARE 's'
#define PS_DIAMOND 'd'
#define PS_VDIAMOND 'D'

#define LS_CONTINUOS_KEY '|'
#define LS_DASH_KEY '-'
#define LS_DOTS_KEY ':'

#define LS_DASH std::vector<double>({8,4})
#define LS_DOTS std::vector<double>({2,3})

#define RED {1, 0, 0, 1}
#define GREEN {0, 0.8, 0, 1}
#define BLUE {0, 0, 0.8, 1}
#define BLACK {0, 0, 0, 1}
#define WHITE {1, 1, 1, 1}

#define CM_GRAY std::vector<rgba>({BLACK, WHITE})

struct lim {
  double min;
  double max;
};

struct point{
  double x;
  double y;
};

double range(lim a);
lim operator+ (const lim &a, const lim &b);
lim operator* (const lim &a, const double &b);

struct rgba {
  double r;
  double g;
  double b;
  double a;
};

struct plotarea{
  int width;
  int height;
  double inset;
  double outset;
};

class Axis{
public:
  Axis(double line_width = 1);
  ~Axis();
  void draw(const Cairo::RefPtr<Cairo::Context>& cr, plotarea area);

  point scale(double x, double y);
  point scale(point p);

  double xscale(double x);
  double yscale(double y);

  bool xlog;
  bool ylog;

  bool x_ticks;
  bool y_ticks;
  lim xlim;
  lim ylim;

  bool grid;
  bool auto_scale;
  double auto_margin;
  int font_size;
private:
  double line_width;
  Cairo::RefPtr<Cairo::ToyFontFace> font;
};


class Plot{
public:
  Plot(char line_style, char point_style, double line_width, rgba color, std::string name):
  line_style(line_style), line_width(line_width), color(color), name(name), point_style(point_style)
  {};
  virtual ~Plot(){};
  virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr, plotarea area, Axis axis)=0;
  virtual lim xlim()=0;
  virtual lim ylim()=0;

  void draw_point(const Cairo::RefPtr<Cairo::Context>& cr, double x, double y);


  const char point_style;
  const char line_style;
  const double line_width;
  const rgba color;
  const std::string name;
};

class LinePlot: public Plot{
public:
  LinePlot(Eigen::VectorXd x, Eigen::VectorXd y, double line_width, rgba color, char line_style=LS_CONTINUOS_KEY, char point_style=PS_NONE, std::string name="line");
  virtual ~LinePlot();
  virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr, plotarea area, Axis axis) override;

  virtual lim xlim() override;
  virtual lim ylim() override;


private:
  Eigen::VectorXd x, y;
};

class CMap{
public:
  CMap(std::vector<rgba> colors);
  rgba color(double val, lim limits);
  const std::vector<rgba> colors;
};

class MPlot: public Plot
{
public:
  MPlot(Eigen::MatrixXd matrix, std::string name="matrix", std::vector<rgba> cmap=CM_GRAY);
  virtual ~MPlot();
  virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr, plotarea area, Axis axis) override;

  virtual lim xlim() override;
  virtual lim ylim() override;

private:
  Eigen::MatrixXd vals;
  CMap cmap;

};


class Plotty: public Gtk::DrawingArea
{
public:
  Plotty();
  virtual ~Plotty();

  void plot(Eigen::VectorXd y, rgba color={0, 0, 0, 1}, double line_width=1, char line_style=LS_CONTINUOS_KEY, char point_style=PS_NONE, std::string label="label");
  void plot(Eigen::VectorXd x, Eigen::VectorXd y, rgba color={0, 0, 0, 1}, double line_width=1, char line_style=LS_CONTINUOS_KEY, char point_style=PS_NONE, std::string label="label");
  void imshow(Eigen::MatrixXd val, std::vector<rgba> cmap =CM_GRAY, std::string name="label");


  void legend(bool val = true);
  void grid(bool val = true);
  void xlim(lim x);
  void ylim(lim x);
  lim xlim();
  lim ylim();

  void savepdf(std::string name, int width=800, int height=600);
  void savepng(std::string name, int width=800, int height=600);



  plotarea area;
  Axis axis;



protected:
   //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;


private:
  bool legend_;
  std::vector<Plot*> plots;

  void draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
  void draw_legend(const Cairo::RefPtr<Cairo::Context>& cr);
};

class Figure: public Gtk::Window
{
public:
  Figure(std::string title = "Figure");
  virtual ~Figure();
  Plotty plt;
};

#endif

