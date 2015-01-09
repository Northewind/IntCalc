SRC_PATH=src_code
BIN_PATH=bin
OPT= -g -std=c99  -lm  $(SRC_PATH)/*.c
OUTF=intcalc
TEST=cat tests

all: clean build run

build:
	gcc $(OPT) -o $(BIN_PATH)/$(OUTF)_gcc
	clang $(OPT) -o $(BIN_PATH)/$(OUTF)_cl

run:
	$(BIN_PATH)/$(OUTF)_gcc
	#$(BIN_PATH)/$(OUTF)_cl

t1:
	$(TEST)/t1 | $(BIN_PATH)/$(OUTF)_gcc
	#$(TEST)/t1 | $(BIN_PATH)/$(OUTF)_cl

dbox: build clean
	rm -R ~/Public/Dropbox/workspace/intcalc/* 
	cp -R ./* ~/Public/Dropbox/workspace/intcalc

clean:
	rm $(BIN_PATH)/$(OUTF)_gcc $(BIN_PATH)/$(OUTF)_cl

