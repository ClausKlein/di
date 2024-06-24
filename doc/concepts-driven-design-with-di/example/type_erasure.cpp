#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/builtin.hpp>
#include <boost/type_erasure/free.hpp>
#include <boost/type_erasure/member.hpp>
#include <cassert>
#include <fstream>
#include <iostream>

BOOST_TYPE_ERASURE_MEMBER((has_read), read, 0)
BOOST_TYPE_ERASURE_MEMBER((has_show), show, 1)

using Reader = boost::mpl::vector<has_read<int()>, boost::type_erasure::copy_constructible<>>;
using Viewer = boost::mpl::vector<has_show<void(int)>, boost::type_erasure::copy_constructible<>>;

class FileReader {
  const std::string path;
  //XXX std::fstream file;

 public:
  explicit FileReader(const std::string& _path) : path(_path) { }
  //XXX explicit FileReader(const std::string& path) : file(path) { assert(file.good()); }

  int read() {
    auto value = 12;
    std::fstream file(path);    // Note: this is better! CK

    file >> value;
    assert(file.good());

    return value;
  }
};

class ConsoleViewer {
 public:
  void show(int value) { std::cout << value << std::endl; }
};

class App {
  boost::type_erasure::any<Reader> reader;
  boost::type_erasure::any<Viewer> viewer;

 public:
  App(boost::type_erasure::any<Reader> reader, boost::type_erasure::any<Viewer> viewer) : reader(reader), viewer(viewer) {}

  void run() { viewer.show(reader.read()); }
};

int main() {
  FileReader reader{"input.txt"};
  ConsoleViewer viewer{};
  App{reader, viewer}.run();
}
