#ifndef DUMMY_H
#define DUMMY_H



struct StructPadding8
{
	uint64_t p1;
	uint8_t last;
};


struct StructPadding4
{
	uint32_t p1;
	uint32_t p2;
	uint8_t last;
};

struct StructPadding2
{
	uint16_t p1;
	uint16_t p2;
	uint16_t p3;
	uint16_t p4;
	uint8_t last;
};

#endif /* DUMMY_H */
