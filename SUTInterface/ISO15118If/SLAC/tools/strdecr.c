/*====================================================================*
 *
 *   signed strdecr (void * memory, size_t extent, byte_t min, byte_t max);
 *
 *   memory.h
 *
 *   decrement a multi-byte_t memory region; start at max and reset at
 *   min; return -1 if all bytes are min;
 *
 *   Motley Tools by Charles Maier;
 *   Copyright (c) 2001-2006 by Charles Maier Associates;
 *   Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/
#ifndef STRDECR_SOURCE
#define STRDECR_SOURCE
#include "../tools/memory.h"
signed strdecr (void * memory, register size_t extent, register byte_t min, register byte_t max)
{
  register byte_t * offset = (byte_t *)(memory);
  while (extent--)
  {
    if (-- offset [extent] >= min)
    {
      return (0);
    }
    offset [extent] = max;
  }
  return (-1);
}
#endif
