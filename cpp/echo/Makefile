CXX = g++
CXXFLAGS = -std=c++14 -stdlib=libc++
CFLAGS = -MMD -MP -Wall  -g -fsanitize=address -fno-omit-frame-pointer
LIBS = -L/opt/brew/Cellar/libevent/2.1.8/lib -levent -L/opt/brew/Cellar/nghttp2/1.32.0/lib -lnghttp2  -L/opt/brew/Cellar/protobuf/3.6.0/lib -lprotobuf
INCLUDE = -I/opt/brew/include -I/opt/brew/Cellar/protobuf/3.6.0/include

TARGET = server
SRCS := main.cc hellworld.pb.cc
OBJS = $(addsuffix .o, $(basename $(SRCS)))
DEPS := $(SRCS:%.cc=%.d)

$(TARGET): $(OBJS)
		$(CXX) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

$(OBJS): $(SRCS)
		$(CXX) $(CFLAGS) $(CXXFLAGS) -c $^ $(INCLUDE)

.PHONY: clean all

clean:
		$(RM) $(TARGET) $(OBJS) $(DEPS)

all: clean $(TARGET)

-include $(DEPS)
