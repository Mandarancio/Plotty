#include "plotty.h"
#include <cmath>

#include <cairomm/context.h>
#include <cairomm/surface.h>
#include <glibmm/main.h>
#include <gdkmm.h>

#include <sstream> // stringstream
#include <iomanip> // setprecision
#include <string>
#include <iostream> // debug only

double range(lim a)
{
  return abs(a.max-a.min);
}

lim operator* (const lim &a, const double &b)
{
  double r = range(a);
  double nr = r*b;
  double delta = (nr-r)/2;
  double min = a.min < a.max ? a.min - delta : a.min + delta;
  double max = a.max > a.min ? a.max + delta : a.max - delta;
  return {min, max};
}

lim operator+ (const lim &a, const lim &b)
{
  double min = a.min < b.min ? a.min : b.min;
  double max = a.max > b.max ? a.max : b.max;
  return {min, max};
}


Axis::Axis(double lw):
  x_ticks(true), y_ticks(true), xlim({0,1}), ylim({0, 1}), grid(true),
  auto_scale(true), auto_margin(1),  font_size(10),
  line_width(lw),
  font(Cairo::ToyFontFace::create("Bitstream Charter",Cairo::FONT_SLANT_NORMAL,
  Cairo::FONT_WEIGHT_NORMAL))
{
}

Axis::~Axis()
{
}

void Axis::draw(const Cairo::RefPtr<Cairo::Context>& cr, plotarea area)
{
  int use_width = area.width-area.outset*2-area.inset;
  int use_height = area.height-area.outset-area.inset;

  cr->set_line_width(line_width);
  cr->set_font_face(font);
  cr->set_font_size(font_size);
  cr->save();
  cr->set_source_rgba(0, 0, 0, 1);   // black
  cr->rectangle(area.outset*2, area.inset, use_width, use_height);
  cr->stroke();
  cr->restore(); /* stack-pen-size */

  double n_x = 8;
  double n_y = 6;
  double x_grid_size = use_width/n_x;
  double y_grid_size = use_height/n_y;

  int tick_size = 8;

  std::stringstream stream;

  if (x_ticks){
    double y = use_height+area.inset;
    double delta=(xlim.max-xlim.min)/(n_x);
    for (int i=0; i<n_x+1;i++){
      double x = i*x_grid_size+area.outset*2;
      cr->save();
      cr->move_to(x, y);
      cr->line_to(x, y+tick_size);

      if (i == n_x){
          cr->move_to(x-4*font_size, y+tick_size+4+font_size);
      }
      else{
        cr->move_to(x-2.5*font_size, y+tick_size+4+font_size);
      }

      stream.str("");
      stream<<std::scientific<<std::setprecision(2)<<xlim.min+i*delta;

      cr->show_text(stream.str());

      cr->stroke();
      cr->restore();
      if (grid){
        cr->save();
        cr->set_source_rgba(0, 0, 0, 0.5);
        cr->set_line_width(line_width/2);
        cr->move_to(x, y);
        cr->line_to(x, y-use_height);

        cr->stroke();
        cr->restore();
      }
    }
  }

  if (y_ticks){
    double x = area.outset*2;
    double delta = (ylim.max-ylim.min)/n_y;

    for (int i=0; i<n_y+1;i++){
      double y = use_height+area.inset-i*y_grid_size;
      cr->save();
      cr->move_to(x, y);
      cr->line_to(x-tick_size, y);

      cr->move_to(2, y+font_size/3);


      stream.str("");
      stream<<std::scientific<<std::setprecision(2)<<ylim.min+i*delta;
      cr->show_text(stream.str());

      cr->stroke();
      cr->restore();
      if (grid){
        cr->save();
        cr->set_source_rgba(0, 0, 0, 0.5);
        cr->set_line_width(line_width/2);
        cr->move_to(x, y);
        cr->line_to(x+use_width, y);
        cr->stroke();
        cr->restore();
      }
    }
  }


}


