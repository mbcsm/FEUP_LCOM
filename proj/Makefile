PROG=proj

SRCS = proj.c timer.c keyboard.c mouse.c packet.c cursor.c video.c bitmap.c

CPPFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
