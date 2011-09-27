
default: byteio.h data.h erros.h header.h pagina.h tipos.h header.o
	g++ $(LDFLAGS) header.o -o AardvarkDB

header.o: byteio.h data.h erros.h header.cpp header.h pagina.h tipos.h
	g++ -c header.cpp

check:
	g++ -fsyntax-only byteio.h 
	g++ -fsyntax-only data.h 
	g++ -fsyntax-only erros.h 
	g++ -fsyntax-only header.h 
	g++ -fsyntax-only pagina.h 
	g++ -fsyntax-only tipos.h 
	g++ -fsyntax-only header.cpp 

clean:
	$(RM) *.o
