#ifndef LILC_AST_HPP
#define LILC_AST_HPP

#include <ostream>
#include <list>
#include "symbols.hpp"

//Here is a suggestion for all the different kinds of AST nodes
// and what kinds
// of children they have. All of these kinds of AST nodes are
// subclasses of ASTNode.
// Indentation indicates further subclassing:
//
//     Subclass		Children
//     --------		------
//     ProgramNode	DeclListNode
//     DeclListNode	linked list of DeclNode
//     DeclNode
//       VarDeclNode	TypeNode, IdNode, int
//       FnDeclNode	TypeNode, IdNode, FormalsListNode, FnBodyNode
//       FormalDeclNode    TypeNode, IdNode
//       StructDeclNode    IdNode, DeclListNode
//
//     FormalsListNode     linked list of FormalDeclNode
//     FnBodyNode          DeclListNode, StmtListNode
//     StmtListNode        linked list of StmtNode
//     ExpListNode         linked list of ExpNode
//
//     TypeNode:
//       IntNode           -- none --
//       BoolNode          -- none --
//       VoidNode          -- none --
//       StructNode        IdNode
//
//     StmtNode:
//       AssignStmtNode      AssignNode
//       PostIncStmtNode     ExpNode
//       PostDecStmtNode     ExpNode
//       ReadStmtNode        ExpNode
//       WriteStmtNode       ExpNode
//       IfStmtNode          ExpNode, DeclListNode, StmtListNode
//       IfElseStmtNode      ExpNode, DeclListNode, StmtListNode,
//                                    DeclListNode, StmtListNode
//       WhileStmtNode       ExpNode, DeclListNode, StmtListNode
//       CallStmtNode        CallExpNode
//       ReturnStmtNode      ExpNode
//
//     ExpNode:
//       IntLitNode          -- none --
//       StrLitNode          -- none --
//       TrueNode            -- none --
//       FalseNode           -- none --
//       IdNode              -- none --
//       DotAccessNode       ExpNode, IdNode
//       AssignNode          ExpNode, ExpNode
//       CallExpNode         IdNode, ExpListNode
//       UnaryExpNode        ExpNode
//         UnaryMinusNode
//         NotNode
//       BinaryExpNode       ExpNode ExpNode
//         PlusNode
//         MinusNode
//         TimesNode
//         DivideNode
//         AndNode
//         OrNode
//         EqualsNode
//         NotEqualsNode
//         LessNode
//         GreaterNode
//         LessEqNode
//         GreaterEqNode
//
//
// Here are the different kinds of AST nodes again, organized according to
// whether they are leaves, internal nodes with linked lists of kids, or
// internal nodes with a fixed number of kids:
//
// (1) Leaf nodes:
//        IntNode,   BoolNode,  VoidNode,  IntLitNode,  StrLitNode,
//        TrueNode,  FalseNode, IdNode
//
// (2) Internal nodes with (possibly empty) linked lists of children:
//        DeclListNode, FormalsListNode, StmtListNode, ExpListNode
//
// (3) Internal nodes with fixed numbers of kids:
//        ProgramNode,     VarDeclNode,     FnDeclNode,     FormalDeclNode,
//        StructDeclNode,  FnBodyNode,      StructNode,     AssignStmtNode,
//        PostIncStmtNode, PostDecStmtNode, ReadStmtNode,   WriteStmtNode
//        IfStmtNode,      IfElseStmtNode,  WhileStmtNode,  CallStmtNode
//        ReturnStmtNode,  DotAccessNode,   CallExpNode,
//        UnaryExpNode,    BinaryExpNode,   UnaryMinusNode, NotNode,
//        PlusNode,        MinusNode,       TimesNode,      DivideNode,
//        AndNode,         OrNode,          EqualsNode,     NotEqualsNode,
//        LessNode,        GreaterNode,     LessEqNode,     GreaterEqNode
//
// **********************************************************************

// **********************************************************************
// ASTnode class (base class for all other kinds of nodes)
// **********************************************************************

