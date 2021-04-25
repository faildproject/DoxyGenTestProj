/**
 * @file Utils.cpp
 * @author Philipp Heise (philipp.heise.2012@gmail.com)
 * @brief Contains some usefull Functions to have Fun
 * @version 0.1
 * @date 2021-04-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <Utils.h>
/**
 * @brief Prints "Hello Chat" a few Times
 * 
 * @param t_howmany How often print "Hello Chat"
 * @param t_stream Where to print
 * @note Example-Call
 * @code .cpp
 * helloWorldFkt(Serial, 12);
 * @endcode 
 */
void helloWorldFkt(Stream& t_stream, int t_howmany){
  for (int i=0; i<t_howmany;i++){
    t_stream.println("Hello Chat");
  }
}