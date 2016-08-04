#include "utility.h"

void color_printf(int brightness, int foreground, int background, char *label_text, char *format, ...){
	char *color_label = (char *)malloc(28 + strlen(label_text)); // »Ý­n°t¸m¥¢±Ñ¨Ò¥~ª¬ªp
	sprintf(color_label, "ansicon -E [%d;%d;%dm%s:[0m ", brightness, foreground, background, label_text);
	system(color_label);

	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}
