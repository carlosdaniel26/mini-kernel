#define WHITE_TXT 15
#define BLACK_TXT 0

#define VIDEO_MEM_START 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define VIDEO_MEM_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT * 2)


void k_clear_screen() {
    char *vidmem = (char *) VIDEO_MEM_START;
    for (unsigned int i = 0; i < VIDEO_MEM_SIZE; i += 2) {
        vidmem[i] = ' ';
        vidmem[i + 1] = WHITE_TXT;
    }
}


unsigned int k_printf(char *message, unsigned int line) {
    char *vidmem = (char *) VIDEO_MEM_START;
    unsigned int i = (line * SCREEN_WIDTH * 2);

    while (*message != 0) {
        if (*message == '\n') {
            line++;
            i = (line * SCREEN_WIDTH * 2);
            message++;
        } else {
            vidmem[i] = *message;
            message++;
            i++;
            vidmem[i] = WHITE_TXT;
            i++;
        }
    }

    return 1;
}
