%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace {LILC}
%define parser_class_name {LilC_Parser}
%output "lilc_parser.cc"
%token-table

%code requires{
   #include <list>
   #include "symbols.hpp"
   #include "ast.hpp"
   namespace LILC {
      class LilC_Compiler;
      class LilC_Scanner;
   }

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { LilC_Scanner  &scanner  }
%parse-param { LilC_Compiler &compiler }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   /* include for interoperation between scanner/parser */
   #include "lilc_compiler.hpp"

#undef yylex
#define yylex scanner.yylex
}

/*%define api.value.type variant*/
%union {
	int intVal;
	std::string * strVal;
	LILC::SynSymbol * symbolValue;
	LILC::IDToken * idTokenValue;
	LILC::ASTNode * astNode;
	LILC::ProgramNode * programNode;
	std::list<DeclNode *> * declList;
	LILC::DeclNode * declNode;
	LILC::VarDeclNode * varDeclNode;
  LILC::FnDeclNode * fnDeclNode;
	LILC::StructDeclNode * structDeclNode;
	LILC::TypeNode * typeNode;
	LILC::IdNode * idNode;
  std::list<StmtNode*> * stmtListNode;
  LILC::StmtNode * stmtNode;
  std::list<FormalDeclNode *> * formalsListNode;
  LILC::FnBodyNode * fnBodyNode;
  LILC::ExpNode * expNode;
  std::list<ExpNode *> * expNodeList;
	/*LILC::Token * token;*/
}

%define parse.assert

%token               END    0     "end of file"
%token               NEWLINE "newline"
%token               CHAR
%token               BOOL
%token               INT
%token               VOID
%token               TRUE
%token               FALSE
%token               STRUCT
%token               INPUT
%token               OUTPUT
%token               IF
%token               ELSE
%token               WHILE
%token               RETURN
%token <idTokenValue> ID
%token <intVal>      INTLITERAL
%token <strVal>      STRINGLITERAL
%token               LCURLY
%token               RCURLY
%token               LPAREN
%token               RPAREN
%token               SEMICOLON
%token               COMMA
%token               DOT
%token               WRITE
%token               READ
%token               PLUSPLUS
%token               MINUSMINUS
%token               PLUS
%token               MINUS
%token               TIMES
%token               DIVIDE
%token               NOT
%token               AND
%token               OR
%token               EQUALS
%token               NOTEQUALS
%token               LESS
%token               GREATER
%token               LESSEQ
%token               GREATEREQ
%token               ASSIGN

/* Nonterminals
*  NOTE: You will need to add more nonterminals
*  to this list as you add productions to the grammar
*  below.
*/
%type <programNode> program
%type <declList> declList
%type <declNode> decl
%type <varDeclNode> varDecl
%type <declList> structBody
%type <structDeclNode> structDecl
%type <fnDeclNode> fnDecl
%type <fnBodyNode> fnBody
%type <formalsListNode> formals
%type <declList> varDeclList
%type <stmtListNode> stmtList
%type <stmtNode> stmt
%type <typeNode> type
%type <idNode> id
%type <expNode> assignExp
%type <expNode> exp
%type <expNode> term
%type <expNode> fncall
%type <expNodeList> actualList
%type <expNode> loc


/* NOTE: Make sure to add precedence and associativity
 * declarations
*/

%%

program : declList {
		   //$$ = new ProgramNode(new DeclListNode($1));
		   $$ = new ProgramNode(new DeclListNode($1));
		   compiler.setASTRoot($$);
		   }
  	;

declList : declList decl {
			 $1->push_back($2);
			 $$ = $1;
			 }
	| /* epsilon */ {
			$$ = new std::list<DeclNode *>();
			}
	;

decl : varDecl { $$ = $1; }
          | fnDecl { }
          | structDecl { $$ = $1; }
;

varDeclList : varDeclList varDecl {
				$1->push_back($2);
				$$=$1;
				}
	| /* epsilon */ { $$ = new std::list<DeclNode *>(); }
;

varDecl : type id SEMICOLON {
		$$ = new VarDeclNode($1, $2, VarDeclNode::NOT_STRUCT);
			    }
;

fnDecl : type id formals fnBody { $$ = new FnDeclNode($1, $2, new FormalsListNode($3), $4); } ;
formals : LPAREN RPAREN { $$ = new std::list<FormalDeclNode *>(); } ;
structDecl : STRUCT id LCURLY structBody RCURLY SEMICOLON {
    $$ = new StructDeclNode(new DeclListNode($4), $2);
          }
;

structBody : structBody varDecl {
    $1->push_back($2);
    $$ = $1;
 }
                | varDecl {
    std::list<DeclNode*> list;
    list.push_back($1);
    $$ = &list;
                }
;

fnBody : LCURLY varDeclList stmtList RCURLY { $$ = new FnBodyNode(new DeclListNode($2), new StmtListNode($3)); } ;
stmtList : stmtList stmt {
    $1->push_back($2);
    $$ = $1;
}
  | /* epsilon */ { $$ = new std::list<StmtNode *>(); }
;

stmt : assignExp SEMICOLON {} ;

assignExp : loc ASSIGN exp { $$ = new AssignNode($1, $3);} ;

exp : assignExp { $$ = $1; }
  | exp PLUS exp { $$ = new PlusNode($1, $3); }
  | exp MINUS exp { $$ = new MinusNode($1, $3); }
  | exp TIMES exp { $$ = new TimesNode($1, $3); }
  | exp DIVIDE exp { $$ = new DivideNode($1, $3); }
  | NOT exp { $$ = new NotNode($2); }
  | exp AND exp { $$ = new AndNode($1, $3); }
  | exp OR exp { $$ = new OrNode($1, $3); }
  | exp EQUALS exp { $$ = new EqualsNode($1, $3); }
  | exp NOTEQUALS exp { $$ = new NotEqualsNode($1, $3); }
  | exp LESS exp { $$ = new LessNode($1, $3); }
  | exp GREATER exp { $$ = new GreaterNode($1, $3); }
  | exp LESSEQ exp { $$ = new LessEqNode($1, $3); }
  | exp GREATEREQ exp { $$ = new GreaterEqNode($1, $3); }
  | MINUS term { $$ = new UnaryMinusNode($2); }
  | term { $$ = $1; }
;

term : loc { $$ = $1; }
  | INTLITERAL { $$ = new IntLitNode($1); }
  | STRINGLITERAL { $$ = new StrLitNode($1); }
  | TRUE { $$ = new TrueNode(); }
  | FALSE { $$ = new FalseNode(); }
  | LPAREN exp RPAREN { $$ = $2; }
  | fncall { $$ = $1; }
;

fncall : id LPAREN RPAREN { $$ = new CallExpNode($1, new ExpListNode(new std::list<ExpNode *>())); }
  | id LPAREN actualList RPAREN { $$ = new CallExpNode($1, new ExpListNode($3)); }
;

actualList : exp { $$ = (new std::list<StmtNode *>())->push_front($1); }
  | actualList COMMA exp { $1->push_front($3); $$ = $1; }
;

type : INT { $$ = new IntNode(); }
  | BOOL { $$ = new BoolNode(); }
  | VOID { $$ = new VoidNode(); }
;

loc : id { $$ = $1; }
  | loc DOT id { $$ = new DotAccessNode($1, $3); }
;

id : ID { $$ = new IdNode($1); } ;
%%
void
LILC::LilC_Parser::error(const std::string &err_message )
{
   std::cerr << "Error: " << err_message << "\n";
}
