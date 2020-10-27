CXXFLAGS = -I../Empiru/sources/ -I../Empiru/libs/ -O2 -g -Wall -fmessage-length=0 -std=c++2a

TESTS = IteratorSafeness WorldObjectSignal

%: %.cpp
	pwd
	$(CXX) -o $@ $^ $(CXXFLAGS)

all: $(TESTS)

clean:
	rm -f $(OBJS) $(TARGET)
