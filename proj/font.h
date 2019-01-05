#pragma once
#ifndef FONT_H
#define FONT_H

#include "xpm.h"

#include "pixmap/fonts/black-size36/1.h"
#include "pixmap/fonts/black-size36/0.h"
#include "pixmap/fonts/black-size36/2.h"
#include "pixmap/fonts/black-size36/3.h"
#include "pixmap/fonts/black-size36/4.h"
#include "pixmap/fonts/black-size36/5.h"
#include "pixmap/fonts/black-size36/6.h"
#include "pixmap/fonts/black-size36/7.h"
#include "pixmap/fonts/black-size36/8.h"
#include "pixmap/fonts/black-size36/9.h"
#include "pixmap/fonts/black-size36/a.h"
#include "pixmap/fonts/black-size36/b.h"
#include "pixmap/fonts/black-size36/c.h"
#include "pixmap/fonts/black-size36/colon.h"
#include "pixmap/fonts/black-size36/d.h"
#include "pixmap/fonts/black-size36/e.h"
#include "pixmap/fonts/black-size36/f.h"
#include "pixmap/fonts/black-size36/g.h"
#include "pixmap/fonts/black-size36/h.h"
#include "pixmap/fonts/black-size36/i.h"
#include "pixmap/fonts/black-size36/j.h"
#include "pixmap/fonts/black-size36/k.h"
#include "pixmap/fonts/black-size36/l.h"
#include "pixmap/fonts/black-size36/m.h"
#include "pixmap/fonts/black-size36/n.h"
#include "pixmap/fonts/black-size36/o.h"
#include "pixmap/fonts/black-size36/p.h"
#include "pixmap/fonts/black-size36/q.h"
#include "pixmap/fonts/black-size36/question_mark.h"
#include "pixmap/fonts/black-size36/r.h"
#include "pixmap/fonts/black-size36/s.h"
#include "pixmap/fonts/black-size36/slash.h"
#include "pixmap/fonts/black-size36/t.h"
#include "pixmap/fonts/black-size36/u.h"
#include "pixmap/fonts/black-size36/v.h"
#include "pixmap/fonts/black-size36/w.h"
#include "pixmap/fonts/black-size36/x.h"
#include "pixmap/fonts/black-size36/y.h"
#include "pixmap/fonts/black-size36/z.h"

void printstring(char * string, int size, char * font, int x , int y);

bool loadChar(char textI, uint16_t *data, xpm_image_t imgData);

#endif


