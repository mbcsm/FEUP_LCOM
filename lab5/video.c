#include <lcom/lcf.h>
#include "video.h"
#include <liblm.h>

void mapVRAM(){

    static void *video_mem; /* frame-buffer VM address (static global variable*/ 
    int r; 
    struct minix_mem_range mr; 
    static unsigned int vram_base; /* VRAM's physical addresss */ 
    static unsigned int vram_size; /* VRAM's size, but you can use the frame-buffer size, instead */ 
    
    /* Allow memory mapping */ 
    mr.mr_base = (phys_bytes) vram_base; 
    mr.mr_limit = mr.mr_base + vram_size; 
    
    if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) 
        panic("sys_privctl (ADD_MEM) failed: %d\n", r); /* Map memory */ 
        
    video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size); 
    
    if(video_mem == MAP_FAILED) 
        panic("couldn't map video memory");

}

