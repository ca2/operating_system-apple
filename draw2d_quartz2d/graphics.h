#pragma once


#include "aura/graphics/draw2d/graphics.h"


namespace draw2d_quartz2d
{

   class graphics;


   class brush;
   class pen;
   class font;
   class path;


   class CLASS_DECL_DRAW2D_QUARTZ2D graphics :
      virtual public ::draw2d::graphics
   {
   public:

      
      int                           m_iSaveDC;
      bool                          m_bOwnDC;
      CGContextRef                  m_pdc;
      CGLayerRef                    m_layer;

      i32                           m_iType;
#ifdef __MM
      NSColor *                     m_nscolorFore;
      NSColor *                     m_nscolorBack;
#else
      void *                        m_pnscolorFore;
      void *                        m_pnscolorBack;
#endif

      bool                          m_bForeColor;
      bool                          m_bBackColor;
      u64                           m_uiForeColor;
      u64                           m_uiBackColor;
      bool                          m_bPrinting;
      


      graphics();
      ~graphics() override;
      
      
      void destroy() override;
      void destroy_os_data() override;


      //bool IsPrinting() override;            // true if being used for printing

      ::draw2d::pen * get_current_pen() override;
      ::draw2d::brush * get_current_brush() override;
      ::draw2d::palette * get_current_palette() override;
      ::write_text::font * get_current_font() override;
      ::draw2d::bitmap * get_current_bitmap() override;


      // for bidi and mirrored localization
      ::u32 GetLayout() override;
      ::u32 SetLayout(::u32 dwLayout) override;


      virtual double get_dpix() override;

      // Constructors
//      bool CreateDC(const ::string & lpszDriverName, const ::string & lpszDeviceName, const ::string & lpszOutput, const void * lpInitData) override;
//      bool CreateIC(const ::string & lpszDriverName, const ::string & lpszDeviceName, const ::string & lpszOutput, const void * lpInitData) override;
      void CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      void DeleteDC() override;

      // Device-Context Functions
      virtual i32 SaveDC() override;
      virtual void RestoreDC(i32 nSavedDC) override;
      i32 GetDeviceCaps(i32 nIndex) override;
      ::u32 SetBoundsRect(const ::rectangle_f64 & rectBounds, ::u32 flags) override;
      ::u32 GetBoundsRect(::rectangle_f64 * rectBounds, ::u32 flags) override;
      // xxx      bool ResetDC(const DEVMODE* lpDevMode);

      // Drawing-Tool Functions
      point_f64 GetBrushOrg() override;
      point_f64 SetBrushOrg(double x, double y) override;
      point_f64 SetBrushOrg(const ::point_f64 & point) override;
//      i32 EnumObjects(i32 nObjectType,
//                          i32 (CALLBACK* lpfn)(void *, LPARAM), LPARAM lpData) override;

//      // Type-safe selection helpers
//   public:
//      virtual ::draw2d::object* SelectStockObject(i32 nIndex) override;
//      ::draw2d::pen* SelectObject(::draw2d::pen* pPen) override;
//      ::draw2d::brush* SelectObject(::draw2d::brush* pBrush) override;
//      virtual ::write_text::font* SelectObject(::write_text::font* pFont) override;
      void set(::draw2d::bitmap* pBitmap) override;
//      i32 SelectObject(::draw2d::region* pRgn) override;       // special return for regions
//      ::draw2d::object* SelectObject(::draw2d::object* pObject);


      // ::draw2d::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

      //void SelectFont(::write_text::font * pfont) override;


      // color and color Palette Functions
//      color32_t GetNearestColor(const ::color::color & color) override;
//      ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
//      ::u32 RealizePalette() override;
//      void UpdateColors() override;

//      // Drawing-Attribute Functions
//      color32_t GetBkColor() const;
//      i32 GetBkMode() const;
//      i32 GetPolyFillMode() override;
//      i32 GetROP2() override;
//      i32 GetStretchBltMode() override;
//
//      //virtual color32_t SetBkColor(const ::color::color & color);
//      i32 SetBkMode(i32 nBkMode);
//      i32 SetPolyFillMode(i32 nPolyFillMode) override;
//      i32 SetROP2(i32 nDrawMode) override;
      void set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode) override;

