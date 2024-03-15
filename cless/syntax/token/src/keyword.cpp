#include "cless/syntax/token/keyword.h"

#include "cless/core/types/exception.h"

namespace cless::syntax::token {

std::ostream &operator<<(std::ostream &os, KeywordType type) {
    switch (type) {
        case KeywordType::Continue:
            return os << "continue", os;
        case KeywordType::Register:
            return os << "register", os;
        case KeywordType::Unsigned:
            return os << "unsigned", os;
        case KeywordType::Volatile:
            return os << "volatile", os;
        case KeywordType::Default:
            return os << "default", os;
        case KeywordType::Typedef:
            return os << "typedef", os;
        case KeywordType::Double:
            return os << "double", os;
        case KeywordType::Extern:
            return os << "extern", os;
        case KeywordType::Return:
            return os << "return", os;
        case KeywordType::Signed:
            return os << "signed", os;
        case KeywordType::Sizeof:
            return os << "sizeof", os;
        case KeywordType::Static:
            return os << "static", os;
        case KeywordType::Struct:
            return os << "struct", os;
        case KeywordType::Switch:
            return os << "switch", os;
        case KeywordType::Break:
            return os << "break", os;
        case KeywordType::Const:
            return os << "const", os;
        case KeywordType::Float:
            return os << "float", os;
        case KeywordType::Short:
            return os << "short", os;
        case KeywordType::While:
            return os << "while", os;
        case KeywordType::Union:
            return os << "union", os;
        case KeywordType::Auto:
            return os << "auto", os;
        case KeywordType::Case:
            return os << "case", os;
        case KeywordType::Char:
            return os << "char", os;
        case KeywordType::Else:
            return os << "else", os;
        case KeywordType::Enum:
            return os << "enum", os;
        case KeywordType::Goto:
            return os << "goto", os;
        case KeywordType::Long:
            return os << "long", os;
        case KeywordType::Void:
            return os << "void", os;
        case KeywordType::For:
            return os << "for", os;
        case KeywordType::Int:
            return os << "int", os;
        case KeywordType::Do:
            return os << "do", os;
        case KeywordType::If:
            return os << "if", os;
    }
    throw core::types::Exception("Unknown keyword type");
}

std::optional<KeywordType> keywordTypeFromStr(const std::string &str) {
    if (str == "continue")
        return KeywordType::Continue;
    if (str == "register")
        return KeywordType::Register;
    if (str == "unsigned")
        return KeywordType::Unsigned;
    if (str == "volatile")
        return KeywordType::Volatile;
    if (str == "default")
        return KeywordType::Default;
    if (str == "typedef")
        return KeywordType::Typedef;
    if (str == "double")
        return KeywordType::Double;
    if (str == "extern")
        return KeywordType::Extern;
    if (str == "return")
        return KeywordType::Return;
    if (str == "signed")
        return KeywordType::Signed;
    if (str == "sizeof")
        return KeywordType::Sizeof;
    if (str == "static")
        return KeywordType::Static;
    if (str == "struct")
        return KeywordType::Struct;
    if (str == "switch")
        return KeywordType::Switch;
    if (str == "break")
        return KeywordType::Break;
    if (str == "const")
        return KeywordType::Const;
    if (str == "float")
        return KeywordType::Float;
    if (str == "short")
        return KeywordType::Short;
    if (str == "while")
        return KeywordType::While;
    if (str == "union")
        return KeywordType::Union;
    if (str == "auto")
        return KeywordType::Auto;
    if (str == "case")
        return KeywordType::Case;
    if (str == "char")
        return KeywordType::Char;
    if (str == "else")
        return KeywordType::Else;
    if (str == "enum")
        return KeywordType::Enum;
    if (str == "goto")
        return KeywordType::Goto;
    if (str == "long")
        return KeywordType::Long;
    if (str == "void")
        return KeywordType::Void;
    if (str == "for")
        return KeywordType::For;
    if (str == "int")
        return KeywordType::Int;
    if (str == "do")
        return KeywordType::Do;
    if (str == "if")
        return KeywordType::If;
    return std::nullopt;
}

}  // namespace cless::syntax::token
