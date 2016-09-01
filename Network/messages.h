#pragma once
#include "message.h"

namespace Network {

#define PING 0
#define PONG 1


	class GeneralMessage : public Message
	{
	public:
		GeneralMessage(const char msgtype, const std::string& body, const std::string& uuid)
		{
			message_header h;
			memcpy(&h.guid, uuid.data(), 36);
			h.type = msgtype;
			h.ttl = 1;
			h.hops = 0;
			h.length = htonl(body.length());
			m_header = h;
			malloc_payload();
			memcpy(m_payload, body.data(), body.length());
		}
	};

	class PingMessage : public Message
	{
	public:
		PingMessage(std::string uid)
		{
			message_header h;
			memcpy(&h.guid, uid.c_str(), 36);
			h.type = PING;
			h.ttl = 1;
			h.hops = 0;
			h.length = 0;
			m_header = h;
			m_payload = 0;
		}
	};

	class PongMessage : public Message
	{
	public:
		PongMessage(std::string uid)
		{
			message_header h;
			memcpy(&h.guid, uid.c_str(), 36);
			h.type = PONG;
			h.ttl = 1;
			h.hops = 0;
			h.length = 0;
			m_header = h;
			m_payload = 0;
		}
	};
}