point Axis::scale(double x, double y)
{
  return {
    xscale(x),
    yscale(y)
  };
}

point Axis::scale(point p)
{
  return scale(p.x, p.y);
}


double Axis::xscale(double x)
{
  return x-xlim.min;
}

double Axis::yscale(double y)
{
  return y-ylim.min;
}


LinePlot::LinePlot(Eigen::VectorXd vx, Eigen::VectorXd vy, double lw, rgba c,
char ls, char ps, std::string n) :
  Plot(ls, ps, lw, c, n), x(vx), y(vy)
{

}

LinePlot::~LinePlot()
{
}

void LinePlot::draw(const Cairo::RefPtr<Cairo::Context>& cr, plotarea area, Axis axis)
{
  int x0 = area.outset*2;
  int y0 = area.height-area.outset;


  cr->save();
  // clip plot area
  cr->move_to(x0, y0);
  cr->line_to(area.width-area.inset,y0);
  cr->line_to(area.width-area.inset,area.inset);
  cr->line_to(x0, area.inset);
  cr->line_to(x0, y0);
  cr->clip();


  cr->set_line_width(line_width);
  cr->set_source_rgba(color.r, color.g, color.b, color.a);

  switch (line_style){
    case LS_DASH_KEY:
      cr->set_dash(LS_DASH, 0.0);
      break;
    case LS_DOTS_KEY:
      cr->set_dash(LS_DOTS, 0.0);
      break;
    default:
      break;
  }

  double use_width = area.width-area.outset*2-area.inset;
  double use_height = area.height-area.outset-area.inset;

  double xscale = use_width/(axis.xlim.max-axis.xlim.min);
  double yscale = use_height/(axis.ylim.max-axis.ylim.min);
  double xx = axis.xscale(x(0))*xscale+x0;
  double yy = y0 - axis.yscale(y(0))*yscale;

  cr->move_to(xx, yy);
  for (unsigned int i = 1; i < x.size(); i++)
  {
    xx = axis.xscale(x(i))*xscale+x0;
    yy = y0 -axis.yscale(y(i))*yscale;
    cr->line_to(xx, yy);
  }
  cr->stroke();

  if (point_style != PS_NONE)
  {
    for (unsigned int i = 0; i < x.size(); i++)
    {
      xx = axis.xscale(x(i))*xscale+x0;
      yy = y0 - axis.yscale(y(i))*yscale;
      draw_point(cr, xx, yy);
    }
  }
  cr->restore();
}


void Plot::draw_point(const Cairo::RefPtr<Cairo::Context>& cr, double x, double y)
{
  cr->save();
  cr->set_source_rgba(color.r, color.g, color.b, color.a);
  cr->set_line_width(1);
  cr->set_dash(std::vector<double>(),0);
  switch (point_style)
  {
    case PS_DOT:
      cr->arc(x, y, 2, 0, 2*G_PI);
      cr->fill();
      break;
    case PS_CIRCLE:
      cr->arc(x, y, 3, 0, 2*G_PI);
      cr->fill();
      break;
    case PS_VCIRCLE:
      cr->arc(x, y, 3, 0, 2*G_PI);
      cr->stroke();
      break;
    case PS_CROSS:
      cr->move_to(x-3,y);
      cr->line_to(x+3,y);
      cr->move_to(x,y-3);
      cr->line_to(x,y+3);
      cr->stroke();
      break;
    case PS_XCROSS:
      cr->move_to(x-2.5,y-2.5);
      cr->line_to(x+2.5,y+2.5);
      cr->move_to(x+2.5,y-2.5);
      cr->line_to(x-2.5,y+2.5);
      cr->stroke();
      break;
    case PS_SQUARE:
      cr->rectangle(x-1.5,y-1.5,3,3);
      cr->fill();
      break;
    case PS_DIAMOND:
      cr->move_to(x-3,y);
      cr->line_to(x, y+3);
      cr->line_to(x+3, y);
      cr->line_to(x, y-3);
      cr->line_to(x-3, y);
      cr->fill();
      break;
    case PS_VDIAMOND:
      cr->move_to(x-3,y);
      cr->line_to(x, y+3);
      cr->line_to(x+3, y);
      cr->line_to(x, y-3);
      cr->line_to(x-3, y);
      cr->stroke();
      break;
    default:
      break;
  }
  cr->restore();
}

