#include "cless/core/types/token.h"

namespace cless::core::types {

struct TokenToStringVisitor {
    std::string operator()(const token::keyword::Auto&) const { return "auto"; }
    std::string operator()(const token::keyword::Break&) const { return "break"; }
    std::string operator()(const token::keyword::Bool&) const { return "bool"; }
    std::string operator()(const token::keyword::Case&) const { return "case"; }
    std::string operator()(const token::keyword::Char&) const { return "char"; }
    std::string operator()(const token::keyword::Complex&) const { return "complex"; }
    std::string operator()(const token::keyword::Const&) const { return "const"; }
    std::string operator()(const token::keyword::Continue&) const { return "continue"; }
    std::string operator()(const token::keyword::Default&) const { return "default"; }
    std::string operator()(const token::keyword::Do&) const { return "do"; }
    std::string operator()(const token::keyword::Double&) const { return "double"; }
    std::string operator()(const token::keyword::Else&) const { return "else"; }
    std::string operator()(const token::keyword::Enum&) const { return "enum"; }
    std::string operator()(const token::keyword::Extern&) const { return "extern"; }
    std::string operator()(const token::keyword::Float&) const { return "float"; }
    std::string operator()(const token::keyword::For&) const { return "for"; }
    std::string operator()(const token::keyword::Generic&) const { return "generic"; }
    std::string operator()(const token::keyword::Goto&) const { return "goto"; }
    std::string operator()(const token::keyword::If&) const { return "if"; }
    std::string operator()(const token::keyword::Imaginary&) const { return "imaginary"; }
    std::string operator()(const token::keyword::Inline&) const { return "inline"; }
    std::string operator()(const token::keyword::Int&) const { return "int"; }
    std::string operator()(const token::keyword::Long&) const { return "long"; }
    std::string operator()(const token::keyword::Register&) const { return "register"; }
    std::string operator()(const token::keyword::Restrict&) const { return "restrict"; }
    std::string operator()(const token::keyword::Return&) const { return "return"; }
    std::string operator()(const token::keyword::Short&) const { return "short"; }
    std::string operator()(const token::keyword::Signed&) const { return "signed"; }
    std::string operator()(const token::keyword::Sizeof&) const { return "sizeof"; }
    std::string operator()(const token::keyword::Static&) const { return "static"; }
    std::string operator()(const token::keyword::StaticAssert&) const { return "static_assert"; }
    std::string operator()(const token::keyword::Struct&) const { return "struct"; }
    std::string operator()(const token::keyword::Switch&) const { return "switch"; }
    std::string operator()(const token::keyword::Typedef&) const { return "typedef"; }
    std::string operator()(const token::keyword::Union&) const { return "union"; }
    std::string operator()(const token::keyword::Unsigned&) const { return "unsigned"; }
    std::string operator()(const token::keyword::Void&) const { return "void"; }
    std::string operator()(const token::keyword::Volatile&) const { return "volatile"; }
    std::string operator()(const token::keyword::While&) const { return "while"; }
    std::string operator()(const token::punct::OpenBracket&) const { return "["; }
    std::string operator()(const token::punct::CloseBracket&) const { return "]"; }
    std::string operator()(const token::punct::OpenParenthesis&) const { return "("; }
    std::string operator()(const token::punct::CloseParenthesis&) const { return ")"; }
    std::string operator()(const token::punct::OpenBrace&) const { return "{"; }
    std::string operator()(const token::punct::CloseBrace&) const { return "}"; }
    std::string operator()(const token::punct::Dot&) const { return "."; }
    std::string operator()(const token::punct::Arrow&) const { return "->"; }
    std::string operator()(const token::punct::DoublePlus&) const { return "++"; }
    std::string operator()(const token::punct::DoubleMinus&) const { return "--"; }
    std::string operator()(const token::punct::Ampersand&) const { return "&"; }
    std::string operator()(const token::punct::Asterisk&) const { return "*"; }
    std::string operator()(const token::punct::Plus&) const { return "+"; }
    std::string operator()(const token::punct::Minus&) const { return "-"; }
    std::string operator()(const token::punct::Tilde&) const { return "~"; }
    std::string operator()(const token::punct::Exclamation&) const { return "!"; }
    std::string operator()(const token::punct::Slash&) const { return "/"; }
    std::string operator()(const token::punct::Percent&) const { return "%"; }
    std::string operator()(const token::punct::DoubleLessThan&) const { return "<<"; }
    std::string operator()(const token::punct::DoubleGreaterThan&) const { return ">>"; }
    std::string operator()(const token::punct::LessThan&) const { return "<"; }
    std::string operator()(const token::punct::GreaterThan&) const { return ">"; }
    std::string operator()(const token::punct::LessThanOrEqualTo&) const { return "<="; }
    std::string operator()(const token::punct::GreaterThanOrEqualTo&) const { return ">="; }
    std::string operator()(const token::punct::DoubleEqual&) const { return "=="; }
    std::string operator()(const token::punct::ExclamationEqual&) const { return "!="; }
    std::string operator()(const token::punct::Caret&) const { return "^"; }
    std::string operator()(const token::punct::VerticalBar&) const { return "|"; }
    std::string operator()(const token::punct::DoubleAmpersand&) const { return "&&"; }
    std::string operator()(const token::punct::DoubleVerticalBar&) const { return "||"; }
    std::string operator()(const token::punct::Question&) const { return "?"; }
    std::string operator()(const token::punct::Colon&) const { return ":"; }
    std::string operator()(const token::punct::Semicolon&) const { return ";"; }
    std::string operator()(const token::punct::Ellipsis&) const { return "..."; }
    std::string operator()(const token::punct::Equal&) const { return "="; }
    std::string operator()(const token::punct::AsteriskEqual&) const { return "*="; }
    std::string operator()(const token::punct::SlashEqual&) const { return "/="; }
    std::string operator()(const token::punct::PercentEqual&) const { return "%="; }
    std::string operator()(const token::punct::PlusEqual&) const { return "+="; }
    std::string operator()(const token::punct::MinusEqual&) const { return "-="; }
    std::string operator()(const token::punct::DoubleLessThanEqual&) const { return "<<="; }
    std::string operator()(const token::punct::DoubleGreaterThanEqual&) const { return ">>="; }
    std::string operator()(const token::punct::AmpersandEqual&) const { return "&="; }
    std::string operator()(const token::punct::CaretEqual&) const { return "^="; }
    std::string operator()(const token::punct::VerticalBarEqual&) const { return "|="; }
    std::string operator()(const token::punct::Comma&) const { return ","; }
    std::string operator()(const token::Identifier& identifier) const { return identifier.name; }
    std::string operator()(const token::IntegerConstant& integer_constant) const { return integer_constant.value; }
    std::string operator()(const token::FloatingConstant& floating_constant) const { return floating_constant.value; }
    std::string operator()(const token::CharacterConstant& character_constant) const {
        return character_constant.value;
    }
    std::string operator()(const token::StringLiteral& string_literal) const { return string_literal.value; }
};

std::string to_string(const Token& token) {
    return std::visit(TokenToStringVisitor{}, token);
}

}  // namespace cless::core::types
