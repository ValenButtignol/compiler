flex -o extern/lex.yy.c extern/lexicon2.l
bison -b extern/syntax2 -d extern/syntax2.y 
gcc main2.c extern/lex.yy.c extern/syntax2.tab.c -o output/output.out
./a.out input/input.txt 