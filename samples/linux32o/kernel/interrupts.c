#include "interrupts.h"

#define INTERRUPT_GATE_COUNT 256
#define IDT_INTERRUPT_GATE  0xE
#define HW_INTERRUPT_OFFSET  0x20


void kernelPrint(const char *str, unsigned int value);
void kernelPrintInt(int value);

static void print(const char *str) {
	unsigned int size = 0;
	while (str[size++] != '\0');
	kernelPrint(str, size);
}

extern void InterruptIgnore();


extern void HandleInterruptRequest0x00();
extern void HandleInterruptRequest0x01();
extern void HandleInterruptRequest0x02();
extern void HandleInterruptRequest0x03();
extern void HandleInterruptRequest0x04();
extern void HandleInterruptRequest0x05();
extern void HandleInterruptRequest0x06();
extern void HandleInterruptRequest0x07();
extern void HandleInterruptRequest0x08();
extern void HandleInterruptRequest0x09();
extern void HandleInterruptRequest0x0A();
extern void HandleInterruptRequest0x0B();
extern void HandleInterruptRequest0x0C();
extern void HandleInterruptRequest0x0D();
extern void HandleInterruptRequest0x0E();
extern void HandleInterruptRequest0x0F();
extern void HandleInterruptRequest0x31();

extern void HandleInterruptRequest0x80();

extern void HandleException0x00();
extern void HandleException0x01();
extern void HandleException0x02();
extern void HandleException0x03();
extern void HandleException0x04();
extern void HandleException0x05();
extern void HandleException0x06();
extern void HandleException0x07();
extern void HandleException0x08();
extern void HandleException0x09();
extern void HandleException0x0A();
extern void HandleException0x0B();
extern void HandleException0x0C();
extern void HandleException0x0D();
extern void HandleException0x0E();
extern void HandleException0x0F();
extern void HandleException0x10();
extern void HandleException0x11();
extern void HandleException0x12();
extern void HandleException0x13();


static struct GateDescriptor idt[INTERRUPT_GATE_COUNT]; 
static Port picMasterCmd = {0x20};
static Port picMasterData = {0x21};
static Port picSlaveCmd = {0xA0};
static Port picSlaveData = {0xA1};
static Port kbdCmd = {0x64};
static Port kbdData = {0x60};

static unsigned short hwInterruptOffset;
static unsigned char isInterruptActive = 0;

static inline void write8(Port port, unsigned char data) {
	__asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (port.number));
}

static inline unsigned char read8(Port port) {
	unsigned char data = 0;
	__asm__ volatile("inb %1, %0" : "=a" (data) : "Nd" (port.number));
	return data;
}

static void installKeyboard() {
	
	while(read8(kbdCmd) & 0x1)
        read8(kbdData);
	
	write8(kbdCmd, 0xAE);
	write8(kbdCmd, 0x20);
	unsigned char status = (read8(kbdData) | 1) & ~0x10;
	write8(kbdCmd, 0x60);
	write8(kbdData, status);
	write8(kbdData, 0xF4);
}

static void setTableEntry(unsigned char interrupt,
    unsigned short CodeSegment, void (*handler)(), 
    unsigned char DescriptorPrivilegeLevel, unsigned char DescriptorType)
{
    // address of pointer to code segment (relative to global descriptor table)
    // and address of the handler (relative to segment)
    idt[interrupt].handlerAddressLowBits = ((unsigned int) handler) & 0xFFFF;
    idt[interrupt].handlerAddressHighBits = (((unsigned int) handler) >> 16) & 0xFFFF;
    idt[interrupt].gdt_codeSegmentSelector = CodeSegment;

    const unsigned char IDT_DESC_PRESENT = 0x80;
    idt[interrupt].access = IDT_DESC_PRESENT | ((DescriptorPrivilegeLevel & 3) << 5) | DescriptorType;
    idt[interrupt].reserved = 0;
}

