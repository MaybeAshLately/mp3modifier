# MP3 modifier
This is a simple program to modify metadata of mp3 file for Windows.

## Program overview
To open file to edit you should drag and drop it in the main program window. When the file is dropped editor is open (if the file is a .mp3 file). In editor view it is possible to:
- modify song title,
- modify artist name,
- modify album name,
- clear other metadata (e.g. year and genre) **attention** by default this option is checked!
- modify song cover (by drag and drop either an .jpg/.jpeg or .png file).
You can either save the changes or discard them. 

## Libraries
- The GUI was created using the QT framework ([https://www.qt.io/](https://www.qt.io/)), version 6.8.1 under the GPL license.
- TagLib 2.0.2 was used to access the metadata, distributed under LGPL and MPL license
## License
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see [https://www.gnu.org/licenses/](https://www.gnu.org/licenses/).

