## SubOctaveForBass
Simple but effective analog-style sub-Octave LV2 plugin for bass guitar.<br>
No GUI.<br>
Tested Environment: Arch Linux / Ardour.<br>

![SubOctaveForBass Screenshot](./images/octaveplug.png)

### Features
- Zero-crossing Flip-Flop logic for stable tracking.
- Built-in Low Pass Filters for smooth sub tones.
- Dry / Wet / Tone controls.

### Requirements
- LV2 SDK
- C++20 compatible compiler (GCC/Clang)
- CMake

### Build & Install (LINUX)
```bash
# Clone the repository
git clone https://github.com/YimRakHee/SubOctaveForBass.git
cd SubOctaveForBass

# Create a build directory
mkdir build && cd build

# Configure CMake and compile
cmake ..
make

# Install the plugin (installs to ~/.lv2/ by default)
make install
```


