add_library(candriver candriver.c candriver.h)



link_directories(
  lib
)


target_link_libraries(candriver
  usbcan  #if use usbcan ii
  #usbcanfd
)