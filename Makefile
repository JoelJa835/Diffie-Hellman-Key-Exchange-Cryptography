CC=gcc  #compiler
CFLAGS = -Wall
LDFLAGS = -lgmp
OBJFILES = dh_assign_1.o  
TARGET=dh_assign_1 #target file name
 
all:$(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
 
clean:
	rm -rf $(OBJFILES) $(TARGET) *~