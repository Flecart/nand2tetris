# I SINGOLI TEST FUNZIONANO!
# make
# mv ./VMTranslator ./correzioni/easy_test
# cd ./correzioni/easy_test
# ./VMTranslator TempTest.vm 
# ./VMTranslator FibonacciElement.vm # FUNZIONA
# ./VMTranslator StaticTest.vm # FUNZIONA
# ./VMTranslator Basicloop.vm # FUNZIONA
# ./VMTranslator BasicTest.vm # FUNZIONA
# ./VMTranslator SimpleFunction.vm # FUNZIONA
# ./VMTranslator StackTest.vm #FUNZIONA
# ./VMTranslator SimpleAdd.vm #FUNZIONA
# USE this to check pong
make 
valgrind --leak-check=full  ./VMTranslator ./correzioni/pong
wc -l ./correzioni/pong/Main.asm


