#pragma once

#include <string_view>
#include <stdexcept>
#include <cstdlib>

#include "../lexical_analyzer.hpp"

namespace compiler_parser::ll1_parser {
    class parser {
    public:
	parser(std::string_view input) : input_stream{input} {}

	int parse()
	{
	    lexeme lex;
	    
	    input_stream >> lex;
	    
	    return stmt(lex);
	}

    private:
	token_stream input_stream;

	int stmt(lexeme lex)
	{
	    int res = 0;

	    switch(lex.token) {
		case tokens::lp:
		case tokens::num:
		    res = expr(lex);
		    break;
		default:
		    throw std::invalid_argument(std::string("int ll1_parser::parser::stmt(lexeme lex) [lex.lex = ") + lex.lex + 
			    std::string("] invalid argument: lex.token could be tokens::num or tokens::lp"));
		    break;
	    }

	    return res;
	}

	int expr(lexeme lex)
	{
	    int res = 0;
	    lexeme look_ahead;

	    switch(lex.token) {
		case tokens::num:
		case tokens::lp:
		    res = term(lex);

		    input_stream >> look_ahead;

		    switch(look_ahead.token) {
			case tokens::plus:
			    input_stream >> look_ahead;
                            res += expr(look_ahead);
			    break;
			case tokens::rp:
                            input_stream << look_ahead;
			    break;
		    }
		    break;
		default:
		    throw std::invalid_argument(std::string("int ll1_parser::parser::expr(lexeme lex) [lex.lex = ") + lex.lex + 
			    std::string("] invalid argument: lex.token could be tokens::num or tokens::lp"));
		    break;
	    }

	    return res;
	}

	int term(lexeme lex)
	{
	    int res = 0;
	    lexeme look_ahead;

	    switch(lex.token) {
		case tokens::num:
		case tokens::lp:
		    res = fact(lex);

		    input_stream >> look_ahead;

		    switch(look_ahead.token) {
			case tokens::mul:
			    input_stream >> look_ahead;
                            res *= term(look_ahead);
			    break;
			case tokens::plus:
			case tokens::rp:
                            input_stream << look_ahead;
			    break;
		    }
		    break;
		default:
		    throw std::invalid_argument(std::string("int ll1_parser::parser::term(lexeme lex) [lex.lex = ") + lex.lex + 
			    std::string("] invalid argument: lex.token could be tokens::num or tokens::lp"));
		    break;
	    }

	    return res;
	}

	int fact(lexeme lex)
	{
	    int res = 0;
	    lexeme look_ahead;

	    switch(lex.token) {
		case tokens::num:
		    res = std::atoi(&lex.lex);
		    break;
		case tokens::lp:
		    input_stream >> look_ahead;
		    res = expr(look_ahead);
		    input_stream >> look_ahead;
		    if(look_ahead.token != tokens::rp)
			throw std::invalid_argument(std::string("int ll1_parser::parser::fact(lexeme lex) [lex.lex = ") + lex.lex + 
			    std::string("] invalid argument: no closing parenthese"));
		    break;
		dafault:
		    throw std::invalid_argument(std::string("int ll1_parser::parser::fact(lexeme lex) [lex.lex = ") + lex.lex + 
			    std::string("] invalid argument: lex.token could be tokens::num or tokens::lp"));
		    break;
	    }

	    return res;
	}
    };
}
