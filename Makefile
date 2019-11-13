.PHONY: all clean test install
all clean test install:
	$(MAKE) -C ppm       $@
	$(MAKE) -C timer     $@
	$(MAKE) -C trace     $@
	$(MAKE) -C tracetest $@
