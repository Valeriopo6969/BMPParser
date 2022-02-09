#pragma once
#include <SDL.h>

#pragma region internals
#define __BMPP_DATA_OFFSET 10 
#define __BMPP_DIM_OFFSET 18 
#define __BMPP_C_DEPTH_OFFSET 28
#define __ALIGNMENT 4


static int __bmpp_get_file_content(const char *file_path, Uint8 **file_content)
{
    SDL_RWops *rw = SDL_RWFromFile(file_path, "rb");
    if(!rw)
    {
        SDL_Log("Unable to open the file [%s]: %s", file_path, SDL_GetError());
        return 1;
    }

    Sint64 file_size = SDL_RWsize(rw);
    *file_content = SDL_malloc(file_size);
   
    if(!*file_content)
    {
        SDL_Log("Unable to allocate file memory: %s", SDL_GetError());
        SDL_RWclose(rw);
        return 1;
    }

    SDL_RWread(rw, *file_content, file_size, 1);
    SDL_RWclose(rw);
    
    return 0;
}



#pragma endregion

#pragma region public 


/*
 * Parse a BMP file into a SDL_Texture of type: Static
 * @param *file_path the path were u keep the file to parse
 * @param *renderer the rendering context
 * @param **texture the texture u want to update
 */
int bmpp_get_texture(const char *file_path, SDL_Renderer *renderer, SDL_Texture **texture)
{
    Uint8 *file_content;
    if(__bmpp_get_file_content(file_path,&file_content))
    {
        return 1;
    }

    Uint8 *pixels_offset = file_content + (*(file_content+__BMPP_DATA_OFFSET));

    Uint32 image_dimension[2];
    SDL_memcpy(image_dimension, file_content + __BMPP_DIM_OFFSET, 8);
    
    Uint32 color_depth;
    SDL_memcpy(&color_depth, file_content + __BMPP_C_DEPTH_OFFSET, 2);

    if(color_depth!=24 && color_depth !=32)
    {
        SDL_Log("Only images that are TRUE COLOR (32 or 24 bit per pixel) are yet supported, here u have: %llu", color_depth);
        return 1;
    }
    
    const Uint32 bytes_per_pixel = color_depth / 8;
   
    Uint32 row_size = image_dimension[0] * bytes_per_pixel;
    
    Uint32 padded_row_size = (row_size / __ALIGNMENT) * __ALIGNMENT;
    if(row_size % __ALIGNMENT != 0)
    {
        padded_row_size+=__ALIGNMENT;
    }
    
    Uint8 *pixels = SDL_malloc(row_size * image_dimension[1]);
    
    if(!pixels)
    {
        SDL_Log("Unable to allocate texture memory: %s", SDL_GetError());
        return 1;
    }
    
    *texture =  color_depth == 24 ?
                SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGR24, SDL_TEXTUREACCESS_STATIC, image_dimension[0], image_dimension[1]) :
                SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STATIC, image_dimension[0], image_dimension[1]) ;
    
    if(color_depth==32) SDL_SetTextureBlendMode(*texture, SDL_BLENDMODE_BLEND);

    for(Uint32 y = 0; y < image_dimension[1]; y++)
    {
        
        Uint8 *texture_row = pixels + (y * row_size);
        Uint8 *bitmap_row = pixels_offset + ((image_dimension[1] - 1) - y) * padded_row_size;

        SDL_memcpy(texture_row, bitmap_row, row_size);
    }

    SDL_UpdateTexture(*texture, NULL, pixels, row_size);
    SDL_free(pixels);
    SDL_free(file_content);
    return 0;
}
   
#pragma endregion
    
    
  
    

    
    
    
    

    

