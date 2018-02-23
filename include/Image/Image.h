#pragma once

// std
#include <cstdint> // for integer types.
#include <string>
// AmazingCow Libs
#include "acow/cpp_goodies.h"
#include "acow/math_goodies.h"


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
    const std::string& GetPath    () const noexcept;
    const std::string  GetDirname () const noexcept;
    const std::string  GetBasename() const noexcept;

    const acow::math::Size& GetSize() const noexcept;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
public:
    std::string m_path;

    uint8_t          *m_pData;
    acow::math::Size  m_size;

}; // class Image
