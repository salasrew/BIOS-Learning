
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

	UINTN count;

	count = 0;

	// EFI Boot Phase / EFI Protocol / EFI Driver Binding / EFI Shell HW2
    // HelloWord Part
	for(count ; count < 5 ; count++)
	{
		Print(L"Hello World\n");
	}

    // Return EFI_SUCCESS
    return Status;
}
