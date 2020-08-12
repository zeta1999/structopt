#include <structopt/structopt.hpp>
#include <utility>

struct Foo {
  // positional arguments
  int foo{0};
  float bar{0.0f};
  bool baz{false};
  std::array<char, 5> chars;

  // optional "flag" argument
  // -v or --verbose works
  std::optional<bool> verbose;

  // optional "flag" ARRAY argument
  // --blah 1 2 3
  std::optional<std::array<int, 3>> blah;
};
STRUCTOPT(Foo, foo, bar, baz, chars, verbose, blah);

int main(int argc, char *argv[]) {
  auto foo = structopt::parse<Foo>(argc, argv);
  std::cout << "foo, bar, baz: " << foo.foo << " " << foo.bar << " " << std::boolalpha << foo.baz
            << "\n";

  std::cout << "chars: ";
  for (auto &c : foo.chars) {
    std::cout << c << " ";
  }

  std::cout << "\nverbose? " << std::boolalpha << foo.verbose.value_or(false) << "\n";

  if (foo.blah.has_value()) {
    std::cout << "Blah: ";
    auto blah = foo.blah.value();
    for (auto &v : blah) {
      std::cout << v << " ";
    }
    std::cout << "\n";
  }
}