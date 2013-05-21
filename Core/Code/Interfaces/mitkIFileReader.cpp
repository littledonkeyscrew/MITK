/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/


#include "mitkIFileReader.h"

mitk::IFileReader::~IFileReader()
{

}

const std::string mitk::IFileReader::PROP_EXTENSION = "org.mitk.services.FileReader.Extension";
const std::string mitk::IFileReader::PROP_DESCRIPTION = "org.mitk.services.FileReader.Description";

/**
* @brief Used to indicate that an image should be read as an binary image.
*/
const std::string mitk::IFileReader::OPTION_READ_AS_BINARY = "org.mitk.services.FileReader.Option.ReadAsBinary";
const std::string mitk::IFileReader::OPTION_READ_MULTIPLE_FILES = "org.mitk.services.FileReader.Option.ReadMultipleFiles";
