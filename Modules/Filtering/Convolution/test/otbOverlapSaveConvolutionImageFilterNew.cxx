/*
 * Copyright (C) 2005-2017 Centre National d'Etudes Spatiales (CNES)
 *
 * This file is part of Orfeo Toolbox
 *
 *     https://www.orfeo-toolbox.org/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



#include "otbImage.h"
#include "otbOverlapSaveConvolutionImageFilter.h"

int otbOverlapSaveConvolutionImageFilterNew(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{
  typedef double InputPixelType;
  typedef double OutputPixelType;
  const unsigned int Dimension = 2;

  typedef otb::Image<InputPixelType,  Dimension>                                  InputImageType;
  typedef otb::Image<OutputPixelType, Dimension>                                  OutputImageType;
  typedef otb::OverlapSaveConvolutionImageFilter<InputImageType, OutputImageType> FilterType;

  FilterType::Pointer conv = FilterType::New();

  std::cout << conv << std::endl;

  return EXIT_SUCCESS;
}
