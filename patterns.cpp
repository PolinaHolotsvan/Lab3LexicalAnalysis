#include <iostream>
#include "patterns.h"

using namespace std;

string getMultilineComments() {
    return R"(\/\*(.+|\r|\n)*\*\/)";
}

string getSingleLineComment() {
    return "//.*";
}

string getString() {
    return R"("((\\\")|[^"])*")";
}

string getChar() {
    return R"(("([^"]|\\.)*"|'(\\['"tvrnafb\\]|[^'\\])'))";
}

string getBoolean() {
    return R"(\b(false|true)\b)";
}

string getIntFloatScientific() {
    return "[0-9]*[.]?[0-9]+([eE][-+]?[0-9]+)";
}

string getIntFloat() {
    return "[0-9]*[.]?[0-9]+([eE][-+]?[0-9]+)?";
}

string getHexNumbers() {
    return "0x[0-9A-Fa-f]*";
}

string getBinaryNumbers() {
    return "0b[01]*";
}

string getOctalNumbers() {
    return "0[1-7][0-7]*";
}

string getVariable() {
    return "[_A-Za-z][0-9A-Za-z_]*(?!\\()";
}

string getTypeNames() {
    return R"(\b(asm|bool|auto|char|class|double|struct|enum|typedef|"
           "template|int|union|wchar_t|long|unsigned|signed|void|int)\b)";
}

string getDirectives() {
    return "#[ ]*(define|import|include|elif|else|ifndef|"
           "error|if|ifdef|pragma|line|undef|using|endif)";
}

string getLibraries() {
    return "[ ]+<("
           "cassert|cctype|cerrno|cfloat|ciso646|climits|clocale|cmath|"
           "csetjmp|csignal|cstdarg|cstddef|cstdio|cstdlib|cstring|ctime|"
           "ccomplex|cfenv|cinttypes|cstdalign|cstdbool|cstdint|ctgmath|"
           "cwchar|cwctype|algorithm|bitset|complex|deque|exception|"
           "fstream|functional|iomanip|ios|iosfwd|iostream|istream|"
           "iterator|limits|list|locale|map|memory|new|numeric|ostream|"
           "queue|set|sstream|stack|stdexcept|streambuf|string|typeinfo|"
           "utility|valarray|vector|array|atomic|chrono|condition_variable|"
           "forward_list|future|initializer_list|mutex|random|ratio|regex|"
           "scoped_allocator|system_error|thread|tuple|typeindex|type_traits|"
           "unordered_map|unordered_set|bits\\/stdc\\+\\+\\.h)>";
}

string getCLibraries() {
    return "[ ]+<("
           "assert|complex|ctype|errno|fenv|float|inttypes|iso646|limits|"
           "locale|math|setjmp|signal|stdalign|stdarg|stdatomic|stdbool|"
           "stddef|stdint|stdio|stdlib|stdnoreturn|string|tgmath|threads|"
           "time|uchar|wchar|wctype)\\.h>";
}

string getAdditionalLibraries() {
    return "[ ]+<.*\\.h>";
}

string getReservedWords() {
    return R"(\b("
           "break|case|catch|const|const_cast|continue|delete|do|dynamic_cast|"
           "far|near|new|sizeof|volatile|goto|static|public|private|explicit|export|else|huge|"
           "try|this|throw|typeid|switch|sizeof|if|register|operator|mutable|"
           "namespace|extern|inline|return|using|virtual|while|default|for)\b)";
}

string getTypeDefinition() {
    return R"(typedef\s+([A-Za-z_][A-Za-z_0-9]*))";
}

string getMain() {
    return R"(\b(main)\b(?=\(\)))";
}

string getFunctionDefinition() {
    return R"([_A-Za-z][0-9A-Za-z_]*(?=\((([A-Za-z_][A-Za-z_0-9]*[*&]*[\s]+[A-Za-z_]+[A-Za-z_0-9]*)+|\))))";
}

string getFunctionCall() {
    return "[_A-Za-z][0-9A-Za-z_]*(?=\\()";
}

string getDelimiters() {
    return R"([\(\)\{\}\;])";
}

string getOperators() {
    return R"([\+\-\*\/\.\%\[\]\<\>\=\&\|\,\?\:\!\^\~\\\#])";
}

string getLinesAndSpaces() {
    return "[ \t\n]+";
}

string getError() {
    return ".*";
}
