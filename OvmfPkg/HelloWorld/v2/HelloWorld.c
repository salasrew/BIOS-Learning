#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/IoLib.h>

#include <IndustryStandard/Pci.h>
#include <Protocol/PciIo.h>
#include <Protocol/PciRootBridgeIo.h>

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

    // MMIO
    // Print 0 to 256 first
    Print(L"Address 0x%016x \n", Addr);
    Print(L"Address　| Reserved | BusNum | Device | Function | Register ");

    // for(Offset;Offset <= 255 ; Offset++)
    // {
    //     Addr = PCIBaseAddr + Offset;
    //     Print(L"%x ", MmioRead32(Addr));
    //     // if(Offset % 15 == 0 ) Print(L"\n");
    // }

    // Print(L"---------------------------------------------------\n");

    // for(Bus = 0 ; Bus <= 0xFF ; Bus++)
    // {
    //     for(Device = 0 ; Device <= 0x1F ; Device++)
    //     {
    //         for(Function = 0 ; Function <= 0x7 ; Function++)
    //         {
    //             Addr = PCIBaseAddr + (Bus << 16) + (Device << 11) + (Function << 8);
    //             Print(L"Data at address 0x%08x: %x \n", Addr, MmioRead64(Addr));
                
    //             Print(L"DeviceID: %d ,VendorID: %d ,FunctionID: %d ,");
    //         }
    //     }
    // }


    // while(Offset <= 0x100)
    // {
    //     Addr = PCIBaseAddr + Offset;
    //     Print(L"%x ", MmioRead64(Addr));
    //     if(Offset%16 == 0)
    //     {
    //         Print(L"\n");
    //     }
    //     Offset++;
    // }

    // -----------------------PCI----------------------------
    // Config_Address CF8 , CFC  
    // it seems like we need to write specific address in 0x0CF8 Register
    // And Then we can get the specific address's Data from 0x0CFC 
    // And the maximum is to 0x0CFF (?)


    // -----------------------PCIE----------------------------
    // the address that Out the Bound should use MMIO to get the data 
    // 


    return Status;
}
