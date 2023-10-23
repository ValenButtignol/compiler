flex -o extern/lex.yy.c extern/lexicon.l
bison -b extern/syntax -d extern/syntax.y 
gcc main2.c extern/lex.yy.c extern/syntax.tab.c -o output/output.out
./a.out input/input.txt 