      // xxx      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
      // xxx      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);

//#if (_WIN32_WINNT >= 0x0500)
//
//      color32_t GetDCBrushColor() const;
//      color32_t SetDCBrushColor(const ::color::color & color);
//
//      color32_t GetDCPenColor() const;
//      color32_t SetDCPenColor(const ::color::color & color);
//
//#endif
//
//      // Graphics mode
//      i32 SetGraphicsMode(i32 iMode) override;
//      i32 GetGraphicsMode() override;

//      // World transform
//      bool SetWorldTransform(const XFORM* pXform);
//      bool ModifyWorldTransform(const XFORM* pXform,::u32 iMode);
//      bool GetWorldTransform(XFORM* pXform) const;

      // Mapping Functions
//      virtual i32 GetMapMode() override;
      virtual point_f64 get_origin() override;
//      virtual i32 SetMapMode(i32 nMapMode) override;
//      // Viewport Origin
      virtual point_f64 set_origin(double x, double y) override;
      virtual point_f64 set_origin(const ::point_f64 & point) override;
      virtual point_f64 offset_origin(double nWidth, double nHeight) override;

      // Viewport Extent
      virtual size_f64 get_extents() override;
      virtual size_f64 set_extents(double cx, double cy) override;
      virtual size_f64 set_extents(const ::size_f64 & size) override;
      virtual size_f64 scale_extents(double xNum, double xDenom, double yNum, double yDenom) override;

      // Window Origin
      point_f64 GetWindowOrg() override;
      point_f64 SetWindowOrg(double x, double y) override;
      point_f64 SetWindowOrg(const ::point_f64 & point) override;
      point_f64 offset_window_org(double nWidth, double nHeight) override;

      // Window extent
      size_f64 GetWindowExt() override;
      virtual size_f64 set_window_ext(double cx, double cy) override;
      size_f64 set_window_ext(const ::size_f64 & size) override;
      virtual size_f64 scale_window_ext(double xNum, double xDenom, double yNum, double yDenom) override;

      // Coordinate Functions
      void DPtoLP(::point_f64 * ppoints, i32 nCount = 1) const;
      void DPtoLP(::rectangle_f64 * prectangle) override;
      void DPtoLP(::size_f64 * psize) override;
      void LPtoDP(::point_f64 * ppoints, i32 nCount = 1) const;
      void LPtoDP(::rectangle_f64 * prectangle) override;
      void LPtoDP(::size_f64 * psize) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(::size_f64 * psize) override;
      void LPtoHIMETRIC(::size_f64 * psize) override;
      void HIMETRICtoDP(::size_f64 * psize) override;
      void HIMETRICtoLP(::size_f64 * psize) override;

      // Region Functions
      void fill_region(::draw2d::region * pregion, ::draw2d::brush * pbrush) override;
      void frame_region(::draw2d::region * pregion, ::draw2d::brush * pbrush, double nWidth, double nHeight) override;
      void invert_region(::draw2d::region * pregion) override;
      void paint_region(::draw2d::region * pregion) override;

