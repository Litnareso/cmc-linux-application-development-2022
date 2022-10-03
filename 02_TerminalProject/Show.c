#include <fcntl.h>
#include <ncurses.h>
#include "stdlib.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "unistd.h"

enum Commands
{
    C_NEXT = 32,
    C_QUIT = 27,
};

enum Args
{
    A_ARG_NUM = 2,
    A_FILE_NAME_NUM = 1,
};

enum Window
{
    W_DX = 3,
};

off_t
wfill_from_mapping(WINDOW *win, char *mapping, off_t offset, off_t eof)
{
    int cur_row = 0;
    off_t cur_offset = offset;
    char *buf = malloc(COLS - 2 * W_DX);
    while (cur_row < LINES - 2 * (W_DX + 1)) {
        if (cur_offset >= eof) {
            free(buf);
            return eof;
        }
        int cur_col = 0;
        while (cur_col < COLS - 2 * (W_DX + 1)) {
            char ch = mapping[cur_offset + cur_col];
            buf[cur_col++] = ch;
            if (ch == '\n') {
                buf[cur_col] = 0;
                break;
            }
        }
        cur_offset += cur_col;
        mvwprintw(win, ++cur_row, 1, "%s", buf);
    }
    free(buf);
    return cur_offset;
}

int
main(int argc, char **argv)
{
    if (argc < A_ARG_NUM) {
        return 0;
    }

    int fd = open(argv[A_FILE_NAME_NUM], O_RDONLY);
    if (fd == -1) {
        return 0;
    }

    struct stat buffer;
    int status = fstat(fd, &buffer);
    if (status != 0) {
        close(fd);
        return 0;
    }
    off_t size = buffer.st_size;

    void *mapping = mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapping == MAP_FAILED) {
        close(fd);
        return 0;
    }

    initscr();
    noecho();
    cbreak();
    printw("File: %s; size: %jd", argv[A_FILE_NAME_NUM], (intmax_t)size);
    refresh();

    WINDOW *win;
    int c = 0;
    win = newwin(LINES - 2 * W_DX, COLS - 2 * W_DX, W_DX, W_DX);
    keypad(win, TRUE);
    scrollok (win, TRUE);
    box(win, 0, 0);

    off_t offset = 0;
    off_t new_offset = 0;

    do {
        if (c == C_NEXT && new_offset < size) {
            offset = new_offset;
        }
        werase(win);
        new_offset = wfill_from_mapping(win, mapping, offset, size);
        box(win, 0, 0);
        wrefresh(win);
    } while((c = wgetch(win)) != C_QUIT);
    endwin();

    munmap(mapping, size);

    close(fd);
    return 0;
}
