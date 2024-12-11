
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
    UINT32 Data;

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

    Print(L"|---Data---|---VendorID---|---DeviceID---|---Bus---|---Device---|---Function---|\n");
    for(Bus = 0; Bus < 256 ; Bus++)
    {
        for(Device = 0; Device < 32 ; Device++)
        {
            for(Function = 0; Function < 8 ; Function++)
            {
                Data = MmioRead32(PCIBaseAddr + (Bus << 20) + (Device << 15) + (Function << 12));
                VendorID = Data & 0xFFFF;
                DeviceID = (Data >> 16) & 0xFFFF;
                // VendorID DeviceID BusNumber DeviceNumber FunctionNumber
                if(Data != 0xFFFFFFFF)
                {
                    // Data VendorID DeviceID Bus Device Function
                    // Print(L"VendorID: %4x DeviceID: %4x BusNumber: %2x DeviceNumber: %2x FunctionNumber: %2x\n", VendorID, DeviceID, Bus, Device, Function);
                    Print(L"| %8x | %4x | %4x | %2x | %2x | %2x |\n",Data, VendorID, DeviceID, Bus, Device, Function);
                }
                
            }
        }
    }

    Print(L"---------------------------------------------------\n");


    return Status;
}
