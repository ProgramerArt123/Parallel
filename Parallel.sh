lex Parallel.l
yacc -d Parallel.y
g++ *.cpp -ll -ly
