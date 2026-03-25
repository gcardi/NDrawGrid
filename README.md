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

## For the 32 bit IDE
Run the 32-bit IDE and load the NDrawGrid.groupproj project group.

In order, compile the NDrawGridPkgRun package in Release mode for the following platforms:

Windows 32-bit
Windows 64-bit
Windows 64-bit (Modern)

Now compile and install the NDrawGridPkgDsgn package in 32-bit Release mode.

The IDE should confirm the installation of the component.

## For the 64 bit IDE
Launch the 64-bit IDE, then load the NDrawGrid64.groupproj project group. 

Compile the NDrawGridPkg64Run in Release mode.

Compile and install NDrawGridPkg64Dsgn.

