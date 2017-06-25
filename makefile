OBJS := s1c1.o s1c2.o s1c3.o s1c4.o s1c5.o s1c6.o s1c7.o s1c8.o
OBJS += s2c9.o s2c10.o
OBJS += main.o

all: cryptopal

cryptopal: ${OBJS}
	clang++ -Wall -Werror $^ -lcrypto -o $@

%.o : %.c
	clang -Wall -Werror -g -c $^ -o $@

clean:
	rm ${OBJS} cryptopal
