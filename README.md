# Lofi-Player :headphones:
A light weight music player which plays internet radio streams featuring lofi music made using qt5.


## ScreenShots
![Screenshot](https://raw.githubusercontent.com/Roshan-R/Lofi-Player/master/imgs/screenshot.png)

## Installation
### Arch PKGBUILD
For users running Arch linux or any of it's derivatives, use the PKGBUILD for compilation.

`wget https://raw.githubusercontent.com/Roshan-R/Lofi-Player/master/PKGBUILD && makepkg -si`

### Compiling from source
```plaintext
git clone https://github.com/Roshan-R/Lofi-Player
cd Lofi-Player
mkdir build
cd build
qmake ../lofi.pro
make
```

The executable would be called lofi

## How it Works
The player is provided with a list of 7 streaming urls, loaded via a JSON file.

The default streams used are -

| Station Name        | Streaming Url                                           |
|---------------------|---------------------------------------------------------|
| Lauft fm            | http://stream.laut.fm/lofi                              |
| Planet Lofi         | http://198.245.60.88:8080                               |
| Chill Cafe          | http://192.99.35.215:5078                               |
| Chillsky            | https://lfhh.radioca.st/stream                          |
| The Augmented Ear   | http://66.228.41.10:8000/http://thirtythree-45.com:8000 |
| Lofi Hip Hop Radio  | https://stream.zeno.fm/0r0xa792kwzuv                    |
| KauteMusik FM Study | http://de-hz-fal-stream07.rautemusik.fm/study           |

To load a custom list of streams, create a JSON file as such:
```json
[
    {"name": "My Stream Name", "url", "http://my_stream.com:8080"},
    {"name": "My Other Stream", "url", "http://my_other_stream.com:9080"}
]
```

And pass to the application via the '--streams'/-s' argument
```bash
lofi --streams my_stream_file.json
#or
lofi -s my_stream_file.json
```

A help function is available if needed:
```bash
lofi --help
```

## Contributing

Pull requests are more than welcome.
