#ifndef EMP_UI_ELEMENT_SLATE_H
#define EMP_UI_ELEMENT_SLATE_H

///////////////////////////////////////////////////////////////////////////////////////////
//
//  Manage a section of the current web page
//

#include <map>
#include <string>

#include "emscripten.h"

#include "../tools/assert.h"
#include "../tools/alert.h"

#include "Element.h"
#include "ElementText.h"
#include "ElementWrapper.h"

namespace emp {
namespace UI {

  using ElementButton = emp::UI::ElementWrapper<emp::UI::Button>;
  using ElementImage = emp::UI::ElementWrapper<emp::UI::Image>;
  using ElementTable = emp::UI::ElementWrapper<emp::UI::Table>;

  class ElementSlate : public Element {
  protected:
    std::map<std::string, Element *> element_dict;  // By-name lookup for elements.

    // Return a text element for appending, either the current last element or build new one.
    ElementText & GetTextElement() {
      // If the final element is not text, add one.
      if (children.size() == 0 || children.back()->IsText() == false)  {
        std::string new_name = name + std::string("__") + std::to_string(children.size());
        Element * new_child = new ElementText(new_name, this);
        children.push_back(new_child);
      }
      return *((ElementText *) children.back());
    }
    
    void Register(Element * in_element) {
      // Make sure name is not already used
      emp_assert(element_dict.find(in_element->GetName()) == element_dict.end()); 

      element_dict[in_element->GetName()] = in_element;  // Save element name
      if (parent) parent->Register(in_element);          // Also register in parent, if available
    }

    // Provide a quick method for generating unique names when not otherwise specified.
    static std::string CalcNextName() {
      static int next_id = 0;
      return std::string("emp__") + std::to_string(next_id++);
      // return name + std::string("__") + std::to_string(children.size());
    }

    void UpdateHTML() {
      HTML.str("");                               // Clear the current stream.
      for (auto * element : children) {
        HTML << "<span id=\"" << element->GetName() << "\"></span>\n";
      }
    }

  
public:
    ElementSlate(const std::string & name, Element * in_parent=nullptr)
      : Element(name, in_parent) { ; }
    ~ElementSlate() { ; }
    
    bool Contains(const std::string & test_name) {
      return element_dict.find(test_name) != element_dict.end();
    }
    Element & operator[](const std::string & test_name) {
      emp_assert(Contains(test_name));
      return *(element_dict[test_name]);
    }
    ElementButton & Button(const std::string & test_name) {
      // Assert that we have the correct type, then return it.
      emp_assert(dynamic_cast<ElementButton *>( element_dict[test_name] ) != NULL);
      return dynamic_cast<ElementButton&>( operator[](test_name) );
    }
    ElementImage & Image(const std::string & test_name) {
      // Assert that we have the correct type, then return it.
      emp_assert(dynamic_cast<ElementImage *>( element_dict[test_name] ) != NULL);
      return dynamic_cast<ElementImage&>( operator[](test_name) );
    }
    ElementSlate & Slate(const std::string & test_name) {
      // Assert that we have the correct type, then return it.
      emp_assert(dynamic_cast<ElementSlate *>( element_dict[test_name] ) != NULL);
      return dynamic_cast<ElementSlate&>( operator[](test_name) );
    }
    ElementTable & Table(const std::string & test_name) {
      // Assert that we have the correct type, then return it.
      emp_assert(dynamic_cast<ElementTable *>( element_dict[test_name] ) != NULL);
      return dynamic_cast<ElementTable&>( operator[](test_name) );
    }
    ElementText & Text(const std::string & test_name) {
      // Assert that we have the correct type, then return it.
      emp_assert(dynamic_cast<ElementText *>( element_dict[test_name] ) != NULL);
      return dynamic_cast<ElementText&>( operator[](test_name) );
    }


    // Add additional children on to this element.
    Element & Append(const std::string & in_text) {
      return GetTextElement().Append(in_text);
    }

    Element & Append(const std::function<std::string()> & in_fun) {
      return GetTextElement().Append(in_fun);
    }

    // Default to passing specialty operators to parent.
    Element & Append(emp::UI::Button info) {
      // If a name was passed in, use it.  Otherwise generate a default name.
      if (info.GetTempName() == "") info.TempName( CalcNextName() );

      ElementButton * new_child = new ElementButton(info, this);
      children.push_back(new_child);
      
      return *new_child;
    }
    Element & Append(emp::UI::Image info) {
      // If a name was passed in, use it.  Otherwise generate a default name.
      // @CAO should we default name to URL??
      if (info.GetTempName() == "") info.TempName( CalcNextName() );

      ElementImage * new_child = new ElementImage(info, this);
      children.push_back(new_child);
      
      return *new_child;
    }
    Element & Append(emp::UI::Table info) {
      // If a name was passed in, use it.  Otherwise generate a default name.
      if (info.GetTempName() == "") info.TempName( CalcNextName() );

      ElementTable * new_child = new ElementTable(info, this);
      children.push_back(new_child);
      
      return *new_child;
    }


  };

};
};

#endif