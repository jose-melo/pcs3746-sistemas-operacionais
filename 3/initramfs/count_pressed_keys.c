#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    for (;;)
    {
        switch (getchar())
        {
        case '\n':
        {
            int count = 4;
            char item[5];
            char file[] = "/sys/key_pressed/key_pressed_count";
            int fd = open(file, O_RDONLY);
            if (fd == -1)
            {
                perror("open");
                return -1;
            }

            int size = read(fd, &item, count);
            if (!size)
            {
                printf("EOF\n");
                return 0;
            }
            if (size < 0)
            {
                perror("read");
                return -1;
            }
            printf("This is written on file %s: %s\n\n", file, item);
            break;
        }

        case 'q':
        case EOF:
            return 0;
        }
    }
}
