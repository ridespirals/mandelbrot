main: main.cpp
	clang++ -Wall -std=c++11 -stdlib=libc++ main.cpp  -I/usr/local/include -L/usr/local/lib -lSDL2 -o main

run: main
	./main

bundle: main
	cp main Mandelbrot.app/Content/MacOS
	echo "Mandelbrot.app bundle complete"
