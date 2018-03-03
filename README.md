## Setup:
- install `tup`
- install `kqwait`
- `tup init`

## Develop:
- `sh builder.sh`

### Notes:

    clang++ -Wall -std=c++11 -stdlib=libc++ main.cpp  -I/usr/local/include -L/usr/local/lib -lSDL2 -o main

    clang++ -std=c++11 -stdlib=libc++ main.cpp  -I/usr/local/include -L/usr/local/lib -lSDL2 -headerpad_max_install_names -o main

* [http://lazyfoo.net/tutorials/SDL/index.php#Hello SDL](http://lazyfoo.net/tutorials/SDL/index.php#Hello%20SDL)
* [https://stackoverflow.com/questions/1596945/building-osx-app-bundle](https://stackoverflow.com/questions/1596945/building-osx-app-bundle)
* [https://randomascii.wordpress.com/2011/08/13/faster-fractals-through-algebra/](https://randomascii.wordpress.com/2011/08/13/faster-fractals-through-algebra/)

### Building app bundle
1. `otool -L executable_name` : list libs used by the binary
2. copy libs to `/Bundle.app/Content/MacOS/`
3. compile binary with flag `-headerpad_max_install_names`
4. `install_name_tool -change /usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib @executable_path/libSDL2-2.0.0.dylib foo.app/Contents/MacOS/foo`
5. In order to fix the current working directory when running the app, can edit *CFBundleExecutable* to point to a launch script instead of the binary:

```
    #!/bin/bash
    cd "${0%/*}"
    ./foo
```

