#include <string.h>

#include "esp_log.h"

#include "plankton.h"

#define swap(x,y) do \
    { unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
        memcpy(swap_temp,&y,sizeof(x)); \
        memcpy(&y,&x,       sizeof(x)); \
        memcpy(&x,swap_temp,sizeof(x)); \
    } while (0)

#define PLN_HAS_LL_HLINE /* TODO, these should come from config. */
#define PLN_HAS_LL_VLINE
#define PLN_HAS_LL_BITMAP

static const char *TAG = "plankton";

void pln_put_pixel(uint16_t x1, uint16_t y1, uint16_t colour)
{
    if((x1 < 320) && (y1 < 240)) {
        pln_ll_put_pixel(x1, y1, colour);
    }
}

/* https://github.com/jb55/bresenham-line.c/blob/master/bresenham_line.c */

void pln_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour)
{
	int16_t dx;
    int16_t sx;
    int16_t dy;
    int16_t sy;
    int16_t err;
    int16_t e2;

	dx = ABS(x2 - x1);
	sx = x1 < x2 ? 1 : -1;
	dy = ABS(y2 - y1);
	sy = y1 < y2 ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;

	while (1) {
		pln_ll_put_pixel(x1, y1, colour);

		if (x1 == x2 && y1 == y2) {
            break;
        };

		e2 = err;

		if (e2 > -dx) {
			err -= dy;
			x1 += sx;
		}

		if (e2 < dy) {
			err += dx;
			y1 += sy;
		}
	}
}

