/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 hathach for Adafruit Industries
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

#ifndef MICROPY_INCLUDED_SUPERVISOR_USB_H
#define MICROPY_INCLUDED_SUPERVISOR_USB_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "supervisor/memory.h"

// Ports must call this as frequently as they can in order to keep the USB
// connection alive and responsive.  Normally this is called from background
// tasks after the USB IRQ handler is executed, but in specific circumstances
// it may be necessary to call it directly.
void usb_background(void);

// Schedule usb background
void usb_background_schedule(void);

// Ports must call this from their particular USB IRQ handler
void usb_irq_handler(int instance);

// Only inits the USB peripheral clocks and pins. The peripheral will be initialized by
// TinyUSB.
void init_usb_hardware(void);

// Temporary hook for code after init. Only used for RP2040.
void post_usb_init(void);

// Indexes and counts updated as descriptors are built.
typedef struct {
    size_t current_interface;
    size_t current_endpoint;
    size_t num_in_endpoints;
    size_t num_out_endpoints;
} descriptor_counts_t;

// Shared implementation.
bool usb_enabled(void);
void usb_add_interface_string(uint8_t interface_string_index, const char str[]);
void usb_build_descriptors(void);
void usb_disconnect(void);
void usb_init(void);
void usb_set_defaults(void);
size_t usb_boot_py_data_size(void);
void usb_get_boot_py_data(uint8_t *temp_storage, size_t temp_storage_size);
void usb_return_boot_py_data(uint8_t *temp_storage, size_t temp_storage_size);

// Further initialization that must be done with a VM present.
void usb_setup_with_vm(void);

#define MAX_INTERFACE_STRINGS 16
typedef union {
    const char *char_str;
    const uint16_t *descriptor;
} interface_string_t;
// #define COMMON_HAL_MCU_PROCESSOR_UID_LENGTH 16

extern char serial_number_hex_string[];
extern supervisor_allocation *device_descriptor_allocation;
extern supervisor_allocation *configuration_descriptor_allocation;
extern supervisor_allocation *string_descriptors_allocation;
extern interface_string_t collected_interface_strings[MAX_INTERFACE_STRINGS];
extern size_t collected_interface_strings_length;

extern int test1;
extern int test2;
extern int test3;
extern int test4;
extern int test5;
extern int test6;
extern int test7;
extern int test8;
extern int test9;
extern int test10;
extern int test11;
extern int test12;
extern int test13;
extern int test14;
extern int test15;
extern int test16;
extern int test17;
extern int test18;
extern int test19;

extern uint8_t text1[10];
extern uint8_t text2[113];
extern uint16_t text3[113];
extern uint8_t text4[10];
extern uint8_t text5[10];
extern uint8_t text6[10];
extern uint8_t text7[10];
extern uint8_t text8[10];
extern uint8_t text9[10];

// Propagate plug/unplug events to the MSC logic.
#if CIRCUITPY_USB_MSC
void usb_msc_mount(void);
void usb_msc_umount(void);
bool usb_msc_ejected(void);

// Locking MSC prevents presenting the drive on plug-in when in use by something
// else (likely BLE.)
bool usb_msc_lock(void);
void usb_msc_unlock(void);
#endif

#endif // MICROPY_INCLUDED_SUPERVISOR_USB_H
