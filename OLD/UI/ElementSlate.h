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

#include "Animate.h"
#include "Element.h"
#include "ElementTable.h"
#include "ElementText.h"
#include "ElementWrapper.h"

namespace emp {
namespace UI {

  // Elements that do not override Append() can be generated on the fly from their widgets.
  using ElementButton = emp::UI::ElementWrapper<emp::UI::Button>;
  using ElementCanvas = emp::UI::ElementWrapper<emp::UI::Canvas>;
  using ElementImage = emp::UI::ElementWrapper<emp::UI::Image>;
  using ElementSelector = emp::UI::ElementWrapper<emp::UI::Selector>;

  class ElementSlate : public Element, public Slate {
  protected:
    std::map<std::string, Element *> element_dict;  // By-name lookup for elements.

    ElementSlate(const ElementSlate & src, Element * parent, const std::string & ext)
      : Element(src, parent, ext), UI::Slate(src)
    {
      for (auto * e : children) element_dict[e->GetName()] = e;
    }

    // Return a text element for appending.  Use the last element unless there are no elements,
    // the last element is not text, or it is not appendable (instead, build a new one).
    ElementText & GetTextElement() {
      // If the final element is not text, add one.
      if (children.size() == 0
          || children.back()->IsText() == false
          || children.back()->AppendOK() == false)  {
        Element * new_child = new ElementText(UI::Text(), this);
        children.push_back(new_child);
      }
      return *((ElementText *) children.back());
    }
    
    void Register(Element * in_element) override {
      // Make sure name is not already used
      if (element_dict.find(in_element->GetName()) != element_dict.end()) {
        emp::Alert(in_element->GetType(), " called ", in_element->GetName());
      }
      emp_assert(element_dict.find(in_element->GetName()) == element_dict.end()); 

      element_dict[in_element->GetName()] = in_element;  // Save element name
      if (parent) parent->Register(in_element);          // Also register in parent, if available
    }

    void UpdateHTML() override {
      HTML.str("");                               // Clear the current stream.
      for (auto * element : children) {
        const std::string & tag = element->GetWrapperTag();
        HTML << "<" << tag << " id=\"" << element->GetName() << "\"></" << tag << ">\n";
      }
    }
    void UpdateCSS() override {
      TriggerCSS();
    }
    
    // Add additional children on to this element.
    Element & Append(const std::string & in_text) override {
      return GetTextElement().Append(in_text);
    }

    Element & Append(const std::function<std::string()> & in_fun) override {
      return GetTextElement().Append(in_fun);
    }

    // Default to passing specialty operators to parent.
    Element & Append(emp::UI::Button info) override {
      ElementButton * new_child = new ElementButton(info, this);
      children.push_back(new_child);
      return *new_child;
    }
    Element & Append(emp::UI::Canvas info) override {
      ElementCanvas * new_child = new ElementCanvas(info, this);
      children.push_back(new_child);
      return *new_child;
    }
    Element & Append(emp::UI::Image info) override {
      ElementImage * new_child = new ElementImage(info, this);
      children.push_back(new_child);
      return *new_child;
    }
    Element & Append(emp::UI::Selector info) override {
      ElementSelector * new_child = new ElementSelector(info, this);
      children.push_back(new_child);
      return *new_child;
    }
    Element & Append(emp::UI::Slate info) override {
      ElementSlate * new_child = new ElementSlate(info, this);
      children.push_back(new_child);
      return *new_child;
    }
    Element & Append(emp::UI::Table info) override {
      ElementTable * new_child = new ElementTable(info, this);
      children.push_back(new_child);
      return *new_child;
    }
    Element & Append(emp::UI::Text info) override {
      ElementText * new_child = new ElementText(info, this);
      children.push_back(new_child);
      return *new_child;
    }

    // BuildElement allows any element to build another as long as an ancestor knows how.
    Element * BuildElement(emp::UI::Button info, Element * fwd_parent) override {
      return new ElementButton(info, fwd_parent);
    }
    Element * BuildElement(emp::UI::Canvas info, Element * fwd_parent) override {
      return new ElementCanvas(info, fwd_parent);
    }
    Element * BuildElement(emp::UI::Image info, Element * fwd_parent) override {
      return new ElementImage(info, fwd_parent);
    }
    Element * BuildElement(emp::UI::Selector info, Element * fwd_parent) override {
      return new ElementSelector(info, fwd_parent);
    }
    Element * BuildElement(emp::UI::Table info, Element * fwd_parent) override {
      return new ElementTable(info, fwd_parent);
    }
    Element * BuildElement(emp::UI::Text info, Element * fwd_parent) override {
      return new ElementText(info, fwd_parent);
    }
    Element * BuildElement(emp::UI::Slate info, Element * fwd_parent) override {
      return new ElementSlate(info, fwd_parent);
    }
      

public:
    ElementSlate(const Slate & in_slate, Element * in_parent=nullptr)
      : Element(in_slate.GetDivID(), in_parent), emp::UI::Slate(in_slate) { ; }
    ElementSlate(const std::string & in_name, Element * in_parent=nullptr)
      : Element(in_name, in_parent), emp::UI::Slate(in_name) { ; }
    ~ElementSlate() { ; }
    
