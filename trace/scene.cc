//scene.cc

//The bigger functions are in scene2.cc:
// Scene::point
// Scene::find_closest
// Scene::trace_ray

#include <math.h>
#include <iostream>

#include "timer.h"

#include "scene.h"
#include "random.h"

Scene::Scene(void)
{
 RANDOM_INIT
 set_objects(0);
 set_lights(0);
 set_resolution(320, 240);
 set_position(Vector(0,0,0));
 set_direction(Z);
 set_up(Y*0.5);
 set_aspect(4.0/3.0);
 set_anti_aliasing(false);
 set_bg_color(BLACK);
 set_ray_threshold(1.0/256.0);
 set_brightness(0.5);
 set_gamma(2.0);
 set_dof_quality(1);
 set_dof_focus(1);
 set_dof_aperture(0);
 xs=ys=0;
 ray_tally=0;
}

void destroy_scene(Scene *s)
{
 destroy_list(((*s).get_objects()));
 destroy_list(((*s).get_lights()));
 delete s;
}

void Scene::set_objects(List* o)
{
 objects=o;
 if (objects!=0)
  objects=(*objects).find_head();
}

void Scene::set_lights(List* l)
{
 lights=l;
 if (lights!=0)
  lights=(*lights).find_head();
}

List* Scene::get_objects(void)
{
 return objects;
}

List* Scene::get_lights(void)
{
 return lights;
}

void Scene::set_resolution(int x, int y)
{
 image.set_dimensions(x, y);
}

void Scene::set_xres(int x)
{
 image.set_width(x);
}

void Scene::set_yres(int y)
{
 image.set_height(y);
}

void Scene::render(void)
{
 std::cout << "Rendering " << image.get_width() << "*" << image.get_height() << ":\n"; 
 image.allocate();
 
 ray_tally=0;
 int x, y;
 //xs and ys are the width and the height of the smallest section a pixel is split into
 // (on the -1 to 1 scale)
 xs=2.0/(get_xres()*16);
 ys=2.0/(get_yres()*16);
 rgb p;
 
 Timer timer;
 
 for (y=0; y<get_yres(); y++)
 {
  std::cout << "\r                                                            \r\tLine: " << (y+1);
  
  if (y>0)
  {
   timer.update();
   int
    eta=static_cast<int>((timer.read()*(get_yres()-y))/y),
    w=eta/604800,
    d=(eta/86400)%7,
    h=(eta/3600)%24,
    m=(eta/60)%60,
    s=eta%60;
    
   std::cout << " \tTime remaining: " << w << "w " << d << "d " << h << "h" << m << "m" << s << "s";
  }
  
  std::cout.flush();
  for (x=0; x<get_xres(); x++)
  {
   p=point(x*16, y*16, 0);
   image.set_pixel(x, y,
    static_cast<unsigned char>((p.red*255)),
    static_cast<unsigned char>((p.green*255)),
    static_cast<unsigned char>((p.blue*255))
   );
  }
 }
 
 std::cout << "\nDone\n";
 std::cout << ray_tally << " rays traced.\n";
}

int Scene::get_xres(void)
{
 return image.get_width();
}

int Scene::get_yres(void)
{
 return image.get_height();
}

void Scene::save_to_file(const char *filename)
{
 image.save_to_file(filename);
}

void Scene::set_position(Vector pos)
{
 position=pos;
}

Vector Scene::get_position(void)
{
 return position;
}

void Scene::set_direction(Vector dir)
{
 direction=dir;
 calc_side();
}

void Scene::set_up(Vector u)
{
 up=u;
 calc_side();
}

void Scene::calc_side(void)
{
 side=rotate(up, direction, M_PI/2)*aspect;
}

void Scene::set_aspect(double asp)
{
 aspect=asp;
 calc_side();
}

PPM* Scene::get_image(void)
{
 return &image;
}

void Scene::set_anti_aliasing(bool aa)
{
 anti_aliasing=aa;
}

rgb Scene::pinpoint(int xi, int yi)
{
// TODO: make DOF effects adaptive if full scene AA is off
/*
 It would be cool if a ray would be fired at each "corner" of the aperture
 radius and the routine would recurse deeper if needed.  It would be a bit like
 anti-aliasing but for DOF.
 
 This would be pointless if full scene anti-aliasing was on..  so maybe not..
 
 Currently it just fires a ray to each corner of the DOF box thingie. 
*/

 //Finds the color of the image at a given co-ord
 //xi and yi are in 1/16ths of a pixel (don't ask)
 double x=-1 + xi*xs;
 double y=-1 + yi*ys;
 
 Ray ray;
 ray.set_significance(1.0/dof_quality);
 rgb retval=BLACK;
 Vector fp=(-x*side - y*up + direction)*dof_focus + position;

 for (int count=0;count<dof_quality;count++)
 {
  double angle=RANDOM*M_PI;
  double mag=sqrt(RANDOM)*dof_aperture;
  
  Vector pos=position + cos(angle)*mag*side + sin(angle)*mag*up;
  Vector dir=fp-pos;

  ray.set_start(pos);
  ray.set_direction(dir);
  retval=retval+trace_ray(ray);
 }

 retval=retval/dof_quality; 
 retval=retval*brightness;
 retval.red=pow(retval.red, gamma);
 retval.green=pow(retval.green, gamma);
 retval.blue=pow(retval.blue, gamma);
 retval.clip();
 return retval;
}

void Scene::set_bg_color(rgb bg_col)
{
 bg_color=bg_col;
}

void Scene::set_ray_threshold(double rt)
{
 ray_threshold=rt;
}

void Scene::set_brightness(double b)
{
 brightness=b;
}

void Scene::set_gamma(double g)
{
 gamma=1.0/g;
}

void Scene::set_dof_aperture(double aperture)
{
 dof_aperture=aperture;
}

void Scene::set_dof_focus(double focus)
{
 dof_focus=focus; 
}

void Scene::set_dof_quality(int quality)
{
 dof_quality=quality;
}
