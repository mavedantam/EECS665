#include "ast.hpp"

namespace LILC{

void ProgramNode::unparse(std::ostream& out, int indent){
	myDeclList->unparse(out, indent);
}

void DeclListNode::unparse(std::ostream& out, int indent){
	for (std::list<DeclNode *>::iterator it=myDecls.begin();
		it != myDecls.end(); ++it){
	    DeclNode * elt = *it;
	    elt->unparse(out, indent);
	}
}

void VarDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myType->unparse(out, 0);
	out << " ";
	myId->unparse(out, 0);
	out << "\n";
}

void StmtListNode::unparse(std::ostream& out, int indent){
	for (std::list<StmtNode *>::iterator it=myStmts.begin();
		it != myStmts.end(); ++it){
	    StmtNode * elt = *it;
	    elt->unparse(out, indent);
	}
}

void ExpListNode::unparse(std::ostream& out, int indent){
	for (std::list<ExpNode *>::iterator it=myExps.begin();
		it != myExps.end(); ++it){
	    ExpNode * elt = *it;
	    elt->unparse(out, indent);
	}
}

void FnDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myType->unparse(out, 0);
	out << " ";
	myId->unparse(out, 0);
	out << " ";
	myFormalsList->unparse(out, 0);
	out << " ";
	myFnBody->unparse(out, 0);
	out << "\n";
}

void FormalsListNode::unparse(std::ostream& out, int indent){
	for (std::list<FormalDeclNode *>::iterator it=myFormals.begin();
		it != myFormals.end(); ++it){
	    FormalDeclNode * elt = *it;
	    elt->unparse(out, indent);
	}
}

void FormalDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myType->unparse(out, 0);
	out << " ";
	myId->unparse(out, 0);
	out << "\n";
}

void FnBodyNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myDeclList->unparse(out, 0);
	out << " ";
	myStmtList->unparse(out, 0);
	out << "\n";
}

void StructDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myId->unparse(out, 0);
	out << " ";
	myDeclList->unparse(out, 0);
	out << "\n";
}

void DotAccessNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp->unparse(out, 0);
	out << ".";
	myId->unparse(out, 0);
	out << "\n";
}

void AssignNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExpL->unparse(out, 0);
	out << " = ";
	myExpR->unparse(out, 0);
	out << "\n";
}

void CallExpNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myId->unparse(out, 0);
	out << "(";
	myExpList->unparse(out, 0);
	out << ")\n";
}

void IdNode::unparse(std::ostream& out, int indent){
	out << myStrVal;
}

void IntNode::unparse(std::ostream& out, int indent){
	out << "int";
}

void BoolNode::unparse(std::ostream& out, int indent){
	out << "bool";
}

void VoidNode::unparse(std::ostream& out, int indent){
	out << "void";
}

} // End namespace LIL' C
