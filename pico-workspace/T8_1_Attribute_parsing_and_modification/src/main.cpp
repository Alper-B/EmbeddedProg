/**
 * @file main.cpp
 * @brief Demonstration entry point for attribute parsing and modification.
 *
 * DISCLAIMER:
 * This file is the task template file for ELEC C7222
 * Module 8 Task 8.1: Attribute Parsing and Modification.
 * Students are expected to complete and/or modify this template according to
 * the assignment instructions.
 * NOTE: This file is for local testing only.
 */

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>

#include "attribute.hpp"
#include "attribute_ops.hpp"

static void PrintBytes(const std::vector<std::uint8_t>& bytes) {
	for(std::size_t i = 0; i < bytes.size(); ++i) {
		std::cout << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
				  << static_cast<int>(bytes[i]);
		if(i + 1 < bytes.size()) {
			std::cout << ' ';
		}
	}
	std::cout << std::dec;
}

int main() {
	auto service = c7222::Attribute::PrimaryServiceDeclaration(c7222::Uuid(0x180F), 0x0001);
	auto cccd = c7222::Attribute::ClientCharacteristicConfiguration(0x0000, 0x0004);

	const auto service_kind = ClassifyAttribute(service);
	const auto cccd_kind = ClassifyAttribute(cccd);
	const auto initial_cccd = ReadAttributeSlice(cccd, 0, 2);
	const auto status = WriteAttributeValue(cccd, {0x01, 0x00});
	const auto updated_cccd = ReadAttributeSlice(cccd, 0, 2);

	std::cout << "service kind: " << service_kind << '\n';
	std::cout << "cccd kind: " << cccd_kind << '\n';
	std::cout << "initial cccd: ";
	PrintBytes(initial_cccd);
	std::cout << '\n';
	std::cout << "write status: " << status << '\n';
	std::cout << "updated cccd: ";
	PrintBytes(updated_cccd);
	std::cout << '\n';
	return 0;
}