      // Clipping Functions
      i32 get_clip_box(::rectangle_f64 & rectangle) override;
      //void PtVisible(double x, double y) override;
      //void PtVisible(const ::point_f64 & point) override;
      //void RectVisible(const ::rectangle_f64 & rectangle) override;
//      virtual i32 SelectClipRgn(::draw2d::region* pRgn) override;
//      virtual i32 ExcludeClipRect(double x1, double y1, double x2, double y2) override;
//      virtual i32 ExcludeClipRect(const ::rectangle_f64 & rectangle) override;
      //i32 ExcludeUpdateRgn(::user::interaction * pWnd);
      //virtual i32 IntersectClipRect(double x1, double y1, double x2, double y2) override;
      //virtual i32 IntersectClipRect(const ::rectangle_f64 & rectangle) override;
      //virtual i32 OffsetClipRgn(double x, double y) override;
      //virtual i32 OffsetClipRgn(const ::size_f64 & size) override;
      //virtual i32 SelectClipRgn(::draw2d::region* pRgn, i32 nMode) override;
      
      
      void reset_clip() override;
      void _intersect_clip() override;
      virtual void _intersect_eo_clip();
      
      
      void intersect_clip(const ::rectangle & rectangle) override;
      void intersect_clip(const ::ellipse & ellipse) override;
      void intersect_clip(const ::polygon & polygon) override;
      
      
      void _add_clipping_shape(const ::rectangle & rectangle, ___shape < ::draw2d::region > & shape) override;
      void _add_shape(const ::rectangle & rectangle);
      void _add_clipping_shape(const ::ellipse & ellipse, ___shape < ::draw2d::region > & shape) override;
      void _add_shape(const ::ellipse & ellipse);
      void _add_clipping_shape(const ::polygon & polygon, ___shape < ::draw2d::region > & shape) override;
      void _add_shape(const ::polygon & polygon);

      
      //virtual void on_apply_clip_region() override;

      // Line-Output Functions
      virtual point_f64 current_position() override;
      //      ::point_f64 MoveTo(double x, double y);
      //    ::point_f64 MoveTo(const ::point_f64 & point);
      void line_to(const ::point_f64 & point) override;
      //  bool LineTo(const ::point_f64 & point);
//      void Arc(double x1, double y1, i32 w, i32 h, double start, double extends) override;
  //    void Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
//      void Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      void arc(double x, double y, double w, double h, angle start, angle end) override;
//      void Arc(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
      void polyline(const ::point_f64* lpPoints, count nCount) override;

      void angle_arc(double x, double y, double dRadius, angle fStartAngle, angle fSweepAngle) override;
//      void ArcTo(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      void arc_to(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
//      virtual i32 GetArcDirection() override;
//      virtual i32 SetArcDirection(i32 nArcDirection) override;

//      bool PolyDraw(const ::point_f64* lpPoints, const byte* lpTypes, i32 nCount) override;
//      bool polyline_to(const ::point_f64* lpPoints, i32 nCount);
//      bool poly_polyline(const ::point_f64* lpPoints,
//                        const ::u32* lpPolyPoints, i32 nCount);
//
//      bool poly_bezier(const ::point_f64* lpPoints, i32 nCount);
//      bool poly_bezier_to(const ::point_f64* lpPoints, i32 nCount);

      // Simple Drawing Functions
      void fill_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush* pbrush) override;
      void draw_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::pen* ppen) override;

      void rectangle(const ::rectangle_f64 & rectangle) override;
      void draw_rectangle(const ::rectangle_f64 & rectangle) override;
      void fill_rectangle(const ::rectangle_f64 & rectangle) override;

      void frame_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush* pbrush) override;
      void invert_rectangle(const ::rectangle_f64 & rectangle) override;
      
      
//      void draw_icon(double x, double y, ::draw2d::icon * picon) override;
//      void draw_icon(const ::point_f64 & point, ::draw2d::icon * picon) override;
//      void draw_icon(double x, double y, ::draw2d::icon * picon, i32 cx, i32 cy, ::u32 istepIfAniCur, HBRUSH hbrFlickerFreeDraw, ::u32 diFlags) override;
//      void DrawState(const ::point_f64 & point, const ::size_f64 & size, HBITMAP hBitmap, ::u32 nFlags,
//                             HBRUSH hBrush = nullptr) override;
//      void DrawState(const ::point_f64 & point, const ::size_f64 & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags,
//                             ::draw2d::brush* pBrush = nullptr) override;
      /*      bool DrawState(const ::point_f64 & point, const ::size_f64 & size, HICON hIcon, ::u32 nFlags,
                           HBRUSH hBrush = nullptr);
            bool DrawState(const ::point_f64 & point, const ::size_f64 & size, HICON hIcon, ::u32 nFlags,
                           ::draw2d::brush* pBrush = nullptr);*/
