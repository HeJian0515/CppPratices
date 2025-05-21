#include <fmt/printf.h>
#include <gsl/pointers>
#include <memory>

struct Foo {
   static int count;

   int id;
   explicit Foo(): id(++count) {
      fmt::print("Foo:{} created\n", id);
   }
   ~Foo() {
      fmt::print("Foo:{} destroyed\n", id);
   }
};

int Foo::count = 0;

int main() {
   fmt::print("Hello, {}!\n", "Clion");
   gsl::owner<Foo*> foo = new Foo();
   delete foo;
   gsl::unique_ptr<Foo> foo1 = std::make_unique<Foo>();
   gsl::unique_ptr<Foo> foo2 = std::make_unique<Foo>();
   return 0;
}
