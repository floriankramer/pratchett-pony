#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <variant>

namespace pony {
struct Pony {
  std::string pony;
};

using PonyId = std::string;

using PonyList = std::vector<PonyId>;
using Error = std::string;

PonyList loadPonies();

std::tuple<Pony, unsigned int> pickRandomPony(PonyList ponies,
                                             unsigned int rng_seed);

std::variant<Pony, Error> parsePony(PonyId pony);

std::string ponysay(const Pony &pony, const std::string &message);
std::string balloon(const std::string &message);
size_t getMessageWidth(const std::string &message);
size_t getMessageHeight(const std::string &message);
std::string indentMessage(const std::string &message, size_t indentations);

}  // namespace pony
