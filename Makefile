BISON = /home/a807d786/tools/bison-3.0.2/src/bison

EXE = P2

CDEBUG = -g
CXXDEBUG = -g

CSTD = -std=c99
CXXSTD = -std=c++14

CFLAGS = -O0  $(CDEBUG) $(CSTD)
CXXFLAGS = -O0  $(CXXDEBUG) $(CXXSTD)

TESTDIR = test/
TESTEXPDIR = test/expectedResults/

P2: lilc_lexer.o P2.o lilc_compiler.o
	$(CXX) $(CXXFLAGS) -o P2 lilc_compiler.o P2.o lilc_lexer.o

P2.o: P2.cpp grammar.hh
	$(CXX) $(CXXFLAGS) -c $<

lilc_compiler.o: lilc_compiler.cpp
	$(CXX) $(CXXFLAGS) -c $<

lilc_lexer.o: lilc_lexer.l
	flex --outfile=lilc_lexer.yy.cc  $<
	$(CXX)  $(CXXFLAGS) -c lilc_lexer.yy.cc -o lilc_lexer.o

.PHONY: clean test cleantest
clean:
	rm -rf *.o *.output \
	lilc_lexer.yy.cc \
	P2 P3 P4 P5 P6
test: P2
	./P2 ${TESTDIR}keywordTokens.in ${TESTDIR}keywordTokens.output
	./P2 ${TESTDIR}operatorTokens.in ${TESTDIR}operatorTokens.output
	./P2 ${TESTDIR}eofToken.in ${TESTDIR}eofToken.output
	./P2 ${TESTDIR}comments.in ${TESTDIR}comments.output
	./P2 ${TESTDIR}illegalCharacters.in ${TESTDIR}illegalCharacters.output
	diff ${TESTDIR}keywordTokens.output ${TESTEXPDIR}keywordTokens.output || echo '\nUNEXPECTED ERROR IN keywordTokens OUTPUT\n'
	diff ${TESTDIR}operatorTokens.output ${TESTEXPDIR}operatorTokens.output || echo '\nUNEXPECTED ERROR IN operatorTokens OUTPUT\n'
	diff ${TESTDIR}eofToken.output ${TESTEXPDIR}eofToken.output || echo '\nUNEXPECTED ERROR IN eofToken OUTPUT\n'
	diff ${TESTDIR}comments.output ${TESTEXPDIR}eofToken.output || echo '\nUNEXPECTED ERROR IN comment OUTPUT\n'
	diff ${TESTDIR}illegalCharacters.output ${TESTEXPDIR}eofToken.output || echo '\nUNEXPECTED ERROR IN illegalCharacters OUTPUT\n'

cleantest: test
	rm test/*.output