lim LinePlot::xlim()
{
  double min = x.minCoeff();
  double max = x.maxCoeff();

  return {min, max};
}

lim LinePlot::ylim()
{
  double min = y.minCoeff();
  double max = y.maxCoeff();
  return {min, max};
}


MPlot::MPlot(Eigen::MatrixXd matrix, std::string n, std::vector<rgba> map):
  Plot(LS_CONTINUOS_KEY, PS_NONE, 0, BLACK, n), vals(matrix), cmap(map)
{}

MPlot::~MPlot()
{}

void MPlot::draw(const Cairo::RefPtr<Cairo::Context>& cr, plotarea area, Axis axis)
{
  int x0 = area.outset*2;
  int y0 = area.height-area.outset;

  double use_width = area.width-area.outset*2-area.inset;
  double use_height = area.height-area.outset-area.inset;
  double xscale = use_width/(axis.xlim.max-axis.xlim.min);
  double yscale = use_height/(axis.ylim.max-axis.ylim.min);

  cr->save();
  // clip plot area
  cr->move_to(x0, y0);
  cr->line_to(area.width-area.inset,y0);
  cr->line_to(area.width-area.inset,area.inset);
  cr->line_to(x0, area.inset);
  cr->line_to(x0, y0);
  cr->clip();

  lim limits = {vals.minCoeff(), vals.maxCoeff()};
  y0 = area.inset;

  for (int x=0;x<vals.rows();x++)
  {
    for (int y=0;y<vals.cols();y++)
    {
      rgba c = this->cmap.color(vals(x,y), limits);
      cr->save();
      cr->set_source_rgba(c.r, c.g, c.b, c.a);
      cr->rectangle(x0+x*xscale, y0+y*yscale,1.5*xscale,1.5*yscale);
      cr->fill();
      cr->restore();
    }
  }
  cr->restore();
}

lim MPlot::xlim()
{
  return {0, double(vals.rows())};
}

lim MPlot::ylim()
{
  return {0, double(vals.cols())};
}

CMap::CMap(std::vector<rgba> c) :
  colors(c)
{
}
rgba CMap::color(double val, lim limits)
{
  if (colors.size() == 0)
  {
    return BLACK;
  }
  if (colors.size() == 1)
  {
    return colors[0];
  }
  if (colors.size() == 2)
  {
    double n_val = (val-limits.min)/(limits.max-limits.min);
    double r = colors[0].r+n_val*(colors[1].r-colors[0].r);
    double g = colors[0].g+n_val*(colors[1].g-colors[0].g);
    double b = colors[0].b+n_val*(colors[1].b-colors[0].b);
    double a = colors[0].a+n_val*(colors[1].a-colors[0].a);
    return {r,g,b,a};
  }
  return {0, 0, 0, 1};
}

Plotty::Plotty():
  area({0, 0, 10, 30}), axis(), legend_(false)
{
}

Plotty::~Plotty()
{
  for (unsigned int i = 0; i<plots.size(); i++)
  {
    delete plots[i];
  }
  plots.clear();
}

void Plotty::legend(bool val)
{
  legend_ = val;
}

void Plotty::draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
  double m_line_width = 1;


  area.width = width;
  area.height = height;

  cr->set_line_width(m_line_width);

  if (axis.auto_scale) {
    lim xlim = {0, 0};
    lim ylim = {0, 0};
    for (Plot * plot : plots){
      xlim = xlim + plot->xlim();
      ylim = ylim + plot->ylim();
    }

    axis.xlim = xlim*axis.auto_margin;
    axis.ylim = ylim*axis.auto_margin;
  }

  axis.draw(cr, area);

  for (Plot * plot : plots){
    plot->draw(cr, area, axis);
  }

  if (legend_)
  {
    draw_legend(cr);
  }
}

