# Pratchett Pony
pratchett-pony is a tool that combines the awesome features of [ponysay](https://github.com/erkin/ponysay/tree/master/ponies) and
the [pql](https://www.lspace.org/books/pqf/) (pratchet quote file) into a single, relocatable, almost dependency free executable
file.
pratchett-pony only uses the pony resource files from ponysay, it doesn't use any of the code and instead implements it's own balloon renderer
to add a message baloon to the ponies. It only uses the free ponies of ponysay.

The recommended use of the tool is to include it in your .bashrc (or the alternative for your personal shell). This greatly increases
your exposure to Terry Pratchett and to ponies, the combination of which can greatly increase your mood and productivity during
digital work.

Many thanks to Leo Breebaart and Kimberley Verburg for creating and maintaining the pqf.
Many thanks also to the people behind ponysay, and the people who committed the many ponies of ponysay.

## Building
To avoid licensing issues neither ponysay nor the pql are directly included in this repository, and neither of the fall under the license
of this repository.  

Run `git submodule --init` to download ponysay and the [cmrc](https://github.com/vector-of-bool/cmrc) (a resource compiler pratchett-pony uses
to bundle the ponies and pratchett quotes into the executable).

Run the provided `download_pqf.sh` bash script to download the pqf from https://www.lspace.org/ftp/words/pqf/pqf. The script requires `bash` and `wget`.

Now run cmake and build the executable
- `mkdir build`
- `cd build`
- `cmake ..`
- `cmake --build ..`
The resulting `pratchett-pony` executable is standalone and only depends on your systems c++ standard library.

