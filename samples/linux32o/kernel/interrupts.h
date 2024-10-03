#ifndef INCLUDE_MEMORY_SEGMENTS
#define INCLUDE_MEMORY_SEGMENTS


struct GateDescriptor {
	unsigned short handlerAddressLowBits;
	unsigned short gdt_codeSegmentSelector;
	unsigned char reserved;
	unsigned char access;
	unsigned short handlerAddressHighBits;
} __attribute__((packed));


struct InterruptDescriptorTablePointer {
	unsigned short size;
	unsigned int base;
} __attribute__((packed));


typedef struct  {
	unsigned short number;
} Port;

void InstallIDT(unsigned short hardwareInterruptOffset, unsigned short CodeSegment);

unsigned int CKernelInterruptHandler(unsigned char interrupt, unsigned int esp);



#endif /* INCLUDE_MEMORY_SEGMENTS */
