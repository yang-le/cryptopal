all: cryptopal

cryptopal: s1c1.o s1c2.o s1c3.o common.o
	clang++ $^ -o $@

%.o : %.c
	clang -g -c $^ -o $@

clean:
	rm *.o
