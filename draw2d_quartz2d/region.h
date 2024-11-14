#pragma once


#include "object.h"
#include "aura/graphics/draw2d/region.h"


namespace draw2d_quartz2d
{


   class region :
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::region
   {
   public:


      CGMutablePathRef        m_path;

      // xxx     Gdiplus::Region *       m_pregion;

      //static region * PASCAL from_handle(::base::application * papp, HRGN hRgn);
      //operator HRGN() const;

      region();
      ~region() override;


      //virtual void * get_os_data() const;


      /*bool CreateRectRgn(int x1, int y1, int x2, int y2);
       bool CreateRectRgnIndirect(const ::int_rectangle & rectangle);
       bool CreateEllipticRgn(int x1, int y1, int x2, int y2);
       bool CreateEllipticRgnIndirect(const ::int_rectangle & rectangle);
       bool CreatePolygonRgn(POINT_I32 * lpPoints, int nCount, int nMode);
       bool CreatePolyPolygonRgn(POINT_I32 * lpPoints, LPINT lpPolyCounts,
       int nCount, int nPolyFillMode);
       bool CreateRoundRectRgn(int x1, int y1, int x2, int y2, int x3, int y3);
       bool CreateFromPath(::image::image * pimage);
       bool CreateFromData(const XFORM* lpXForm, int nCount,
       const RGNDATA* pRgnData);*/

      // Operations
      //void SetRectRgn(int x1, int y1, int x2, int y2);
      //void SetRectRgn(const ::int_rectangle & rectangle);
      //int CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, int nCombineMode);
      //int CopyRgn(const ::draw2d::region* pRgnSrc);
      //bool EqualRgn(const ::draw2d::region* pRgn) const;
      //int OffsetRgn(int x, int y);
      //int OffsetRgn(const ::int_point & point);
      //int GetRgnBox(RECTANGLE_I32 * prectangle) const;
      //bool PtInRegion(int x, int y) const;
      //bool PtInRegion(const ::int_point & point) const;
      //bool RectInRegion(const ::int_rectangle & rectangle) const;
      // xxx      int GetRegionData(LPRGNDATA lpRgnData, int nCount) const;

//      bool get(cairo_t * pdc);
      //    bool get_rect(cairo_t * pdc);
      //  bool get_oval(cairo_t * pdc);
      //bool get_polygon(cairo_t * pdc);
      //  bool get_poly_polygon(cairo_t * pdc);
      //bool get_combine(cairo_t * pdc);

      void destroy() override;
      void destroy_os_data() override;

      void create(::draw2d::graphics * pgraphics, char iCreate) override;

      virtual void * detach();
      

   };


} // namespace draw2d_quartz2d



