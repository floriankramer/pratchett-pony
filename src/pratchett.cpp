#include "pratchett.h"

#include <cmrc/cmrc.hpp>
#include <fstream>
#include <vector>

CMRC_DECLARE(pratchett_res);

namespace pratchett {

std::string getRandomQuote() {
  auto fs = cmrc::pratchett_res::get_filesystem();
  auto pqf = fs.open("pqf");
  std::string raw(pqf.begin(), pqf.end());

  size_t num_quotes = pqf.size() > 0 ? 1 : 0;
  std::string::size_type pos = 0;
  std::vector<std::string::size_type> positions;
  while ((pos = raw.find("\n\n\n", pos + 3)) != std::string::npos) {
    positions.push_back(pos);
    num_quotes++;
  }

  // Read random data from urandom
  unsigned int rng_seed;
  std::ifstream in("/dev/urandom");
  in.read(reinterpret_cast<char *>(&rng_seed), sizeof(unsigned int));

  size_t idx = rand_r(&rng_seed) % num_quotes;

  std::string quote;
  if (idx == 0) {
    if (positions.empty()) {
      quote = raw;
    } else {
      quote = raw.substr(0, positions[0]);
    }
  } else if (idx >= positions.size()) {
    quote = raw.substr(positions.back() + 3);
  } else {
    size_t start = positions[idx - 1] + 3;
    quote = raw.substr(start, positions[idx] - start);
  }

  return quote;
}
}