//      void DrawState(const ::point_f64 & point, const ::size_f64 & size, const char * lpszText, ::u32 nFlags,
//                             bool bPrefixText = true, i32 nTextLen = 0, HBRUSH hBrush = nullptr) override;
//      void DrawState(const ::point_f64 & point, const ::size_f64 & size, const char * lpszText, ::u32 nFlags,
//                             bool bPrefixText = true, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;
      //xxx      bool DrawState(const ::point_f64 & point, const ::size_f64 & size, DRAWSTATEPROC lpDrawProc,
      //xxx         LPARAM lData, ::u32 nFlags, HBRUSH hBrush = nullptr);
      //xxx      bool DrawState(const ::point_f64 & point, const ::size_f64 & size, DRAWSTATEPROC lpDrawProc,
      //xxx         LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush = nullptr);

      // Ellipse and Polygon Functions
//      void Chord(double x1, double y1, double x2, double y2, double x3, double y3,
//                         double x4, double y4) override;
//      void Chord(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
      void DrawFocusRect(const ::rectangle_f64& rectangle) override;

//      bool DrawEllipse(double x1, double y1, double x2, double y2) override;
//      bool DrawEllipse(const ::rectangle_f64 & rectangle) override;
//
//      bool FillEllipse(double x1, double y1, double x2, double y2) override;
//      bool FillEllipse(const ::rectangle_f64 & rectangle) override;

      //bool draw(double x1, double y1, double x2, double y2) override;
      void draw_ellipse(const ::rectangle_f64 & rectangle) override;

      //void FillEllipse(double x1, double y1, double x2, double y2) override;
      void fill_ellipse(const ::rectangle_f64 & rectangle) override;

//      void Pie(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
  //    void Pie(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd) override;
      void set_polygon(const POINT_F64 * lpPoints, count nCount);
      void set_polygon(const ::point_f64 * lpPoints, count nCount);
      void set_polygon(const POINT_F64 * lpPoints, count nCount, const ::POINT_F64 & pointOffset);
      void set_polygon(const ::point_f64 * lpPoints, count nCount, const ::point_f64 & pointOffset);
      void fill_polygon(const POINT_F64 * lpPoints, count nCount) override;
//      void fill_polygon(const ::point_f64* lpPoints, count nCount) override;
      void draw_polygon(const POINT_F64 * lpPoints, count nCount) override;
//      void draw_polygon(const ::point_f64 * lpPoints, count nCount) override;
      void polygon(const POINT_F64 * ppoint,count nCount) override;
      void round_rectangle(const ::rectangle_f64 & rectangle, double dRadius) override;
      
      
      void _draw_raw(const image_drawing & imagedrawing) override;

      // Bitmap Functions
//      void PatBlt(double x, double y, double dWidth, double dHeight, ::u32 dwRop) override;
//      using ::draw2d::graphics::BitBlt;
//      void BitBltRaw(double x, double y, double dWidth, double dHeight, ::draw2d::graphics * pgraphicsSrc,
//                     double xSrc, double ySrc, ::u32 dwRop) override;
//      void StretchBltRaw(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
//                                 double xSrc, double ySrc, i32 nSrcWidth, i32 nSrcHeight, ::u32 dwRop) override;
      ::color::color GetPixel(double x, double y) override;
      ::color::color GetPixel(const ::point_f64 & point) override;
      ::color::color SetPixel(double x, double y, const ::color::color & color) override;
      ::color::color SetPixel(const ::point_f64 & point, const ::color::color & color) override;
//      void FloodFill(double x, double y, const ::color::color & color) override;
//      void ExtFloodFill(double x, double y, const ::color::color & color, ::u32 nFillType) override;
//      void MaskBlt(double x, double y, double dWidth, double dHeight, ::draw2d::graphics * pgraphicsSrc,
//                   double xSrc, double ySrc, ::draw2d::bitmap& maskBitmap, double xMask, double yMask,
//                   ::u32 dwRop) override;
//      void PlgBlt(::point_f64 * lpPoint, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc,
//                  double dWidth, double dHeight, ::draw2d::bitmap& maskBitmap, double xMask, double yMask) override;
      void SetPixelV(double x, double y, const ::color::color & color) override;
      void SetPixelV(const ::point_f64 & point, const ::color::color & color) override;
