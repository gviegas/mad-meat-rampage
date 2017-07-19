# Installing

The only dependency is [SFML](https://www.sfml-dev.org/index.php). In the SFML site, you can find precompiled binaries to 
[download](https://www.sfml-dev.org/download.php).

### Linux

The application was tested on Debian, Ubuntu and Fedora. SFML is also available via package manager in this distributions,
`apt-get` for Debian/Ubuntu and `dnf` for Fedora:

`$ sudo apt-get install libsfml-dev`

`$ sudo dnf install SFML`

After installing SFML for your distribution, just use `make` to build the application, as explained in the [README](../README.md#how-to-run).

### macOS

It *should* work on the macOS with little to no modifications (no, I didn't test). You will need to install the Developer Tools
to use the C++ compiler `clang` and the `make` program (just type 'clang' in the Terminal app and accept the installation that pops up). As far as I can remember, clang is masqueraded as gcc in macOS so you *probably* won't even have to make changes in the makefile (no pun intended). What I can assure you is that the application compiles succesfully using clang (on Linux at least).

### Windows

Shouldn't work but all is not lost. SFML supports Windows so no problem here. There is a function defined in [aux.hxx](../include/aux.hxx) that uses a UNIX-specific call to find your current working directory (unlike SDL, SFML doesn't handle this stuff). You may need to implement the support for this function with whatever Windows offers (or just skip this as it *could* still work due to relative paths). Other than that, the application itself only uses SFML and C++11 stuff. Now I have no clue what that Visual compiler thing might do, so you're on your own from here. Good luck!
