SRC_PATH=src_code
BIN_PATH=bin
OPT= -g -std=c99  -lm  $(SRC_PATH)/*.c
OUTF=icalc
TESTS=tests


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
	$(BIN_PATH)/$(OUTF) -W < $(TESTS)/t1

t2:
	$(BIN_PATH)/$(OUTF) -W < $(TESTS)/t2

t3:
	$(BIN_PATH)/$(OUTF) -W < $(TESTS)/t3

t4:
	$(BIN_PATH)/$(OUTF) -W < $(TESTS)/t4

t5:
	$(BIN_PATH)/$(OUTF) -W < $(TESTS)/t5

tn:
	$(BIN_PATH)/$(OUTF) < $(TESTS)/tn
