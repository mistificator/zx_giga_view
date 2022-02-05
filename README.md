# zx_giga_view
ZX Spectrum 48k/128k/+2A/+3 gigascreen viewer. Images should be prepared via Image Spectrumizer (https://github.com/jarikomppa/img2spec) using "Device -> 3x64 mode", then compile tape image (TAP) with "GIGAVIEW.TAP" and your screen file (SCR), prepared as data block with header at address 0xC000. See example tapes for more details.

Compile viewer from source via z88dk + Visual Studio Code.
