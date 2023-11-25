if (Test-Path build) {
    Remove-Item build -Recurse -Force
}
cmake -S . -B build -DAPP_PACKAGE=ON
cmake --build build --config Release -- /m
cd build
cpack --config CPackConfig.cmake -G NSIS
cd ..

if (Test-Path build\_CPack_Packages\win64\NSIS\Xash*win64.exe) {
    Remove-Item Xash*win64.exe
    Move-Item build\_CPack_Packages\win64\NSIS\Xash*win64.exe .
}
