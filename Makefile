CXX = g++  # Cpp compiler
CCLINK= ${CXX} # Cpp linker
CXXFLAGS = -Wall -std=c++11 -g # Cpp flags
EXEC = firewall.exe
OBJS = main.o libfirewall.so libinput.so ip.o port.o field.o string.o
RM = rm -rf   # rm command

${EXEC}: main.o libfirewall.so libinput.so
	${CCLINK} main.o libfirewall.so libinput.so -o ${EXEC}

main.o: main.cpp input.h
libfirewall.so: ip.o port.o field.o string.o
	${CCLINK} ${CXXFLAGS} -shared ip.o port.o field.o string.o -o libfirewall.so
ip.o: ip.h ip.cpp
	${CXX} ${CXXFLAGS} -c -fpic ip.cpp

port.o: port.h port.cpp
	${CXX} ${CXXFLAGS} -c -fpic port.cpp

field.o: field.h field.cpp
	${CXX} ${CXXFLAGS} -c -fpic field.cpp

string.o: string.h string.cpp
	${CXX} ${CXXFLAGS} -c -fpic string.cpp

clean:
	${RM} *.o libfirewall.so ${EXEC}