#include "json.h"

json::json(int size, ...) {
	con = "{";
	va_list va_ptr;
	va_start(va_ptr, size);
	for (int i = 0; i < size; i += 2) {
		char* k = va_arg(va_ptr, char*);
		std::string key(k);
		char* val = va_arg(va_ptr, char*);
		std::string value(val);
		con += "\"";
		con += key + "\":";
		con += value;
		if (i != size - 2) {
			con += ",";
		}
	}
	con += "}";
}

int json::getSize() {
	return con.length();
}

std::string json::getTe() {
	return con;
}