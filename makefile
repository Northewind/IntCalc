SRC_PATH=src_code
BIN_PATH=bin
OPT= -g -std=c99  -lm  $(SRC_PATH)/*.c
OUTF=intcalc
TEST=cat tests

all: build run

build:
	time gcc $(OPT) -o $(BIN_PATH)/$(OUTF)
	time clang $(OPT) -o $(BIN_PATH)/$(OUTF)_cl
	ls -l bin/

run:
	$(BIN_PATH)/$(OUTF)

t1:
	$(TEST)/t1 | $(BIN_PATH)/$(OUTF)

t2:
	$(TEST)/t2 | $(BIN_PATH)/$(OUTF)

t3:
	$(TEST)/t3 | $(BIN_PATH)/$(OUTF)

t4:
	$(TEST)/t4 | $(BIN_PATH)/$(OUTF)


dbox: build clean
	rm -R ~/Public/Dropbox/workspace/intcalc/* 
	cp -R ./* ~/Public/Dropbox/workspace/intcalc

clean:
	rm $(BIN_PATH)/$(OUTF) $(BIN_PATH)/$(OUTF)_cl

