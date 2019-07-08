#ifndef PACKET_DESCRIPTOR_H
#define PACKET_DESCRIPTOR_H

#include <cstdint>

struct PacketDescriptor
{
	uint8_t txPort;
	uint64_t timestampNs;
	uint16_t length;
	uint64_t* auxData;
	uint8_t flag1:1;
	uint8_t flag2:1;
	uint8_t flag3:1;
	uint64_t userData;

	inline void setTimestampNs(uint64_t _timestampNs)
    {
        timestampNs = _timestampNs;
    }

    inline void setLength(uint16_t _length)
    {
        length = _length;
    }

    inline void setFlag3()
    {
        flag3 = 1;
    }
};

struct PacketDescriptor_reordered
{
	uint64_t timestampNs;
	uint64_t userData;
	uint64_t* auxData;

	uint16_t length:13;
	uint16_t flag1:1;
	uint16_t flag2:1;
	uint16_t flag3:1;

	uint8_t txPort:3;

    inline void setTimestampNs(uint64_t _timestampNs)
    {
        timestampNs = _timestampNs;
    }

    inline void setLength(uint16_t _length)
    {
        length = _length;
    }

    inline void setFlag3()
    {
        flag3 = 1;
    }
};

struct PacketDescriptor_packed
{
	uint64_t timestampNs;
	uint64_t userData;
	uint64_t* auxData;

	uint16_t length:13;
	uint16_t flag1:1;
	uint16_t flag2:1;
	uint16_t flag3:1;

	uint8_t txPort:3;

    inline void setTimestampNs(uint64_t _timestampNs)
    {
        timestampNs = _timestampNs;
    }

    inline void setLength(uint16_t _length)
    {
        length = _length;
    }

    inline void setFlag3()
    {
        flag3 = 1;
    }
} __attribute__ ((__packed__));

struct PacketDescriptor_taggedPointers
{
	uint64_t timestampNs;
	uint64_t userData;
	union
	{
		uint64_t* auxData;
		uintptr_t txPort; //3 bits;
	} tiny;

	uint16_t length:13;
	uint16_t flag1:1;
	uint16_t flag2:1;
	uint16_t flag3:1;

    inline void setTimestampNs(uint64_t _timestampNs)
    {
        timestampNs = _timestampNs;
    }

    inline void setLength(uint16_t _length)
    {
        length = _length;
    }

    inline void setFlag3()
    {
        flag3 = 1;
    }
} __attribute__ ((__packed__));

struct PacketDescriptor_48bitPointers
{
    uint64_t timestampNs;
    uint64_t userData;

    // 3bit flags | 13bit length | 45 bit ptr | 3 bit txPort = 64 bits
    uintptr_t _data;

    inline void setTimestampNs(uint64_t _timestampNs)
    {
        timestampNs = _timestampNs;
    }

    inline void setLength(uint16_t _length)
    {
        _data |= static_cast<uintptr_t>(_length) << 51;
    }

    inline void setFlag3()
    {
        _data |= 1ul << 48;
    }
} __attribute__ ((__packed__));
#endif /* PACKET_DESCRIPTOR_H */
