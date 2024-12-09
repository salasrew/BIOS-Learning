
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

    // // PCIList DS Start 
    // EFI_STATUS Status;
    // EFI_HANDLE *HandleBuffer;
    // UINTN HandleCount;
    // UINTN Index;
    // EFI_PCI_IO_PROTOCOL *PciIo;
    // PCI_TYPE00 Pci;

    // PCIList DS End

    // EFI_STATUS Status;
    // Status = Status = gBS->LocateHandleBuffer(ByProtocol, &gEfiPciIoProtocolGuid, NULL, &HandleCount, &HandleBuffer);
    // EFI_HANDLE PciHandle = NULL;
    // EFI_PCI_IO_PROTOCOL *PciIo = NULL;

    // for(Index = 0 ; Index < HandleCount ; Index++)
    // {
    //     Status = gBS->HandleProtocol(HandleBuffer[Index], &gEfiPciIoProtocolGuid, (VOID **)&PciIo);
    // }

    // Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32, 0, sizeof(Pci) / sizeof(UINT32), &Pci);

    
    // HelloWord Part
    // Print "Hello, World!" to the console
    Print(L"[HelloPoint] Hello, World Entry Point Start .. ! \n");
    Print(L"[HelloPoint] Hello, World Entry Point End .. ! \n");
    // HelloWord Part


    // echo PCI list vendorID deviceID FunctionID 


    // Return EFI_SUCCESS
    return Status;
}