//      void GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
//                        void * pMesh, WINULONG nMeshElements, ::u32 dwMode) override;
//      void TransparentBlt(double xDest, double yDest, i32 nDestWidth, i32 nDestHeight,
//                          ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, i32 nSrcWidth, i32 nSrcHeight,
//                          ::u32 clrTransparent) override;

//      void alpha_blendRaw(double xDest, double yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity) override;

      /*void alpha_blend(double xDest, double yDest, i32 nDestWidth, i32 nDestHeight,
       ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, i32 nSrcWidth, i32 nSrcHeight,
       BLENDFUNCTION blend);*/


      void _get(::draw2d::matrix & matrix) override;
      void _set(const ::draw2d::matrix & matrix) override;

      // Text Functions
      void internal_show_text(double x, double y, double w, const  string & str, CGTextDrawingMode emode, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, bool bDraw = true, CGFloat * pascent = nullptr, CGFloat * pdescent = nullptr, CGFloat * pleading = nullptr, CGFloat * pwidth = nullptr, ::draw2d::pen * ppen=nullptr, ::draw2d::brush * pbrush = nullptr, ::write_text::font * pfont = nullptr);

      void internal_show_text(::write_text::font * pfont,::draw2d::brush * pbrush,::draw2d::pen * ppen, double x, double y, double w, const string & str, CGTextDrawingMode emode, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, bool bDraw = true, CGFloat * pascent = nullptr, CGFloat * pdescent = nullptr, CGFloat * pleading = nullptr, CGFloat * pwidth = nullptr);
      
      void internal_draw_text(CGTextDrawingMode emode, double x, double y, CTLineRef line, ::draw2d
::brush * pbrush);

//      void BitBltAlphaBlend(double x, double y, double dWidth, double dHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc) override;

      void draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen) override;
      void text_out(double x, double y, const block & block) override;

//      void text_out(double x, double y, const string & str) override;
      void TextOutRaw(double x, double y, const block & block) override;
//      void text_out(double x, double y, const string & str) override;
//      void ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle,
//                              const char * lpszString, ::u32 nCount, int * lpDxWidths);
//      void ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle,
//                      const string & str, int * lpDxWidths) override;
//      virtual size_f64 TabbedTextOut(double x, double y, const char * lpszString, i32 nCount,
//                                 i32 nTabPositions, int * lpnTabStopPositions, i32 nTabOrigin);
//      size_f64 TabbedTextOut(double x, double y, const string & str,
//                         i32 nTabPositions, int * lpnTabStopPositions, i32 nTabOrigin);

      virtual i32 draw_text(const char * lpszString, i32 nCount, const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);
