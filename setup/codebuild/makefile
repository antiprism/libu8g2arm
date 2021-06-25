# 
# U8g2 codebuild_cpper
# 

CPPFLAGS = -g -Wall 
#CFLAGS = -O4 -Wall

SRC = codebuild_cpp.c

OBJ = $(SRC:.c=.o)

codebuild_cpp: $(SRC) codebuild_cpp.c
	$(CC) -Wall -g $(LDFLAGS) $(SRC) -o codebuild_cpp

clean:	
	-rm ./codebuild_cpp codebuild_cpp.o

build: codebuild_cpp
	./codebuild_cpp
	
