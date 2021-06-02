#pragma once

#include <string_view>
#include <stdexcept>

namespace compiler_parser {
    enum class tokens {
	eoi,
	num,
	plus,
	mul,
	lp,
	rp,
	unkown
    };

    struct lexeme {
	lexeme(tokens token, char lex) : token{token}, lex{lex} {}
	lexeme() : token{tokens::unkown}, lex{0} {}
	tokens token;
	char lex;
    };

    class token_stream {
    public:
	token_stream(std::string_view input) : input{input}, index{0} {}

	token_stream& operator>>(lexeme& lex)
	{
	    lex = lexeme{};
	    lex.token = analyze();

	    lex.lex = input[index];
	    if(lex.token != tokens::eoi)
		++index;

	    return *this;
	}

	token_stream& operator<<(lexeme lex)
	{
            if(lex.lex == input[index - 1]) {
		--index;
	    } else {
		throw std::invalid_argument(std::string("token_stream::operator<<(lexeme& lex) [lex.lex = ") + lex.lex +
			std::string("] invalid argument: lex must be last read character ") + input[index]);
	    }

	    return *this;
	}

    private:
        size_t index;
	std::string_view input;

	tokens analyze()
	{
	    switch(input[index]) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		    return tokens::num;
		case '+':
		    return tokens::plus;
		case '*':
		    return tokens::mul;
		case '(':
		    return tokens::lp;
		case ')':
		    return tokens::rp;
		case '\0':
		    return tokens::eoi;
		case ' ':
		    ++index;
		    return analyze();
		default:
		    throw std::invalid_argument(std::string("token_stream::token_stream(std::string_view input) Invalid argument: ") + input[index]);
	    }
	}
    };
}
