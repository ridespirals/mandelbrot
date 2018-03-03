main: main.cpp
	clang++ -std=c++11 -stdlib=libc++ main.cpp  -I/usr/local/include -L/usr/local/lib -lSDL2 -o main
