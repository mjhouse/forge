cmd.exe /c "call `"C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/VC/Auxiliary/Build/vcvarsall.bat`" x64 && set > %temp%\vcvars.txt"

Get-Content "$env:temp\vcvars.txt" | Foreach-Object {
  if ($_ -match "^(.*?)=(.*)$") {
    Set-Content "env:\$($matches[1])" $matches[2]
  }
}

mkdir bin\\Release
cd bin/Release
cmake ../.. -G Ninja
cmake --build . --config Release