    virtual Element * Clone(Element * parent, const std::string & ext) const override {
      return new ElementSlate(*this, parent, ext);
    };

    virtual bool IsSlate() const override { return true; }
    virtual std::string GetWrapperTag() const override { return "div"; }

    bool Contains(const std::string & test_name) {
      return element_dict.find(test_name) != element_dict.end();
    }
    Element & operator[](const std::string & test_name) {
      emp_assert(Contains(test_name));
      return *(element_dict[test_name]);
    }

    // Methods to look up previously created elements, by type.

    ElementButton & Button(const std::string & test_name) {
      // Assert that we have the correct type, then return it.
      emp_assert(dynamic_cast<ElementButton *>( element_dict[test_name] ) != NULL);
      return dynamic_cast<ElementButton&>( operator[](test_name) );
    }
    ElementCanvas & Canvas(const std::string & test_name) {
      // Assert that we have the correct type, then return it.
      emp_assert(dynamic_cast<ElementCanvas *>( element_dict[test_name] ) != NULL);
      return dynamic_cast<ElementCanvas&>( operator[](test_name) );
    }
    ElementImage & Image(const std::string & test_name) {
      // Assert that we have the correct type, then return it.
      emp_assert(dynamic_cast<ElementImage *>( element_dict[test_name] ) != NULL);
      return dynamic_cast<ElementImage&>( operator[](test_name) );
    }
    ElementSelector & Selector(const std::string & test_name) {
      // Assert that we have the correct type, then return it.
      emp_assert(dynamic_cast<ElementSelector *>( element_dict[test_name] ) != NULL);
      return dynamic_cast<ElementSelector&>( operator[](test_name) );
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


    // Add a an element to this slate that was created elsewhere.
    Element & AddChild(Element * child) {
      emp_assert(child != nullptr);
      child->SetParent(this);
      children.push_back(child);
      return *child;
    }


    // Build a new element of the specified type in this slate.
    // Add additional children on to this element.

    ElementButton & Add(UI::Button info) {
      ElementButton * new_child = new ElementButton(info, this);
      children.push_back(new_child);
      return *new_child;
    }
    ElementCanvas & Add(UI::Canvas info) {
      ElementCanvas * new_child = new ElementCanvas(info, this);
      children.push_back(new_child);
      return *new_child;
    }
    ElementImage & Add(UI::Image info) {
      ElementImage * new_child = new ElementImage(info, this);
      children.push_back(new_child);
      return *new_child;
    }
    ElementSelector & Add(UI::Selector info) {
      ElementSelector * new_child = new ElementSelector(info, this);
      children.push_back(new_child);
      return *new_child;
    }
    ElementSlate & Add(UI::Slate info) {
      ElementSlate * new_child = new ElementSlate(info, this);
      children.push_back(new_child);
      return *new_child;
    }
    ElementTable & Add(UI::Table info) {
      ElementTable * new_child = new ElementTable(info, this);
      children.push_back(new_child);
      return *new_child;
    }
    ElementText & Add(UI::Text info) {
      ElementText * new_child = new ElementText(info, this);
      children.push_back(new_child);
      return *new_child;
    }

    // Shortcut adders where parameters don't have to be widgets
    template <class... T> ElementButton& AddButton(T... args){return Add(UI::Button(args...));}
    template <class... T> ElementCanvas& AddCanvas(T... args){return Add(UI::Canvas(args...));}
    template <class... T> ElementImage&  AddImage(T... args) {return Add(UI::Image(args...));}
    template <class... T> ElementSelector&AddSelector(T... args){return Add(UI::Selector(args...));}
    template <class... T> ElementSlate&  AddSlate(T... args) {return Add(UI::Slate(args...));}
    template <class... T> ElementTable&  AddTable(T... args) {return Add(UI::Table(args...));}
    template <class... T> ElementText&   AddText(T... args)  {return Add(UI::Text(args...));}

    // Other helpful adders...
    ElementButton & AddAnimToggle(UI::Animate & anim,
                                  const std::string & play_label="Play",
                                  const std::string & pause_label="Pause",
                                  const std::string & button_id
                                  =emp::to_string("emp__", internal::NextWidgetID())) {
      UI::Button toggle_but = UI::Button([&anim, play_label, pause_label, button_id, this](){
          anim.ToggleActive();                           // Toggle state of animation.
          auto & but = Button(button_id);                // Lookup this button...
          if (anim.GetActive()) but.Label(pause_label);  // Setup proper label on button.
          else but.Label(play_label);
          but.Update();                                  // Redraw the button.
        }, play_label, button_id).Size(50,30);  
      return Add(toggle_but);
    }



    virtual std::string GetType() override {
      return "ElementSlate";
    }

    virtual bool OK(std::stringstream & ss, bool verbose=false, const std::string & prefix="") override {
      bool ok = true;

      if (verbose) {
        ss << prefix << "Scanning: emp::UI::ElementSlate with name = '" << name << "'" << std::endl;
      }

      Element::OK(ss, verbose, prefix);  // Check base class; same obj, don't change prefix

      // @CAO Make sure the element_dict is okay?

      return ok;
    }

  };

  using Document = emp::UI::ElementSlate;
};
};

#endif
