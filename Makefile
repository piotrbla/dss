COPT = -std=c++11 -g
SRCS=$(wildcard *.cc)
OBJS=$(SRCS:.cc=.o)

all:	dss

dss:	$(OBJS)
	$(CXX) $(COPT) -o dss $(OBJS) -L/usr/local/lib -L/usr/local/lib -lisl -lpet

%.o:	%.cc
	$(CXX) $(COPT) -c  $<

clean:
	rm *.o *~ dss
