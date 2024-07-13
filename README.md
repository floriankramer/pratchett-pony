# Pratchett Pony

![image](https://github.com/user-attachments/assets/729d6610-b883-42ed-a833-a1097a68529b)

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

Run `git submodule --init` to download ponysay.

Run the provided `download_pqf.sh` bash script to download the pqf from https://www.lspace.org/ftp/words/pqf/pqf. The script requires `bash` and `wget`.

Now use `cargo build -r` to build pratchett-pony.
The resulting `pratchett-pony` executable (located at `target/release/pratchett-pony`) should only depend on your systems glibc.
For a fully dependency-free executable (such as the ones in the release section) build the project under alpine linux and
statically link against the musl c standard library. A docker setup for this is not yet included in the repo.