//      void draw_text(const string & str, const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;
      void draw_text(const string & strParam,const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

//      virtual i32 draw_text_ex(char * lpszString, i32 nCount, const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams);
//      void draw_text_ex(const string & str, const ::rectangle_f64 & rectangle, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams) override;

      size_f64 get_text_extent(const ::scoped_string & scopedstr, i32 iIndex);
      size_f64 get_text_extent(const ::scoped_string & scopedstr) override;
      //size_f64 get_text_extent(const block & block) override;
//      void get_text_extent(size_f64 & size, const char * lpszString, strsize nCount, i32 iIndex) ;
//      void get_text_extent(size_f64 & size, const char * lpszString, strsize nCount) override;
//      void get_text_extent(size_f64 & size, const string & str) override;
//      size_f64 GetOutputTextExtent(const char * lpszString, strsize nCount) override;
//      size_f64 GetOutputTextExtent(const string & str) override;
//      size_f64 GetTabbedTextExtent(const char * lpszString, strsize nCount, i32 nTabPositions, int * lpnTabStopPositions);
//      size_f64 GetTabbedTextExtent(const string & str, i32 nTabPositions, int * lpnTabStopPositions);
//      size_f64 GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, i32 nTabPositions, int * lpnTabStopPositions);
//      size_f64 GetOutputTabbedTextExtent(const string & str, i32 nTabPositions, int * lpnTabStopPositions) ;
//      void GrayString(::draw2d::brush* pBrush,
//                              void (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData,
//                              i32 nCount, double x, double y, double dWidth, double dHeight) override;
      ::u32 GetTextAlign() override;
      ::u32 SetTextAlign(::u32 nFlags) override;
//      i32 GetTextFace(i32 nCount, char * lpszFacename);
//      i32 GetTextFace(string & rString) override;
      void get_text_metrics(::write_text::text_metric * lpMetrics) override;
      void get_output_text_metrics(::write_text::text_metric * lpMetrics) override;
//      i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount) override;
//      i32 GetTextCharacterExtra() override;
//      i32 SetTextCharacterExtra(i32 nCharExtra) override;

      //xxx      ::u32 GetCharacterPlacement(const char * lpString, i32 nCount, i32 nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags) const;
      //xxx      ::u32 GetCharacterPlacement(string & str, i32 nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags) const;

//#if (_WIN32_WINNT >= 0x0500)
//
//      void GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, int * lpnFit, int * alpDx, __out_opt LPSIZE32 LPSIZE32) const;
//      void GetTextExtentPointI(LPWORD pgiIn, i32 cgi, __out_opt LPSIZE32 LPSIZE32) const;
//
//#endif



//      // Advanced Drawing
//      void DrawEdge(rectangle_f64 * prectangle, ::u32 nEdge, ::u32 nFlags);
//      void DrawFrameControl(rectangle_f64 * prectangle, ::u32 nType, ::u32 nState);

//      // Scrolling Functions
//      void ScrollDC(i32 Δx, i32 Δy, const ::rectangle_f64 & rectScroll, const ::rectangle_f64 & rectClip,
//                    ::draw2d::region* pRgnUpdate, rectangle_f64 * lpRectUpdate) override;
//
//      // font Functions
//      void GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, int * lpBuffer) override;
//      void GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, int * lpBuffer) override;
//      ::u32 SetMapperFlags(::u32 dwFlag) override;
//      size_f64 GetAspectRatioFilter() override;
//
//      //xxx      void GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC lpabc) const;
//      ::u32 GetFontData(::u32 dwTable, ::u32 dwOffset, void * lpData, ::u32 cbData) override;
//      //xxx      i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair) const;
//      //xxx      ::u32 GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRIC lpotm) const;
//      //xxx      ::u32 GetGlyphOutline(::u32 nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm,
//      //xxx    ::u32 cbBuffer, void * lpBuffer, const MAT2* lpmat2) const;
//
//      //xxx      void GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar,
//      //xxx         LPABCFLOAT lpABCF) const;
//      void GetCharWidth(::u32 nFirstChar, ::u32 nLastChar,
//                        float* lpFloatBuffer) override;
//
//      ::u32 GetFontLanguageInfo() override;
//
//#if (_WIN32_WINNT >= 0x0500)
//
//      void GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc) const;
//      void GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, int * lpBuffer) const;
//
//#endif
//
//      // Printer/Device Escape Functions
//      virtual i32 Escape(i32 nEscape, i32 nCount, const char * lpszInData, void * lpOutData) override;
//      i32 Escape(i32 nEscape, i32 nInputSize, const char * lpszInputData, i32 nOutputSize, char * lpszOutputData) override;
//      i32 DrawEscape(i32 nEscape, i32 nInputSize, const char * lpszInputData) override;

      // Escape helpers
      //i32 StartDoc(const ::string & lpszDocName) override;  // old Win3.0 version
      //xxx      i32 StartDoc(LPDOCINFO lpDocInfo);
      i32 StartPage() override;
      i32 EndPage() override;
      //i32 SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32)) override;
      i32 AbortDoc() override;
      i32 EndDoc() override;

      // MetaFile Functions
      //xxx      void PlayMetaFile(HMETAFILE hMF);
//      void PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rectangle_f64 & rectBounds);
//      void AddMetaFileComment(::u32 nDataSize, const byte* pCommentData) override;
      // can be used for enhanced metafiles only

      // Path Functions
      void abort_path() override;
      void begin_path() override;
      void close_figure() override;
      void end_path() override;
      void fill_path() override;
      void flatten_path() override;
      void stroke_and_fill_path() override;
      void stroke_path() override;
      void widen_path() override;
      using ::draw2d::graphics::draw;
      void draw(::draw2d::path * ppath) override;
      void fill(::draw2d::path * ppath) override;

      void draw(::draw2d::path * ppath, ::draw2d::pen * ppen) override;
      void fill(::draw2d::path * ppath, ::draw2d::brush * pbrush) override;

      void draw_inline_path(::draw2d::path * ppath, ::draw2d::pen * ppen);
      void fill_inline_path(::draw2d::path * ppath, ::draw2d::brush * pbrush);


      float GetMiterLimit() override;
      void SetMiterLimit(float fMiterLimit) override;
      //i32 GetPath(::point_f64 * lpPoints, LPBYTE lpTypes, i32 nCount) ;
      //void SelectClipPath(i32 nMode) override;

      // Misc Helper Functions
//      static ::draw2d::brush* PASCAL GetHalftoneBrush(::base::application * papp);
//      void DrawDragRect(const ::rectangle_f64 & rectangle, const ::size_f64 & size,
//                        const ::rectangle_f64 & rectLast, const ::size_f64 & sizeLast,
//                        ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;
      void fill_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color) override;
