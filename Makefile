main: mandelbrot.cpp
	clang++ -Wall -std=c++11 -stdlib=libc++ mandelbrot.cpp  -I/usr/local/include -L/usr/local/lib -lSDL2 -o mandelbrot

run: mandelbrot
	./mandelbrot

bundle: mandelbrot
	cp mandelbrot Mandelbrot.app/Contents/MacOS
	echo "Mandelbrot.app bundle complete"
