#include "cless/syntax/token/punctuation.h"

#include "cless/core/types/exception.h"

namespace cless::syntax::token {

std::ostream &operator<<(std::ostream &os, PunctuationType type) {
    switch (type) {
        case PunctuationType::DoubleLessThanEqual:
            return os << "<<=", os;
        case PunctuationType::DoubleGreaterThanEqual:
            return os << ">>=", os;
        case PunctuationType::Ellipsis:
            return os << "...", os;
        case PunctuationType::Arrow:
            return os << "->", os;
        case PunctuationType::DoublePlus:
            return os << "++", os;
        case PunctuationType::DoubleMinus:
            return os << "--", os;
        case PunctuationType::DoubleLessThan:
            return os << "<<", os;
        case PunctuationType::DoubleGreaterThan:
            return os << ">>", os;
        case PunctuationType::LessThanEqual:
            return os << "<=", os;
        case PunctuationType::GreaterThanEqual:
            return os << ">=", os;
        case PunctuationType::DoubleEqual:
            return os << "==", os;
        case PunctuationType::ExclamationEqual:
            return os << "!=", os;
        case PunctuationType::DoubleAmpersand:
            return os << "&&", os;
        case PunctuationType::DoubleVerticalBar:
            return os << "||", os;
        case PunctuationType::AsteriskEqual:
            return os << "*=", os;
        case PunctuationType::SlashEqual:
            return os << "/=", os;
        case PunctuationType::PercentEqual:
            return os << "%=", os;
        case PunctuationType::PlusEqual:
            return os << "+=", os;
        case PunctuationType::MinusEqual:
            return os << "-=", os;
        case PunctuationType::AmpersandEqual:
            return os << "&=", os;
        case PunctuationType::CaretEqual:
            return os << "^=", os;
        case PunctuationType::VerticalBarEqual:
            return os << "|=", os;
        case PunctuationType::DoubleHash:
            return os << "##", os;
        case PunctuationType::OpenBracket:
            return os << "[", os;
        case PunctuationType::CloseBracket:
            return os << "]", os;
        case PunctuationType::OpenParenthesis:
            return os << "(", os;
        case PunctuationType::CloseParenthesis:
            return os << ")", os;
        case PunctuationType::OpenBrace:
            return os << "{", os;
        case PunctuationType::CloseBrace:
            return os << "}", os;
        case PunctuationType::Dot:
            return os << ".", os;
        case PunctuationType::Ampersand:
            return os << "&", os;
        case PunctuationType::Asterisk:
            return os << "*", os;
        case PunctuationType::Plus:
            return os << "+", os;
        case PunctuationType::Minus:
            return os << "-", os;
        case PunctuationType::Tilde:
            return os << "~", os;
        case PunctuationType::Exclamation:
            return os << "!", os;
        case PunctuationType::Slash:
            return os << "/", os;
        case PunctuationType::Percent:
            return os << "%", os;
        case PunctuationType::LessThan:
            return os << "<", os;
        case PunctuationType::GreaterThan:
            return os << ">", os;
        case PunctuationType::Caret:
            return os << "^", os;
        case PunctuationType::VerticalBar:
            return os << "|", os;
        case PunctuationType::Question:
            return os << "?", os;
        case PunctuationType::Colon:
            return os << ":", os;
        case PunctuationType::Semicolon:
            return os << ";", os;
        case PunctuationType::Equal:
            return os << "=", os;
        case PunctuationType::Comma:
            return os << ",", os;
        case PunctuationType::Hash:
            return os << "#", os;
    }
    throw core::types::Exception("Unknown punctuation type");
}

std::optional<PunctuationType> punctuationTypeFromStr(const std::string &str) {
    if (str == "<<=")
        return PunctuationType::DoubleLessThanEqual;
    if (str == ">>=")
        return PunctuationType::DoubleGreaterThanEqual;
    if (str == "...")
        return PunctuationType::Ellipsis;
    if (str == "->")
        return PunctuationType::Arrow;
    if (str == "++")
        return PunctuationType::DoublePlus;
    if (str == "--")
        return PunctuationType::DoubleMinus;
    if (str == "<<")
        return PunctuationType::DoubleLessThan;
    if (str == ">>")
        return PunctuationType::DoubleGreaterThan;
    if (str == "<=")
        return PunctuationType::LessThanEqual;
    if (str == ">=")
        return PunctuationType::GreaterThanEqual;
    if (str == "==")
        return PunctuationType::DoubleEqual;
    if (str == "!=")
        return PunctuationType::ExclamationEqual;
    if (str == "&&")
        return PunctuationType::DoubleAmpersand;
    if (str == "||")
        return PunctuationType::DoubleVerticalBar;
    if (str == "*=")
        return PunctuationType::AsteriskEqual;
    if (str == "/=")
        return PunctuationType::SlashEqual;
    if (str == "%=")
        return PunctuationType::PercentEqual;
    if (str == "+=")
        return PunctuationType::PlusEqual;
    if (str == "-=")
        return PunctuationType::MinusEqual;
    if (str == "&=")
        return PunctuationType::AmpersandEqual;
    if (str == "^=")
        return PunctuationType::CaretEqual;
    if (str == "|=")
        return PunctuationType::VerticalBarEqual;
    if (str == "##")
        return PunctuationType::DoubleHash;
    if (str == "[")
        return PunctuationType::OpenBracket;
    if (str == "]")
        return PunctuationType::CloseBracket;
    if (str == "(")
        return PunctuationType::OpenParenthesis;
    if (str == ")")
        return PunctuationType::CloseParenthesis;
    if (str == "{")
        return PunctuationType::OpenBrace;
    if (str == "}")
        return PunctuationType::CloseBrace;
    if (str == ".")
        return PunctuationType::Dot;
    if (str == "&")
        return PunctuationType::Ampersand;
    if (str == "*")
        return PunctuationType::Asterisk;
    if (str == "+")
        return PunctuationType::Plus;
    if (str == "-")
        return PunctuationType::Minus;
    if (str == "~")
        return PunctuationType::Tilde;
    if (str == "!")
        return PunctuationType::Exclamation;
    if (str == "/")
        return PunctuationType::Slash;
    if (str == "%")
        return PunctuationType::Percent;
    if (str == "<")
        return PunctuationType::LessThan;
    if (str == ">")
        return PunctuationType::GreaterThan;
    if (str == "^")
        return PunctuationType::Caret;
    if (str == "|")
        return PunctuationType::VerticalBar;
    if (str == "?")
        return PunctuationType::Question;
    if (str == ":")
        return PunctuationType::Colon;
    if (str == ";")
        return PunctuationType::Semicolon;
    if (str == "=")
        return PunctuationType::Equal;
    if (str == ",")
        return PunctuationType::Comma;
    if (str == "#")
        return PunctuationType::Hash;
    return std::nullopt;
}

}  // namespace cless::syntax::token
