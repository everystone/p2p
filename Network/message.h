#pragma once
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <iostream>

namespace Network {
	class Message;
	typedef boost::shared_ptr<Message> message_ptr;

	struct message_header {
		char    guid[36];
		char    type;
		char    ttl;
		char    hops;
		boost::uint32_t length;
	};

	class Message
	{
	public:
		Message()
			:m_payload(0) {}

		Message(const message_header& header) {
			m_header = header;
		}
		~Message() {
			if (m_payload) {
				free(m_payload);
			}
		}

		virtual const std::string str() const
		{
			std::ostringstream os;
			os << "[Msg type:" << (int)type()
				<< " ttl:" << (int)ttl()
				<< " hops:" << (int)hops()
				<< " length:" << (int)length()
				<< " guid:" << guid() << "]";
			return os.str();
		}

		virtual message_header& header() { return m_header; }
		virtual const char type() const { return m_header.type; }
		virtual const short ttl() const { return m_header.ttl; }
		virtual const short hops() const { return m_header.hops; }
		virtual const boost::uint32_t length() const { return ntohl(m_header.length); }
		virtual const std::string& guid() const
		{
			if (m_guid.empty())
			{
				m_guid = std::string(m_header.guid, 36);
			}
			return m_guid;
		}
		// payload, binary ?
		virtual const char * payload() const { return m_payload; }
		virtual char * payload() { return m_payload; }

		/// sucks to have to do this really, jsonspirit needs a string or stream:
		virtual std::string payload_str() const
		{
			std::string s(m_payload, length());
			return s;
		}

		virtual size_t malloc_payload()
		{
			if (length() == 0) return 0;
			free(m_payload);
			m_payload = (char*)malloc(length());
			return length();
		}

		virtual const boost::asio::mutable_buffer payload_buffer() const
		{
			return boost::asio::buffer(m_payload, length());
		}

		virtual std::vector<boost::asio::const_buffer> to_buffers() const
		{
			std::vector<boost::asio::const_buffer> buffers;
			buffers.push_back(boost::asio::buffer(
				(char*)&m_header, sizeof(message_header)));
			if (length())
			{
				buffers.push_back(boost::asio::buffer(m_payload, length()));
			}

			return buffers;
		}


	protected:
		message_header m_header;
		mutable std::string m_guid;
		char * m_payload;
	};

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

}