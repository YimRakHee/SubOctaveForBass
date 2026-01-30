## SubOctaveForBass
Simple but effective Analog-style Sub-Octave LV2 Plugin for Bass Guitar.<br>
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
# 1. Clone the repository
git clone https://github.com/YimRakHee/SubOctaveForBass.git
cd SubOctaveForBass

# 2. Create a build directory
mkdir build && cd build

# 3. Configure CMake and compile
cmake ..
make

# 4. Install the plugin (installs to ~/.lv2/ by default)
make install
```


