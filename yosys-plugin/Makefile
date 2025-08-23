CXX=g++

eqsat.so: eqsat.cc
	$(CXX) $(shell yosys-config --cxxflags --ldflags --libs) -shared -fPIC -o $@ $<



