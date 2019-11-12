#include <iostream>
#include <stdio.h>

#include "trace.h"

#define INIT
//#define DEMO1
//#define DEMO2
//#define DEMO3
//#define DEMO4
//#define DEMO5
#define DEMO6
//#define DEMO7

#define RENDER(a,b,c,d) scene.set_resolution(b, c);scene.set_anti_aliasing(d);scene.render();scene.save_to_file(a);

int main(void)
{
#ifdef INIT
 Scene scene;
#endif

#ifdef DEMO1
 TPlain redball, greenball, blueball, shiny, glassball, black, white;
  redball.surface.color=RED;
  greenball.surface.color=GREEN;
  blueball.surface.color=BLUE;
  black.surface.color=BLACK;
  white.surface.color=WHITE;
  glassball.surface.color=WHITE;
  glassball.surface.refract=1.0;
  glassball.surface.ior=1.5;
  glassball.surface.reflect=0;
  glassball.surface.diffuse=0;
  shiny.surface.diffuse=0.25;
  shiny.surface.reflect=0.75;
  shiny.surface.specular=1.0;
  shiny.surface.hardness=100;
  
 //TChecked floor;
 // floor.texture_a=&redball;
 // floor.texture_b=&blueball;
 
 Noise floor;
  floor.min=&black;
  floor.max=&white;
  
 redball.slave=
 greenball.slave=
 blueball.slave=
 glassball.slave=
 floor.slave=&shiny;
 
 Sphere s1(Vector(-2,0,1), 1);
  s1.texture=&redball;
 Sphere s2(Vector(0,0,-1), 1);
  s2.texture=&greenball;
 Sphere s3(Vector(2,0,1), 1);
  s3.texture=&blueball;
 Plane p1(Vector(0,1,0), -1.0001);
  p1.texture=&floor;
  
 //Ring of glass balls on the floor
 Sphere *s=0, *os=0;;
 for (int ball=0;ball<36;ball++)
 {
  os=s;
  s=new Sphere;
  if (os!=0)
   (*os).set_child(s);
  
  double angle=DEG_TO_RAD(ball*10);
  
  (*s).set_center( rotate(Vector(0,-0.5,-4), Y, angle) );
  (*s).set_radius( 0.1 );
  (*s).texture=&glassball;
 }

 s1.set_child(&s2);
 s2.set_child(&s3);
 s3.set_child(&p1);
 p1.set_child((*s).find_head());

 scene.set_objects(&s1);
 
 Vector camera_pos(0, 2, -8);
 
 Light l1(camera_pos, GREY),
  l2(Vector(0,100,0),WHITE),
  l3(Vector(0,0,0.5),WHITE);
 l1.set_child(&l2);
 l2.set_child(&l3);
 
 scene.set_lights(&l1);

 scene.set_bg_color(BLACK);
 scene.set_position(camera_pos);
 scene.set_direction(rotate(Z, X, DEG_TO_RAD(20)));
 scene.set_up(rotate(Y*0.5, X, DEG_TO_RAD(20)));//*(128.0/1024.0));
 scene.set_brightness(1.0);

 RENDER("tracetest.ppm", 1024, 768, true);
#endif

#ifdef DEMO2
 TPlain blue;
  blue.surface.color=BLUE;
  blue.surface.diffuse=1.0;

 Box b1;
  b1.set_corners(Vector(1,0.5,0.25), Vector(-1, -0.5, -0.25));
 
 Rotate r1;
  r1.set_object(&b1);
  r1.set_axis(X+Y);
  r1.set_angle(DEG_TO_RAD(60));
  r1.texture=&blue;
  
 Light l1(Vector(0,0,-5), WHITE);
 
 scene.set_objects(&r1);
 scene.set_lights(&l1);
 scene.set_position(Vector(0,0,-5));
#endif

#ifdef DEMO3
 TPlain blue;
  blue.surface.color=BLUE;
  blue.surface.diffuse=1.0;
  
 Sphere
  s1(Vector(0,0,5), 1),
  s2(Vector(1,0,4), 1);
  
 Delete blob(&s1, &s2);
  blob.texture=&blue;
 
 Light l1(Vector(0,0,0), WHITE);
 
 scene.set_objects(&blob);
 scene.set_lights(&l1);
 //scene.set_bg_color(CYAN);
#endif

#ifdef DEMO4
 Sphere sphere(Vector(0, 1, 15), 2);
 Plane plane(Vector(0, 1, 0), -1);
 sphere.set_child(&plane);
 
 TPlain yellow, white, diffuse;
 yellow.surface.color=YELLOW;
 white.surface.color=WHITE;
 diffuse.surface.diffuse=1.0;
 yellow.slave=white.slave=&diffuse;
 
 sphere.texture=&yellow;
 plane.texture=&white;
 
 Light
  light1(Vector(5,0,0), WHITE),
  light2(Vector(-5,0,0), WHITE);
 light1.set_child(&light2);
 
 scene.set_objects(&sphere);
 scene.set_lights(&light1);
#endif

#ifdef DEMO5
 Cylinder cyl;
  cyl.set_length(4);
  cyl.set_radius_a(0);
  cyl.set_radius_b(1.0);
 
 Translate t1(&cyl, Vector(-2,0,0));

 Rotate r1(&t1, Y, DEG_TO_RAD(-80));

 TPlain white;
  white.surface.color=WHITE;
  white.surface.diffuse=0.25;
  white.surface.reflect=0.75;
  white.surface.specular=1.0;
  white.surface.hardness=100;
  
 Light l1(Vector(0,0,-3), BLUE),
  l2(Vector(0,0,3), RED),
  l3(Vector(0,1.5,0), GREEN);
 l1.set_child(&l2);
 l2.set_child(&l3);

 TPlain red, blue, matt;
  red.surface.color=RED;
  blue.surface.color=BLUE;
  matt.surface.diffuse=1.0;
  
 TChecked check;
  check.texture_a=&red;
  check.texture_b=&blue;
  check.slave=&matt;

 Plane
  p1(Y,-1.6),
  p2(-1.0*Y,-1.6);
 
 r1.texture=&white;
 p1.texture=&check;
 p2.texture=&check;
 
 r1.set_child(&p1);
 p1.set_child(&p2);
  
 scene.set_objects(&r1);
 scene.set_lights(&l1);
 scene.set_bg_color(GREY);
 scene.set_position(Vector(0,0,-5));
 
 scene.set_dof_quality(4);
 scene.set_dof_aperture(0.1);
 scene.set_dof_focus(5);
  
 RENDER("tracetest.ppm", 320, 240, true);
#endif

#ifdef DEMO6
/*
 Noise noise;
  noise.set_persistence(0.5);
*/
 Wood noise;

 TScale scale;
  scale.texture=&noise;
  scale.scale=Vector(5, 5, 5);

 TPlain base, light, dark;
  //base.surface.color=WHITE;
  base.surface.diffuse=0.9;
  base.surface.reflect=0.1;
  base.surface.specular=0.05;
  base.surface.hardness=100;
  dark.surface.color=rgb(35.0/256.0, 22.0/256.0, 9.0/256.0);
  light.surface.color=rgb(79.0/256.0, 48.0/256.0, 20.0/256.0);
  
 noise.min=&light;
 noise.max=&dark;
 scale.slave=&base; 
 
 Cylinder cyl;
  cyl.set_radius_a(1);
  cyl.set_radius_b(0);
  cyl.set_length(6);
 
 Rotate cy(&cyl, Z, DEG_TO_RAD(90));
 Translate c(&cy, Vector(-3,-3, 0));
 Plane
  p1(X, -6),
  p2(Y, -6),
  p3(-1*Z, -6);
 
 c.set_child(&p1);
 p1.set_child(&p2);
 p2.set_child(&p3);
 
 Merge objects(&c);
  objects.texture=&scale;
 
 
 Vector
  camera_pos(5, 5, -10),
  camera_dir=rotate(Z,    X-Y, DEG_TO_RAD(30)),
  camera_up=rotate(Y*0.5, X-Y, DEG_TO_RAD(30));
 Light
  l1(Vector(0,0,0), WHITE),
  l2(camera_pos, WHITE),
  l3(Vector(0,100,0), WHITE);
 
 l1.set_child(&l2);
 l2.set_child(&l3);
 
 scene.set_objects(&objects);
 scene.set_lights(&l1);
 scene.set_position(camera_pos);
 scene.set_direction(camera_dir);
 scene.set_up(camera_up);
 
 RENDER("demo6.ppm", 1024, 768, true);
#endif

#ifdef DEMO7
 Noise noise;
  noise.set_persistence(0.5);

 TPlain base, shiny, dull;
  //base.surface.color=WHITE;
  base.surface.diffuse=0.8;
  base.surface.reflect=0.2;
  shiny.surface.color=WHITE;
  dull.surface.color=BLACK;
  
 noise.min=&dull;
 noise.max=&shiny;
 scale.slave=&base; 
 
 Sphere s1(Vector(0,0,0), 1);
 Plane
  p1(X, -6),
  p2(Y, -6),
  p3(-1*Z, -6);
 
 s1.set_child(&p1);
 p1.set_child(&p2);
 p2.set_child(&p3);
 
 Merge objects(&s1);
  objects.texture=&scale;
 
 Light
  l1(Vector(-5,0,-5), RED),
  l2(Vector(0,5,-5), GREEN),
  l3(Vector(5,0,-5), BLUE),
  l4(Vector(0,0,-10), WHITE);
 
 l1.set_child(&l2);
 l2.set_child(&l3);
 l3.set_child(&l4);
 
 scene.set_objects(&objects);
 scene.set_lights(&l1);
 scene.set_position(Vector(0,0,-10));
 
 RENDER("demo6.ppm", 1024, 768, true);
#endif

 return 0;
}
