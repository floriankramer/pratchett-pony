#include "pony.h"

#include <cmrc/cmrc.hpp>
#include <cstdlib>
#include <sstream>

CMRC_DECLARE(ponies);

namespace pony {
PonyList loadPonies() {
  PonyList ponies;
  auto fs = cmrc::ponies::get_filesystem();
  for (const auto &entry : fs.iterate_directory("/")) {
    ponies.push_back(entry.filename());
  }
  return ponies;
}

std::tuple<Pony, unsigned int> pickRandomPony(PonyList ponies,
                                              unsigned int rng_seed) {
  if (ponies.empty()) {
    return {Pony{"PonyList is empty"}, rng_seed};
  }
  int random = rand_r(&rng_seed) % ponies.size();
  auto res = parsePony(ponies[random]);
  if (std::holds_alternative<Error>(res)) {
    return {Pony{std::get<Error>(res)}, rng_seed};
  } else {
    return {std::get<Pony>(res), rng_seed};
  }
}

std::variant<Pony, Error> parsePony(PonyId pony) {
  auto fs = cmrc::ponies::get_filesystem();
  if (!fs.exists(pony) || fs.is_directory(pony)) {
    return Error(pony + ": No such pony exists in the database");
  }
  Pony p;

  auto pony_file = fs.open(pony);
  std::string raw_pony(pony_file.begin(), pony_file.end());
  std::string::size_type body_start = raw_pony.rfind("$$$");

  p.pony = raw_pony.substr(body_start + 4);
  return p;
}

std::string ponysay(const Pony &pony, const std::string &message) {
  std::string res = pony.pony;
  std::string::size_type first_line_end = res.find('\n');
  if (first_line_end == std::string::npos) {
    return "";
  }
  std::string balloon_descriptor = res.substr(0, first_line_end);
  res = res.substr(first_line_end + 1);

  // Remove thje $ signs surrounding the balloons line
  std::string::size_type dollar_pos;
  while ((dollar_pos = res.find('$')) != std::string::npos) {
    res[dollar_pos] = ' ';
  }

  std::string balloon = pony::balloon(message);

  // Parse the balloon descriptor
  std::string::size_type num_pos = balloon_descriptor.find("$balloon");
  if (num_pos != std::string::npos) {
    num_pos += 8; // The length of $balloon
    std::string::size_type end_pos = balloon_descriptor.find('$', num_pos);
    if (end_pos != std::string::npos) {
      unsigned long balloon_pos =
          std::stoul(balloon_descriptor.substr(num_pos, end_pos - num_pos));
      size_t balloon_size = getMessageWidth(balloon);
      if (balloon_size < balloon_pos + 3) {
        balloon = indentMessage(balloon, balloon_pos + 3 - balloon_size);
      }
    }
  }
  return balloon + '\n' + res;
}

std::string balloon(const std::string &message) {
  size_t msg_width = getMessageWidth(message);
  size_t msg_height = getMessageHeight(message);

  std::ostringstream balloon;
  balloon << ' ';
  for (size_t i = 0; i < msg_width + 2; ++i) {
    balloon << '_';
  }
  balloon << " \n";
  balloon << "/";
  for (size_t i = 0; i < msg_width + 2; ++i) {
    balloon << ' ';
  }
  balloon << "\\\n";

  size_t msg_pos = 0;
  for (size_t line = 0; line < msg_height; ++line) {
    balloon << "| ";
    size_t msg_line_length = 0;
    while (msg_pos < message.size() && message[msg_pos] != '\n') {
      balloon << message[msg_pos];
      msg_line_length++;
      msg_pos++;
    }
    for (int i = msg_line_length; i < msg_width; ++i) {
      balloon << ' ';
    }
    msg_pos++;
    balloon << " |\n";
  }
  balloon << "\\";
  for (size_t i = 0; i < msg_width + 2; ++i) {
    balloon << ' ';
  }
  balloon << "/\n";
  balloon << ' ';
  for (size_t i = 0; i < msg_width + 2; ++i) {
    balloon << '-';
  }
  return balloon.str();
}

size_t getMessageWidth(const std::string &message) {
  std::string::size_type start = 0;
  std::string::size_type end = message.find('\n');
  if (end == std::string::npos) {
    return message.length();
  }
  end = 0;
  size_t length = 0;
  while ((end = message.find('\n', end + 1)) != std::string::npos) {
    length = std::max(length, end - start);
    start = end + 1;
  }
  length = std::max(length, message.length() - start);
  return length;
}

size_t getMessageHeight(const std::string &message) {
  size_t length = message.length() > 0 ? 1 : 0;
  std::string::size_type pos = 0;
  while ((pos = message.find('\n', pos + 1)) != std::string::npos) {
    length++;
  }
  return length;
}

std::string indentMessage(const std::string &message, size_t indentations) {
  std::string indentation(indentations, ' ');
  std::string res;
  std::string::size_type start = 0;
  std::string::size_type end = 0;
  while ((end = message.find('\n', end + 1)) != std::string::npos) {
    res += indentation + message.substr(start, end - start + 1);
    start = end + 1;
  }
  res += indentation + message.substr(start);
  return res;
}

}  // namespace pony
