# NDrawGrid
Enhanced TDrawGrid for VCL applications

## Features

NDrawGrid is an advanced VCL grid component that extends the standard TDrawGrid with enhanced customization capabilities and user interaction features.

### Enhanced Cell Drawing
- **OnDrawCellBackground** event for complete control over cell background rendering
- **OnDrawCellHighlight** event for custom cell selection highlighting
- Support for modern VCL Styles themes

### Automatic Tooltips
- **CellAutoHintEnabled** property enables automatic tooltips when cell text is too wide to display
- Smart tooltip positioning based on text alignment (left, center, right)

### Advanced Text Formatting
- **OnGetTextFormat** event for per-cell text alignment and formatting control
- Support for left, center, and right text alignment

### Interactive Fixed Cells (Headers)
- **OnFixedCellGetText** event for dynamic header text
- **OnFixedCellCanClick** event to control header clickability
- **OnFixedCellMouseUp** event for advanced header interactions

### Enhanced In-place Editing
- Custom **TNDrawGridInplaceEditList** with styled buttons
- **DropdownRowCount** property for picklist dropdown height control
- **OnGetEditStyle** event for per-cell editor style selection
- **OnGetPickListItems** event for dynamic dropdown content

### Text Management Events
- **OnNormalCellGetText** event for dynamic cell content in data cells
- Separate text handling for fixed and normal cells

### Additional Events
- **OnEditButtonClick** for custom edit dialogs
- **OnColWidthsChanged** for layout persistence
- **OnOverlay** for additional drawing operations

### Public Methods
- `DefaultDrawCellBackground()` - Draw default cell background
- `DefaultDrawCellHighlight()` - Draw default cell highlighting
- Exposed inherited methods: `SelectCell()`, `GetCellText()`, `GetCellTextFormat()`

## Steps to verify/execute before install the packages

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

## Installation

Open the `Delphi` folder and run `install.bat` from a normal command prompt. The script builds the runtime package for Win32, Win64, and Win64x, builds and registers the design-time package for the IDE hosts available in the installed RAD Studio version, and updates the IDE Library Search Path. Administrator privileges are not normally required. Restart RAD Studio after the script reports success.

To remove the component, run `uninstall.bat` from the same folder.

### Troubleshooting

If `install.bat` reports that it cannot load `*.tasks` from `C:\Windows\Microsoft.NET\Framework\v2.0.50727`, followed by `MSB4036` for the `CreateItem` task, check the MSBuild `DefaultToolsVersion` setting. A system-wide value of `2.0` can make MSBuild 4 look for tasks in the .NET Framework 2.0 folder even when `where msbuild` resolves to the .NET Framework 4 executable. This occurs before the Delphi package is compiled and does not indicate a source-code error.

Run the installer from a normal command prompt and check which MSBuild is being used:

```bat
call "C:\Program Files (x86)\Embarcadero\Studio\<version>\bin\rsvars.bat"
where msbuild
msbuild -version
```

The installer explicitly selects MSBuild ToolsVersion 4.0. If building manually, add `/tv:4.0` to the MSBuild command. Alternatively, an administrator can inspect `DefaultToolsVersion` under `HKLM\SOFTWARE\Microsoft\MSBuild\4.0` and `HKLM\SOFTWARE\WOW6432Node\Microsoft\MSBuild\4.0` for a stale `2.0` setting. Avoid changing machine-wide registry settings unless you understand the effect on other build tools.
