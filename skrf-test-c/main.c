#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#define MAVLINK_V2_STX 0xFD
#define MAVLINK_V2_HEADER_LEN 10
#define MAVLINK_V2_CRC_LEN 2

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s mavlink.bin\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        perror("Cannot open file");
        return 1;
    }

    /* determine file size */
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);
    if (fsize <= 0) {
        fprintf(stderr, "File empty or unreadable\n");
        fclose(fp);
        return 1;
    }

    uint8_t *buf = (uint8_t *)malloc((size_t)fsize);
    if (!buf) {
        fprintf(stderr, "Out of memory\n");
        fclose(fp);
        return 1;
    }

    if (fread(buf, 1, (size_t)fsize, fp) != (size_t)fsize) {
        fprintf(stderr, "File read error\n");
        free(buf);
        fclose(fp);
        return 1;
    }
    fclose(fp);

    printf("File size: %ld bytes\n\n", fsize);

    size_t count = 0;
    for (size_t i = 0; i + 2 < (size_t)fsize; ++i) {
        if (buf[i] != MAVLINK_V2_STX)
            continue;

        size_t start = i;
        uint8_t len_byte = buf[i + 1];
        size_t msg_start = i + 2;

        /* extract printable ASCII until first 0x00 */
        char text[256];
        size_t tpos = 0;
        for (size_t j = msg_start; j < (size_t)fsize; ++j) {
            if (buf[j] == 0x00 || tpos >= sizeof(text) - 1)
                break;
            if (isprint(buf[j]))
                text[tpos++] = (char)buf[j];
        }
        text[tpos] = '\0';

        /* read message id if header is complete */
        int msgid = -1;
        if (i + MAVLINK_V2_HEADER_LEN < (size_t)fsize) {
            msgid = (int)buf[i + 7]
            | ((int)buf[i + 8] << 8)
            | ((int)buf[i + 9] << 16);
        }

        printf("Offset: %6zu | LenByte: %3u | msg id: %d\n",
        start, len_byte, msgid);
        if (tpos > 0)
            printf(" text: \"%s\"\n", text);

        ++count;
    }

    printf("\nTotal segments found: %zu\n", count);
    free(buf);
    return 0;
}
