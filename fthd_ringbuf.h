/*
 * Broadcom PCIe 1570 webcam driver
 *
 * Copyright (C) 2015 Sven Schnelle <svens@stackframe.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation.
 *
 */

#ifndef _FTHD_RINGBUF_H
#define _FTHD_RINGBUF_H

#define FTHD_RINGBUF_ENTRY_SIZE 64

#define FTHD_RINGBUF_ADDRESS_FLAGS 0
#define FTHD_RINGBUF_REQUEST_SIZE 4
#define FTHD_RINGBUF_RESPONSE_SIZE 8

enum ringbuf_type_t {
	RINGBUF_TYPE_H2T=0,
	RINGBUF_TYPE_T2H=1,
	RINGBUF_TYPE_UNIDIRECTIONAL,
};

struct fthd_ringbuf {
	void *doorbell;
	int idx;
};

struct fw_channel;
struct fthd_private;
extern void fthd_channel_ringbuf_dump(struct fthd_private *dev_priv, struct fw_channel *chan);
extern void fthd_channel_ringbuf_init(struct fthd_private *dev_priv, struct fw_channel *chan);
extern u32 fthd_channel_ringbuf_get_entry(struct fthd_private *, struct fw_channel *);
extern int fthd_channel_ringbuf_send(struct fthd_private *dev_priv, struct fw_channel *chan,
				     u32 data_offset, u32 request_size, u32 response_size, u32 *entry);

extern u32 fthd_channel_ringbuf_receive(struct fthd_private *dev_priv,
					struct fw_channel *chan);

extern int fthd_channel_wait_ready(struct fthd_private *dev_priv, struct fw_channel *chan, u32 entry, int timeout);
#define get_entry_addr(chan, num) chan->offset + num * FTHD_RINGBUF_ENTRY_SIZE;
#endif
