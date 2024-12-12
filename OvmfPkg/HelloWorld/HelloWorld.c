
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <IndustryStandard/Pci.h>
#include <Protocol/PciIo.h>
#include <Library/IoLib.h>
#include <Library/ShellCommandLib.h>

// #include "ShellPkg/Library/UefiShellDebug1CommandsLib/Pci.h"
// #include <ShellPkg/Library/UefiShellDebug1CommandsLib/UefiShellDebug1CommandsLib.h>
// #include <Library/ShellDebug1CommandsLib.h>

typedef struct PCI_CLASS_ENTRY_TAG {
  UINT8                         Code;             // Class, subclass or I/F code
  CHAR16                        *DescText;        // Description string
  struct PCI_CLASS_ENTRY_TAG    *LowerLevelClass; // Subclass or I/F if any
} PCI_CLASS_ENTRY;
PCI_CLASS_ENTRY  PCIBlankEntry[];

PCI_CLASS_ENTRY  gClassStringList[] = {
  {
    0x00,
    L"Pre 2.0 device",
    // PCISubClass_00
  },
  {
    0x01,
    L"Mass Storage Controller",
    // PCISubClass_01
  },
  {
    0x02,
    L"Network Controller",
    // PCISubClass_02
  },
  {
    0x03,
    L"Display Controller",
    // PCISubClass_03
  },
  {
    0x04,
    L"Multimedia Device",
    // PCISubClass_04
  },
  {
    0x05,
    L"Memory Controller",
    // PCISubClass_05
  },
  {
    0x06,
    L"Bridge Device",
    // PCISubClass_06
  },
  {
    0x07,
    L"Simple Communications Controllers",
    // PCISubClass_07
  },
  {
    0x08,
    L"Base System Peripherals",
    // PCISubClass_08
  },
  {
    0x09,
    L"Input Devices",
    // PCISubClass_09
  },
  {
    0x0a,
    L"Docking Stations",
    // PCISubClass_0a
  },
  {
    0x0b,
    L"Processors",
    // PCISubClass_0b
  },
  {
    0x0c,
    L"Serial Bus Controllers",
    // PCISubClass_0c
  },
  {
    0x0d,
    L"Wireless Controllers",
    // PCISubClass_0d
  },
  {
    0x0e,
    L"Intelligent IO Controllers",
    // PCISubClass_0e
  },
  {
    0x0f,
    L"Satellite Communications Controllers",
    // PCISubClass_0f
  },
  {
    0x10,
    L"Encryption/Decryption Controllers",
    // PCISubClass_10
  },
  {
    0x11,
    L"Data Acquisition & Signal Processing Controllers",
    // PCISubClass_11
  },
  {
    0x12,
    L"Processing Accelerators",
    // PCISubClass_12
  },
  {
    0x13,
    L"Non-Essential Instrumentation",
    // PCISubClass_13
  },
  {
    0xff,
    L"Device does not fit in any defined classes",
    PCIBlankEntry
  },
  {
    0x00,
    NULL,
    /* null string ends the list */ NULL
  }
};
UINT16 SwapBytes(UINT16 value) {
    return (value >> 8) | (value << 8);
}

// HelloWorldEntryPoint()
EFI_STATUS
EFIAPI 
HelloWorldEntryPoint(
    // EFI_HANDLE is an important pointer 
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
    )
    {
    EFI_STATUS Status = EFI_SUCCESS;

    // gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress|0xE0000000
    UINT32 PCIBaseAddr;
    UINT32 PCIEndAddr;
    UINT32 Data;
    UINT32 ClassCode;
    UINT8 MainClass;
    UINT8 MainLeftHex;
    UINT8 MainRightHex;

    UINT32 VendorID;
    UINT32 Bus;
    UINT32 Device;
    UINT32 DeviceID;

    UINT32 Function;
    UINT32 Offset;

    PCIBaseAddr = 0xE0000000;
    PCIEndAddr =  0xEFFFF000;

    VendorID = 0;

    Offset = 0;
    Data = 0;
    ClassCode = 0;
    MainClass = 0;

    // Show 256 pcie configuration space
    Print(L"--------------------PCI256Byte---------------------\n");
    Print(L"   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F \n");
    while (Offset <= 0xFF)
    {
        Data = MmioRead8(PCIBaseAddr);

        if(Offset % 0x10 == 0)
        {
            Print(L"%2x ", Offset);
        }
        
        Print(L"%2x ", Data);
        Offset++;
        if (Offset % 16 == 0)
        {
            Print(L"\n");
        }
        PCIBaseAddr = PCIBaseAddr + 1;
    }
    Print(L"---------------------------------------------------\n");

    // PCIE Initialization
    PCIBaseAddr = 0xE0000000;

    Print(L"|---Data---|---VendorID---|---DeviceID---|---Bus---|---Device---|---Function---|---ClassCode---|---Swap---|\n");
    for(Bus = 0; Bus < 256 ; Bus++)
    {
        for(Device = 0; Device < 32 ; Device++)
        {
            for(Function = 0; Function < 8 ; Function++)
            {
                Data = MmioRead32(PCIBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12));

                // VendorID DeviceID BusNumber DeviceNumber FunctionNumber
                if(Data != 0xFFFFFFFF)
                {
                    ClassCode = MmioRead32(PCIBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12) + 0x08);
                    // 23:16 -> ClassCode 15:8 -> SubClass 7:0 -> Interface
                    
                    // MainClass
                    MainClass = (ClassCode >> 24) & 0xFF;
                    MainLeftHex = MainClass >> 4;
                    MainRightHex = MainClass & 0xF;
                    // Print(L"MainLeftHex , MainRightHex , Merge \n");
                    // Print(L"%2x , %2x , %2x\n", MainLeftHex, MainRightHex, MainLeftHex | MainRightHex);

                    VendorID = Data & 0xFFFF;
                    DeviceID = (Data >> 16) & 0xFFFF;

                    // Data VendorID DeviceID Bus Device Function
                    // Print(L"VendorID: %4x DeviceID: %4x BusNumber: %2x DeviceNumber: %2x FunctionNumber: %2x\n", VendorID, DeviceID, Bus, Device, Function);
                    Print(L"| %8x | %4x | %4x | %2x | %2x | %2x | %12x | %12x |\n",Data, VendorID, DeviceID, Bus, Device, Function , ClassCode , MainLeftHex | MainRightHex);
                
                    // if (ClassCode >> 16) & 0xFF == gClassStringList[(ClassCode >> 16) & 0xFF] return gClassStringList[(ClassCode >> 16) & 0xFF].DescText
                    // Print(L"ClassCode , SubClass, Interface\n");
                    Print(L"DescText : %s\n", gClassStringList[MainClass].DescText);
                
                }
                
            }
        }
    }

    Print(L"---------------------------------------------------\n");


    return Status;
}
