/*====================================================================*
 *
 *   Copyright (c) 2013 Qualcomm Atheros, Inc.
 *
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted (subject to the limitations
 *   in the disclaimer below) provided that the following conditions
 *   are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials
 *     provided with the distribution.
 *
 *   * Neither the name of Qualcomm Atheros nor the names of
 *     its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.
 *
 *   NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
 *   GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE
 *   COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 *   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 *   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *   NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 *   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *--------------------------------------------------------------------*/
/*====================================================================*
 *
 *   config.c - configuration config_file reader;
 *
 *   configuration files contain named parts where each part may
 *   contain one of more named items that have text definitions;
 *
 *   the named config_file can be searched for the first occurance of a
 *   named part then the first occurance of a named item;
 *
 *   [part1]
 *   item1=text
 *   item2=text
 *
 *   [part2]
 *   item1=text
 *   item2=text
 *
 *--------------------------------------------------------------------*/
#ifndef CONFIG_SOURCE
#define CONFIG_SOURCE
/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/
#include "../tools/config.h"
#include "../tools/types.h"
#include "../tools/chars.h"
/*====================================================================*
 *   program variables;
 *--------------------------------------------------------------------*/
static char glb_buffer [1024] = "";
static signed glb_file_char;
/*====================================================================*
 *
 *   bool compare (FILE * fp, char const *sp);
 *
 *   compare file and text characters until they differ or until end
 *   of text, line or file occurs; a match is declared when the text
 *   ends before the line or file;
 *
 *   spaces and tabs within the argument string or file string are
 *   ignored such that "item1", " item1 " and "item 1" all match;
 *
 *--------------------------------------------------------------------*/
static bool compare (FILE * fp, char const * sp)
{
  while (isblank (*sp))
  {
    sp++;
  }
  while ((*sp) && (glb_file_char != '\n') && (glb_file_char != EOF))
  {
    // compare text with input part
    if (toupper (glb_file_char) != toupper (*sp))
    {
      return (0);
    }
    do
    {
      sp++;
    }
    while (isblank (*sp));
    do
    {
      glb_file_char = getc (fp);
    }
    while (isblank (glb_file_char));
  }
  return (!*sp);
}
/*====================================================================*
 *
 *   void collect (FILE * fp);
 *
 *   collect text to end of line; remove leading and trailing space
 *   but preserve embedded space; replace selected escape sequences;
 *
 *--------------------------------------------------------------------*/
static void collect (FILE * fp)
{
  char *bp = glb_buffer;
  char *cp = glb_buffer;
  while ((glb_file_char != ';') && (glb_file_char != '\n') && (glb_file_char != EOF))
  {
    if (glb_file_char == '\\')
    {
      glb_file_char = getc (fp);
      if (glb_file_char == 'n')
      {
        glb_file_char = '\n';
      }
      if (glb_file_char == 't')
      {
        glb_file_char = '\t';
      }
    }
    if ((cp - glb_buffer) < (signed)(sizeof (glb_buffer) - 1))
    {
      *cp++ = glb_file_char;
    }
    if (!isblank (glb_file_char))
    {
      bp = cp;
    }
    glb_file_char = getc (fp);
  }
  *bp = '\0';
  return;
}
/*====================================================================*
 *
 *   void discard (FILE * fp);
 *
 *   read and discard characters until end-of-line or end-of-file
 *   is detected; read the first character of next line if end of
 *   file has not been detected;
 *
 *--------------------------------------------------------------------*/
static void discard (FILE * fp)
{
  while ((glb_file_char != '\n') && (glb_file_char != EOF))
  {
    glb_file_char = getc (fp);
  }
  if (glb_file_char != EOF)
  {
    glb_file_char = getc (fp);
  }
  return;
}
/*====================================================================*
 *
 *   Const char * configstring (char const * file, char const * part, char const * item, char const * text)
 *
 *   open the named file, locate the named part and return the named
 *   item text, if present; return alternative text if the file part
 *   or item is missing; the calling function must preserve returned
 *   text because it may be over-written on successive calls;
 *
 *--------------------------------------------------------------------*/
