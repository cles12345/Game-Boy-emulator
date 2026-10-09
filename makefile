CXX      = g++
SRCDIR   = src
BUILDDIR = build
INCDIR   = -Iinc/SDL3 -Iinc
LIBDIR   = lib

CXXFLAGS = -Wall -Wextra $(INCDIR)
LDLIBS   = -L$(LIBDIR)/SDL3 -lSDL3

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
OBJS = $(addprefix $(BUILDDIR)/, $(OBJ))

TARGET = $(BUILDDIR)/emu

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

run: $(TARGET)
	@cp $(LIBDIR)/SDL3/SDL3.dll $(BUILDDIR)/ 2>/dev/null || true
	cd $(BUILDDIR) && ./emu

clean:
	rm -rf $(BUILDDIR)

.PHONY: all run clean