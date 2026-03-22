#include "characteristic.hpp"

namespace c7222 {

BleError Characteristic::UpdateValue() {
	return BleError::kSuccess;
}

BleError Characteristic::DispatchBleHciPacket(uint8_t packet_type,
                                              const uint8_t* packet_data,
                                              uint16_t packet_data_size) {
	(void)packet_type;
	(void)packet_data;
	(void)packet_data_size;
	return BleError::kSuccess;
}

BleError Characteristic::DispatchEvent(EventId event_id,
                                       const uint8_t* event_data,
                                       uint16_t event_data_size) {
	(void)event_id;
	(void)event_data;
	(void)event_data_size;
	return BleError::kSuccess;
}

}  // namespace c7222
