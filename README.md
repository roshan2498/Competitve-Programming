### 💻 C++ Compiler Flags : g++ -std=c++17 -Wshadow -Wall -O2 -Wno-unused-result
https://gcc.gnu.org/onlinedocs/gcc/#toc-GCC-Command-Options<br/>
https://caiorss.github.io/C-Cpp-Notes/compiler-flags-options.html

### How to fix policy based DS import error ?

```Rename C:\MinGW\lib\gcc\mingw32\9.2.0\include\c++\ext\pb_ds\detail\resize_policy\hash_standard_resize_policy_imp.hppXYZ to hash_standard_resize_policy_imp.hpp```

### Windows Terminal Customizations : Fonts Used : Cascadia Code PL
``` 
Install-Module posh-git -Scope CurrentUser
Install-Module oh-my-posh -Scope CurrentUser
Install-Module -Name PSReadLine -Scope CurrentUser -Force -SkipPublisherCheck
>> notepad $PROFILE (Add Following)
    Import-Module posh-git
    Import-Module oh-my-posh
    Set-Theme Powerlevel10k-Lean

    # Chocolatey profile
    $ChocolateyProfile = "$env:ChocolateyInstall\helpers\chocolateyProfile.psm1"
    if (Test-Path($ChocolateyProfile)) {
      Import-Module "$ChocolateyProfile"
    }
```

### Windows Terminal settings.json : 
   https://raw.githubusercontent.com/roshan2498/Competitve-Programming/main/customizations/settings.json.txt

### Remove Powershell Logo From VS Code : 
   ``` "terminal.integrated.shellArgs.windows": ["-nologo"]```
