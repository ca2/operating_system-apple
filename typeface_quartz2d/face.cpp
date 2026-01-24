#include "framework.h"
#include "face.h"
#include "aura/graphics/write_text/text_metric.h"


namespace typeface_quartz2d
{

face::face()
{
   m_bFace = false;
   m_font = nullptr;
}

face::~face()
{
   if (m_font)
   {
      CFRelease(m_font);
      m_font = nullptr;
   }
}

void face::initialize(::particle * pparticle)
{
   ::typeface::face::initialize(pparticle);
}

void face::create_character(
   ::typeface::character& ch,
   const ::scoped_string& scopedstr)
{
   _synchronous_lock lock(this->synchronization());

   if (!m_bFace)
   {
      CFStringRef cfName =
         CFStringCreateWithCString(
            nullptr,
            m_strFontName.c_str(),
            kCFStringEncodingUTF8);

      if (!cfName)
         return;

      CTFontDescriptorRef desc =
         CTFontDescriptorCreateWithNameAndSize(
            cfName,
            m_iPixelSize);

      CFRelease(cfName);

      if (!desc)
         return;

      m_font =
         CTFontCreateWithFontDescriptor(
            desc,
            m_iPixelSize,
            nullptr);

      CFRelease(desc);

      if (!m_font)
         return;

      m_bFace = true;

      if (m_dCapHeight < 0)
      {
         m_dCapHeight = CTFontGetCapHeight(m_font);
      }
   }

   if (scopedstr.is_empty())
      return;

   // Unicode → UniChar
   CFStringRef cf =
      CFStringCreateWithCString(
         nullptr,
         scopedstr.c_str(),
         kCFStringEncodingUTF8);

   UniChar uc;
   CFStringGetCharacters(cf, CFRangeMake(0, 1), &uc);
   CFRelease(cf);

   CGGlyph glyph;
   if (!CTFontGetGlyphsForCharacters(m_font, &uc, &glyph, 1))
      return;

   CGRect bounds =
      CTFontGetBoundingRectsForGlyphs(
         m_font,
         kCTFontOrientationDefault,
         &glyph,
         nullptr,
         1);

   CGSize advance;
   CTFontGetAdvancesForGlyphs(
      m_font,
      kCTFontOrientationDefault,
      &glyph,
      &advance,
      1);
   //auto fH = bounds.size.height;
   auto width  = (int)ceil(2.0f + bounds.origin.x +bounds.size.width);
   int height = (int)ceil(bounds.size.height);
   if (width <= 0 || height <= 0)
      return;
   int h5 = height + 3;

   auto yorigin =bounds.origin.y -1.0f;
   ch.Bearing = {
      (int)floor(bounds.origin.x),
      //(int)ceil(yorigin+ bounds.size.height)
      (int)ceil(yorigin+ height)
   };
   //float yRoundingFix =((float)ch.Bearing.y) - (yorigin + //bounds.size.height);
   float yRoundingFix =((float)ch.Bearing.y) - (yorigin + bounds.size.height);
   //yRoundingFix =yRoundingFix;

   ch.Size = { width, h5 };

   ch.Advance = (unsigned int)ceil(advance.width);
   //ch.aHeight2 = m_dCapHeight - ch.Bearing.y;
   ch.aHeight2 = ceil(m_dCapHeight-ceil(bounds.size.height + yorigin));


   ::memory memory;
   memory.set_size(width * h5 * 4);
   memset(memory.data(), 0, memory.size());

   CGColorSpaceRef cs = CGColorSpaceCreateDeviceRGB();

   CGContextRef ctx =
      CGBitmapContextCreate(
         memory.data(),
         width,
         h5,
         8,
         width * 4,
         cs,
         kCGImageAlphaPremultipliedLast);

   CGColorSpaceRelease(cs);

   CGContextSetRGBFillColor(ctx, 1, 1, 1, 1);
   CGContextSetTextMatrix(ctx, CGAffineTransformIdentity);

   auto y= yorigin;
   // Flip Y (Quartz is upside down vs bitmap)
   //CGContextTranslateCTM(ctx, -bounds.origin.x,
   CGContextTranslateCTM(ctx, -bounds.origin.x + 2.0f,
                         //height + y);
                          //m_dCapHeight*1.0f - fH - y);
                         -y - 1.0f + yRoundingFix);
                         //-y +yRoundingFix);
   ::string str(scopedstr);
   informationf("Character %s y %f boundssizeheight %f (%f)", str.m_begin, y, bounds.size.height, m_dCapHeight);

   CGPoint pos = CGPointMake(0, 0);
   CTFontDrawGlyphs(m_font, &glyph, &pos, 1, ctx);

   CGContextRelease(ctx);

   create_texture(ch, memory.data());

}

void face::get_text_metric(::write_text::text_metric* p)
{
   if (!p || !m_font)
      throw ::exception(error_null_pointer);

   p->m_dAscent  = CTFontGetAscent(m_font);
   p->m_dDescent = CTFontGetDescent(m_font);
   p->m_dInternalLeading = 0.0f;
   p->m_dExternalLeading = CTFontGetLeading(m_font);

   p->m_dHeight =
      p->m_dAscent +
      p->m_dDescent +
      p->m_dExternalLeading;

   m_dCapHeight =
      CTFontGetCapHeight(m_font);

}

} // namespace typeface_quartz2d
