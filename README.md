# TWW_Practice_Rom

Practice rom for the original version of The Wind Waker. Currently only supported for NTSC-U release.

- WW_Hacking_API https://github.com/LagoLunatic/WW_Hacking_API
- WWRando https://github.com/LagoLunatic/wwrando/tree/f999cd1dc87c2a3ad9c5cc0d3f8a6d472e1a226a 

# Requirements
Download and install the following:

- Python 3.8.2: https://www.python.org/downloads/release/python-382/
- devkitPro: https://devkitpro.org/

# Setup:
```
git clone https://github.com/TrogWW/TWW_Practice_Rom.git
git submodule update --init --recursive
```
Install dependencies using:
```
py -3.8 -m pip install -r ww_hacking_api/wwrando/requirements.txt
```
# To build :
- copy main.asm into ww_hacking_api\asm_patches\
- navigate to ww_hacking_api directory then run the following commands:
  ```
  py asm_api/assemble.py
  py asmpatch.py "PATH_TO_EXTRACTED_ISO" "PATH_TO_OUTPUT_FOLODER"
  ```
- Replace main.dol in extracted ISO
- Refer to https://github.com/LagoLunatic/WW_Hacking_API for further documentation

Update ghidra repo
  - window -> defined data -> ww_variables_from_ghidra.csv
  - window -> functions -> ww_functions_from_ghidra.csv
  - data type manager -> right click d_a_title.rel -> export c header -> ww_structs_from_ghidra.h
