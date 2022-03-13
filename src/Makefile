
CFLAGS= -Wall -Werror -I../extern -I/usr/include/freetype2 -DLINUX -O2 -march=native
CXXFLAGS= -std=c++11
LDFLAGS= -lpthread -lGLEW -lGL -lSDL2 -lXft -lfreetype

OBJDIR=../obj
OBJS= $(OBJDIR)/camera.o $(OBJDIR)/delta.o $(OBJDIR)/element.o \
$(OBJDIR)/events.o $(OBJDIR)/flag.o $(OBJDIR)/floor.o $(OBJDIR)/font.o \
$(OBJDIR)/font3D.o $(OBJDIR)/hud.o $(OBJDIR)/image.o $(OBJDIR)/memory.o \
$(OBJDIR)/moon.o $(OBJDIR)/object.o $(OBJDIR)/render.o $(OBJDIR)/score.o \
$(OBJDIR)/shader.o $(OBJDIR)/sky.o $(OBJDIR)/sound.o $(OBJDIR)/state.o \
$(OBJDIR)/terminal.o $(OBJDIR)/texture.o $(OBJDIR)/thread.o \
$(OBJDIR)/vertices.o $(OBJDIR)/devel.o

default: prepare $(OBJS)
	g++ $(CFLAGS) $(CXXFLAGS) $(OBJS) $(LDFLAGS) \
	 -o ../devel

prepare:
	[ -d $(OBJDIR) ] || mkdir $(OBJDIR)

$(OBJDIR)/camera.o: camera.c camera.h
	g++ -c $(CFLAGS) $(CXXFLAGS) camera.c -o $(OBJDIR)/camera.o

$(OBJDIR)/delta.o: delta.c delta.h
	g++ -c $(CFLAGS) $(CXXFLAGS) delta.c -o $(OBJDIR)/delta.o

$(OBJDIR)/element.o: element.c element.h
	g++ -c $(CFLAGS) $(CXXFLAGS) element.c -o $(OBJDIR)/element.o

$(OBJDIR)/events.o: events.c events.h
	g++ -c $(CFLAGS) $(CXXFLAGS) events.c -o $(OBJDIR)/events.o

$(OBJDIR)/flag.o: flag.c flag.h
	g++ -c $(CFLAGS) $(CXXFLAGS) flag.c -o $(OBJDIR)/flag.o

$(OBJDIR)/floor.o: floor.c floor.h
	g++ -c $(CFLAGS) $(CXXFLAGS) floor.c -o $(OBJDIR)/floor.o

$(OBJDIR)/font.o: font.c font.h
	g++ -c $(CFLAGS) $(CXXFLAGS) font.c -o $(OBJDIR)/font.o

$(OBJDIR)/font3D.o: font3D.c font3D.h
	g++ -c $(CFLAGS) $(CXXFLAGS) font3D.c -o $(OBJDIR)/font3D.o

$(OBJDIR)/hud.o: hud.c hud.h
	g++ -c $(CFLAGS) $(CXXFLAGS) hud.c -o $(OBJDIR)/hud.o

$(OBJDIR)/image.o: image.c image.h
	g++ -c $(CFLAGS) $(CXXFLAGS) image.c -o $(OBJDIR)/image.o

$(OBJDIR)/memory.o: memory.c memory.h
	g++ -c $(CFLAGS) $(CXXFLAGS) memory.c -o $(OBJDIR)/memory.o

$(OBJDIR)/moon.o: moon.c moon.h
	g++ -c $(CFLAGS) $(CXXFLAGS) moon.c -o $(OBJDIR)/moon.o

$(OBJDIR)/object.o: object.c object.h
	g++ -c $(CFLAGS) $(CXXFLAGS) object.c -o $(OBJDIR)/object.o

$(OBJDIR)/render.o: render.c render.h
	g++ -c $(CFLAGS) $(CXXFLAGS) render.c -o $(OBJDIR)/render.o

$(OBJDIR)/score.o: score.c score.h
	g++ -c $(CFLAGS) $(CXXFLAGS) score.c -o $(OBJDIR)/score.o

$(OBJDIR)/shader.o: shader.c shader.h
	g++ -c $(CFLAGS) $(CXXFLAGS) shader.c -o $(OBJDIR)/shader.o

$(OBJDIR)/state.o: state.c state.h
	g++ -c $(CFLAGS) $(CXXFLAGS) state.c -o $(OBJDIR)/state.o

$(OBJDIR)/sky.o: sky.c sky.h
	g++ -c $(CFLAGS) $(CXXFLAGS) sky.c -o $(OBJDIR)/sky.o

$(OBJDIR)/sound.o: sound.c sound.h
	g++ -c $(CFLAGS) $(CXXFLAGS) sound.c -o $(OBJDIR)/sound.o

$(OBJDIR)/terminal.o: terminal.c terminal.h
	g++ -c $(CFLAGS) $(CXXFLAGS) terminal.c -o $(OBJDIR)/terminal.o

$(OBJDIR)/texture.o: texture.c texture.h
	g++ -c $(CFLAGS) $(CXXFLAGS) texture.c -o $(OBJDIR)/texture.o

$(OBJDIR)/thread.o: thread.c thread.h
	g++ -c $(CFLAGS) $(CXXFLAGS) thread.c -o $(OBJDIR)/thread.o

$(OBJDIR)/vertices.o: vertices.c vertices.h
	g++ -c $(CFLAGS) $(CXXFLAGS) vertices.c -o $(OBJDIR)/vertices.o

$(OBJDIR)/devel.o: devel.c devel.h
	g++ -c $(CFLAGS) $(CXXFLAGS) devel.c -o $(OBJDIR)/devel.o

.PHONY: clean
clean:
	@rm -rfv $(OBJDIR)/*.o $(OBJDIR) ../devel
