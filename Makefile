OUTPUT=parser.out
SRC=src/*.cpp
INCLUDE=include
VERSION=c++1z

default:
	g++ ${SRC} -o ${OUTPUT} -std=${VERSION} -I ${INCLUDE}

clean:
	rm ${OUTPUT}