cd "$env:USERPROFILE"

if(!([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] 'Administrator')) {
 Start-Process -FilePath PowerShell.exe -Verb Runas -ArgumentList "-File `"$($MyInvocation.MyCommand.Path)`"  `"$($MyInvocation.MyCommand.UnboundArguments)`""
 Exit
}

# Use chocolatey for any packages it supports. Makes job easier
$chocoexists = Get-Command -Name choco.exe -ErrorAction SilentlyContinue
if(-not($chocoexists)){
    Write-Output "Chocolatey is not installed, installing now"
    # From chocolatey.org/install
    Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
} else {
    Write-Output "Chocolatey is already installed"
}

# Make `refreshenv` available right away, by defining the $env:ChocolateyInstall
# variable and importing the Chocolatey profile module.
# Note: Using `. $PROFILE` instead *may* work, but isn't guaranteed to.
$env:ChocolateyInstall = Convert-Path "$((Get-Command choco).Path)\..\.."   
Import-Module "$env:ChocolateyInstall\helpers\chocolateyProfile.psm1"


refreshenv # to update enviromen vars

# mingw contains gcc and python3.9
choco install -y cmake --installargs 'ADD_CMAKE_TO_PATH=System' git vscode gcc-arm-embedded mingw ninja # libusbdotnet

# git clone https://github.com/raspberrypi/picotool.git

# cd picotool-master
# mkdir build
# cd build
# cmake -G "NMake Makefiles" ..
# nmake

# cd ../../

refreshenv # to update enviromen vars

echo running pico-setup
git clone https://github.com/agmui/sample_rm_pico_app.git
cd sample_rm_pico_app
git submodule update --init --recommend-shallow 
cd rm_pico_dev
git submodule update --init --recommend-shallow 
cd lib/pico-sdk/
git submodule update --init --recommend-shallow 
setx PICO_SDK_PATH $PWD

refreshenv # to update enviromen vars

cd ../../../

# installing vscode extensions
$json_file = Get-Content $PWD\.vscode\extensions.json | Out-String | ConvertFrom-Json
foreach($elem in $json_file.PsObject.Properties.Value){
    Write-Host $elem # print
    code --install-extension $elem
}

Start-Process -NoNewWindow code .
exit 0

