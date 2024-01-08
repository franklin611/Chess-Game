// code sourced from assignment 4's provided window.cc

#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=800, int height=800);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);


  //   // Draws a string (These functions were used on our personal computers where the fonts worked)
  // void drawString(int x, int y, std::string msg, int colour, const std::string& fontName);
  // void setUpFont(const std::string &fontname);
};

#endif
