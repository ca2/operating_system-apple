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
//      ::u32 GetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries,
//                             LPPALETTEENTRY lpPaletteColors) const;
//      ::u32 SetPaletteEntries(::u32 nStartIndex, ::u32 nNumEntries,
//                             LPPALETTEENTRY lpPaletteColors);

      // Operations
//      void AnimatePalette(::u32 nStartIndex, ::u32 nNumEntries,
//                          LPPALETTEENTRY lpPaletteColors);
      ::u32 GetNearestPaletteIndex(const ::color::color & color) const override;
      //      bool ResizePalette(::u32 nNumEntries);

      // Implementation
   };


} // namespace draw2d_quartz2d




