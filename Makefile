CC=gcc  #compiler
TARGET=dh_assign_1 #target file name
 
all:
	$(CC) dh_assign_1.c -o $(TARGET) -lgmp
 
clean:
	rm -rf *.o $(TARGET)
