include ../Makefile

objects = function.o main.o
libs = -lstdc++

libtimer.a: $(objects)
	$(library) libtimer.a $(objects)
	cd ../lib;ln -s ../timer/libtimer.a libtimer.a;cd ../timer

function.o: function.cc timer.h
	$(compiler) $(flags) $(compile) function.cc

main.o: main.cc timer.h
	$(compiler) $(flags) $(compile) main.cc

clean:
	rm *.o

veryclean: clean
	rm libtimer.a