char const * configstring (char const * config_file, char const * part, char const * item, char const * text)
{
  FILE *fp;
  if ((!config_file) || (!part) || (!item))
  {
    return (text);
  }
  if ((fp = fopen (config_file, "rb")))
  {
    // read line until end of file (discar = clear remaining char in line)
    for (glb_file_char = getc (fp); glb_file_char != EOF; discard (fp))
    {
      // clear blank char
      while (isblank (glb_file_char))
      {
        glb_file_char = getc (fp);
      }
      // if glb_file_char not [ skip
      if (glb_file_char != '[')
      {
        // continue = discard line
        continue;
      }
      do
      {
        glb_file_char = getc (fp);
      }
      while (isblank (glb_file_char));
      // compare if string after [ is specific part <default>
      if (!compare (fp, part))
      {
        // return false = discard
        continue;
      }
      if (glb_file_char != ']')
      {
        // if glb_file_char not ] of [default] then discard line
        continue;
      }
      for (discard (fp); (glb_file_char != '[') && (glb_file_char != EOF); discard (fp))
      {
        while (isblank (glb_file_char))
        {
          glb_file_char = getc (fp);
        }
        if (glb_file_char == ';')
        {
          continue;
        }
        // read text and compare with item (discard blank char)
        if (!compare (fp, item))
        {
          continue;
        }
        // detect equal sign
        if (glb_file_char != '=')
        {
          continue;
        }
        // clear blank
        do
        {
          glb_file_char = getc (fp);
        }
        while (isblank (glb_file_char));
        // colect value
        collect (fp);
        // dupplicate string return to text
        // free() <-
        text = strdup (glb_buffer);
        break;
      }
      break;
    }
    fclose (fp);
  }
  return (text);
}
/*====================================================================*
 *
 *   unsigned confignumber (char const * config_file, char const * part, char const * item, unsigned number)
 *
 *   open the named config_file, locate the named part and return the named
 *   item as an unsigned integer, if present; return a default number
 *   if the config_file, part or item is missing;
 *
 *--------------------------------------------------------------------*/
unsigned confignumber (char const * config_file, char const * part, char const * item, unsigned number)
{
  unsigned value = 0;
  char const * string = configstring (config_file, part, item, "");
  if ((string) && (* string))
  {
    while (isdigit (* string))
    {
      value *= 10;
      value += * string++ - '0';
    }
    if (! (* string))
    {
      number = value;
    }
  }
  return (number);
}
/*====================================================================*
 *
 *   unsigned confignumber_range (char const * config_file, char const * part, char const * item, unsigned number, unsigned min, unsigned max)
 *
 *   open the named config_file, locate the named part and return the named
 *   item as an unsigned integer, if present; return a default number
 *   if the config_file, part or item is missing or item is out of range;
 *
 *--------------------------------------------------------------------*/
unsigned confignumber_range (char const * config_file, char const * part, char const * item, unsigned number, unsigned min, unsigned max)
{
  unsigned value = 0;
  char const * string = configstring (config_file, part, item, "");
  if ((string) && (* string))
  {
    while (isdigit (* string))
    {
      value *= 10;
      value += * string++ - '0';
    }
    if ((*string))
    {
      if ((value >= min) && (value <= max))
      {
        number = value;
      }
    }
  }
  return (number);
}
/*====================================================================*
 *
 *   int main (int argc, char const * argv []);
 *
 *   demo/test program; arguments are config_file, part, item and text in
 *   that order; you can construct your own configuration config_file and
 *   observe behaviour;
 *
 *--------------------------------------------------------------------*/
#if 0
#include <stdio.h>
int main (int argc, char const * argv [])
{
  char const * text = configstring (argv [1], argv [2], argv [3], argv [4]);
  printf ("config_file=[%s] part=[%s] item=[%s] text=[%s]\n", argv [1], argv [2], argv [3], text);
  return (0);
}
#endif
/*====================================================================*
 *
 *--------------------------------------------------------------------*/
#endif
