IDIR = ./include
LINK_TARGET = main
SRCDIR = ./src

# Here is a Make Macro that uses the backslash to extend to multiple lines.
OBJS =  \
LaserHost.o \
LinuxSocket.o \
vLog.o \

REBUILDABLES = $(OBJS) $(LINK_TARGET) -fsanitize=address -static-libasan -g

#-fsanitize=address -static-libasan -g

CFLAGS =-I$(IDIR) -lstdc++ -std=c++1z -pthread 

clean : 
	rm -f $(OBJS) $(LINK_TARGET).o $(FIT_TEST).o
	echo Clean done

all : $(LINK_TARGET) 
	chmod +x $(LINK_TARGET)
	echo All done

$(LINK_TARGET) : $(OBJS) $(LINK_TARGET).o IntegralHash.o
	g++ -g -o $@ $^ $(CFLAGS)

%.o : ${SRCDIR}/%.cpp
	g++ -g -o $@ -c $< $(CFLAGS)