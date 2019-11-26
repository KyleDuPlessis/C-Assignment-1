# DPLKYL002
# Makefile in ./Assignment1_DPLKYL002 project folder to compile the driver and link it against the newly created shared libraries

CPP=g++ 
INCLUDES=-I./libs/databaselib -I./libs/menuinterfacelib
LIBDIRS=-L./libs/databaselib -L./libs/menuinterfacelib
LIBS= -ldatabase -lmenuinterface
CPPFLAGS=-std=c++11 $(INCLUDES) $(LIBDIRS) $(LIBS)
TARGET=Driver

# first compile - IMPLICIT PATTERN RULE for creating binary object files
%.o: %.cpp
	$(CPP) -c -o $@ $< $(CPPFLAGS)

# then link - LINKING RULE for linking binary object files together to create an executable
$(TARGET): Driver.o 
	$(CPP) -o $(TARGET) Driver.o $(CPPFLAGS)
  
# other rules
# never submit binary object / executable files
clean:
	@rm *.o Driver
	@rm ./libs/*.so
	cd ./libs/databaselib && make clean
	cd ./libs/menuinterfacelib && make clean

# build entire project
all:
	cd ./libs/databaselib && make
	cd ./libs/menuinterfacelib && make
	@cp -f ./libs/databaselib/*.so ./libs && cp -f ./libs/menuinterfacelib/*.so ./libs
	make

# run program
run:
	export LD_LIBRARY_PATH=./libs && ./Driver


