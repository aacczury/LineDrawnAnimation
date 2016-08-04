#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

// color_printf
enum{
	c_dark,
	c_bright
};

enum{
	f_black = 30,
	f_red,
	f_green,
	f_yellow,
	f_blue,
	f_pink,
	f_cyan,
	f_white
};

enum{
	b_black = 40,
	b_red,
	b_green,
	b_yellow,
	b_blue,
	b_pink,
	b_cyan,
	b_white
};

void color_printf(int brightness, int foreground, int background, char *label_text, char *format, ...);

#endif

