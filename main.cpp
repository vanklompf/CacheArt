#include <cstdio>
#include <cxxabi.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include "PacketDescriptor.h"
#include "Utils.h"
#include "Dummy.h"

using namespace std::chrono;

static const uint64_t PACKET_BUFFER_SIZE = (uint64_t)2*1024*1024*1024;
static const int REPEAT = 50;
uint64_t antiOpt = 909;

template<typename TDescriptor>
uint64_t updateTimestamps(uint8_t* packetBuffer, int repeat)
{
	int status;
	printf("updateTimestamps for %s\n", abi::__cxa_demangle(typeid(TDescriptor).name(), NULL, NULL, &status));

	uint64_t timestamp = 0;
	uint64_t counter = 0;
	const uint8_t* packetBufferEnd = packetBuffer + PACKET_BUFFER_SIZE;


	for (int i=0; i<repeat; i++)
	{
		TDescriptor* descriptorPtr = reinterpret_cast<TDescriptor*>(packetBuffer);
		do {
			//antiOpt ^= descriptorPtr->timestampNs;
			descriptorPtr->setTimestampNs(timestamp);
            descriptorPtr->setLength(timestamp & 0xFF);
			descriptorPtr->setFlag3();

			timestamp += 10;
			descriptorPtr++;
			counter++;
		} while ((uint8_t*)descriptorPtr < packetBufferEnd);
	}

	return counter;
}


int main()
{
	printf("cache FTW\n");
	printf("PacketDescriptor size: %ld\n", sizeof(PacketDescriptor));
	printf("PacketDescriptor_reordered size: %ld\n", sizeof(PacketDescriptor_reordered));
	printf("PacketDescriptor_packed size: %ld\n", sizeof(PacketDescriptor_packed));
	printf("PacketDescriptor_taggedPointers size: %ld\n", sizeof(PacketDescriptor_taggedPointers));
    printf("PacketDescriptor_48bitPointers size: %ld\n", sizeof(PacketDescriptor_48bitPointers));



	printf("StructPadding8 size: %ld\n", sizeof(StructPadding8));
	printf("StructPadding4 size: %ld\n", sizeof(StructPadding4));
	printf("StructPadding2 size: %ld\n", sizeof(StructPadding2));

	printf("Allocating memory for packets...\n");
	uint8_t* packetBuffer = AllocateWithHugePages(PACKET_BUFFER_SIZE);
	printf("Done!\n");

	auto start = high_resolution_clock::now();
	auto packetCount = updateTimestamps<PacketDescriptor>(packetBuffer, REPEAT);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start).count();
	int kpps = packetCount / duration;
	printf("T: %d kpps\n", kpps);

	start = high_resolution_clock::now();
	packetCount = updateTimestamps<PacketDescriptor_reordered>(packetBuffer, REPEAT);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start).count();
	kpps = packetCount / duration;
	printf("T: %d kpps\n", kpps);

	start = high_resolution_clock::now();
	packetCount = updateTimestamps<PacketDescriptor_packed>(packetBuffer, REPEAT);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start).count();
	kpps = packetCount / duration;
	printf("T: %d kpps\n", kpps);

	start = high_resolution_clock::now();
	packetCount = updateTimestamps<PacketDescriptor_taggedPointers>(packetBuffer, REPEAT);
	stop = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(stop - start).count();
	kpps = packetCount / duration;
	printf("T: %d kpps\n", kpps);

    start = high_resolution_clock::now();
    packetCount = updateTimestamps<PacketDescriptor_48bitPointers>(packetBuffer, REPEAT);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start).count();
    kpps = packetCount / duration;
    printf("T: %d kpps\n", kpps);

	printf("Done! %ld\n Press any key...\n", antiOpt);

	getchar();
}
