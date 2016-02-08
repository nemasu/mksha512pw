CC=g++
CCOPTS=-std=c++11 -fpic -Wall -Werror
LINKOPTS=-lcrypt


all: CCOPTS += -O2
all: mksha512pw

static: LINKOPTS += -static -O2
static: mksha512pw

debug: CCOPTS += -g
debug: mksha512pw

mksha512pw: mksha512pw.o
	${CC} mksha512pw.o -o mksha512pw ${LINKOPTS}

mksha512pw.o: mksha512pw.cpp
	${CC} ${CCOPTS} -c mksha512pw.cpp -o mksha512pw.o

clean:
	rm -rf mksha512pw *.o
