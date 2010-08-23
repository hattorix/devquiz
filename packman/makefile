TARGET = packman.out
LDFLAGS = -lncurses
CXX = g++
CXXFLAGS = -c -g -Wall
OBJDIR = obj
OBJS = $(OBJDIR)/packman.o\
	$(OBJDIR)/game.o\
	$(OBJDIR)/moving_object.o\
	$(OBJDIR)/player.o\
	$(OBJDIR)/enemy.o\
	$(OBJDIR)/around.o\
	$(OBJDIR)/abstract_action.o\
	$(OBJDIR)/factory.o\
	$(OBJDIR)/breadth_first.o\
	$(OBJDIR)/v.o\
	$(OBJDIR)/h.o\
	$(OBJDIR)/j.o

.PHONY : all
all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS)

$(OBJDIR)/%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJDIR)/%.o : packman/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJDIR)/%.o : packman/searcher/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OBJDIR)/%.o : packman/action/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean :
	rm -f $(OBJS)
	rm -f $(TARGET)
