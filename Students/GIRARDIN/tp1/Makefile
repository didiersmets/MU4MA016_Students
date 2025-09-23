Target : Test_queue Test_queue_cpp

#---------------------------------------------------------------------------------------------------------
Test_queue : circular_buffer_queue.o test_queue.o
	gcc -o Test_queue circular_buffer_queue.o test_queue.o

circular_buffer_queue.o  : ./src/circular_buffer_queue.c ./include/circular_buffer_queue.h
	gcc -c ./src/circular_buffer_queue.c

test_queue.o : ./src/test_queue.c ./include/circular_buffer_queue.h
	gcc -c ./src/test_queue.c

#---------------------------------------------------------------------------------------------------------
Test_queue_cpp : test_queue_cpp.o
	g++ -o Test_queue_cpp test_queue_cpp.o

test_queue_cpp.o : ./src/test_queue_cpp.cpp ./include/circular_buffer_queue_cpp.h
	g++ -c ./src/test_queue_cpp.cpp