//      void draw_3drect(const ::rectangle_f64 & rectangle, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder = e_border_all) override;

      //virtual void assert_ok() const override;
//      virtual void dump(dump_context & dumpcontext) const override;

      void set_alpha_mode(::draw2d::enum_alpha_mode ealphamode) override;

      void set_text_rendering_hint(::write_text::enum_rendering etextrenderinghint) override;

      //virtual void * get_os_data() const override;
      //      virtual HDC get_handle() const;
      //    virtual HDC get_handle1() const;
      //  virtual HDC get_handle2() const;

      void attach(void * pdata) override;
      virtual void * detach() override;


      //xxx      virtual Gdiplus::FillMode gdiplus_get_fill_mode();

      void blur(bool bExpand, double dRadius, const ::rectangle_f64 & rectangle) override;


      // platform-specific or platform-internals
      void _clip(::draw2d::region * pregion, bool bEO = false);
      void _add_path(::draw2d::region * pregion);
      void _set(::draw2d::brush * pbrush);
      void _set_pen(::draw2d::brush * pbrush, double dWidth);
      void _set(::draw2d::pen * ppen);
//      //void set(const ::write_text::font * pfont);
//      void _set(::draw2d::path * ppath);
//      void _set(::draw2d::path::matter * pmatter);
//      void _set(::draw2d::path::arc * parc);
//      //void set(const ::draw2d::path::move & move);
//      void _set(::draw2d::path::line * pline);
      void _fill_inline(::draw2d::path * ppath, ::draw2d::brush * pbrush);
      void _draw_inline(::draw2d::path * ppath, ::draw2d::pen * ppen);
      void _fill_inline(___shape < ::draw2d::path > * pshape, ::draw2d::brush * pbrush);
      void _draw_inline(___shape < ::draw2d::path > * pshape, ::draw2d::pen * ppen);
      void _set(::write_text::text_out & textout);
      void _fill_inline(::write_text::text_out & textout, ::draw2d::brush * pbrush);
      void _draw_inline(::write_text::text_out & textout, ::draw2d::pen * ppen);
      void _set(::write_text::draw_text & drawtext);
      void _fill_inline(::write_text::draw_text & drawtext, ::draw2d::brush * pbrush);
      void _draw_inline(::write_text::draw_text & drawtext, ::draw2d::pen * ppen);
      void _fill_and_draw(::draw2d::brush * pbrush, ::draw2d::pen * ppen);
      void _fill(::draw2d::brush * pbrush);
      void _fill(::draw2d::brush * pbrush, bool bClip);
      void _draw(::draw2d::brush * pbrush);
      void _draw(::draw2d::pen * ppen);
      void _fill_and_draw();
      void _fill();
      void _draw();


      void internal_set_fill_color(const ::color::color & color);


//      virtual void enum_fonts(::write_text::font_enum_item_array & itema) override;
//
      
      void clear_current_point() override;
      

   };


} // namespace draw2d_quartz2d





