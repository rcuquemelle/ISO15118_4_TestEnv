/*====================================================================*
 *
 *   signed strincr (void * memory, size_t extent, byte_t min, byte_t max);
 *
 *   memory.h
 *
 *   increment a multi-byte_t memory region; start at min and reset at
 *   max; return -1 if all bytes are max;
 *
 *   Motley Tools by Charles Maier;
 *   Copyright (c) 2001-2006 by Charles Maier Associates;
 *   Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/
#ifndef STRINCR_SOURCE
#define STRINCR_SOURCE
#include "../tools/memory.h"
signed strincr (void * memory, register size_t extent, register byte_t min, register byte_t max)
{
  register byte_t * offset = (byte_t *)(memory);
  while (extent--)
  {
    if (++ offset [extent] <= max)
    {
      return (0);
    }
    offset [extent] = min;
  }
  return (-1);
}
#endif
