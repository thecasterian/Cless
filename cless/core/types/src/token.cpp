#include "cless/core/types/token.h"

#include "cless/core/types/exception.h"

namespace cless::core::types {

std::string toString(IntegerSuffix integer_suffix) {
    switch (integer_suffix) {
        case IntegerSuffix::None:
            return "";
        case IntegerSuffix::Unsigned:
            return "u";
        case IntegerSuffix::Long:
            return "l";
        case IntegerSuffix::UnsignedLong:
            return "ul";
        case IntegerSuffix::LongLong:
            return "ll";
        case IntegerSuffix::UnsignedLongLong:
            return "ull";
    }

    throw Exception("Unknown integer suffix");
}

std::optional<IntegerSuffix> integerSuffixFromStr(const std::string& str) {
    if (str == "")
        return IntegerSuffix::None;
    else if (str == "u" or str == "U")
        return IntegerSuffix::Unsigned;
    else if (str == "l" or str == "L")
        return IntegerSuffix::Long;
    else if (str == "ul" or str == "lu" or str == "UL" or str == "LU")
        return IntegerSuffix::UnsignedLong;
    else if (str == "ll" or str == "LL")
        return IntegerSuffix::LongLong;
    else if (
        str == "ull" or str == "llu" or str == "uLL" or str == "LLu" or str == "Ull" or str == "llU" or str == "ULL" or
        str == "LLU")
        return IntegerSuffix::UnsignedLongLong;
    else
        return std::nullopt;
}

std::string toString(FloatingSuffix floating_suffix) {
    switch (floating_suffix) {
        case FloatingSuffix::None:
            return "";
        case FloatingSuffix::Float:
            return "f";
        case FloatingSuffix::LongDouble:
            return "l";
    }

    throw Exception("Unknown floating suffix");
}

std::optional<FloatingSuffix> floatingSuffixFromStr(const std::string& str) {
    if (str == "")
        return FloatingSuffix::None;
    else if (str == "f" or str == "F")
        return FloatingSuffix::Float;
    else if (str == "l" or str == "L")
        return FloatingSuffix::LongDouble;
    else
        return std::nullopt;
}

std::string toString(EncodingPrefix encoding_prefix) {
    switch (encoding_prefix) {
        case EncodingPrefix::None:
            return "";
        case EncodingPrefix::UTF8:
            return "u8";
        case EncodingPrefix::WChar:
            return "L";
        case EncodingPrefix::Char16:
            return "u";
        case EncodingPrefix::Char32:
            return "U";
    }

    throw Exception("Unknown encoding prefix");
}

std::optional<EncodingPrefix> encodingPrefixFromStr(const std::string& str) {
    if (str == "")
        return EncodingPrefix::None;
    else if (str == "u8")
        return EncodingPrefix::UTF8;
    else if (str == "L")
        return EncodingPrefix::WChar;
    else if (str == "u")
        return EncodingPrefix::Char16;
    else if (str == "U")
        return EncodingPrefix::Char32;
    else
        return std::nullopt;
}

struct TokenToStringVisitor {
    std::string operator()(const Keyword& keyword) const {
        switch (keyword.type) {
            case KeywordType::Alignas:
                return "alignas";
            case KeywordType::Alignof:
                return "alignof";
            case KeywordType::Auto:
                return "auto";
            case KeywordType::Bool:
                return "bool";
            case KeywordType::Break:
                return "break";
            case KeywordType::Case:
                return "case";
            case KeywordType::Char:
                return "char";
            case KeywordType::Complex:
                return "complex";
            case KeywordType::Const:
                return "const";
            case KeywordType::Continue:
                return "continue";
            case KeywordType::Default:
                return "default";
            case KeywordType::Do:
                return "do";
            case KeywordType::Double:
                return "double";
            case KeywordType::Else:
                return "else";
            case KeywordType::Enum:
                return "enum";
            case KeywordType::False:
                return "false";
            case KeywordType::Float:
                return "float";
            case KeywordType::For:
                return "for";
            case KeywordType::Generic:
                return "generic";
            case KeywordType::If:
                return "if";
            case KeywordType::Imaginary:
                return "imaginary";
            case KeywordType::Inline:
                return "inline";
            case KeywordType::Int:
                return "int";
            case KeywordType::Long:
                return "long";
            case KeywordType::NullPtr:
                return "nullptr";
            case KeywordType::Restrict:
                return "restrict";
            case KeywordType::Return:
                return "return";
            case KeywordType::Short:
                return "short";
            case KeywordType::Signed:
                return "signed";
            case KeywordType::Sizeof:
                return "sizeof";
            case KeywordType::Static:
                return "static";
            case KeywordType::StaticAssert:
                return "static_assert";
            case KeywordType::Struct:
                return "struct";
            case KeywordType::Switch:
                return "switch";
            case KeywordType::True:
                return "true";
            case KeywordType::Typedef:
                return "typedef";
            case KeywordType::Typeof:
                return "typeof";
            case KeywordType::Union:
                return "union";
            case KeywordType::Unsigned:
                return "unsigned";
            case KeywordType::Void:
                return "void";
            case KeywordType::Volatile:
                return "volatile";
            case KeywordType::While:
                return "while";
        }

        throw Exception("Unknown keyword type");
    }

