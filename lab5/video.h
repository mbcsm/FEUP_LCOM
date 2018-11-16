#pragma once
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include "video.h"

#include <i8042.h>
#include <stdint.h>
#include <stdio.h>


int mapVRAM();

static char *video_mem;		/* Process (virtual) address to which VRAM is mapped */

static unsigned h_res;	        /* Horizontal resolution in pixels */
static unsigned v_res;	        /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

int vg_start(uint16_t mode);
int get_h_res();
int get_v_res();
int get_bits_per_pixel();
void * get_video_mem();