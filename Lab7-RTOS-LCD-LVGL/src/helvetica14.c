/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#define LV_LVGL_H_INCLUDE_SIMPLE
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef HELVETICA14
#define HELVETICA14 1
#endif

#if HELVETICA14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0043 "C" */
    0x0, 0xe4, 0xe1, 0x82, 0x8, 0x20, 0x86, 0x14,
    0xde,

    /* U+0045 "E" */
    0x1, 0xf4, 0x10, 0x41, 0x7, 0xd0, 0x41, 0x4,
    0x1f,

    /* U+0046 "F" */
    0xfc, 0x21, 0x8, 0x7a, 0x10, 0x84, 0x20,

    /* U+004C "L" */
    0x1, 0x4, 0x10, 0x41, 0x4, 0x10, 0x41, 0x4,
    0x1f,

    /* U+004D "M" */
    0xc1, 0xe0, 0xf8, 0xf4, 0x5a, 0x2d, 0x16, 0x53,
    0x29, 0x94, 0xca, 0x62, 0x20,

    /* U+004E "N" */
    0x0, 0xc5, 0x8a, 0x95, 0x2a, 0x54, 0xa5, 0x4a,
    0x9d, 0x1a, 0x30,

    /* U+004F "O" */
    0x0, 0x71, 0x14, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x5, 0x11, 0xc0,

    /* U+0050 "P" */
    0xfa, 0x38, 0x61, 0x8f, 0xe8, 0x20, 0x82, 0x8,
    0x0,

    /* U+0052 "R" */
    0x0, 0xf9, 0x1a, 0x14, 0x28, 0xde, 0x23, 0x42,
    0x85, 0xa, 0x10,

    /* U+0053 "S" */
    0x1, 0xe8, 0xe1, 0x83, 0x3, 0x83, 0x86, 0x18,
    0xde,

    /* U+0054 "T" */
    0x1, 0xfc, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x80,

    /* U+00B0 "°" */
    0x69, 0x96
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 125, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 9, .adv_w = 112, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 99, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 112, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 174, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 78, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 125, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 112, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 90, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 6}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x2, 0x3, 0x9, 0xa, 0xb, 0xc, 0xd,
    0xf, 0x10, 0x11, 0x6d
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 67, .range_length = 110, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 12, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t helvetica14 = {
#else
lv_font_t helvetica14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if HELVETICA14*/

