/*
 * Copyright (c) 2008-2016 Allwinner Technology Co. Ltd.
 * All rights reserved.
 *
 * File : libSurface.h
 * Description : libSurface
 * History :
 *
 */

#ifndef _LIBSURFACE_H_
#define _LIBSURFACE_H_
#ifdef __cplusplus
extern "C"
{
#endif

int sw_surface_init();

void sw_surface_exit();

void* swgetSurface();

void* swget_VideoSurface();

#ifdef __cplusplus
}
#endif

#endif //_LIBSURFACE_H_
