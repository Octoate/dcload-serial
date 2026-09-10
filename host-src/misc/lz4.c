/*
 * This file is part of the dcload Dreamcast serial loader
 *
 * Andrew Kieschnick <andrewk@napalm-x.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "lz4.h"
#include "lz4hc.h"

void usage(void) {
    printf("usage: lz4 <in> <out>\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    int in, out;
    char *data;
    char *cdata;
    int clength;
    size_t length;
    int max_dst_size;

    if(argc != 3)
        usage();

    in = open(argv[1], O_RDONLY);

    if(in < 0) {
        perror(argv[1]);
        exit(1);
    }

    out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(out < 0) {
        perror(argv[2]);
        exit(1);
    }

    length = lseek(in, 0, SEEK_END);
    lseek(in, 0, SEEK_SET);

    max_dst_size = LZ4_compressBound((int)length);

    data = malloc(length);
    cdata = malloc(max_dst_size);

    if(!data || !cdata) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    if(read(in, data, length) != (ssize_t)length) {
        perror("read");
        exit(1);
    }

    clength = LZ4_compress_HC(data, cdata, (int)length, max_dst_size, LZ4HC_CLEVEL_MAX);
    if(clength > 0) {
        printf("compressed %lu bytes into %d bytes\n",
                (unsigned long) length, clength);
    }
    else {
        /* this should NEVER happen */
        printf("internal error - compression failed: %d\n", clength);
        return 2;
    }

    /* check for an incompressible block */
    if((size_t)clength >= length) {
        printf("This block contains incompressible data.\n");
        return 0;
    }

    if(write(out, cdata, clength) != clength) {
        perror("write");
        exit(1);
    }

    close(in);
    close(out);
    free(data);
    free(cdata);
    exit(0);
}
