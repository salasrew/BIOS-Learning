
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
    UINTN Bus;
    UINTN Device;
    UINTN Function;
    UINTN Offset;

    // Cannot Use UINT32 Addr
    UINT64 Addr;

    PCIBaseAddr = 0xE0000000;

    Bus = 0;
    Device = 0;
    Function = 0;
    Offset = 0;
    Addr = 0;

    Print(L"Address|Reserved|BusNum|Device|Function|Register");

    for(Offset;Offset <= 255 ; Offset = Offset + 4)
    {
        Addr = PCIBaseAddr + Offset;
        Print(L"%x ", MmioRead32(Addr));
        if(Offset % 15 == 0 ) Print(L"\n");
        // Print(L"1");
    }

    Print(L"---------------------------------------------------\n");

    // for(Bus = 0 ; Bus <= 0xFF ; Bus++)
    // {
    //     for(Device = 0 ; Device <= 0x1F ; Device++)
    //     {
    //         for(Function = 0 ; Function <= 0x7 ; Function++)
    //         {
    //             Addr = PCIBaseAddr + (Bus << 16) + (Device << 11) + (Function << 8);
    //             Print(L"Data at address 0x%08x: \n", Addr);

    //             // Print(L"DeviceID: %d ,VendorID: %d ,FunctionID: %d ,");
    //             // Print(L"1");
    //         }
    //     }
    // }

    Print(L"---------------------------------------------------\n");
    Offset = 0;

    // while(Offset <= 0x100)
    // {
    //     Addr = PCIBaseAddr + Offset;
    //     Print(L"0x%x ", MmioRead32(Addr));
    //     if(Offset%15 == 0)
    //     {
    //         Print(L"\n");
    //     }
    //     Offset++;
    // }

    return Status;
}
