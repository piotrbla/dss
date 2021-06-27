COPT = -std=c++11 -g

all:	dss

dss:	dss.o scopinfo.o tester.o
	$(CXX) $(COPT) -O3 -o dss dss.o scopinfo.o tester.o -L/usr/local/lib -L/usr/local/lib -lisl -lpet

dss.o:	dss.cc scopinfo.hh options.hh
	$(CXX) $(COPT) -c -O3 dss.cc

scopinfo.o:	scopinfo.cc scopinfo.hh options.hh
	$(CXX) $(COPT) -c scopinfo.cc

tester.o:	tester.cc tester.hh options.hh
	$(CXX) $(COPT) -c tester.cc

clean:
	rm *.o *~ dss
