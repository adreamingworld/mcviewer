AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4 --install

# Files we want to be packaged in the tar ball distribution
EXTRA_DIST = 	README.md 

bin_PROGRAMS = mcviewer

mcviewer_SOURCES = \
		src/nbt.c \
		src/nbt.h \
		src/nbt_utils.c \
		src/nbt_utils.h \
		src/myz.c \
		src/myz.h \
		src/shader.c \
		src/shader.h \
		src/main.c
			

mcviewer_CFLAGS = @GLEW_CFLAGS@ @SDL2_CFLAGS@ @ZLIB_CFLAGS@ -DDATA_PATH='"$(pkgdatadir)"'
mcviewer_LDADD = @GLEW_LIBS@ @SDL2_LIBS@ @ZLIB_LIBS@
