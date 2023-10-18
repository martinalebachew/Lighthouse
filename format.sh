find . \( -name \*.hpp -o -name \*.cpp \) -exec clang-format -style=file -i {} \;
