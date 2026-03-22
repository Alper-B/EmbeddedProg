#include "attribute_server.hpp"

namespace c7222 {

AttributeServer* AttributeServer::instance_ = nullptr;

BleError AttributeServer::Init(const void* context) {
	services_.clear();
	connection_handle_ = 0;
	security_level_ = 0;
	authorization_granted_ = false;
	initialized_ = false;
	if(context_ == nullptr) {
		context_ = context;
	}
	return BleError::kUnsupportedFeatureOrParameterValue;
}

void AttributeServer::SetConnectionHandle(uint16_t connection_handle) {
	connection_handle_ = connection_handle;
}

void AttributeServer::SetSecurityLevel(uint16_t connection_handle,
                                       uint8_t security_level) {
	if(connection_handle_ == connection_handle) {
		security_level_ = security_level;
	}
}

uint8_t AttributeServer::GetSecurityLevel(uint16_t connection_handle) const {
	return connection_handle_ == connection_handle ? security_level_ : 0;
}

void AttributeServer::SetAuthorizationGranted(uint16_t connection_handle,
                                              bool granted) {
	if(connection_handle_ == connection_handle) {
		authorization_granted_ = granted;
	}
}

bool AttributeServer::IsAuthorizationGranted(uint16_t connection_handle) const {
	return connection_handle_ == connection_handle ? authorization_granted_
	                                               : false;
}

}  // namespace c7222
