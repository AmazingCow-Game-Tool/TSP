#pragma once

// std
#include <string>
// AmazingCow Libs
#include "acow/math_goodies.h"


class Image
{
    //------------------------------------------------------------------------//
    // Static Methods                                                         //
    //------------------------------------------------------------------------//
public:
    static Image LoadFromFile(const std::string &filePath);


    //------------------------------------------------------------------------//
    // Public Methods                                                         //
    //------------------------------------------------------------------------//
public:
    const std::string& GetPath    () const noexcept;
    const std::string  GetBasename() const noexcept;
    const std::string  GetFilename() const noexcept;

    const acow::math::Size& GetSize() const noexcept;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
public:
    std::string      m_path;
    acow::math::Size m_size;

}; // class Image
