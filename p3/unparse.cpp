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
	myType->unparse(out, indent);
	out << " ";
	myId->unparse(out, 0);
	out << ";\n";
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
			if(it != myExps.begin())
				out << ", ";
	    ExpNode * elt = *it;
	    elt->unparse(out, 0);
	}
}

void FnDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myType->unparse(out, 0);
	out << " ";
	myId->unparse(out, 0);
	out << " (";
	myFormalsList->unparse(out, 0);
	out << "){\n";
	myFnBody->unparse(out, 1);
	out << "}\n";
}

void FormalsListNode::unparse(std::ostream& out, int indent){
	for (std::list<FormalDeclNode *>::iterator it=myFormals.begin();
		it != myFormals.end(); ++it){
			if(it != myFormals.begin())
				out << ", ";
	    FormalDeclNode * elt = *it;
	    elt->unparse(out, indent);
	}
}

void FormalDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myType->unparse(out, 0);
	out << " ";
	myId->unparse(out, 0);
}

void FnBodyNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myDeclList->unparse(out, 0);
	myStmtList->unparse(out, 0);
	out << "\n";
}

void StructDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "struct ";
	myId->unparse(out, 0);
	out << " {\n";
	myDeclList->unparse(out, 1);
	out << "};\n";
}

void AssignStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myAssignNode->unparse(out, 0);
	out << ";\n";
}

void PostIncStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp->unparse(out, 0);
	out << "++;\n";
}

void PostDecStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp->unparse(out, 0);
	out << "--;\n";
}

void ReadStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "cout << ";
	myExp->unparse(out, 0);
	out << ";\n";
}

void WriteStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "cin >> ";
	myExp->unparse(out, 0);
	out << ";\n";
}

void IfStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "if(";
	myExp->unparse(out, 0);
	out<<"){\n";
	myDeclList->unparse(out, indent+1);
	myStmtList->unparse(out, indent+1);
	doIndent(out,indent);
	out << "}\n";
}

void IfElseStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "if(";
	myExp->unparse(out, 0);
	out<<"){\n";
	myDeclList->unparse(out, indent+1);
	myStmtList->unparse(out, indent+1);
	doIndent(out,indent);
	out << "}\n";
	doIndent(out, indent);
	out<< "else {\n";
	myDeclList2->unparse(out, indent+1);
	myStmtList2->unparse(out, indent+1);
	doIndent(out, indent);
	out<<"}\n";
}

void WhileStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out<< "while(";
	myExp->unparse(out, 0);
	out<<") {\n";
	myDeclList->unparse(out, indent+1);
	myStmtList->unparse(out, indent+1);
	doIndent(out, indent);
	out<<"}\n";
}

void CallStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myCall->unparse(out, indent);
	out<<";\n";
}

void ReturnStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out<<"return ";
	myExp->unparse(out, 0);
	out<<";\n";
}

void DotAccessNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	myExp->unparse(out, 0);
	out << ".";
	myId->unparse(out, 0);
	out << ")";
}

void AssignNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExpL->unparse(out, 0);
	out << " = ";
	myExpR->unparse(out, 0);
}

void CallExpNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myId->unparse(out, 0);
	out << "(";
	myExpList->unparse(out, 0);
	out << ")";
}

void UnaryMinusNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(-";
	myExp->unparse(out, 0);
	out << ")";
}

void NotNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "!(";
	myExp->unparse(out, 0);
	out << ")";
}

void PlusNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	myExpL->unparse(out, 0);
	out << " + ";
	myExpR->unparse(out, 0);
	out << ")";
}

void MinusNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	myExpL->unparse(out, 0);
	out << " - ";
	myExpR->unparse(out, 0);
	out << ")";
}

void TimesNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	myExpL->unparse(out, 0);
	out << " * ";
	myExpR->unparse(out, 0);
	out << ")";
}

void DivideNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	myExpL->unparse(out, 0);
	out << " / ";
	myExpR->unparse(out, 0);
	out << ")";
}

void AndNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	myExpL->unparse(out, 0);
	out << " && ";
	myExpR->unparse(out, 0);
	out << ")";
}

void OrNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	myExpL->unparse(out, 0);
	out << " || ";
	myExpR->unparse(out, 0);
	out << ")";
}

void EqualsNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	myExpL->unparse(out, 0);
	out << " == ";
	myExpR->unparse(out, 0);
	out << ")";
}

void NotEqualsNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	myExpL->unparse(out, 0);
	out << " != ";
	myExpR->unparse(out, 0);
	out << ")";
}

void LessNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	myExpL->unparse(out, 0);
	out << " < ";
	myExpR->unparse(out, 0);
	out << ")";
}

void GreaterNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	myExpL->unparse(out, 0);
	out << " > ";
	myExpR->unparse(out, 0);
	out << ")";
}

void LessEqNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	myExpL->unparse(out, 0);
	out << " <= ";
	myExpR->unparse(out, 0);
	out << ")";
}

void GreaterEqNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	myExpL->unparse(out, 0);
	out << " >= ";
	myExpR->unparse(out, 0);
	out << ")";
}

void IntLitNode::unparse(std::ostream& out, int indent){
	out << myVal;
}

void StrLitNode::unparse(std::ostream& out, int indent){
	out << myStrVal;
}

void TrueNode::unparse(std::ostream& out, int indent){
	out << "true";
}

void FalseNode::unparse(std::ostream& out, int indent){
	out << "false";
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
