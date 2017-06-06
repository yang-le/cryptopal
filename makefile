all: cryptopal

cryptopal: s1c1.o s1c2.o s1c3.o s1c4.o s1c5.o s1c6.o main.o
	clang++ -Wall -Werror $^ -o $@

%.o : %.c
	clang -Wall -Werror -g -c $^ -o $@

clean:
	rm *.o cryptopal
