# About

This simple parser allows you to parse a BMP file in a static SDL_texture using the SDL library.

In this repository, under app/src folder, u can find an example of use (download or clone the repository and then run the .bat file from your terminal.)





## Yes but how do I get the Texture?

By including the bmp_parser.h in your file u have the bmpp_get_texture(...) method available:
```go
    #include "bmp_parser.h"

    SDL_Texture *example_bgr24_texture;
    bmpp_get_texture("flower.bmp", renderer, &example_bgr24_texture);

    SDL_Texture *example_bgr32_texture;
    bmpp_get_texture("foo.bmp", renderer, &example_bgr32_texture);
```



> **NOTE**
>
> Creation of a texture starting from a BMP file with 24 bits for pixel:
>
> ```bash
>   SDL_Texture *example_bgr24_texture;
>   bmpp_get_texture("flower.bmp", renderer, &example_bgr24_texture);
> ```
> Creation of a texture starting from a BMP file with 32 bits for pixel:
> ```go
>   SDL_Texture *example_bgr32_texture;
>   bmpp_get_texture("foo.bmp", renderer, &example_bgr32_texture);
> ```
>**!!! ONLY bmp file of those two types of bmp files are supported !!!**
>
> You can find more info in the bmp_parser.h file.

Your directory should contain the following two files:
```
.
├── SDL2-2.0.20
├── bmp_parser.h
└── SDL2.dll
```

(N.B. Order isn't relevant)

Enjoy!