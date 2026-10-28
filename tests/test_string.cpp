#include "lab_string.hpp"

#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include <utility>

TEST(String, Empty) {
    String s;
    String text("");
    EXPECT_EQ(s.size(), 0u);
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_STREQ(text.c_str(), "");
}

TEST(String, Text) {
    String s("Hello");
    EXPECT_EQ(s.size(), 5u);
    EXPECT_STREQ(s.c_str(), "Hello");
}

TEST(String, Copy) {
    String a("Hi");
    String b(a);
    EXPECT_NE(a.c_str(), b.c_str());
    b.push_back('!');
    EXPECT_STREQ(a.c_str(), "Hi");
    EXPECT_STREQ(b.c_str(), "Hi!");
}

TEST(String, Move) {
    String a("Hi");
    const char* buffer = a.c_str();
    String b(std::move(a));
    EXPECT_EQ(b.c_str(), buffer);
    EXPECT_STREQ(b.c_str(), "Hi");
    EXPECT_EQ(a.size(), 0u);
    EXPECT_STREQ(a.c_str(), "");
    String c(a);
    c.push_back('X');
    a.push_back('Y');
    EXPECT_STREQ(c.c_str(), "X");
    EXPECT_STREQ(a.c_str(), "Y");
}

TEST(String, Assign) {
    String a("Hello");
    String b("Cat");
    b = a;
    a.push_back('!');
    EXPECT_EQ(b.size(), 5u);
    EXPECT_STREQ(b.c_str(), "Hello");
    b = "";
    EXPECT_EQ(b.size(), 0u);
    EXPECT_STREQ(b.c_str(), "");
}

TEST(String, SelfAssign) {
    String s("Hello");
    String& same = s;
    s = same;
    EXPECT_EQ(s.size(), 5u);
    EXPECT_STREQ(s.c_str(), "Hello");
}

TEST(String, MoveAssign) {
    String a("Hello");
    String b("Cat");
    const char* buffer = a.c_str();
    b = std::move(a);
    EXPECT_EQ(b.c_str(), buffer);
    EXPECT_STREQ(b.c_str(), "Hello");
    EXPECT_EQ(a.size(), 0u);
    EXPECT_STREQ(a.c_str(), "");
}

TEST(String, Swap) {
    String a("Hi");
    String b("Cat");
    a.swap(b);
    EXPECT_EQ(a.size(), 3u);
    EXPECT_STREQ(a.c_str(), "Cat");
    EXPECT_EQ(b.size(), 2u);
    EXPECT_STREQ(b.c_str(), "Hi");
}

TEST(String, PushBack) {
    String s;
    s.push_back('A');
    EXPECT_EQ(s.size(), 1u);
    EXPECT_STREQ(s.c_str(), "A");
    s.push_back('B');
    s.push_back('C');
    s.push_back('D');
    s.push_back('E');
    EXPECT_EQ(s.size(), 5u);
    EXPECT_STREQ(s.c_str(), "ABCDE");
    EXPECT_EQ(s.c_str()[s.size()], '\0');
}

TEST(String, Append) {
    String s("Hi");
    s.append("!");
    EXPECT_STREQ(s.c_str(), "Hi!");
    s.append("");
    EXPECT_STREQ(s.c_str(), "Hi!");
    String empty;
    empty.append(s);
    EXPECT_STREQ(empty.c_str(), "Hi!");
    s.append(s);
    EXPECT_EQ(s.size(), 6u);
    EXPECT_STREQ(s.c_str(), "Hi!Hi!");
}

TEST(String, Find) {
    String s("abcabc");
    EXPECT_EQ(s.find("bc"), 1u);
    EXPECT_EQ(s.find("abcabc"), 0u);
    EXPECT_EQ(s.find("c"), 2u);
    EXPECT_EQ(s.find("cabc"), 2u);
    EXPECT_EQ(s.find("x"), String::npos);
    EXPECT_EQ(s.find("abcabcd"), String::npos);
    EXPECT_EQ(s.find(""), 0u);
    String empty;
    EXPECT_EQ(empty.find(""), 0u);
    EXPECT_EQ(empty.find("a"), String::npos);
}

TEST(String, Print) {
    String s("Hello");
    std::ostringstream output;
    s.print(output);
    EXPECT_EQ(output.str(), "Hello");
    String empty;
    empty.print(output);
    EXPECT_EQ(output.str(), "Hello");
    String moved(std::move(s));
    s.print(output);
    EXPECT_EQ(output.str(), "Hello");
}

TEST(String, Wrap) {
    String s("aa bb ccc");
    String result = s.wrap(5);
    EXPECT_STREQ(result.c_str(), "aa bb\nccc");
    EXPECT_EQ(result.size(), 9u);
    EXPECT_STREQ(s.c_str(), "aa bb ccc");
    EXPECT_STREQ(s.wrap(4).c_str(), "aa\nbb\nccc");
    EXPECT_STREQ(s.wrap(20).c_str(), "aa bb ccc");
}

TEST(String, WrapEmpty) {
    String s;
    EXPECT_STREQ(s.wrap(5).c_str(), "");
    String spaces("   ");
    EXPECT_STREQ(spaces.wrap(5).c_str(), "");
    String a("abc");
    String b(std::move(a));
    EXPECT_STREQ(a.wrap(5).c_str(), "");
}

TEST(String, WrapEdges) {
    String spaces("  aa   bb ccc  ");
    EXPECT_STREQ(spaces.wrap(5).c_str(), "aa bb\nccc");
    String word("abc");
    EXPECT_STREQ(word.wrap(3).c_str(), "abc");
    String longword("longword x y");
    EXPECT_STREQ(longword.wrap(3).c_str(), "longword\nx y");
    String letters("a b");
    EXPECT_STREQ(letters.wrap(1).c_str(), "a\nb");
    EXPECT_THROW(word.wrap(0), std::invalid_argument);
}
