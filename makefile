SRC_PATH=src_code
BIN_PATH=bin
OPT= -g -std=c99  -lm  $(SRC_PATH)/*.c
OUTF=icalc
TEST=cat tests

all: build run

build:
	time clang $(OPT) -o $(BIN_PATH)/$(OUTF)_cl
	time gcc $(OPT) -o $(BIN_PATH)/$(OUTF)
	ls -l bin/

run:
	$(BIN_PATH)/$(OUTF)

dbox: build clean
	rm -R ~/Public/Dropbox/workspace/intcalc/* 
	cp -R ./* ~/Public/Dropbox/workspace/intcalc

clean:
	rm $(BIN_PATH)/$(OUTF) $(BIN_PATH)/$(OUTF)_cl

t1:
	$(TEST)/t1 | $(BIN_PATH)/$(OUTF)

t2:
	$(TEST)/t2 | $(BIN_PATH)/$(OUTF)

t3:
	$(TEST)/t3 | $(BIN_PATH)/$(OUTF)

t4:
	$(TEST)/t4 | $(BIN_PATH)/$(OUTF)

t5:
	$(TEST)/t5 | $(BIN_PATH)/$(OUTF)

t6:
	$(TEST)/t6 | $(BIN_PATH)/$(OUTF)
