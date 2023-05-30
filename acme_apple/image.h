//
//  image.hpp
//  acme_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 01/06/22.
//
#pragma once


#include <CoreGraphics/CoreGraphics.h>
#include <CoreImage/CoreImage.h>


void * cg_image_get_image_data(int & width, int & height, int & iScan, CGImageRef image);



