bto.o: btl.h
	g++ -c -o $@ $^

clean:
	rm btl.o
