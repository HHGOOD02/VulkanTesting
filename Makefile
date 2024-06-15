CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -lpthread -lX11 -lXxf86vm -lXrandr -lXi

TestApp: main.cpp
	g++ $(CFLAGS) -o TestApp main.cpp $(LDFLAGS) 

.PHONY: test clean

test: TestApp
	./TestApp

clean:TestApp
	rm TestApp

