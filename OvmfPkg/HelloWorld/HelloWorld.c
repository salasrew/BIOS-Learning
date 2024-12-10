
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <IndustryStandard/Pci.h>
#include <Protocol/PciIo.h>

#include <Library/IoLib.h>


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

    UINTN Vendor;
    UINTN Bus;
    UINTN Device;
    UINTN Offset;
    UINTN Data;
    UINTN StatusCommand;
    UINTN ClassCode;

    UINTN BusNumber;
    UINTN DeviceNumber;
    UINTN FunctionNumber;
    UINTN RegisterNumber;

    PCIBaseAddr = 0xE0000000;
    PCIEndAddr =  0xE00FF000;

    Vendor = 0;
    Bus = 0;
    Device = 0;
    Offset = 0;
    Data = 0;
    StatusCommand = 0;
    ClassCode = 0;

    BusNumber = 0;
    DeviceNumber = 0;
    FunctionNumber = 0;
    RegisterNumber = 0;

    // Print(L"Address|Reserved|BusNum|Device|Function|Register|\n");

    // for(Offset;Offset <= 0XFF ; Offset++)
    // {
    //     Addr = PCIBaseAddr + Offset;
    //     Print(L"%x ", MmioRead8(Addr));
    //     if(Offset % 15 == 0 ) Print(L"\n");
    // }

    Print(L"---------------------------------------------------\n");

    // for(Bus = 0 ; Bus <= 0xFF ; Bus++)
    // {
    //     for(Device = 0 ; Device <= 0x1F ; Device++)
    //     {
    //         for(Function = 0 ; Function <= 0x7 ; Function++)
    //         {
    //             Addr = PCIBaseAddr + (Bus << 16) + (Device << 11) + (Function << 8);
    //             // Print(L"Data at address 0x%08x: %x \n", Addr, MmioRead32(Addr));

    //             // Print(L"DeviceID: %d ,VendorID: %d ,FunctionID: %d ,");
    //             // Print(L"1");

    //         }
    //     }
    // }

    Print(L"---------------------------------------------------\n");

    // -----------------------PCI----------------------------
    // Config_Address CF8 , CFC  
    // it seems like we need to write specific address in 0x0CF8 Register
    // And Then we can get the specific address's Data from 0x0CFC 
    // And the maximum is to 0x0CFF (?)

    Print(L"|------------PCI256Byte-----------| \n");

    Print(L"   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F \n");

    while (Offset <= 0xFF)
    {
        IoWrite32(0xCF8, PCIBaseAddr);
        Data = IoRead8(0xCFC);

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

    Print(L"|------------PCI256ByteEnd-----------| \n");
    // initialize the PCIBaseAddr
    PCIBaseAddr = 0xE0000000;
    Print(L"|------------PCI Scan-----------| \n");

    // Print(L"|---Data---|---Vendor---|---Device---|---Status---|---CMD---|---ClassCode---|---Revision---|\n");
    Print(L"|---Data---|---Vendor---|---Device---|---BusNum---|---DevNum---|---FuncNum---|---RegNum---| \n");

    while (PCIBaseAddr <= PCIEndAddr)
    {
        IoWrite32(0xCF8, PCIBaseAddr);
        Data = IoRead32(0xCFC);

        if (Data == 0xFFFFFFFF)
        {
            PCIBaseAddr = PCIBaseAddr + 0x100;
            continue;
        }

        // 04 Status Command
        IoWrite32(0xCF8, PCIBaseAddr + 0x04);
        StatusCommand = IoRead32(0xCFC);
        // Print(L"Status Command| %x | \n", Data);

        // 08 ClassCode RevisionID
        IoWrite32(0xCF8, PCIBaseAddr + 0x08);
        ClassCode = IoRead32(0xCFC);
        // Print(L"ClassCode RevisionID| %x | \n", Data);

        // Original Data , Vendor , Device , Status Command , ClassCode RevisionID
        Vendor = Data & 0xFFFF;
        Device = (Data >> 16) & 0xFFFF;
        // Print(L"| %x |   %-8x |   %-8x |   %-8x |   %-8x |   %-8x |   %-8x | \n", Data , Vendor , Device , StatusCommand & 0xFFFF , (StatusCommand >> 16) & 0xFFFF  , (ClassCode >> 8) & 0xFFFFFF , (ClassCode) & 0xFF);

        // Print VendorID , DeviceID , BusNumber , DeviceNumber , FunctionNumber , RegisterNumber
        BusNumber = (PCIBaseAddr >> 16) & 0xFF;
        DeviceNumber = (PCIBaseAddr >> 11) & 0x1F;
        FunctionNumber = (PCIBaseAddr >> 8) & 0x7;
        RegisterNumber = PCIBaseAddr & 0xFF;
        Print(L"| %x |   %-8x |   %-8x |   %7d |   %-4d |   %-4d |   %-4d |   %-4d | \n", Data , Vendor , Device , BusNumber, DeviceNumber, FunctionNumber, RegisterNumber);

        PCIBaseAddr = PCIBaseAddr + 0x100;
    }
    // Print(L"|---------------------------------| \n");

    return Status;
}
