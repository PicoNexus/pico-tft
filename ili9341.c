/*
 * Copyright (C) 2022 Jan Hamal Dvořák <mordae@anilinux.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <tft.h>

#if TFT_DRIVER == TFT_DRIVER_ILI9341

#define WIDTH (TFT_WIDTH * TFT_SCALE)
#define HEIGHT (TFT_HEIGHT * TFT_SCALE)

void tft_preflight(void)
{
	/* 8.2.2 SWRESET: Software Reset */
	tft_control(0x01, NULL, 0);
	sleep_ms(120);

	/* 8.2.12 SLPOUT: Sleep Out */
	tft_control(0x11, NULL, 0);
	sleep_ms(120);

	/* 8.2.6 MADCTL: Memory Access Data Control */
	uint8_t madctl = (TFT_SWAP_XY << 5) | (TFT_FLIP_X << 6) | (TFT_FLIP_Y << 7) |
			 (1 << 3) /* BGR swap */;
	tft_control(0x36, &madctl, 1);

	/* 8.2.33 COLMOD: Interface Pixel Format */
	uint8_t colmod = 0x6d; /* 16 bits in 565 format */
	tft_control(0x3a, &colmod, 1);

	/* 8.2.19 DISPON: Display On */
	tft_control(0x29, NULL, 0);
	sleep_ms(120);

	/* 8.3.8 ETMOD: Entry Mode Set */
	uint8_t etmod = 0x07;
	tft_control(0xb7, &etmod, 1);

	/* 8.2.20 CASET: Column Address Set */
	uint8_t caset[] = { 0, 0, WIDTH >> 8, WIDTH & 0xff };
	tft_control(0x2a, caset, 4);

	/* 8.2.21 PASET: Page Address Set */
	uint8_t paset[] = { 0, 0, HEIGHT >> 8, HEIGHT & 0xff };
	tft_control(0x2b, paset, 4);
}

void tft_begin_sync(void)
{
	/* 8.2.22 RAMWR: Memory Write */
	tft_control(0x2c, NULL, 0);
}

#endif
