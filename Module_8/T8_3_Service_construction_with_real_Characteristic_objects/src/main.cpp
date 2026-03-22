#include <iomanip>
#include <iostream>
#include <vector>

#include "service_builder.hpp"

namespace {
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

int main() {
	auto service = CreateBoardStatusService();

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

	std::cout << "Value handles:";
	for(const auto handle : CollectValueHandles(service)) {
		std::cout << " 0x" << std::hex << handle;
	}
	std::cout << std::dec << '\n';

	const bool updated =
		UpdateCharacteristicValue(service, c7222::Uuid(0xFFF2), {0x05, 0x00});
	std::cout << "Button Count update success: " << std::boolalpha << updated
	          << '\n';

	return 0;
}
