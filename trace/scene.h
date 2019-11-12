//scene.h

#ifndef SCENE
#define SCENE

//#include "object.h"
//#include "light.h"
#include "object.h"
#include "ray.h"
#include "rgb.h"
#include "ppm.h"

class Scene
{
 public:
  Scene(void);
  Scene(List* objects, List* lights);
  
  void set_objects(List* objects);
  void set_lights(List* lights);
  void set_anti_aliasing(bool all);
  void set_resolution(int x, int y);
  void set_xres(int x);
  void set_yres(int y);
  void render(void);
  void save_to_file(const char *filename);
  void set_position(Vector cp);
  void set_direction(Vector dir);
  void set_up(Vector u);
  void set_aspect(double asp);
  void set_bg_color(rgb bg_col);
  void set_ray_threshold(double rt);
  void set_brightness(double b);
  void set_gamma(double g);
  void set_dof_quality(int quality);
  void set_dof_focus(double focus);
  void set_dof_aperture(double aperture);

  Vector get_position(void);       
  List* get_objects(void);
  List* get_lights(void);
  bool get_anti_aliasing(void);
  int get_xres(void);
  int get_yres(void);
  PPM* get_image(void);

 protected:
  rgb trace_ray(Ray ray);
  rgb point(int x, int y, int depth);
  rgb pinpoint(int x, int y);
  void calc_side(void);
  void find_closest(Ray ray, double* closest, Vector* isect, Object** contact, rgb* filter);
  
  rgb bg_color;
  List *objects;
  List *lights;
  PPM image;
  bool anti_aliasing;
  Vector position, direction, up, side;
  double aspect, ray_threshold, brightness, xs, ys, gamma;
  double dof_aperture, dof_focus;
  int ray_tally, dof_quality;
 private:
};

void destroy_scene(Scene *s);

#endif
