#pragma once

// std
#include <cstdint> // for integer types.
#include <string>
// AmazingCow Libs
#include "acow/cpp_goodies.h"
#include "acow/math_goodies.h"
#include "acow/sdl_goodies.h"
#include "CoreFS/CoreFS.h"

namespace TSP { namespace Core {

class Image
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    ACOW_SHARED_PTR_OF(Image);


    //------------------------------------------------------------------------//
    // Static Methods                                                         //
    //------------------------------------------------------------------------//
public:
    static Image::SPtr LoadFromFile(const std::string &filePath);


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    ACOW_DISALLOW_COPY_CTOR_AND_COPY_ASSIGN(Image);

     Image() = default;
    ~Image();



    //------------------------------------------------------------------------//
    // Public Methods                                                         //
    //------------------------------------------------------------------------//
public:
    inline const std::string& GetPath    () const noexcept { return m_path; }
    inline const std::string  GetDirname () const noexcept { return CoreFS::Dirname(m_path);  }
    inline const std::string  GetBasename() const noexcept { return CoreFS::Basename(m_path); }

    inline const acow::math::Size& GetSize() const noexcept { return m_size; }

    inline SDL_Texture* GetTexture() const noexcept { return m_pTexture; }


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
public:
    std::string m_path;

    SDL_Texture      *m_pTexture;
    acow::math::Size  m_size;

}; // class Image

} // namespace Core
} // namespace TSP