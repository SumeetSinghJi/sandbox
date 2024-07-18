
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


1. COPY SUBDIRECTORIES CONTENTS TO PARENT THEN DELETE
```powershell
cd "C:\Users\Sumeet\Downloads"

$source = "C:\Users\Sumeet\Downloads"
$destination = "C:\Users\Sumeet\Downloads"

Get-ChildItem -Directory | ForEach-Object {
    $subDirPath = $_.FullName
    Write-Host "Copying contents from: $subDirPath to  $destination"

    # Use robocopy to move files
    robocopy "$subDirPath" "$destination" /MOV /E /Z /NP /NFL /NDL /NJH /NJS /XD "$subDirPath" /R:1 /W:1
}

# Clean up empty subdirectories
Get-ChildItem -Directory -Recurse | Where-Object { $_.GetFileSystemInfos().Count -eq 0 } | ForEach-Object {
    $directoryPath = $_.FullName
    Write-Host "Deleting directory: $directoryPath"
    $_ | Remove-Item -Force
}
```