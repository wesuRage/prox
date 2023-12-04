#include <vector>
#include <string>
#include <ostream>

#ifndef LEXER_H
#define LEXER_H
enum TokenType { // lista de tokens
    NUMBER,
    IDENTIFIER,
    RPAREN,
    LPAREN,
    RBRACE,
    LBRACE,
    RBRACKET,
    LBRACKET,
    EQUALS,
    ARROW,
    COLON,
    SEMICOLON,
    COMMA,
    DOT,
    GT,
    LT,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    MODULUS,
    _EOF
};
struct Token {
        TokenType type;
        std::string value;

        friend std::ostream& operator<<(std::ostream& os, const Token& obj) {
                os << " type: " << obj.type << ", value: \"" << obj.value << "\" " ;
                return os;
    }
};
#endif

std::vector<Token> tokenize(std::string sourceCode);
