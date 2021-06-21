COPT = -std=c++11

all:	dss.o scopinfo.o
	$(CXX) $(COPT) -O3 -o dss dss.o scopinfo.o -L/usr/local/lib -L/usr/local/lib -lisl -lpet

dss.o:	dss.cc scopinfo.hh
	$(CXX) $(COPT) -c -O3 dss.cc

scopinfo.o:	scopinfo.cc scopinfo.hh
	$(CXX) $(COPT) -c scopinfo.cc

clean:
	rm *.o rm *~ dss