void InstallIDT(unsigned short hardwareInterruptOffset, unsigned short CodeSegment) {
	print("Installing IDT...");
	
	hwInterruptOffset = hardwareInterruptOffset;
	
	asm("cli");
	
    for(unsigned char i = 255; i > 0; --i) {
        setTableEntry(i, CodeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
    }
    //setTableEntry(0, CodeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
    
    setTableEntry(0x00, CodeSegment, &HandleException0x00, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x01, CodeSegment, &HandleException0x01, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x02, CodeSegment, &HandleException0x02, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x03, CodeSegment, &HandleException0x03, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x04, CodeSegment, &HandleException0x04, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x05, CodeSegment, &HandleException0x05, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x06, CodeSegment, &HandleException0x06, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x07, CodeSegment, &HandleException0x07, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x08, CodeSegment, &HandleException0x08, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x09, CodeSegment, &HandleException0x09, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x0A, CodeSegment, &HandleException0x0A, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x0B, CodeSegment, &HandleException0x0B, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x0C, CodeSegment, &HandleException0x0C, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x0D, CodeSegment, &HandleException0x0D, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x0E, CodeSegment, &HandleException0x0E, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x0F, CodeSegment, &HandleException0x0F, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x10, CodeSegment, &HandleException0x10, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x11, CodeSegment, &HandleException0x11, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x12, CodeSegment, &HandleException0x12, 0, IDT_INTERRUPT_GATE);
    setTableEntry(0x13, CodeSegment, &HandleException0x13, 0, IDT_INTERRUPT_GATE);

    setTableEntry(hardwareInterruptOffset + 0x00, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x01, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x02, CodeSegment, &HandleInterruptRequest0x02, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x03, CodeSegment, &HandleInterruptRequest0x03, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x04, CodeSegment, &HandleInterruptRequest0x04, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x05, CodeSegment, &HandleInterruptRequest0x05, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x06, CodeSegment, &HandleInterruptRequest0x06, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x07, CodeSegment, &HandleInterruptRequest0x07, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x08, CodeSegment, &HandleInterruptRequest0x08, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x09, CodeSegment, &HandleInterruptRequest0x09, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x0A, CodeSegment, &HandleInterruptRequest0x0A, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x0B, CodeSegment, &HandleInterruptRequest0x0B, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x0C, CodeSegment, &HandleInterruptRequest0x0C, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x0D, CodeSegment, &HandleInterruptRequest0x0D, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x0E, CodeSegment, &HandleInterruptRequest0x0E, 0, IDT_INTERRUPT_GATE);
    setTableEntry(hardwareInterruptOffset + 0x0F, CodeSegment, &HandleInterruptRequest0x0F, 0, IDT_INTERRUPT_GATE);

    setTableEntry(0x80, CodeSegment, &HandleInterruptRequest0x80, 0, IDT_INTERRUPT_GATE);
	

	write8(picMasterCmd, 0x11);
	write8(picSlaveCmd, 0x11);
	
	write8(picMasterData, hardwareInterruptOffset);
	write8(picSlaveData, hardwareInterruptOffset+8);

	write8(picMasterData, 0x04);
	write8(picSlaveData, 0x02);
	
	write8(picMasterData, 0x01);
	write8(picSlaveData, 0x01);
    
    write8(picMasterData, 0x00);
	write8(picSlaveData, 0x00);


	installKeyboard();
	
	struct InterruptDescriptorTablePointer idt_pointer;
    idt_pointer.size  = 256*sizeof(struct GateDescriptor) - 1;
    idt_pointer.base  = (unsigned int)idt;
    asm volatile("lidt %0" : : "m" (idt_pointer));
	
	
	isInterruptActive = 1;
	print("interrupts active.");
}

static void onKeyDown(char c) {
	print(&c);
}

unsigned int CKernelInterruptHandler(unsigned char interrupt, unsigned int esp) {
	
	//if (!isInterruptActive)
	//	return esp;
	
	//print("InterruptHandler:"); kernelPrintInt(interrupt); print(","); kernelPrintInt(esp);
	
	
	switch (interrupt) {
		case 0x21: 
			unsigned char key = read8(kbdData);
			if(key < 0x80) {
				switch(key) {
					case 0x02: onKeyDown('1'); break;
					case 0x03: onKeyDown('2'); break;
					case 0x04: onKeyDown('3'); break;
					case 0x05: onKeyDown('4'); break;
					case 0x06: onKeyDown('5'); break;
					case 0x07: onKeyDown('6'); break;
					case 0x08: onKeyDown('7'); break;
					case 0x09: onKeyDown('8'); break;
					case 0x0A: onKeyDown('9'); break;
					case 0x0B: onKeyDown('0'); break;
					case 0x10: onKeyDown('q'); break;
					case 0x11: onKeyDown('w'); break;
					case 0x12: onKeyDown('e'); break;
					case 0x13: onKeyDown('r'); break;
					case 0x14: onKeyDown('t'); break;
					case 0x15: onKeyDown('z'); break;
					case 0x16: onKeyDown('u'); break;
					case 0x17: onKeyDown('i'); break;
					case 0x18: onKeyDown('o'); break;
					case 0x19: onKeyDown('p'); break;
					case 0x1E: onKeyDown('a'); break;
					case 0x1F: onKeyDown('s'); break;
					case 0x20: onKeyDown('d'); break;
					case 0x21: onKeyDown('f'); break;
					case 0x22: onKeyDown('g'); break;
					case 0x23: onKeyDown('h'); break;
					case 0x24: onKeyDown('j'); break;
					case 0x25: onKeyDown('k'); break;
					case 0x26: onKeyDown('l'); break;
					case 0x2C: onKeyDown('y'); break;
					case 0x2D: onKeyDown('x'); break;
					case 0x2E: onKeyDown('c'); break;
					case 0x2F: onKeyDown('v'); break;
					case 0x30: onKeyDown('b'); break;
					case 0x31: onKeyDown('n'); break;
					case 0x32: onKeyDown('m'); break;
					case 0x33: onKeyDown(','); break;
					case 0x34: onKeyDown('.'); break;
					case 0x35: onKeyDown('-'); break;
					case 0x1C: onKeyDown('\n'); break;
					case 0x39: onKeyDown(' '); break;

					default:
					{
						print("KEYBOARD 0x");
						kernelPrintInt(key);
						break;
					}
				}
			}
			break;
		case 0x20: // timer
			break;
		default:
			//kernelPrintInt(interrupt); print(",");
			break;
	}
	
	write8(picMasterCmd, 0x20);
			if(hwInterruptOffset + 8 <= interrupt)
				write8(picSlaveCmd, 0x20);
	
	return esp;
}

