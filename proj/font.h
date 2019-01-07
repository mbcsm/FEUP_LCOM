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

#include "pixmap/fonts/white-size22/0.h"
#include "pixmap/fonts/white-size22/1.h"
#include "pixmap/fonts/white-size22/2.h"
#include "pixmap/fonts/white-size22/3.h"
#include "pixmap/fonts/white-size22/4.h"
#include "pixmap/fonts/white-size22/5.h"
#include "pixmap/fonts/white-size22/6.h"
#include "pixmap/fonts/white-size22/7.h"
#include "pixmap/fonts/white-size22/8.h"
#include "pixmap/fonts/white-size22/9.h"
#include "pixmap/fonts/white-size22/a.h"
#include "pixmap/fonts/white-size22/b.h"
#include "pixmap/fonts/white-size22/c.h"
#include "pixmap/fonts/white-size22/colon.h"
#include "pixmap/fonts/white-size22/d.h"
#include "pixmap/fonts/white-size22/dot.h"
#include "pixmap/fonts/white-size22/e.h"
#include "pixmap/fonts/white-size22/f.h"
#include "pixmap/fonts/white-size22/g.h"
#include "pixmap/fonts/white-size22/h.h"
#include "pixmap/fonts/white-size22/i.h"
#include "pixmap/fonts/white-size22/j.h"
#include "pixmap/fonts/white-size22/k.h"
#include "pixmap/fonts/white-size22/l.h"
#include "pixmap/fonts/white-size22/m.h"
#include "pixmap/fonts/white-size22/n.h"
#include "pixmap/fonts/white-size22/o.h"
#include "pixmap/fonts/white-size22/p.h"
#include "pixmap/fonts/white-size22/q.h"
#include "pixmap/fonts/white-size22/question_mark.h"
#include "pixmap/fonts/white-size22/r.h"
#include "pixmap/fonts/white-size22/s.h"
#include "pixmap/fonts/white-size22/slash.h"
#include "pixmap/fonts/white-size22/t.h"
#include "pixmap/fonts/white-size22/u.h"
#include "pixmap/fonts/white-size22/v.h"
#include "pixmap/fonts/white-size22/w.h"
#include "pixmap/fonts/white-size22/x.h"
#include "pixmap/fonts/white-size22/y.h"
#include "pixmap/fonts/white-size22/z.h"

/**
 * @brief Prints string onto a location on the screen
 * @param string set of chars to be printed
 * @param size the size of the string
 * @param font the font of the printed string
 * @param x the x location of the string
 * @param y the y location of the string
*/
void printstring(char * string, int size, char * font, int x , int y);

/**
 * @brief Loads a char pixmap
 * @param textI char to be loaded
 * @param font the font of the printed char
*/
bool loadChar(char textI, char font);

#endif


