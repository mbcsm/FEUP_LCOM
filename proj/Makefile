PROG=proj



SRCS = proj.c game.c timer.c keyboard.c mouse.c packet.c cursor.c video.c board.c font.c

CPPFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>