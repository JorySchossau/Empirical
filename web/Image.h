#ifndef EMP_WEB_IMAGE_H
#define EMP_WEB_IMAGE_H

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Specs for the Image widget.
//

#include "Widget.h"

namespace emp {
namespace web {

  class Image;

  class ImageInfo : public internal::WidgetInfo {
    friend Image;

  protected:

    std::string url;
    std::string alt_text;

      
    ImageInfo(const std::string & in_id="") : internal::WidgetInfo(in_id) { ; }
    ImageInfo(const ImageInfo &) = delete;               // No copies of INFO allowed
    ImageInfo & operator=(const ImageInfo &) = delete;   // No copies of INFO allowed
    virtual ~ImageInfo() { ; }

    virtual void GetHTML(std::stringstream & HTML) override {
      HTML.str("");                                           // Clear the current text.
      HTML << "<img src=\"" << url << "\""
           << " alt=\"" << alt_text << "\""
           << " id=\"" << id << "\">";
    }
      
    void UpdateURL(const std::string & in_url) { url = in_url; if (active) ReplaceHTML(); }
    void UpdateAlt(const std::string & in_alt) { alt_text = in_alt; if (active) ReplaceHTML(); }

  public:
    virtual std::string GetType() override { return "web::ButtonInfo"; }
  };


  class Image : public internal::WidgetFacet<Image> {
    friend ImageInfo;
  protected:
    // Get a properly cast version of indo.  
    ImageInfo * Info() { return (ImageInfo *) info; }
    const ImageInfo * Info() const { return (ImageInfo *) info; }
 
    Image(ImageInfo * in_info) : WidgetFacet(in_info) { ; }

  public:
    Image(const std::string & in_url, const std::string & in_id="")
      : WidgetFacet(in_id)
    {
      info = new ImageInfo(in_id);
      Info()->url = in_url;
    }
    Image(const Image & in) : WidgetFacet(in) { ; }
    Image(const internal::Widget & in) : WidgetFacet(in) { ; }
    virtual ~Image() { ; }

    using INFO_TYPE = ImageInfo;


  public:
    Image & URL(const std::string & in_url) { Info()->UpdateURL(in_url); return *this; }
    Image & Alt(const std::string & in_alt) { Info()->UpdateAlt(in_alt); return *this; }
  };

};
};

#endif