#pragma once


#include "object.h"
#include "aura/graphics/draw2d/palette.h"


namespace draw2d_quartz2d
{


   class CLASS_DECL_DRAW2D_QUARTZ2D palette :
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::palette
   {
   public:


      palette();
      ~palette() override;


      //      bool CreatePalette(LPLOGPALETTE lpLogPalette);
      //      bool CreateHalftonePalette(::image::image * pimage);

      // Attributes
//      operator HPALETTE() const;
      int GetEntryCount() override;
//      unsigned int GetPaletteEntries(unsigned int nStartIndex, unsigned int nNumEntries,
//                             LPPALETTEENTRY lpPaletteColors) const;
//      unsigned int SetPaletteEntries(unsigned int nStartIndex, unsigned int nNumEntries,
//                             LPPALETTEENTRY lpPaletteColors);

      // Operations
//      void AnimatePalette(unsigned int nStartIndex, unsigned int nNumEntries,
//                          LPPALETTEENTRY lpPaletteColors);
      unsigned int GetNearestPaletteIndex(const ::color::color & color) const override;
      //      bool ResizePalette(unsigned int nNumEntries);

      // Implementation
   };


} // namespace draw2d_quartz2d




