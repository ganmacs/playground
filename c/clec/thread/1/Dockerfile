FROM i386/gcc:4.9
WORKDIR /app
COPY . /app
RUN gcc -g -o test1 test1.c thread.c csw-i386.S
CMD ["./test1"]