bool Plotty::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{


  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();
  draw(cr, width, height);
  return true;
}

void Plotty::draw_legend(const Cairo::RefPtr<Cairo::Context>& cr)
{
  if (plots.size()){

    int width = 0;
    Cairo::TextExtents mytest;

    for (Plot * plot: plots)
    {
      cr->get_text_extents(plot->name, mytest);
      if (mytest.width > width)
      {
        width = mytest.width;
      }
    }

    width += 30;
    int height = 20*plots.size()+10;
    double x = area.width - area.inset -width -5;
    double y = area.inset + 5;
    cr->save();
    cr->set_source_rgba(1,1,1,0.5);
    cr->rectangle(x, y, width, height);
    cr->fill();

    cr->set_source_rgba(0,0,0,0.7);
    cr->rectangle(x, y, width, height);
    cr->stroke();



    x += 5;
    y += 15;

    for (Plot * plot : plots){
      cr->save();
      cr->set_source_rgba(plot->color.r, plot->color.g, plot->color.b, plot->color.a);
      cr->set_line_width(plot->line_width);
      switch (plot->line_style){
        case LS_DASH_KEY:
          cr->set_dash(LS_DASH, 0.0);
          break;
        case LS_DOTS_KEY:
          cr->set_dash(LS_DOTS, 0.0);
          break;
        default:
          break;
      }
      cr->move_to(x,y);
      cr->line_to(x+15, y);
      cr->stroke();
      cr->restore();
      plot->draw_point(cr, x+7.5, y);
      cr->save();
      cr->set_source_rgba(0,0,0,1);
      cr->move_to(x+20,y+4);
      cr->show_text(plot->name);
      cr->restore();
      y+=20;
    }

    cr->restore();
  }
}

void Plotty::plot(Eigen::VectorXd y, rgba color,double line_width, char line_style, char point_style, std::string label)
{
  Eigen::VectorXd x(y.size());
  for (unsigned int i = 0; i<y.size();i++)
  {
    x(i) = i;
  }
  plot(x, y, color, line_width, line_style, point_style, label);
}


void Plotty::plot(Eigen::VectorXd x, Eigen::VectorXd y, rgba color,double line_width, char line_style, char point_style, std::string label)
{
  LinePlot * lplot = new LinePlot(x, y, line_width, color, line_style, point_style, label);
  plots.push_back(lplot);
}

void  Plotty::imshow(Eigen::MatrixXd val, std::vector<rgba> cmap, std::string name)
{
  MPlot * mplot = new MPlot(val, name, cmap);
  plots.push_back(mplot);
}



void Plotty::savepdf(std::string name, int width, int height)
{
  Cairo::RefPtr<Cairo::PdfSurface> surface =
        Cairo::PdfSurface::create(name, width, height);

  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);
  draw(cr,width, height);
  cr->show_page();
}

void Plotty::savepng(std::string name, int width, int height)
{
  Cairo::RefPtr<Cairo::ImageSurface> surface =
        Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width, height);

  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);
  draw(cr,width, height);
  surface->write_to_png(name);
}


void Plotty::grid(bool val)
{
  axis.grid = val;
}

void Plotty::xlim(lim x)
{
  axis.xlim = x;
}

void Plotty::ylim(lim x)
{
  axis.ylim = x;
}

lim Plotty::xlim()
{
  return axis.xlim;
}

lim Plotty::ylim()
{
  return axis.ylim;
}

Figure::Figure(std::string title):
  Gtk::Window(), plt()
{
  this->set_default_size(600,400);
  Gdk::Geometry geom = {
    .min_width   = 400,
    .min_height  = 300,
  };
  this->set_geometry_hints(*this, geom , Gdk::HINT_MIN_SIZE);
  this->set_title(title);
  this->add(this->plt);
  this->plt.show();
}

Figure::~Figure()
{}

