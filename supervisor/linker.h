/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Scott Shawcroft for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// These macros are used to place code and data into different linking sections.

#ifndef MICROPY_INCLUDED_SUPERVISOR_LINKER_H
#define MICROPY_INCLUDED_SUPERVISOR_LINKER_H

#if defined(IMXRT10XX) || defined(FOMU) || defined(STM32H7) || defined(RASPBERRYPI)
#define PLACE_IN_DTCM_DATA(name) name __attribute__((section(".dtcm_data." #name)))
#define PLACE_IN_DTCM_BSS(name) name __attribute__((section(".dtcm_bss." #name)))
// Don't inline ITCM functions because that may pull them out of ITCM into other sections.
#define PLACE_IN_ITCM(name) __attribute__((section(".itcm." #name),noinline,aligned(4))) name
#else
#define PLACE_IN_DTCM_DATA(name) name
#define PLACE_IN_DTCM_BSS(name) name
#define PLACE_IN_ITCM(name) name
#endif

#endif  // MICROPY_INCLUDED_SUPERVISOR_LINKER_H
