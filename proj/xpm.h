#pragma once

void draw_xpm(int x, int y, uint16_t *sprite, xpm_image_t img, const uint16_t transp){
    int h_res = get_h_res();
    void *video_mem = get_video_mem();

    for (int i = x; i < x + img.height; i++){
        for (int j = y; j < y + img.width; j++) {
            uint16_t *ptr_VM = (uint16_t*)video_mem;
            ptr_VM += (i * h_res + j);
            if(*sprite != transp)
                *ptr_VM = *sprite;
            sprite++;
        }
    }
}

