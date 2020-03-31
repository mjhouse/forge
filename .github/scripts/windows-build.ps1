cmd.exe /c "call `"C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/VC/Auxiliary/Build/vcvars64.bat`" && set > %temp%\vcvars.txt" >$null 2>&1

Get-Content "$env:temp\vcvars.txt" | Foreach-Object {
    if ($_ -match "^(.*?)=(.*)$") {
       Set-Content "env:\$($matches[1])" $matches[2]
    }
}

# create move to output directory
mkdir bin\\Release >$null 2>&1
cd bin/Release >$null 2>&1

# generate build files
cmake ../..

# build libraries and executables
cmake --build . --config Release

cd ../..