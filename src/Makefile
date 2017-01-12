# Cosas por cambiar entre plataformas...
# 
#  Windows (con msys2 y mingw64):
#  - TARGETEXT := .dll
#  - PREFIX := /mingw64/
#  - Descomentar "cp $(TARGET) $(PREFIX)bin/" y "rm $(TARGET)bin/$(PREFIX)
# 
#  Linux:
#  - TARGETEXT := .so
#  - PREFIX := /usr/
#  - Comentar "cp $(TARGET) $(PREFIX)bin/" y "rm $(TARGET)bin/$(PREFIX)


CC			:= gcc
CXX			:= g++
LD			:= $(CC)
MACROS		:= -DLIBEDS_EXPORTS
ARCH		:= -m64
CFLAGS		:= -c -Wall $(ARCH) -g0 -O3 -fPIC
CXXFLAGS	:= $(CFLAGS)
CSTD		:= -std=c99
CXXSTD		:= -std=c++03
LINKFLAGS	:= $(ARCH) -shared

OBJECTS		:= libbmp.o \
			   EDS_tipos.o \
			   EDS_color.o \
			   EDS_dibujo.o \
			   EDS_geo.o \
			   EDS_texto.o

TARGETNAME	:= libEDS
TARGETEXT	:= .dll
TARGET		:= $(TARGETNAME)$(TARGETEXT)
PREFIX		:= /mingw64/


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LINKFLAGS) $(OBJECTS) -o $(TARGET)

libbmp.o: libbmp.c
	$(CC) $(CFLAGS) $(CSTD) $(MACROS) libbmp.c -o libbmp.o

EDS_tipos.o: EDS_tipos.c
	$(CC) $(CFLAGS) $(CSTD) $(MACROS) EDS_tipos.c -o EDS_tipos.o

EDS_color.o: EDS_color.c
	$(CC) $(CFLAGS) $(CSTD) $(MACROS) EDS_color.c -o EDS_color.o

EDS_dibujo.o: EDS_dibujo.c
	$(CC) $(CFLAGS) $(CSTD) $(MACROS) EDS_dibujo.c -o EDS_dibujo.o

EDS_geo.o: EDS_geo.c
	$(CC) $(CFLAGS) $(CSTD) $(MACROS) EDS_geo.c -o EDS_geo.o

EDS_texto.o: EDS_texto.c
	$(CC) $(CFLAGS) $(CSTD) $(MACROS) EDS_texto.c -o EDS_texto.o



install:
	cp $(TARGET) $(PREFIX)lib/
	mkdir $(PREFIX)include/EDS/
	cp *.h* $(PREFIX)include/EDS/
	cp $(TARGET) $(PREFIX)bin/

uninstall:
	rm $(PREFIX)lib/$(TARGET)
	rm -r $(PREFIX)include/EDS/
	rm $(PREFIX)bin/$(TARGET)

clean:
	rm -f *.o $(TARGET)