namespace LILC{

class SymSymbol;
class DeclListNode;
class DeclNode;
class TypeNode;
class IdNode;

class ASTNode{
public:
	virtual void unparse(std::ostream& out, int indent) = 0;
	void doIndent(std::ostream& out, int indent){
		for (int k = 0 ; k < indent; k++){ out << " "; }
	}
};

class ProgramNode : public ASTNode{
public:
	ProgramNode(DeclListNode * L) : ASTNode(){
		myDeclList = L;
	}
	void unparse(std::ostream& out, int indent);
private:
	DeclListNode * myDeclList;

};

class DeclListNode : public ASTNode{
public:
	DeclListNode(std::list<DeclNode *> * decls) : ASTNode(){
		myDecls = *decls;
	}
	void unparse(std::ostream& out, int indent);
private:
	std::list<DeclNode *> myDecls;
};

class DeclNode : public ASTNode{
public:
	virtual void unparse(std::ostream& out, int indent) = 0;
};

class FormalDeclNode : public DeclNode{
public:
	FormalDeclNode(TypeNode * type, IdNode * id) : DeclNode(){
		myType = type;
		myId = id;
	}
	void unparse(std::ostream& out, int indent);
private:
	TypeNode * myType;
	IdNode * myId;
};

class FormalsListNode : public ASTNode{
public:
	FormalsListNode(std::list<FormalDeclNode *> * formals) : ASTNode(){
		myFormals = *formals;
	}
	void unparse(std::ostream& out, int indent);
private:
	std::list<FormalDeclNode *> myFormals;
};

class StmtNode : public ASTNode{
public:
	virtual void unparse(std::ostream& out, int indent) = 0;
};

class StmtListNode : public ASTNode{
public:
	StmtListNode(std::list<StmtNode *> * stmts) : ASTNode(){
		myStmts = *stmts;
	}
	void unparse(std::ostream& out, int indent);
private:
	std::list<StmtNode *> myStmts;
};

class ExpNode : public ASTNode{
public:
	ExpNode() : ASTNode(){
	}
	virtual void unparse(std::ostream& out, int indent) = 0;
};

class ExpListNode : public ASTNode{
public:
	ExpListNode(std::list<ExpNode *> * exps) : ASTNode(){
		myExps = *exps;
	}
	void unparse(std::ostream& out, int indent);
private:
	std::list<ExpNode *> myExps;
};

class IntLitNode : public ExpNode{
public:
	IntLitNode(int value) : ExpNode(){
		myVal = value;
	}
	void unparse(std::ostream& out, int indent);
private:
	int myVal;
};

class StrLitNode : public ExpNode{
public:
	StrLitNode(std::string * strVal) : ExpNode(){
		myStrVal = *strVal;
	}
	void unparse(std::ostream& out, int indent);
private:
	std::string myStrVal;
};

class TrueNode : public ExpNode{
public:
	TrueNode() : ExpNode(){}
	void unparse(std::ostream& out, int indent);
};

class FalseNode : public ExpNode{
public:
	FalseNode() : ExpNode(){}
	void unparse(std::ostream& out, int indent);
};

class IdNode : public ExpNode{
public:
	IdNode(IDToken * token) : ExpNode(){
		myStrVal = token->value();
	}
	void unparse(std::ostream& out, int indent);
private:
	std::string myStrVal;
};

class DotAccessNode : public ExpNode{
public:
	DotAccessNode(ExpNode * expression, IdNode* id) : ExpNode(){
		myExp = expression;
		myId = id;
	}
	void unparse(std::ostream& out, int indent);
private:
	ExpNode* myExp;
	IdNode* myId;
};

class AssignNode : public ExpNode{
public:
	AssignNode(ExpNode * expL, ExpNode* expR) : ExpNode(){
		myExpL = expL;
		myExpR = expR;
	}
	void unparse(std::ostream& out, int indent);
private:
	ExpNode* myExpL;
	ExpNode* myExpR;
};

class CallExpNode : public ExpNode{
public:
	CallExpNode(IdNode* id, ExpListNode * expList) : ExpNode(){
		myExpList = expList;
		myId = id;
	}
	void unparse(std::ostream& out, int indent);
private:
	ExpListNode* myExpList;
	IdNode* myId;
};

class UnaryExpNode : public ExpNode{
public:
	UnaryExpNode(ExpNode * expression) : ExpNode(){
		myExp = expression;
	}
	virtual void unparse(std::ostream& out, int indent) = 0;
protected:
	ExpNode* myExp;
};

class UnaryMinusNode : public UnaryExpNode{
public:
	UnaryMinusNode(ExpNode * expression) : UnaryExpNode(expression){}
	void unparse(std::ostream& out, int indent);
};

class NotNode : public UnaryExpNode{
public:
	NotNode(ExpNode * expression) : UnaryExpNode(expression){}
	void unparse(std::ostream& out, int indent);
};

class BinaryExpNode : public ExpNode{
public:
	BinaryExpNode(ExpNode * expL, ExpNode* expR) : ExpNode(){
		myExpL = expL;
		myExpR = expR;
	}
	virtual void unparse(std::ostream& out, int indent) = 0;
protected:
	ExpNode* myExpL;
	ExpNode* myExpR;
};

class PlusNode : public BinaryExpNode{
public:
	PlusNode(ExpNode * expL, ExpNode * expR) : BinaryExpNode(expL, expR){}
	void unparse(std::ostream& out, int indent);
};

class MinusNode : public BinaryExpNode{
public:
	MinusNode(ExpNode * expL, ExpNode * expR) : BinaryExpNode(expL, expR){}
	void unparse(std::ostream& out, int indent);
};

class TimesNode : public BinaryExpNode{
public:
	TimesNode(ExpNode * expL, ExpNode * expR) : BinaryExpNode(expL, expR){}
	void unparse(std::ostream& out, int indent);
};

class DivideNode : public BinaryExpNode{
public:
	DivideNode(ExpNode * expL, ExpNode * expR) : BinaryExpNode(expL, expR){}
	void unparse(std::ostream& out, int indent);
};

class AndNode : public BinaryExpNode{
public:
	AndNode(ExpNode * expL, ExpNode * expR) : BinaryExpNode(expL, expR){}
	void unparse(std::ostream& out, int indent);
};

class OrNode : public BinaryExpNode{
public:
	OrNode(ExpNode * expL, ExpNode * expR) : BinaryExpNode(expL, expR){}
	void unparse(std::ostream& out, int indent);
};

class EqualsNode : public BinaryExpNode{
public:
	EqualsNode(ExpNode * expL, ExpNode * expR) : BinaryExpNode(expL, expR){}
	void unparse(std::ostream& out, int indent);
};

class NotEqualsNode : public BinaryExpNode{
public:
	NotEqualsNode(ExpNode * expL, ExpNode * expR) : BinaryExpNode(expL, expR){}
	void unparse(std::ostream& out, int indent);
};

class LessNode : public BinaryExpNode{
public:
	LessNode(ExpNode * expL, ExpNode * expR) : BinaryExpNode(expL, expR){}
	void unparse(std::ostream& out, int indent);
};

class GreaterNode : public BinaryExpNode{
public:
	GreaterNode(ExpNode * expL, ExpNode * expR) : BinaryExpNode(expL, expR){}
	void unparse(std::ostream& out, int indent);
};

class LessEqNode : public BinaryExpNode{
public:
	LessEqNode(ExpNode * expL, ExpNode * expR) : BinaryExpNode(expL, expR){}
	void unparse(std::ostream& out, int indent);
};

class GreaterEqNode : public BinaryExpNode{
public:
	GreaterEqNode(ExpNode * expL, ExpNode * expR) : BinaryExpNode(expL, expR){}
	void unparse(std::ostream& out, int indent);
};

class VarDeclNode : public DeclNode{
public:
	VarDeclNode(TypeNode * type, IdNode * id, int size) : DeclNode(){
		myType = type;
		myId = id;
		mySize = size;
	}
	void unparse(std::ostream& out, int indent);
	static const int NOT_STRUCT = -1; //Use this value for mySize
					  // if this is not a struct type
private:
	TypeNode * myType;
	IdNode * myId;
	int mySize;
};

class FnBodyNode : public DeclNode{
public:
	FnBodyNode(DeclListNode * declList, StmtListNode * stmtList) : DeclNode(){
		myDeclList = declList;
		myStmtList = stmtList;
	}
	void unparse(std::ostream& out, int indent);
private:
	DeclListNode * myDeclList;
	StmtListNode * myStmtList;
};

class FnDeclNode : public DeclNode{
public:
	FnDeclNode(TypeNode * type, IdNode * id, FormalsListNode * formalsList, FnBodyNode * fnBody) : DeclNode(){
		myType = type;
		myId = id;
		myFormalsList = formalsList;
		myFnBody = fnBody;
	}
	void unparse(std::ostream& out, int indent);
private:
	TypeNode * myType;
	IdNode * myId;
	FormalsListNode * myFormalsList;
	FnBodyNode * myFnBody;
};

class StructDeclNode : public DeclNode{
public:
	StructDeclNode(DeclListNode * declList, IdNode * id) : DeclNode(){
		myDeclList = declList;
		myId = id;
	}
	void unparse(std::ostream& out, int indent);
private:
	DeclListNode * myDeclList;
	IdNode * myId;
};

class TypeNode : public ASTNode{
public:
	TypeNode() : ASTNode(){
	}
	virtual void unparse(std::ostream& out, int indent) = 0;
};

class IntNode : public TypeNode{
public:
	IntNode(): TypeNode(){
	}
	void unparse(std::ostream& out, int indent);
};

class BoolNode : public TypeNode{
public:
	BoolNode(): TypeNode(){
	}
	void unparse(std::ostream& out, int indent);
};

class VoidNode : public TypeNode{
public:
	VoidNode(): TypeNode(){
	}
	void unparse(std::ostream& out, int indent);
};

class AssignStmtNode : public StmtNode{
public:
	AssignStmtNode(AssignNode* assignNode): StmtNode(){
		myAssignNode = assignNode;
	}
	void unparse(std::ostream& out, int indent);
private:
	AssignNode* myAssignNode;
};

class PostIncStmtNode : public StmtNode{
public:
	PostIncStmtNode(ExpNode* exp): StmtNode(){
		myExp = exp;
	}
	void unparse(std::ostream& out, int indent);
private:
	ExpNode* myExp;
};

class PostDecStmtNode : public StmtNode{
public:
	PostDecStmtNode(ExpNode* exp): StmtNode(){
		myExp = exp;
	}
	void unparse(std::ostream& out, int indent);
private:
	ExpNode* myExp;
};

class ReadStmtNode : public StmtNode{
public:
	ReadStmtNode(ExpNode* exp): StmtNode(){
		myExp = exp;
	}
	void unparse(std::ostream& out, int indent);
private:
	ExpNode* myExp;
};

class WriteStmtNode : public StmtNode{
public:
	WriteStmtNode(ExpNode* exp): StmtNode(){
		myExp = exp;
	}
	void unparse(std::ostream& out, int indent);
private:
	ExpNode* myExp;
};

class IfStmtNode : public StmtNode{
public:
	IfStmtNode(ExpNode* exp, DeclListNode* declList, StmtListNode* stmtList): StmtNode(){
		myExp = exp;
		myDeclList = declList;
		myStmtList = stmtList;
	}
	void unparse(std::ostream& out, int indent);
private:
	ExpNode* myExp;
	DeclListNode* myDeclList;
	StmtListNode* myStmtList;
};

class IfElseStmtNode : public StmtNode{
public:
	IfElseStmtNode(ExpNode* exp, DeclListNode* declList, StmtListNode* stmtList, DeclListNode* declList2, StmtListNode* stmtList2): StmtNode(){
		myExp = exp;
		myDeclList = declList;
		myStmtList = stmtList;
		myDeclList2 = declList2;
		myStmtList2 = stmtList2;
	}
	void unparse(std::ostream& out, int indent);
private:
	ExpNode* myExp;
	DeclListNode* myDeclList;
	StmtListNode* myStmtList;
	DeclListNode* myDeclList2;
	StmtListNode* myStmtList2;
};

class WhileStmtNode : public StmtNode{
public:
	WhileStmtNode(ExpNode* exp, DeclListNode* declList, StmtListNode* stmtList): StmtNode(){
		myExp = exp;
		myDeclList = declList;
		myStmtList = stmtList;
	}
	void unparse(std::ostream& out, int indent);
private:
	ExpNode* myExp;
	DeclListNode* myDeclList;
	StmtListNode* myStmtList;
};

class CallStmtNode : public StmtNode{
public:
	CallStmtNode(ExpNode* call): StmtNode(){
		myCall = call;
	}
	void unparse(std::ostream& out, int indent);
private:
	ExpNode* myCall;
};

class ReturnStmtNode : public StmtNode{
public:
	ReturnStmtNode(ExpNode* exp): StmtNode(){
		myExp = exp;
	}
	void unparse(std::ostream& out, int indent);
private:
	ExpNode* myExp;
};

} //End namespace LIL' C

#endif
