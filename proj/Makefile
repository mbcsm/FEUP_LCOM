PROG=proj

SRCS = proj.c timer.c keyboard.c video.c mouse.c packet.c

CPPFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
