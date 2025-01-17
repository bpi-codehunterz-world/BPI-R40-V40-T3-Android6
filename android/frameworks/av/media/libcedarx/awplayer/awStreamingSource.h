/*
 * Copyright (c) 2008-2016 Allwinner Technology Co. Ltd.
 * All rights reserved.
 *
 * File : awStreamingSource.h
 *
 * Description : streaming source
 * History :
 *
 */

#ifndef AW_STREAMING_SOURCE_H
#define AW_STREAMING_SOURCE_H
#include <CdxStream.h>
#include "awStreamListener.h"
CdxStreamT *StreamingSourceOpen(const sp<IStreamSource> &source,
        size_t numBuffer, size_t bufferSize);
#endif  // AW_STREAMING_SOURCE_H

