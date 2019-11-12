include ../Makefile

objects = ray.o object.o plane.o list.o light.o scene.o sphere.o line.o rgb.o scene2.o merge.o delete.o scale.o rotate.o translate.o surface.o texture.o tplain.o tchecked.o tjulia.o ttranslate.o trotate.o tscale.o box.o cylinder.o noise.o wood.o
libs = -lstdc++
includes = -I../include

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

#The default library
libtrace.a: $(objects)
	$(library) libtrace.a $(objects)
	cd ../lib;ln -s ../trace/libtrace.a;cd ../trace
	@echo "Total Lines in project: " `cat *.cc *.h | wc -l`

#Other basics
clean:
	rm *.o

veryclean: clean
	rm libtrace.a

rebuild: veryclean libtrace.a

#The various source files
#If anyone knows how to do this section in a more "generic" way then please do it
rgb.o: rgb.cc $(rgb.h)
	$(compiler) $(flags) $(includes) $(compile) rgb.cc

list.o: list.cc $(list.h)
	$(compiler) $(flags) $(includes) $(compile) list.cc

line.o: line.cc $(line.h)
	$(compiler) $(flags) $(includes) $(compile) line.cc

ray.o: ray.cc $(ray.h)
	$(compiler) $(flags) $(includes) $(compile) ray.cc

############################################################
object.o: object.cc $(object.h) $(tplain.h)
	$(compiler) $(flags) $(includes) $(compile) object.cc

plane.o: plane.cc $(plane.h)
	$(compiler) $(flags) $(includes) $(compile) plane.cc

sphere.o: sphere.cc $(sphere.h)
	$(compiler) $(flags) $(includes) $(compile) sphere.cc

light.o: light.cc $(light.h)
	$(compiler) $(flags) $(includes) $(compile) light.cc

scene.o: scene.cc $(scene.h)
	$(compiler) $(flags) $(includes) $(compile) scene.cc

############################################################
scene2.o: scene2.cc $(scene.h) $(object.h) $(light.h)
	$(compiler) $(flags) $(includes) $(compile) scene2.cc

merge.o: merge.cc $(merge.h)
	$(compiler) $(flags) $(includes) $(compile) merge.cc

delete.o: delete.cc $(delete.h)
	$(compiler) $(flags) $(includes) $(compile) delete.cc

scale.o: scale.cc $(scale.h)
	$(compiler) $(flags) $(includes) $(compile) scale.cc

rotate.o: rotate.cc $(rotate.h)
	$(compiler) $(flags) $(includes) $(compile) rotate.cc

translate.o: translate.cc $(translate.h)
	$(compiler) $(flags) $(includes) $(compile) translate.cc

torus.o: torus.cc $(torus.h)
	$(compiler) $(flags) $(includes) $(compile) torus.cc

surface.o: surface.cc $(surface.h)
	$(compiler) $(flags) $(includes) $(compile) surface.cc

texture.o: texture.cc $(texture.h)
	$(compiler) $(flags) $(includes) $(compile) texture.cc

tplain.o: tplain.cc $(tplain.h)
	$(compiler) $(flags) $(includes) $(compile) tplain.cc

tchecked.o: tchecked.cc $(tchecked.h)
	$(compiler) $(flags) $(includes) $(compile) tchecked.cc

tjulia.o: tjulia.cc $(tjulia.h)
	$(compiler) $(flags) $(includes) $(compile) tjulia.cc

tscale.o: tscale.cc $(tscale.h)
	$(compiler) $(flags) $(includes) $(compile) tscale.cc

ttranslate.o: ttranslate.cc $(ttranslate.h)
	$(compiler) $(flags) $(includes) $(compile) ttranslate.cc

trotate.o: trotate.cc $(trotate.h)
	$(compiler) $(flags) $(includes) $(compile) trotate.cc

box.o: box.cc $(box.h)
	$(compiler) $(flags) $(includes) $(compile) box.cc

cylinder.o: cylinder.cc $(cylinder.h)
	$(compiler) $(flags) $(includes) $(compile) cylinder.cc

noise.o: noise.cc $(noise.h)
	$(compiler) $(flags) $(includes) $(compile) noise.cc

############################################################
wood.o: wood.cc $(wood.h) $(tplain.h)
	$(compiler) $(flags) $(includes) $(compile) wood.cc
