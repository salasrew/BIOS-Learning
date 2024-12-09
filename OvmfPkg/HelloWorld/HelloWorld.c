
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <IndustryStandard/Pci.h>
#include <Protocol/PciIo.h>


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


    // Return EFI_SUCCESS
    return Status;
}
