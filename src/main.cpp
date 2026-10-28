#include "lab_string.hpp"

#include <iostream>
#include <utility>

int main() {
    std::cout << "Family A, variant 7\n";

    String text("Hello");
    String copy(text);
    String moved(std::move(copy));

    text.append(", World!");
    text.print(std::cout);
    std::cout << "\nSize: " << text.size() << '\n';
    std::cout << "World position: " << text.find("World") << '\n';

    std::cout << "Moved text: ";
    moved.print(std::cout);
    std::cout << "\nSource size after move: " << copy.size() << '\n';

    copy = text;
    copy.push_back('!');
    std::cout << "Assigned text: ";
    copy.print(std::cout);

    String words("aa bb ccc");
    String wrapped = words.wrap(5);
    std::cout << "\nWrap with width 5:\n";
    wrapped.print(std::cout);
    std::cout << '\n';
}
