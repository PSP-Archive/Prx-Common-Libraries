#include <stdio.h>

#include "font_cg.c"
#include "misaki8x8.c"
#include "font_icon.c"

int main(){
    FILE *fd;
    
    fd = fopen("cg.bin", "wb");
    fwrite(font_cg, 1, sizeof(font_cg), fd);
    fclose(fd);
    
    fd = fopen("hankaku_kana.bin", "wb");
    fwrite(font_hankaku_kana, 1, sizeof(font_hankaku_kana), fd);
    fclose(fd);
    
    fd = fopen("sjis.bin", "wb");
    fwrite(font_sjis, 1, sizeof(font_sjis), fd);
    fclose(fd);
    
    fd = fopen("icon.bin", "wb");
    fwrite(font_icon, 1, sizeof(font_icon), fd);
    fclose(fd);
    
    return 0;
}

