#include "cless/syntax/token/token.h"

#include "cless/core/types/exception.h"

namespace cless::syntax::token {

std::ostream &operator<<(std::ostream &os, const Token &token) {
    std::visit([&os](const auto &t) { os << t; }, token);
    return os;
}

std::ostream &operator<<(std::ostream &os, const PreprocessingToken &pp_token) {
    std::visit([&os](const auto &t) { os << t; }, pp_token);
    return os;
}

static Token buildKeyword(
    KeywordType type,
    std::string file,
    std::size_t line_start,
    std::size_t line_end,
    std::size_t col_start,
    std::size_t col_end) {
    switch (type) {
        case KeywordType::Continue:
            return Continue(file, line_start, line_end, col_start, col_end);
        case KeywordType::Register:
            return Register(file, line_start, line_end, col_start, col_end);
        case KeywordType::Unsigned:
            return Unsigned(file, line_start, line_end, col_start, col_end);
        case KeywordType::Volatile:
            return Volatile(file, line_start, line_end, col_start, col_end);
        case KeywordType::Default:
            return Default(file, line_start, line_end, col_start, col_end);
        case KeywordType::Typedef:
            return Typedef(file, line_start, line_end, col_start, col_end);
        case KeywordType::Double:
            return Double(file, line_start, line_end, col_start, col_end);
        case KeywordType::Extern:
            return Extern(file, line_start, line_end, col_start, col_end);
        case KeywordType::Return:
            return Return(file, line_start, line_end, col_start, col_end);
        case KeywordType::Signed:
            return Signed(file, line_start, line_end, col_start, col_end);
        case KeywordType::Sizeof:
            return Sizeof(file, line_start, line_end, col_start, col_end);
        case KeywordType::Static:
            return Static(file, line_start, line_end, col_start, col_end);
        case KeywordType::Struct:
            return Struct(file, line_start, line_end, col_start, col_end);
        case KeywordType::Switch:
            return Switch(file, line_start, line_end, col_start, col_end);
        case KeywordType::Break:
            return Break(file, line_start, line_end, col_start, col_end);
        case KeywordType::Const:
            return Const(file, line_start, line_end, col_start, col_end);
        case KeywordType::Float:
            return Float(file, line_start, line_end, col_start, col_end);
        case KeywordType::Short:
            return Short(file, line_start, line_end, col_start, col_end);
        case KeywordType::While:
            return While(file, line_start, line_end, col_start, col_end);
        case KeywordType::Union:
            return Union(file, line_start, line_end, col_start, col_end);
        case KeywordType::Auto:
            return Auto(file, line_start, line_end, col_start, col_end);
        case KeywordType::Case:
            return Case(file, line_start, line_end, col_start, col_end);
        case KeywordType::Char:
            return Char(file, line_start, line_end, col_start, col_end);
        case KeywordType::Else:
            return Else(file, line_start, line_end, col_start, col_end);
        case KeywordType::Enum:
            return Enum(file, line_start, line_end, col_start, col_end);
        case KeywordType::Goto:
            return Goto(file, line_start, line_end, col_start, col_end);
        case KeywordType::Long:
            return Long(file, line_start, line_end, col_start, col_end);
        case KeywordType::Void:
            return Void(file, line_start, line_end, col_start, col_end);
        case KeywordType::For:
            return For(file, line_start, line_end, col_start, col_end);
        case KeywordType::Int:
            return Int(file, line_start, line_end, col_start, col_end);
        case KeywordType::Do:
            return Do(file, line_start, line_end, col_start, col_end);
        case KeywordType::If:
            return If(file, line_start, line_end, col_start, col_end);
    }
    throw core::types::Exception("Unknown keyword type");
}

struct PpTokenToTokenVisitor {
    Token operator()(const HeaderName &) const { throw core::types::Exception("HeaderName is not a valid token"); }

    template <typename T>
    Token operator()(const Punctuation<T> &punct) const {
        return static_cast<const T &>(punct);
    }

    Token operator()(const Identifier &ident) const {
        if (auto type = keywordTypeFromStr(ident.name); type.has_value())
            return buildKeyword(
                type.value(), ident.file, ident.line_start, ident.line_end, ident.col_start, ident.col_end);
        return ident;
    }

    template <typename T>
    Token operator()(const Constant<T> &constant) const {
        return static_cast<const T &>(constant);
    }

    Token operator()(const StringLiteral &str_lit) const { return str_lit; }
};

Token toToken(const PreprocessingToken &pp_token) {
    return std::visit(PpTokenToTokenVisitor{}, pp_token);
}

}  // namespace cless::syntax::token
