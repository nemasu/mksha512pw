CC=g++
CCOPTS=-std=c++11 -fpic -Wall -Werror
LINKOPTS=-lcrypt


all: CCOPTS += -O2
all: strip

static: LINKOPTS += -static -O2
static: strip

debug: CCOPTS += -g
debug: mksha512pw

mksha512pw: mksha512pw.o
	${CC} mksha512pw.o -o mksha512pw ${LINKOPTS}

mksha512pw.o: mksha512pw.cpp
	${CC} ${CCOPTS} -c mksha512pw.cpp -o mksha512pw.o

strip: mksha512pw
	strip --strip-debug mksha512pw
	strip --strip-all mksha512pw

clean:
	rm -rf mksha512pw *.o

install: all
	cp -v mksha512pw /usr/bin/
