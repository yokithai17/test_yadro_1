#include "FileTape.h"

#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

FileTape::FileTape(const std::string& filename, const std::string& configPath)
  : M_position_(0) {

  std::filesystem::path p(filename);
  if (p.has_parent_path()) {
    create_directories(p.parent_path());
  }

  M_file_.open(filename, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
  if (!M_file_)
    throw std::runtime_error("Cannot open tape file " + filename + " (Error: " + std::string(strerror(errno)) + ")");

  M_file_.seekg(0, std::ios::end);
  M_size_ = M_file_.tellg() / sizeof(int32_t);
  M_file_.seekg(0, std::ios::beg);

  load_config(configPath);
}

FileTape::~FileTape() {
  M_file_.close();
}

void FileTape::load_config(const std::string& configPath) {
  std::ifstream configFile(configPath);
  if (!configFile)
    throw std::runtime_error("Config file not found");

  std::string line;
  while (std::getline(configFile, line)) {
    std::istringstream iss(line);
    std::string key;
    if (std::getline(iss, key, '=')) {
      unsigned int value;
      iss >> value;
      if (key == "read_delay")
        M_read_delay_ = value;
      else if (key == "write_delay")
        M_write_delay = value;
      else if (key == "move_delay")
        M_move_delay = value;
      else
        if (key == "reset_delay")
          M_reset_delay_ = value;
    }
  }
}

void FileTape::apply_delay(unsigned int milliseconds) const {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int32_t FileTape::read() {
  apply_delay(M_read_delay_);
  int32_t data;
  M_file_.seekg(M_position_ * sizeof(int32_t));
  M_file_.read(reinterpret_cast<char*>(&data), sizeof(int32_t));
  return data;
}

void FileTape::write(int32_t data) {
  apply_delay(M_write_delay);
  M_file_.seekp(M_position_ * sizeof(int32_t));
  M_file_.write(reinterpret_cast<const char*>(&data), sizeof(int32_t));
}

void FileTape::move_forward() {
  apply_delay(M_move_delay);
  if (M_position_ < M_size_)
    M_position_++;
}

void FileTape::move_backward() {
  apply_delay(M_move_delay);
  if (M_position_ > 0)
    M_position_--;
}

void FileTape::reset() {
  apply_delay(M_reset_delay_);
  M_position_ = 0;
}

bool FileTape::is_end() const {
  return M_position_ >= M_size_;
}
