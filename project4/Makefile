OS := $(shell uname)

# Input and output directories
out_dir = bin
src_dir = source
h_dir = headers

# Places to search for sources
VPATH = $(src_dir):$(h_dir)

# Names of the libraries
projs = Graph Node dijkstra
libs = $(foreach proj,$(projs),$(out_dir)/$(proj).lib)

ifeq ($(OS), Darwin) # OSX
	CLIBS= 		-std=c++11
	CFLAGS=		$(CLIBS)
else # Linux
	CLIBS= 		-std=c++11 # Untested
	CPATHS=		-I/usr/include -L/usr/lib
	CFLAGS=		$(CPATHS) $(CLIBS)
endif

# Compile any lib
$(out_dir)/%.lib: %.cpp %.h
	@mkdir -p $(out_dir) # "@" prefix silences the command
	g++ $(CFLAGS) -c $< -o $@

# Compile complete project with driver
dijkstra: $(libs) $(src_dir)/driver.cpp
	g++ $(CFLAGS) $(src_dir)/driver.cpp $(libs) -o $(out_dir)/dijkstra

# Clean up
clean:
	rm $(out_dir)/*
