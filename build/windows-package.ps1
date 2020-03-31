cd bin > $null

New-Item -Path . -Name "Package" -ItemType "directory" -Force > $null
New-Item -Path Package -Name "geometryloaders" -ItemType "directory" -Force > $null
New-Item -Path Package -Name "platforms" -ItemType "directory" -Force > $null

Function CopyFiles($Pattern,$Path,$Output) {
    Get-ChildItem -Path $Path -Filter $Pattern -Recurse -ErrorAction SilentlyContinue -Force |
    Foreach-Object {
        Copy-Item $_.FullName -Destination $Output
    }
}

CopyFiles -Path "Release/forge" -Pattern Qt5*.dll -Output "Package/"
CopyFiles -Path "Release/forge" -Pattern "Forge.exe" -Output "Package/"
CopyFiles -Path "Release/forge/geometryloaders/" -Pattern "*.dll" -Output "Package/geometryloaders/"
CopyFiles -Path "Release/forge/platforms/" -Pattern "*.dll" -Output "Package/platforms/"

Copy-Item "Release/forge/resources" -Destination "Package/" -Recurse

cd .. > $null