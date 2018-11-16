#include <lcom/lcf.h>
#include "video.h"
#include <liblm.h>

int mapVRAM(){

    static void *video_mem; /* frame-buffer VM address (static global variable*/ 
    int r; 
    struct minix_mem_range mr; 
    static unsigned int vram_base; /* VRAM's physical addresss */ 
    static unsigned int vram_size; /* VRAM's size, but you can use the frame-buffer size, instead */ 
    
    /* Allow memory mapping */ 
    mr.mr_base = (phys_bytes) vram_base; 
    mr.mr_limit = mr.mr_base + vram_size; 
    
    if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))){ 
        panic("sys_privctl (ADD_MEM) failed: %d\n", r); /* Map memory */ 
        return 1;
    }

    video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size); 
    
    if(video_mem == MAP_FAILED) {
        panic("couldn't map video memory");
        return 1;
    }

    return 0;
}

int(vg_start)(uint16_t mode) {
	vbe_mode_info_t vbe_mode;
  vbe_get_mode_info(mode, &vbe_mode);

  v_res = vbe_mode.YResolution;
  h_res = vbe_mode.XResolution;
  bits_per_pixel = vbe_mode.BitsPerPixel;

  struct reg86u reg86;
  memset(&reg86, 0, sizeof(reg86)); /* zero the structure */
  reg86.u.w.ax = 0x4F02;            // VBE call, function 02 -- set VBE mode
  reg86.u.w.bx = 1 << 14 | mode;    // set bit 14: linear framebuffer
  reg86.u.b.intno = 0x10;

  if (sys_int86(&reg86) != OK) {
    printf("set_vbe_mode: sys_int86() failed \n");
    return 1;
  }

  int r_mem;
  struct minix_mem_range mr;
  unsigned int vram_size = h_res * v_res * (bits_per_pixel / 8);
  

  mr.mr_base = (phys_bytes) vbe_mode.PhysBasePtr;
  mr.mr_limit = mr.mr_base + vram_size;
  if (OK != (r_mem = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r_mem);
  /* Map memory */
  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);
  if (video_mem == MAP_FAILED)
    panic("couldn’t map video memory");

    return 0;
}

int(get_h_res)(){
  return h_res;
}
int(get_v_res)(){
  return v_res;
}
int(get_bits_per_pixel)(){
  return bits_per_pixel;
}
void * (get_video_mem)(){
  return video_mem;
}