INC_CXXFLAGS ?= -I$(CURDIR)/../include

objects = \
	ray.o \
	object.o \
	plane.o \
	list.o \
	light.o \
	scene.o \
	sphere.o \
	line.o \
	rgb.o \
	scene2.o \
	merge.o \
	delete.o \
	scale.o \
	rotate.o \
	translate.o \
	surface.o \
	texture.o \
	tplain.o \
	tchecked.o \
	tjulia.o \
	ttranslate.o \
	trotate.o \
	tscale.o \
	box.o \
	cylinder.o \
	noise.o \
	wood.o

#Dependancy crap for the .h files
rgb.h = rgb.h
list.h = list.h
line.h = line.h
ray.h = ray.h $(line.h)
surface.h = surface.h $(rgb.h)
texture.h = texture.h $(surface.h)
object.h = object.h $(list.h) $(line.h) $(rgb.h) $(texture.h)
plane.h = plane.h $(object.h)
sphere.h = sphere.h $(object.h)
light.h = light.h $(list.h) $(rgb.h)
scene.h = scene.h $(ray.h) $(rgb.h)
merge.h = merge.h $(object.h)
delete.h = delete.h $(merge.h)
scale.h = scale.h $(merge.h)
rotate.h = rotate.h $(merge.h)
translate.h = translate.h $(merge.h)
torus.h = torus.h $(object.h)
tplain.h = tplain.h $(texture.h)
tchecked.h = tchecked.h $(texture.h)
tjulia.h = tjulia.h $(texture.h)
ttranslate.h = ttranslate.h $(texture.h)
trotate.h = trotate.h $(texture.h)
tscale.h = tscale.h $(texture.h)
box.h = box.h $(delete.h) $(plane.h)
cylinder.h = cylinder.h $(object.h)
noise.h = noise.h $(texture.h)
wood.h = wood.h $(noise.h)

.PHONY: all
all: libtrace.a

libtrace.a: $(objects)
	$(AR) $(ARFLAGS) $@ $^

.PHONY: clean
clean:
	$(RM) $(objects) libtrace.a

rebuild: veryclean libtrace.a

rgb.o: rgb.cc $(rgb.h)

list.o: list.cc $(list.h)

line.o: line.cc $(line.h)

ray.o: ray.cc $(ray.h)

############################################################
object.o: object.cc $(object.h) $(tplain.h)

plane.o: plane.cc $(plane.h)

sphere.o: sphere.cc $(sphere.h)

light.o: light.cc $(light.h)

scene.o: scene.cc $(scene.h)

############################################################
scene2.o: scene2.cc $(scene.h) $(object.h) $(light.h)

merge.o: merge.cc $(merge.h)

delete.o: delete.cc $(delete.h)

scale.o: scale.cc $(scale.h)

rotate.o: rotate.cc $(rotate.h)

translate.o: translate.cc $(translate.h)

torus.o: torus.cc $(torus.h)

surface.o: surface.cc $(surface.h)

texture.o: texture.cc $(texture.h)

tplain.o: tplain.cc $(tplain.h)

tchecked.o: tchecked.cc $(tchecked.h)

tjulia.o: tjulia.cc $(tjulia.h)

tscale.o: tscale.cc $(tscale.h)

ttranslate.o: ttranslate.cc $(ttranslate.h)

trotate.o: trotate.cc $(trotate.h)

box.o: box.cc $(box.h)

cylinder.o: cylinder.cc $(cylinder.h)

noise.o: noise.cc $(noise.h)

wood.o: wood.cc $(wood.h) $(tplain.h)

%.o: %.cc
	$(CXX) $(INC_CXXFLAGS) $(CXXFLAGS) -c $< -o $@
