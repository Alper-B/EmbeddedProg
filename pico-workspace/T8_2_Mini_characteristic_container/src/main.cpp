/**
 * @file main.cpp
 * @brief Demonstration entry point for the mini characteristic container task.
 */

#include <cstdint>
#include <iomanip>
#include <iostream>

#include "mini_characteristic.hpp"

static void PrintBytes(const c7222::Attribute& attr) {
	const auto* data = attr.GetValueData();
	const auto size = attr.GetValueSize();
	for(std::size_t i = 0; i < size; ++i) {
		std::cout << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
				  << static_cast<int>(data[i]);
		if(i + 1 < size) {
			std::cout << ' ';
		}
	}
	std::cout << std::dec;
}

int main() {
	MiniCharacteristic ch(c7222::Uuid(0x2A19), 0x0002, 0x0003, true, "Battery Level");
	ch.SetValue({85});

	std::cout << "attribute count: " << ch.GetAllAttributes().size() << '\n';
	std::cout << "declaration handle: 0x" << std::hex << std::setw(4) << std::setfill('0')
			  << ch.GetDeclarationAttribute().GetHandle() << std::dec << '\n';
	std::cout << "value bytes: ";
	PrintBytes(ch.GetValueAttribute());
	std::cout << '\n';
	if(const auto* cccd = ch.GetCccdAttribute()) {
		std::cout << "cccd handle: 0x" << std::hex << std::setw(4) << std::setfill('0')
				  << cccd->GetHandle() << std::dec << '\n';
	}
	return 0;
}
