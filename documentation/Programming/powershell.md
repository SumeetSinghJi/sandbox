
___________________________________________________________________________

                                WINGET
___________________________________________________________________________

SEARCH INSTALLED PACKAGES
```bash
winget list
```

SEARCH PACKAGE
```bash
winget search g++
```

INSTALL
```bash
winget install LLVM
```

UNINSTALL
```bash
winget remove LLVM
```


UPLOADING A WINGET
```bash

```



___________________________________________________________________________

                        POWERSHELL PROFILE
___________________________________________________________________________

MAKE PROFILE
```bash
PS C:\Users\Sumeet\Documents\sandbox> $PROFILE
C:\Users\Sumeet\Documents\WindowsPowerShell\Microsoft.PowerShell_profile.ps1
mkdir C:\Users\Sumeet\Documents\WindowsPowerShell # make profile directory
new-item -path C:\Users\Sumeet\Documents\WindowsPowerShell\Microsoft.PowerShell_profile.ps1 # make profile
notepad $PROFILE # open profile
Write-Host "Welcome, $env:USERNAME@$env:COMPUTERNAME Today is $(Get-Date -Format 'dddd, MMMM dd yyyy')." # add line in profile
. $PROFILE # reset profile

# RESULT
Welcome, Sumeet@SUMEETS-PC Today is Sunday, July 07 2024.
PS C:\Users\Sumeet\Documents\sandbox> 
```


___________________________________________________________________________

                        POWERSHELL COMMANDS
___________________________________________________________________________


1. COPY ALL CONTENTS FROM SUBDIRECTORIES TO PARENT
```powershell
Get-ChildItem -Directory | ForEach-Object {
    Move-Item -Path $_.FullName\* -Destination "C:\path\to\destination"
    # Remove-Item -Path $_.FullName -Force -Recurse # OPTIONAL TO REMOVE EMPTY SUBDIRECTORIES
}
```

1. DELETE EMPTY SUBDIRECTORIES
```powershell
Get-ChildItem -Directory | ForEach-Object {
    if (!(Get-ChildItem -Path $_.FullName)) {
        Remove-Item -Path $_.FullName -Force -Recurse
    }
}
```