# NDrawGrid
Enhanced TDrawGrid for VCL applications

##Steps to verify/execute before install the packages

The packages for 32-bit IDE and 64-bit IDE must have different names, otherwise the 64-bit IDE will complain that it cannot load them.

For the 64-bit IDE to properly find and load the required packages, you need to add the following paths to the override PATH environment variable in the IDE settings:

```
C:\Users\Public\Documents\Embarcadero\Studio\37.0\Bpl\win64x\Release
C:\Users\Public\Documents\Embarcadero\Studio\37.0\Bpl\win64x\Debug
C:\Users\Public\Documents\Embarcadero\Studio\37.0\Bpl\win64x
```

The final PATH environment variable in the 64-bit IDE should look like this:

```
$(PATH);$(PUBLIC)\Documents\Embarcadero\InterBase\redist\InterBase2020\IDE_spoof;c:\program files (x86)\embarcadero\studio\37.0\redist\boost\win64x;c:\program files (x86)\embarcadero\studio\37.0\redist\boost\win64;c:\program files (x86)\embarcadero\studio\37.0\redist\boost\win32c;c:\program files (x86)\embarcadero\studio\37.0\redist\boost\win32;c:\program files (x86)\embarcadero\studio\37.0\redist\boost\win32c;c:\program files (x86)\embarcadero\studio\37.0\redist\boost\win64;c:\program files (x86)\embarcadero\studio\37.0\redist\boost\win64x;C:\Users\Public\Documents\Embarcadero\Studio\37.0\Bpl\win64x\Release;C:\Users\Public\Documents\Embarcadero\Studio\37.0\Bpl\win64x\Debug;C:\Users\Public\Documents\Embarcadero\Studio\37.0\Bpl\win64x;
```

##Installation

##For the 32 bit IDE
Run the 32-bit IDE and load the NDrawGrid.groupproj project group.

In order, compile the NDrawGridPkgRun package in Release mode for the following platforms:

Windows 32-bit
Windows 64-bit
Windows 64-bit (Modern)

Now compile and install the NDrawGridPkgDsgn package in 32-bit Release mode.

The IDE should confirm the installation of the component.

##For the 64 bit IDE
Launch the 64-bit IDE, then load the NDrawGrid64.groupproj project group. 

Compile the NDrawGridPkg64Run in Release mode.

Compile and install NDrawGridPkg64Dsgn.

