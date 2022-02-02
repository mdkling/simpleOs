// lex.re
#include "../localTypes.h"
#include "../gram.h"
/*!re2c                              // start of re2c block
	
	scm = "//" [^\x00\n]*;
	wsp = [ \t\r]; // removed \v
	// integer literals
	dec = [0-9]+;
	hex = "0x" [0-9A-F]+; // a-f removed
	string_lit = ["] ([^"\x00] | ([\\] ["]))* ["];
	//string_lit_chain = string_lit ([ \n\t\r]* string_lit)+;
	//string_lit_chain = ([^"\n] | ([\\] ["]))* ("\n" | ["]);
	string_lit_chain = ([^'\n] | ([\\] [']))* "\n";
	string_lit_end = ([^'\n] | ([\\] [']))* ['];
	mangled_string_lit = ['] ([^'\x00\x03] | ([\\] [']))* "\x00";
	char_lit = [`] ([^`\x03] | ([\\] [`]))* [`];
	integer = (dec | hex);
	wordOperators = [@#$^~;:!?];
	ident = [a-zA-Z_] [a-zA-Z_0-9?!-]*;
	word = [a-zA-Z_] [a-zA-Z0-9?!-]*;
	word_definition = word "{";
	var_declaration = word "$";
	var_assign = word "=";
	var_decl_assign = word "$=";
	const_declaration = word ":=";
	word_increment = word "++";
	function_call_addr = "@" word ;
	function_definition = word ":";

	
*/                                   // end of re2c block

#define COMMENT_TOKEN -2

/*e*/
u8* lex(u8 *sourceCode, TokenInfo *t)/*p;*/
{
	u8 *YYCURSOR = sourceCode;
	u8 *YYMARKER;
	u8 *start;


	loop:
	start = YYCURSOR;

	/*!re2c                            // start of re2c block **/
	re2c:define:YYCTYPE = "u8";
	re2c:yyfill:enable  = 0;

	* {
		t->tokenType = 0;
		io_printi(t->lineNumber);
		io_prints(" :lexical error\n");
		return 0;
	}
	[\x00] {
		t->tokenType = 0;
		return YYCURSOR - 1;
	}
	
	wsp { goto loop; }
	
	scm {
		t->tokenType = COMMENT_TOKEN;
		t->string = start;
		t->length = YYCURSOR - start;
		return YYCURSOR;
	}
	
	"\n" {
		t->lineNumber++;
		goto loop;
	}
	
	";" {
		t->tokenType = SEMI;
		return YYCURSOR;
	}
	
	integer {
		t->tokenType = INTEGER;
		t->length    = s2i(start);
		return YYCURSOR;
	}
	
	string_lit {
		t->tokenType = STRING_LIT;
		start++;
		t->string = start;
		t->length = YYCURSOR - start - 1;
		return YYCURSOR;
	}
	
	*/                                  // end of re2c block
}