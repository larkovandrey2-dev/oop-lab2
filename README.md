# Лабораторная работа 2

Семейство A, вариант 7. Класс `String` с ручным управлением памятью,
копированием, перемещением и присваиванием через copy-and-swap.
Метод варианта `wrap(width)` переносит текст по словам.

Нужны CMake 3.16+, компилятор C++20 и интернет при первой сборке для Google Test.

```bash
cmake -S . -B build
cmake --build build
./build/lab2
ctest --test-dir build --output-on-failure
```

Проверка ошибок памяти:

```bash
cmake -S . -B build-asan -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -g"
cmake --build build-asan
ctest --test-dir build-asan --output-on-failure
```

В `wrap` слова разделяются обычными пробелами. Лишние пробелы убираются,
между словами остаётся один пробел или перенос. Ширина считается в байтах;
примеры используют латиницу. Слово длиннее ширины сохраняется целиком
на отдельной строке. При нулевой ширине выбрасывается `std::invalid_argument`.


Конструктор из `const char*` принимает корректную C-строку, не `nullptr`.
В проекте 15 тестов Google Test.
