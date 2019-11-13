objects = main.o io.o

.PHONY: all
all: libppm.a

libppm.a: $(objects)
	$(AR) $(ARFLAGS) $@ $^

main.o: main.cc ppm.h

io.o: io.cc ppm.h

.PHONY: clean
clean:
	$(RM) *.o libppm.a

.PHONY: install
install:

.PHONY: test
test:
