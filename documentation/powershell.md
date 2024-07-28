
# PROGRAMMING WITH POWERSHELL

By: Sumeet Singh @ sumeet-singh.com

Date: July 2024

# TABLE OF CONTENTS
- [1. Requirements](#requirements)
- [2. Installing](#installing)
- [3. Profile script](#profile-script)
- [4. Common Commands](#common-commands)
- [5. Scripts](#scripts)
- [6. Winget](#winget)

# REQUIREMENTS

MAKE PROFILE
```powershell
```

# INSTALLING

MAKE PROFILE
```powershell
```

# PROFILE SCRIPT

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

# COMMON COMMANDS

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

# SCRIPTS

SCRIPTS
```powershell

```

# WINGET

SEARCH INSTALLED PACKAGES
```powershell
winget list
```

SEARCH PACKAGE
```powershell
winget search g++
```

INSTALL
```powershell
winget install LLVM
```

UNINSTALL
```powershell
winget remove LLVM
```


UPLOADING A WINGET
```powershell

```