    std::string operator()(const Punctuation& punctuation) const {
        switch (punctuation.type) {
            case PunctuationType::OpenBracket:
                return "[";
            case PunctuationType::CloseBracket:
                return "]";
            case PunctuationType::OpenParenthesis:
                return "(";
            case PunctuationType::CloseParenthesis:
                return ")";
            case PunctuationType::OpenBrace:
                return "{";
            case PunctuationType::CloseBrace:
                return "}";
            case PunctuationType::Dot:
                return ".";
            case PunctuationType::Arrow:
                return "->";
            case PunctuationType::DoublePlus:
                return "++";
            case PunctuationType::DoubleMinus:
                return "--";
            case PunctuationType::Ampersand:
                return "&";
            case PunctuationType::Asterisk:
                return "*";
            case PunctuationType::Plus:
                return "+";
            case PunctuationType::Minus:
                return "-";
            case PunctuationType::Tilde:
                return "~";
            case PunctuationType::Exclamation:
                return "!";
            case PunctuationType::Slash:
                return "/";
            case PunctuationType::Percent:
                return "%";
            case PunctuationType::DoubleLessThan:
                return "<<";
            case PunctuationType::DoubleGreaterThan:
                return ">>";
            case PunctuationType::LessThan:
                return "<";
            case PunctuationType::GreaterThan:
                return ">";
            case PunctuationType::LessThanOrEqualTo:
                return "<=";
            case PunctuationType::GreaterThanOrEqualTo:
                return ">=";
            case PunctuationType::DoubleEqual:
                return "==";
            case PunctuationType::ExclamationEqual:
                return "!=";
            case PunctuationType::Caret:
                return "^";
            case PunctuationType::VerticalBar:
                return "|";
            case PunctuationType::DoubleAmpersand:
                return "&&";
            case PunctuationType::DoubleVerticalBar:
                return "||";
            case PunctuationType::Question:
                return "?";
            case PunctuationType::Colon:
                return ":";
            case PunctuationType::Semicolon:
                return ";";
            case PunctuationType::Ellipsis:
                return "...";
            case PunctuationType::Equal:
                return "=";
            case PunctuationType::AsteriskEqual:
                return "*=";
            case PunctuationType::SlashEqual:
                return "/=";
            case PunctuationType::PercentEqual:
                return "%=";
            case PunctuationType::PlusEqual:
                return "+=";
            case PunctuationType::MinusEqual:
                return "-=";
            case PunctuationType::DoubleLessThanEqual:
                return "<<=";
            case PunctuationType::DoubleGreaterThanEqual:
                return ">>=";
            case PunctuationType::AmpersandEqual:
                return "&=";
            case PunctuationType::CaretEqual:
                return "^=";
            case PunctuationType::VerticalBarEqual:
                return "|=";
            case PunctuationType::Comma:
                return ",";
        }

        throw Exception("Unknown punctuation type");
    }

    std::string operator()(const Identifier& identifier) const { return std::string(identifier.name); }

    std::string operator()(const IntegerConstant& integer_constant) const { return integer_constant.value; }

    std::string operator()(const FloatingConstant& floating_constant) const { return floating_constant.value; }

    std::string operator()(const CharacterConstant& character_constant) const { return character_constant.value; }

    std::string operator()(const StringLiteral& string_literal) const { return string_literal.value; }
};

std::string toString(const Token& token) {
    return std::visit(TokenToStringVisitor{}, token);
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << toString(token);
    return os;
}

}  // namespace cless::core::types
