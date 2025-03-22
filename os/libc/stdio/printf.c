#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}

int printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format++;

		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} else if (*format == 'd') { // int32_t
			++format;
			int n = va_arg(parameters, int);
			char num[11];
			int i = 0;
			int is_negative = 0;
		
			// Обрабатываем знак
			if (n < 0) {
				is_negative = 1;
				n = -n;
			}
		
			// Преобразуем число в строку
			if (n == 0) {
				num[i++] = '0';
			} else {
				while (n != 0) {
					num[i++] = '0' + (n % 10);
					n /= 10;
				}
			}
		
			// Добавляем знак, если нужно
			if (is_negative) {
				num[i++] = '-';
			}
		
			// Выводим в обратном порядке
			for (int j = i - 1; j >= 0; j--) {
				if (!print(&num[j], 1)) {
					return -1;
				}
			}
			written += i; // Учитываем все символы
		} else if (*format == 'l') {
            format++; // Пропускаем 'l'
            long long n = va_arg(parameters, long long);
            char num[21]; // 20 символов достаточно для long long (включая знак), +1 для безопасности
            int i = 0;
            int is_negative = 0;

            // Обрабатываем знак
            if (n < 0) {
                is_negative = 1;
                n = -n;
            }

            // Преобразуем число в строку
            if (n == 0) {
                num[i++] = '0';
            } else {
                while (n != 0) {
                    num[i++] = '0' + (n % 10);
                    n /= 10;
                }
            }

            // Добавляем знак, если нужно
            if (is_negative) {
                num[i++] = '-';
            }

            // Выводим в обратном порядке
            for (int j = i - 1; j >= 0; j--) {
                if (!print(&num[j], 1)) {
                    return -1;
                }
            }
            written += i; // Учитываем все символы 
		
		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}
