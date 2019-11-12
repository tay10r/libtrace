include ../Makefile

objects = main.o ../lib/libtrace.a ../lib/libppm.a ../lib/libtimer.a
libs = -lstdc++
includes = -I../include

tracetest: $(objects)
	$(compiler) $(flags) $(libs) $(link) tracetest $(objects)

main.o: main.cc
	$(compiler) $(flags) $(includes) $(compile) main.cc

clean:
	rm *.o

veryclean: clean
	rm tracetest *.ppm
