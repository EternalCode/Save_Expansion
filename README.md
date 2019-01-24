# Save_Expansion
Expansion/modification of FR's disposable Save RAM

## Building

Requirements (Windows):
- DevkitPro/ARM (https://devkitpro.org/wiki/Getting_Started/devkitARM windows installer here)
- Python (Atleast 3.4 https://www.python.org/downloads/)
- Armips(Latest: https://buildbot.orphis.net/armips/)
- Visual C++ runtime DLL https://www.microsoft.com/en-ca/download/details.aspx?id=48145

Make sure you have an *environment variable* for `DEVKITARM`, `python` and `armips`. If not, create them.

After cloning the repository, delete the deps folder if you're not planning to build the dependancies. Extract the `deps.zip` file. I've taken the liberty of building them so you don't have to.

Next, create a directory called `roms` and place a clean FireRed US version 1.0 ROM inside and rename it to `BPRE0.gba`.
Now we can build the project by running `make`.

If the last line is `Done.` then everything succeeded.


Credits:
- https://github.com/Touched project structure
- https://github.com/pret string related tools and pokeemerald resources
- JPAN
- All contributors!

