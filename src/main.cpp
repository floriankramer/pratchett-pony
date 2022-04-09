#include <fstream>
#include <iostream>
#include <tuple>

#include "pony.h"
#include "pratchett.h"

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  // Read random data from urandom
  unsigned int rng_seed;
  std::ifstream in("/dev/urandom");
  in.read(reinterpret_cast<char *>(&rng_seed), sizeof(unsigned int));

  // Load a random pony
  auto res = pony::pickRandomPony(pony::loadPonies(), rng_seed);
  pony::Pony p = std::get<0>(res);
  std::cout << pony::ponysay(p, pratchett::getRandomQuote()) << std::endl;
  return 0;
}
