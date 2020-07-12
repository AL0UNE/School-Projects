INCLDIR	:= include
OBJDIR	:= obj
SRCDIR	:= src
BINDIR	:= bin

CC      := g++
VPATH	:=
LDFLAGS :=
LIBRARY :=
CFLAGS  := -std=c++11 -Wall -I $(INCLDIR)


SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(subst $(SRCDIR)/,$(OBJDIR)/, $(subst .cpp,.o, $(SRCS)))


EXEC = main testDenseMatrix testBlock testBlockMatrix


all : makedir $(EXEC)


$(EXEC) : %: %.cpp $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


.PHONY: clean
clean :
	rm -rf $(OBJDIR)/*
	rm -rf $(BINDIR)/*

.PHONY: makedir
makedir :
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)


.PHONY: print
print :
	echo $(SRCS)
	echo $(OBJS)
