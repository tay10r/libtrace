include ../Makefile

objects = main.o io.o
libs = -lstdc++

libppm.a: $(objects)
	$(library) libppm.a $(objects)
	cd ../lib;ln -s ../ppm/libppm.a libppm.a;cd ../ppm

main.o: main.cc ppm.h
	$(compiler) $(flags) $(compile) main.cc

io.o: io.cc ppm.h
	$(compiler) $(flags) $(compile) io.cc

clean:
	rm *.o

veryclean: clean
	rm libppm.a
