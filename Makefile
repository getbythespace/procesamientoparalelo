
CXX = g++

CXXFLAGS = -std=c++11 -O2 -I/usr/include/opencv4 -fopenmp

LDLIBS = -lopencv_core -lopencv_imgcodecs -lopencv_highgui


all: bin/programa_secuencial bin/programa_paralelo_thread bin/programa_paralelo_openmp


bin/programa_secuencial: src/programa_secuencial.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)

bin/programa_paralelo_thread: src/programa_paralelo_thread.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS) -pthread

bin/programa_paralelo_openmp: src/programa_paralelo_openmp.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)


clean:
	rm -f bin/*

