#include <wchar.h>
#include <locale.h>
#include <stdio.h>
int main() {
	setlocale(LC_ALL, "");
	wprintf(L"%lc", L'\x25A0');
	return 0;
}
