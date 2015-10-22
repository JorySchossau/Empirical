#include "../../web/web.h"

namespace UI = emp::web;

UI::Document doc("emp_base");

int r = 4;
int c = 4;
  
void IncR() {
  r++;
  UI::Table test_table = doc.Table("test");
  test_table.Rows(r);
  test_table.GetCell(r-1, 0) << r-1;
  test_table.GetCell(r-2, 1) << "Ping!";
  test_table.GetCell(0, 1) << "Ping!";
  doc.Redraw();

  std::stringstream ss;
  if (!test_table.OK(ss)) emp::Alert(ss.str());
}
  
void DecR() {
  r--;
  UI::Table test_table = doc.Table("test");
  test_table.Rows(r);
  doc.Redraw();
}
  
void IncC() {
  c++;
  UI::Table test_table = doc.Table("test");
  test_table.Cols(c);
  doc.Redraw();
}
  
void DecC() {
  c--;
  UI::Table test_table = doc.Table("test");
  test_table.Cols(c);
  doc.Redraw();
}
  
int main()
{
  doc << "<h1>This is my file!</h1>"
      << "Table size = " << r << "x" << c << "<p>"
      << "(live) size = " << UI::Live(r) << "x" << UI::Live(c) << "<p>";

  UI::Table test_table(r, c, "test");
  test_table.SetCSS("border-collapse", "collapse");
  test_table.GetCell(0,0) << "Zero";
  test_table.GetCell(1,1) << "One";
  test_table.GetCell(2,2) << "Two";
  test_table.GetCell(3,3) << "Three";
  doc << test_table;

  test_table.GetCell(0,3) << "Test1";
  test_table.GetCell(3,0) << "Test2";

  doc << "<p>";
  
  doc << UI::Button(IncR, "Inc Rows!");
  doc << UI::Button(DecR, "Dec Rows!");
  doc << UI::Button(IncC, "Inc Cols!");
  doc << UI::Button(DecC, "Dec Cols!");
}
