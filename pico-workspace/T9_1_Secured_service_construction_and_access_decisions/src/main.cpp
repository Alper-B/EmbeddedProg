/**
 * @file main.cpp
 * @brief Small driver program for Module 9 Task 9.1.
 *
 * This file exercises the secured service-builder template so the created
 * service and access-decision helpers can also be inspected outside the
 * automated tests.
 */

#include <iomanip>
#include <iostream>
#include <vector>

#include "service_builder.hpp"

namespace {
/**
 * @brief Print the current value bytes of one characteristic.
 *
 * This helper is only used by the small template driver program in this file.
 *
 * @param characteristic Characteristic whose stored value bytes are printed.
 */
void PrintBytes(const c7222::Characteristic& characteristic) {
	const auto* data = characteristic.GetValueData();
	const auto size = characteristic.GetValueSize();

	std::cout << "  value=";
	for(std::size_t i = 0; i < size; ++i) {
		std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0')
		          << static_cast<int>(data[i]) << ' ';
	}
	std::cout << std::dec << '\n';
}
}  // namespace

/**
 * @brief Exercise the secured service-builder template from the command line.
 *
 * The program constructs the secured custom service, prints its basic layout,
 * lists the protected value handles, and evaluates two example access checks.
 *
 * @return ``0`` after the template inspection output has been printed.
 */
int main() {
	auto service = CreateSecureBoardStatusService();

	std::cout << "Service UUID: " << service.GetUuid() << '\n';
	std::cout << "Service declaration handle: 0x" << std::hex
	          << service.GetDeclarationHandle() << std::dec << '\n';
	std::cout << "Characteristic count: " << service.GetCharacteristicCount()
	          << '\n';

	for(const auto& characteristic : service.GetCharacteristics()) {
		std::cout << "Characteristic UUID: " << characteristic.GetUuid() << '\n';
		std::cout << "  declaration handle=0x" << std::hex
		          << characteristic.GetDeclarationHandle() << '\n';
		std::cout << "  value handle=0x" << characteristic.GetValueHandle()
		          << std::dec << '\n';
		PrintBytes(characteristic);
	}

	std::cout << "Protected value handles:";
	for(const auto handle : CollectProtectedValueHandles(service)) {
		std::cout << " 0x" << std::hex << handle;
	}
	std::cout << std::dec << '\n';

	std::cout << "Button Count read at level 0: "
	          << static_cast<int>(EvaluateReadAccess(service,
	                                                c7222::Uuid(0xFFF2),
	                                                0,
	                                                false))
	          << '\n';
	std::cout << "Control Mode write at level 2 without authorization: "
	          << static_cast<int>(EvaluateWriteAccess(service,
	                                                 c7222::Uuid(0xFFF3),
	                                                 2,
	                                                 false))
	          << '\n';

	return 0;
}
